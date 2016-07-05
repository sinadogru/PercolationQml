#include "percolationmodel.h"
#include "percolation.h"

PercolationModel::PercolationModel()
    : QAbstractListModel(),
      m_percolation(nullptr)
{
}

Percolation *PercolationModel::percolation()
{
    return m_percolation;
}

void PercolationModel::setPercolation(Percolation *percolation)
{
    if (m_percolation == percolation)
        return;

    if (m_percolation)
        m_percolation->disconnect(this);

    beginResetModel();
    m_percolation = percolation;
    emit percolationChanged();
    endResetModel();

    if (m_percolation) {
        QObject::connect(m_percolation, &Percolation::gridSizeChanged, this, &PercolationModel::resetModel);
        QObject::connect(m_percolation, &Percolation::siteOpened, this, &PercolationModel::onSiteOpened);
    }
}

int PercolationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (m_percolation) {
        int gridSize = m_percolation->gridSize();
        return gridSize * gridSize;
    }
    return 0;
}

QVariant PercolationModel::data(const QModelIndex &index, int role) const
{
    if (!m_percolation)
        return QVariant();

    const Percolation::Position position(index.row() + 1, m_percolation->gridSize());
    if (role == OpenRole)
        return m_percolation->isOpen(position.i, position.j);
    else if (role == FullRole)
        return m_percolation->isFull(position.i, position.j);
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
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

void PercolationModel::resetModel()
{
    beginResetModel();
    endResetModel();
}

void PercolationModel::onSiteOpened(int i, int j)
{
    if (m_percolation) {
        const Percolation::Index idx(i, j, m_percolation->gridSize());
        const QModelIndex siteIdx = index(idx.idx - 1);
        emit dataChanged(siteIdx, siteIdx, {OpenRole});
    }
}
