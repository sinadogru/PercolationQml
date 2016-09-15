#include "percolationmanager.h"

#include <QtGlobal>


PercolationManager* PercolationManager::mp_self = nullptr;

PercolationManager::PercolationManager()
    : m_isActive{false},
      m_gridSize{0},
      m_openings{}
{
    Q_ASSERT_X(!mp_self, "PercolationManager::PercolationManager",
               "Can not create PercolationManager. There is already one!");

    PercolationManager::mp_self = this;
}

PercolationManager::~PercolationManager()
{ PercolationManager::mp_self = nullptr; }

auto PercolationManager::isActive() const -> bool
{ return m_isActive; }

auto PercolationManager::activate() -> void
{ m_isActive = true; }

auto PercolationManager::gridSize() const -> int
{ return m_gridSize; }

auto PercolationManager::setGridSize(int gridSize) -> void
{ m_gridSize = gridSize; }

auto PercolationManager::addOpening(int x, int y) -> void
{ m_openings.push_back({x, y}); }

auto PercolationManager::openings() const -> Openings
{ return m_openings; }
