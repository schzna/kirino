#ifndef INCLUDED_ARITH_HPP
#define INCLUDED_ARITH_HPP

#include <cstdint>
#include <iostream>
#include <utility>

const int irreducible = 0b100011011;

inline std::pair<int, int> gdiv(int x, int y)
{
    int mod = x;
    int q = 0;
    int tmpy = y;
    int si = 0, sj = 0;
    while (x > 1)
    {
        x = x >> 1;
        si++;
    }
    while (tmpy > 1)
    {
        tmpy = tmpy >> 1;
        sj++;
    }
    while (si >= sj)
    {
        if (((mod >> si) & x) == 1)
        {
            mod = mod ^ (y << (si - sj));
            q = q + (1 << (si - sj));
        }
        si--;
    }
    return std::make_pair(q, mod);
}

inline uint8_t greduce(int x)
{
    return gdiv(x, irreducible).second;
}

inline int gmul(int a, int b)
{
    int res = 0;
    int ta = static_cast<int>(a);
    while (b > 0)
    {
        if ((b & 1) == 1)
        {
            res = res ^ ta;
            res = greduce(res);
        }
        b = b >> 1;
        ta = greduce(ta << 1);
    }
    return greduce(res);
}

std::pair<int, int> gexeuclid(int a, int b)
{
    auto t = gdiv(std::max(a, b), std::min(a, b));
    int m = std::min(a, b);
    int n = t.second;
    int k = t.first;

    bool is_swap = (b > a);

    std::pair<int, int> res;

    if (n == 0)
    {
        res = {0, (m == 1) ? 1 : 0};
    }
    else if (n == 1)
    {
        res = {1, k};
    }
    else
    {
        auto rec = gexeuclid(m, n);
        res = {rec.second, rec.first ^ gmul(k, rec.second)};
    }

    if (is_swap)
    {
        std::swap(res.first, res.second);
    }

    return res;
}

int ginv(int x)
{
    if (x == 0)
        return 0;
    return gexeuclid(x, irreducible).first;
}

inline int extbit(int x, size_t i)
{
    return ((x >> i) & 1);
}

#endif