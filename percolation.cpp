#include "percolation.h"

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
Percolation::size_type indexForPosition(Percolation::size_type i, Percolation::size_type j, Percolation::size_type N)
{
    Percolation::size_type index = (j - 1) * N;
    return index += i;
}

struct Adjacents {
    Adjacents(Percolation::size_type i, Percolation::size_type j, Percolation::size_type N);
    Percolation::size_type top;
    Percolation::size_type right;
    Percolation::size_type bottom;
    Percolation::size_type left;
    Percolation::size_type self;
};
}

Percolation::Percolation(QObject *parent)
    : QObject{parent},
      m_uf{},
      m_N{0}
{
}

int Percolation::gridSize() const
{
    return static_cast<int>(m_N);
}

void Percolation::setGridSize(int gridSize)
{
    if (gridSize < 0 && m_N == static_cast<UF::size_type>(gridSize))
        return;

    m_N = static_cast<UF::size_type>(gridSize);
    emit gridSizeChanged();

    resetPercolation();
    initPercolation(static_cast<UF::size_type>(gridSize));
}

bool Percolation::percolates() const
{
    UF::size_type virtualBottom{0};
    UF::size_type virtualTop{m_N * m_N + 1};
    return m_uf->connected(virtualBottom, virtualTop);
}

void Percolation::open(int i, int j)
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
}

bool Percolation::isOpen(int i, int j) const
{
    return m_openSites[indexForPosition(static_cast<size_type>(i), static_cast<size_type>(j), m_N)];
}

bool Percolation::isFull(int i, int j) const
{
    return !isOpen(i, j);
}

void Percolation::resetPercolation()
{
    m_uf.reset(nullptr);
    m_openSites.clear();
}

void Percolation::initPercolation(size_type N)
{
    Q_ASSERT_X(!m_uf && m_openSites.empty(), "Percolation::initPercolation",
               "The member variables must have been reset before calling this function!!");

    allocateUF(N);
    m_openSites.assign(N * N + 2, false);

    constructVirtualComponents();
}

void Percolation::allocateUF(Percolation::size_type N)
{
    m_uf = std::make_unique<UF>(N * N + 2);
}

void Percolation::constructVirtualComponents()
{
    size_type N{m_N};

    size_type virtualTop = 0;
    std::pair<size_type, size_type> firstLine{1, N + 1};
    for (size_type i = firstLine.first; i < firstLine.second; ++i)
        m_uf->make_union(virtualTop, i);
    m_openSites[virtualTop] = true;

    size_type virtualBottom = N * N + 1;
    std::pair<size_type, size_type> lastLine{N * (N - 1) + 1, N * N + 1};
    for (size_type i = lastLine.first; i < lastLine.second; ++i)
        m_uf->make_union(virtualBottom, i);
    m_openSites[virtualBottom] = true;
}

Adjacents::Adjacents(Percolation::size_type i, Percolation::size_type j, Percolation::size_type N)
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
