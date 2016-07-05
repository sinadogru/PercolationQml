#ifndef RANDOMGRIDGENERATOR_H
#define RANDOMGRIDGENERATOR_H

#include <random>
#include <memory>
#include <QObject>
#include <QtQml>

class Percolation;

class RandomGridSiteGenerator : public QObject {
    Q_OBJECT
    Q_PROPERTY(int gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
    Q_PROPERTY(int row READ row)
    Q_PROPERTY(int column READ column)

public:
    explicit RandomGridSiteGenerator(QObject *parent = 0);

    int gridSize() const;
    void setGridSize(int gridSize);

    int row();
    int column();

signals:
    void gridSizeChanged();

private:
    std::random_device m_rd;
    std::mt19937 m_e;
    std::unique_ptr<std::uniform_int_distribution<int>> m_u;
    int m_gridSize;
};

QML_DECLARE_TYPE(RandomGridSiteGenerator)

#endif // RANDOMGRIDGENERATOR_H
