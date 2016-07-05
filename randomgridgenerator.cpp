#include "randomgridgenerator.h"

RandomGridGenerator::RandomGridGenerator(QObject *parent)
    : QObject(parent),
      m_rd(),
      m_e(static_cast<int>(m_rd())),
      m_u()
{
}

Percolation *RandomGridGenerator::percolation()
{
    return m_percolation;
}

void RandomGridGenerator::setPercolation(Percolation *percolation)
{
    if (m_percolation == percolation)
        return;


}

int RandomGridGenerator::row()
{
    return m_u ? (*m_u)(m_e) : -1;
}

int RandomGridGenerator::column()
{
    return m_u ? (*m_u)(m_e) : -1;
}


