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
    Q_PROPERTY(bool isPercolates READ isPercolates NOTIFY isPercolatesChanged)

public:
    using UF = WeightedQuickUnionFind;
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

    explicit Percolation(QObject *parent = Q_NULLPTR);

    int gridSize() const;
    void setGridSize(int gridSize);

    bool isPercolates() const;

public slots:
    void openComponent(int i, int j);
    bool isComponentPercolates(int i, int j) const;
    bool isComponentOpen(int i, int j) const;
    bool isComponentFull(int i, int j) const;
    void resetPercolation();

signals:
    void gridSizeChanged();
    void isPercolatesChanged();
    void percolated();

    void siteOpened(int i, int j);
    void percolationReseted();

private:
    void clearPercolation();
    void initPercolation(UF::size_type N);
    void allocateUF(UF::size_type N);
    void constructVirtualComponents(UF::size_type N);
    void checkPercolates();

    std::unique_ptr<UF> m_uf;
    std::vector<bool> m_openSites;
    UF::size_type m_N;
    bool m_isPercolates : 1;
    UF::size_type m_virtualTop;
    UF::size_type m_virtualBottom;
};

QML_DECLARE_TYPE(Percolation)

#endif // PERCOLATION_H
