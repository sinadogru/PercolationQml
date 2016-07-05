#ifndef PERCOLATIONMODEL_H
#define PERCOLATIONMODEL_H

#include <QAbstractListModel>
#include <QtQml>

class Percolation;

class PercolationModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(Percolation *percolation READ percolation WRITE setPercolation NOTIFY percolationChanged)

public:
    enum Roles {
        OpenRole = Qt::UserRole,
        FullRole,
        PercolatesRole,
    };

    PercolationModel();

    Percolation *percolation();
    void setPercolation(Percolation *percolation);

    int rowCount( const QModelIndex & parent = QModelIndex() ) const override;

    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private slots:
    void resetModel();
    void onSiteOpened(int i, int j);
    void onPercolated();

signals:
    void percolationChanged();

private:
    Percolation *m_percolation;
};

QML_DECLARE_TYPE(PercolationModel)

#endif // PERCOLATIONMODEL_H
