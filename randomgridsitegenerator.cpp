#include "randomgridsitegenerator.h"

#include <memory>

RandomGridSiteGenerator::RandomGridSiteGenerator(QObject *parent)
    : QObject(parent),
      m_rd(),
      m_e(static_cast<int>(m_rd())),
      m_u()
{
}

int RandomGridSiteGenerator::gridSize() const
{
    return m_gridSize;
}

void RandomGridSiteGenerator::setGridSize(int gridSize)
{
    if (m_gridSize != gridSize) {
        m_gridSize = gridSize;
        emit gridSizeChanged();
        m_u = std::make_unique<std::uniform_int_distribution<int>>(1, m_gridSize);
    }
}

int RandomGridSiteGenerator::row()
{
    return m_u ? (*m_u)(m_e) : -1;
}

int RandomGridSiteGenerator::column()
{
    return m_u ? (*m_u)(m_e) : -1;
}


