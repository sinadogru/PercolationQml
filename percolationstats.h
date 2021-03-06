#ifndef PERCOLATIONSTATS_H
#define PERCOLATIONSTATS_H

#include <QObject>
#include <QVector>

class PercolationStats : public QObject {
    Q_OBJECT
    Q_PROPERTY(qreal mean READ mean NOTIFY meanChanged)
    Q_PROPERTY(qreal stddev READ stddev NOTIFY stddevChanged)
    Q_PROPERTY(qint32 intervalCount READ intervalCount NOTIFY intervalCountChanged)

public:
    explicit PercolationStats(QObject *parent = Q_NULLPTR);

    qreal mean() const;
    qreal stddev() const;
    qint32 intervalCount() const;

    Q_INVOKABLE void percolated(qint32 numberOfOpenComponents, qint32 numberOfTotalComponents);
    Q_INVOKABLE void resetStats();

signals:
    void meanChanged();
    void stddevChanged();
    void intervalCountChanged();

private:
    void calculateStats();

    QVector<qreal> m_stats;
    qreal m_mean;
    qreal m_stddev;
};

#endif // PERCOLATIONSTATS_H
