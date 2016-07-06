#include "percolationstats.h"

#include <cmath>

PercolationStats::PercolationStats(QObject *parent)
    : QObject{parent},
      m_stats{},
      m_mean{},
      m_stddev{}
{
}

qreal PercolationStats::mean() const
{
    return m_mean;
}

qreal PercolationStats::stddev() const
{
    return m_stddev;
}

void PercolationStats::percolated(qint32 numberOfOpenComponents, qint32 numberOfTotalComponents)
{
    m_stats.push_back(static_cast<qreal>(numberOfOpenComponents) / numberOfTotalComponents);
    calculateStats();
}

void PercolationStats::resetStats()
{
    m_stats.clear();
    m_mean = 0.;
    emit meanChanged();
    m_stddev = 0.;
    emit stddevChanged();
}

void PercolationStats::calculateStats()
{
    const qreal sum = std::accumulate(m_stats.begin(), m_stats.end(), 0.);

    const qreal mean = sum / m_stats.size();
    m_mean = round(mean * 100) / 100;
    emit meanChanged();

    QVector<qreal> diff(m_stats.size());
    std::transform(m_stats.begin(), m_stats.end(), diff.begin(), [mean](double e) { return e - mean; });
    qreal sqSum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.);
    m_stddev = round(std::sqrt(sqSum / m_stats.size()) * 100) / 100;
    emit stddevChanged();
}
