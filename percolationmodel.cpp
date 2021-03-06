#include "percolationmodel.h"

#include <QColor>

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
        QObject::connect(m_percolation, &Percolation::percolated, this, &PercolationModel::onPercolated);
        QObject::connect(m_percolation, &Percolation::percolationReseted, this, &PercolationModel::resetModel);
    }
}

int PercolationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (m_percolation) {
        const int gridSize = m_percolation->gridSize();
        return gridSize * gridSize;
    }
    return 0;
}

QVariant PercolationModel::data(const QModelIndex &index, int role) const
{
    if (!m_percolation)
        return QVariant();

    if (!index.isValid())
        return QVariant();

    const int idx = index.row();
    if (idx < 0 || idx >= rowCount())
        return QVariant();

    const Percolation::Position position(idx + 1, m_percolation->gridSize());
    switch (role) {
    case PercolatesRole:
        return m_percolation->isComponentPercolates(position.i, position.j);
    case ComponentColorRole: {
        const int N = m_percolation->gridSize();
        const int r = idx / N;
        const int c = idx % N;
        Qt::GlobalColor componentColor;
        if (m_percolation->gridSize() % 2)
            componentColor = idx % 2 ? Qt::white : Qt::lightGray;
        else
            componentColor = r % 2 ? (c % 2 ? Qt::white : Qt::lightGray)
                                   : (c % 2 ? Qt::lightGray : Qt::white);
        return QColor(componentColor);

    }
    case OpenRole:
        return m_percolation->isComponentOpen(position.i, position.j);
    case FullRole:
        return m_percolation->isComponentFull(position.i, position.j);
    default:
        break;
    }

    return QVariant();
}

bool PercolationModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!m_percolation)
        return false;

    if (role == OpenRole && value.toBool()) {
        m_percolation->openComponent(index.row() + 1, index.column() + 1);
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
    roleNames[PercolatesRole] = "percolates";
    roleNames[ComponentColorRole] = "componentColor";
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
        if (m_percolation->isPercolates() && m_percolation->isComponentPercolates(i, j))
            emit dataChanged(siteIdx, siteIdx, {OpenRole, PercolatesRole});
        else
            emit dataChanged(siteIdx, siteIdx, {OpenRole});
    }
}

void PercolationModel::onPercolated()
{
    // TODO optimization: check if updating the model elements one by one performance better then reseting the model
    resetModel();
}
