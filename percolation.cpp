#include "percolation.h"

#include "percolationmanager.h"


/*  if N == 5
 *      * -----> 0th component
 *  * * * * *    \
 *  * * * * *     |
 *  * * * * *     |-> 25 components
 *  * * * * *     |
 *  * * * * *    /
 *  |   * -----> 26th component (N * N + 1)
 *  |  Total = 5 * 5 + 2 = 27 Component
 *  `-> N * (N - 1) + 1
 */

namespace {
Percolation::UF::size_type indexForPosition(Percolation::UF::size_type i, Percolation::UF::size_type j, Percolation::UF::size_type N)
{
    Percolation::UF::size_type index = (j - 1) * N;
    return index += i;
}

struct Adjacents {
    Adjacents(Percolation::UF::size_type i, Percolation::UF::size_type j, Percolation::UF::size_type N);
    Percolation::UF::size_type top;
    Percolation::UF::size_type right;
    Percolation::UF::size_type bottom;
    Percolation::UF::size_type left;
    Percolation::UF::size_type self;
};
}

Percolation::Percolation(QObject *parent)
    : QObject{parent},
      m_uf{},
      m_openSites{},
      m_N{},
      m_isPercolates{},
      m_virtualTop{},
      m_virtualBottom{}
{
    auto manager = PercolationManager::instance();
    if (manager && manager->isActive())
    {
        auto gridSize = static_cast<UF::size_type>(manager->gridSize());

        initPercolation(gridSize);
        m_N = gridSize;

        auto openings = manager->openings();
        for (const auto& e : openings)
        {
            openComponent(e.first, e.second);
        }
    }
}

int Percolation::gridSize() const
{
    return static_cast<int>(m_N);
}

void Percolation::setGridSize(int gridSize)
{
    if (gridSize < 0 && m_N == static_cast<UF::size_type>(gridSize))
        return;

    clearPercolation();
    initPercolation(static_cast<UF::size_type>(gridSize));

    m_N = static_cast<UF::size_type>(gridSize);
    emit gridSizeChanged();
}

bool Percolation::isPercolates() const
{
    return m_isPercolates;
}

void Percolation::openComponent(int i, int j)
{
    Adjacents adj{static_cast<UF::size_type>(i), static_cast<UF::size_type>(j), m_N};

    if (m_openSites[adj.self])
        return;

    if (adj.top != adj.self && m_openSites[adj.top] && !m_uf->connected(adj.top, adj.self))
        m_uf->make_union(adj.top, adj.self);

    if (adj.right != adj.self && m_openSites[adj.right] && !m_uf->connected(adj.right, adj.self))
        m_uf->make_union(adj.right, adj.self);

    if (adj.bottom != adj.self && m_openSites[adj.bottom] && !m_uf->connected(adj.bottom, adj.self))
        m_uf->make_union(adj.bottom, adj.self);

    if (adj.left != adj.self && m_openSites[adj.left] && !m_uf->connected(adj.left, adj.self))
        m_uf->make_union(adj.left, adj.self);

    m_openSites[adj.self] = true;
    emit siteOpened(i, j);

    checkPercolates();
}

bool Percolation::isComponentPercolates(int i, int j) const
{
    const Index idx(i, j, static_cast<int>(m_N));
    if (m_openSites[static_cast<UF::size_type>(idx.idx)]
        && m_uf->connected(static_cast<UF::size_type>(idx.idx), m_virtualTop)
        && m_uf->connected(static_cast<UF::size_type>(idx.idx), m_virtualBottom))
        /* FIXME first row and last row components pretend as they are percolated component
         * because of they are connected to related virtual componenent and
         */
        return true;
    return false;
}

bool Percolation::isComponentOpen(int i, int j) const
{
    return m_openSites[indexForPosition(static_cast<UF::size_type>(i), static_cast<UF::size_type>(j), m_N)];
}

bool Percolation::isComponentFull(int i, int j) const
{
    return !isComponentOpen(i, j);
}

void Percolation::resetPercolation()
{
    clearPercolation();
    initPercolation(m_N);

    m_isPercolates = false;
    emit isPercolatesChanged();

    emit percolationReseted();
}

void Percolation::clearPercolation()
{
    m_uf.reset(nullptr);
    m_openSites.clear();
}

void Percolation::initPercolation(UF::size_type N)
{
    Q_ASSERT_X(!m_uf && m_openSites.empty(), "Percolation::initPercolation",
               "The member variables must have been reset before calling this function!!");

    allocateUF(N);
    m_openSites.assign(N * N + 2, false);

    constructVirtualComponents(N);
}

void Percolation::allocateUF(UF::size_type N)
{
    m_uf = std::make_unique<UF>(N * N + 2);
}

void Percolation::constructVirtualComponents(UF::size_type N)
{
    m_virtualTop = 0;
    std::pair<UF::size_type, UF::size_type> firstRow{1, N + 1};
    for (UF::size_type i = firstRow.first; i < firstRow.second; ++i)
        m_uf->make_union(m_virtualTop, i);
    m_openSites[m_virtualTop] = true;

    m_virtualBottom = N * N + 1;
    std::pair<UF::size_type, UF::size_type> lastRow{N * (N - 1) + 1, N * N + 1};
    for (UF::size_type i = lastRow.first; i < lastRow.second; ++i)
        m_uf->make_union(m_virtualBottom, i);
    m_openSites[m_virtualBottom] = true;
}

void Percolation::checkPercolates()
{
    if (!m_isPercolates && m_uf->connected(m_virtualBottom, m_virtualTop)) {
        m_isPercolates = true;
        emit percolated();
        emit isPercolatesChanged();
    }
}

Adjacents::Adjacents(Percolation::UF::size_type i, Percolation::UF::size_type j, Percolation::UF::size_type N)
    : self(indexForPosition(i, j, N))
{
    Q_ASSERT_X(i != 0 && j != 0, "Adjacents::Adjacents", "Zero index");

    if (j == 1)
        top = self;
    else
        top = self - N;

    if (i == N)
        right = self;
    else
        right = self + 1;

    if (j == N)
        bottom = self;
    else
        bottom = self + N;

    if (i == 1)
        left = self;
    else
        left = self - 1;
}

Percolation::Position::Position(int index, int N)
    : i{},
      j{}
{
    if (!(index > 0 && N > 0))
        qWarning() << "Percolation::Position::Position: index or N parameters must be greater then 0!";
    else {
        i = index % N == 0 ? N : index % N;
        j = index % N == 0 ? index / N : index / N + 1;
    }
}

Percolation::Index::Index(int i, int j, int N)
    : idx{}
{
    if (!(i > 0 && j > 0 && N > 0))
        qWarning() << "Percolation::Index::Index: i, j or N parameters must be greater then 0!";
    else
        idx = static_cast<int>(indexForPosition(static_cast<UF::size_type>(i),
                                                static_cast<UF::size_type>(j),
                                                static_cast<UF::size_type>(N)));
}
