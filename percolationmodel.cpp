#include "percolationmodel.h"
#include "percolation.h"

PercolationModel::PercolationModel()
    : QAbstractTableModel(),
      m_percolation(nullptr)
{
}

Percolation *PercolationModel::percolation()
{
    return m_percolation;
}

void PercolationModel::setPercolation(Percolation *percolation)
{
    if (m_percolation == percolation || !percolation)
        return;

    if (m_percolation)
        m_percolation->disconnect(this);

    beginResetModel();
    m_percolation = percolation;
    emit percolationChanged();
    endResetModel();

    QObject::connect(m_percolation, &Percolation::gridSizeChanged, this, &PercolationModel::resetModel);
    QObject::connect(m_percolation, &Percolation::siteOpened, this, &PercolationModel::onSiteOpened);
}

int PercolationModel::rowCount(const QModelIndex &parent) const
{
    return m_percolation ? m_percolation->gridSize() : 0;
}

int PercolationModel::columnCount(const QModelIndex &parent) const
{
    return m_percolation ? m_percolation->gridSize() : 0;
}

QVariant PercolationModel::data(const QModelIndex &index, int role) const
{
    if (!m_percolation)
        return QVariant();

    if (role == OpenRole)
        return m_percolation->isOpen(index.row() + 1, index.column() + 1);
    else if (role == FullRole)
        return m_percolation->isFull(index.row() + 1, index.column() + 1);
    return QVariant();
}

bool PercolationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!m_percolation)
        return false;

    if (role == OpenRole && value.toBool()) {
        m_percolation->open(index.row() + 1, index.column() + 1);
        emit dataChanged(index, index, {OpenRole});
        return true;
    }

    return false;
}

QHash<int, QByteArray> PercolationModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[OpenRole] = "open";
    roleNames[FullRole] = "full";
    return roleNames;
}

Qt::ItemFlags PercolationModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void PercolationModel::resetModel()
{
    beginResetModel();
    endResetModel();
}

void PercolationModel::onSiteOpened(int i, int j)
{
    QModelIndex idx = index(i - 1, j - 1);
    emit dataChanged(idx, idx, {OpenRole});
}
