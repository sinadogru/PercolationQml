#include "weightedquickunionfind.h"
#include <iostream>

WeightedQuickUnionFind::WeightedQuickUnionFind(size_type N)
    : id(N), sz(N)
{
    for (size_type i = 0; i < N; ++i) {
        id[i] = i;
        sz[i] = 1;
    }
}

void WeightedQuickUnionFind::make_union(size_type p, size_type q)
{
    size_type i = root(p);
    size_type j = root(q);
    if (i == j)
        return;
    // we make the root of the smaller tree points to the root of the larger tree.
    if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    }
    else {
        id[j] = i;
        sz[i] += sz[j];
    }
}

bool WeightedQuickUnionFind::connected(size_type p, size_type q) const
{
    return root(p) == root(q);
}

std::ostream &WeightedQuickUnionFind::print_id_array(std::ostream &os) const
{
    for (const auto &e : id)
        os << e << " ";

    return os;
}

auto WeightedQuickUnionFind::root(size_type i) const -> size_type
{
    while (i != id[i]) {
//        id[i] = id[id[i]]; // Path Comprasion!!
        i = id[i];
    }
    return i;
}
