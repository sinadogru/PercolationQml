#ifndef WEIGHTEDQUICKUNIONFIND_H
#define WEIGHTEDQUICKUNIONFIND_H

#include <vector>
#include <cstddef>
#include <iosfwd>

class WeightedQuickUnionFind {
public:
    using size_type = size_t;

    WeightedQuickUnionFind(size_type N);

    void make_union(size_type p, size_type q);
    bool connected(size_type p, size_type q) const;

    std::ostream &print_id_array(std::ostream &os) const;

private:
    size_type root(size_type i) const;

    std::vector<size_type> id;
    std::vector<size_type> sz;
};

#endif // WEIGHTEDQUICKUNIONFIND_H
