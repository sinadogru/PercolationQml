#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <vector>
#include <memory>
#include <QObject>
#include <QtQml>
#include "weightedquickunionfind.h"

/*!
 * \brief The Percolation class
 *
 * Corner cases. The row and column indices i and j are integers
 * between 1 and N, where (1, 1) is the upper-left site.
 */

class Percolation : public QObject {
    Q_OBJECT
    Q_PROPERTY(int gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
    Q_PROPERTY(bool isPercolates READ isPercolates NOTIFY percolated)

    using UF = WeightedQuickUnionFind;

public:
    struct Position {
        int i;
        int j;
        Position(int index, int N);
        Position() = default;
    };
    struct Index {
        int idx;
        Index(int i, int j, int N);
    };

    using size_type = UF::size_type;

    explicit Percolation(QObject *parent = nullptr);

    int gridSize() const;
    void setGridSize(int gridSize);

    bool isPercolates() const;

public slots:
    void openComponent(int i, int j);
    bool isComponentPercolates(int i, int j) const;
    bool isComponentOpen(int i, int j) const;
    bool isComponentFull(int i, int j) const;

signals:
    void gridSizeChanged();
    void percolated();

    void siteOpened(int i, int j);

private:
    void resetPercolation();
    void initPercolation(size_type N);
    void allocateUF(size_type N);
    void constructVirtualComponents();
    void checkPercolation();

    std::unique_ptr<UF> m_uf;
    std::vector<bool> m_openSites;
    size_type m_N;
    bool m_isPercolates : 1;
    size_type m_virtualTop;
    size_type m_virtualBottom;
};

QML_DECLARE_TYPE(Percolation)

#endif // PERCOLATION_H
