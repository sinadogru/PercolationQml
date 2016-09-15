#ifndef PERCOLATIONMANAGER_H
#define PERCOLATIONMANAGER_H

#include <utility>
#include <vector>


class PercolationManager
{
public:
    using Openings = std::vector<std::pair<int, int>>;

    PercolationManager();

    ~PercolationManager();

    static auto instance()
    { return mp_self; }

    auto isActive() const -> bool;
    auto activate() -> void;

    auto gridSize() const -> int;
    auto setGridSize(int) -> void;

    auto addOpening(int, int) -> void;
    auto openings() const -> Openings;

private:
    static PercolationManager* mp_self;

    bool m_isActive : 1;
    int m_gridSize;
    Openings m_openings;
};

#endif // PERCOLATIONMANAGER_H
