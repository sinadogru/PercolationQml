#ifndef RANDOMGRIDGENERATOR_H
#define RANDOMGRIDGENERATOR_H

#include <random>
#include <memory>
#include <QObject>
#include <QtQml>

class Percolation;

class RandomGridGenerator : public QObject {
    Q_OBJECT
    Q_PROPERTY(Percolation *percolation READ percolation WRITE setPercolation NOTIFY percolationChanged)
    Q_PROPERTY(int row READ row)
    Q_PROPERTY(int column READ column)

public:
    using size_type = int;

    explicit RandomGridGenerator(QObject *parent = 0);

    Percolation *percolation();
    void setPercolation(Percolation *percolation);

    int row();
    int column();

signals:
    void percolationChanged();

private:
    std::random_device m_rd;
    std::mt19937 m_e;
    std::unique_ptr<std::uniform_int_distribution<size_type>> m_u;
    Percolation *m_percolation;
};

QML_DECLARE_TYPE(RandomGridGenerator)

#endif // RANDOMGRIDGENERATOR_H
