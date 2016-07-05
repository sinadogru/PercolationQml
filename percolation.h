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
 * Corner cases.  By convention, the row and column indices i and j are
 * integers between 1 and N, where (1, 1) is the upper-left site.
 */

class Percolation : public QObject {
    Q_OBJECT
    Q_PROPERTY(int gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
    Q_PROPERTY(bool percolates READ percolates NOTIFY percolatesChanged)

    using UF = WeightedQuickUnionFind;

public:
    struct Position {
        int i;
        int j;
        Position(int index, int N);
    };
    struct Index {
        int idx;
        Index(int i, int j, int N);
    };

    using size_type = UF::size_type;

    explicit Percolation(QObject *parent = nullptr);

    int gridSize() const;
    void setGridSize(int gridSize);

    bool percolates() const;

public slots:

    void open(int i, int j);
    bool isOpen(int i, int j) const;
    bool isFull(int i, int j) const;

signals:
    void gridSizeChanged();
    void percolatesChanged();

    void siteOpened(int i, int j);

private:
    void resetPercolation();
    void initPercolation(size_type N);
    void allocateUF(size_type N);
    void constructVirtualComponents();

    std::unique_ptr<UF> m_uf;
    std::vector<bool> m_openSites;
    size_type m_N;
};

QML_DECLARE_TYPE(Percolation)

#endif // PERCOLATION_H
