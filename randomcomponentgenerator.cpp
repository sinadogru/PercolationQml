#include "randomcomponentgenerator.h"

#include <memory>

RandomComponentGenerator::RandomComponentGenerator(QObject *parent)
    : QObject(parent),
      m_rd{},
      m_e{m_rd()},
      m_u{}
{
}

int RandomComponentGenerator::gridSize() const
{
    return m_gridSize;
}

void RandomComponentGenerator::setGridSize(int gridSize)
{
    if (m_gridSize != gridSize) {
        m_gridSize = gridSize;
        emit gridSizeChanged();
        m_u = std::make_unique<std::uniform_int_distribution<int>>(1, m_gridSize);
    }
}

int RandomComponentGenerator::row()
{
    return m_u ? (*m_u)(m_e) : -1;
}

int RandomComponentGenerator::column()
{
    return m_u ? (*m_u)(m_e) : -1;
}


