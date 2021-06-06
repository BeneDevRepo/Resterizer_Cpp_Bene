#pragma once

#include <cstddef>

template <typename _Type, int _Rows, int _Cols>
struct mat {
    _Type m[_Rows * _Cols];
};

template<typename _Type, int _Length>
struct vec {
    _Type v[_Length];

    using _Vec = vec<_Type, _Length>;

    inline _Vec operator+(const _Vec& right) {
        _Vec v;

        for (int i = 0; i < _Length; i++)
            v.v[i] = this->v[i] + right.v[i];
            
        return v;
    }

    inline _Vec operator-(const _Vec& right) {
        _Vec v;

        for (int i = 0; i < _Length; i++)
            v.v[i] = this->v[i] - right.v[i];

        return v;
    }

    inline _Vec operator*(const _Vec& right) {
        _Vec v;

        for (int i = 0; i < _Length; i++)
            v.v[i] = this->v[i] * right.v[i];

        return v;
    }

    inline _Vec operator/(const _Vec& right) {
        _Vec v;

        for (int i = 0; i < _Length; i++)
            v.v[i] = this->v[i] / right.v[i];

        return v;
    }

    inline _Type dot(const _Vec& right) {
        _Type res = 0;

        for (size_t i = 0; i < _Length; i++)
            res += this->v[i] * right.v[i];

        return res;
    }

    inline _Vec cross(const _Vec& right) requires(_Length == 3) {
        _Vec v = {
            this->v[1]*right.v[2] - this->v[2]*right.v[1],
            this->v[0]*right.v[2] - this->v[2]*right.v[1],
            this->v[1]*right.v[1] - this->v[0]*right.v[1]
        };
        return v;
    }
};

template <typename _Type, int _Length>
inline vec<_Type, _Length> operator*(const vec<_Type, _Length>& left, const mat<_Type, _Length, _Length>& right)
{
    vec<_Type, _Length> v;
    for (size_t row = 0; row < _Length; row++)
        for (size_t col = 0; col < _Length; col++)
            v.v[row] += left.v[col]*right.m[row * _Length + col];

    return v;

    // vec3_t v = {
    //    v1.x*m1.r1.x + v1.y*m1.r1.y + v1.z*m1.r1.z, 
    //    v1.x*m1.r2.x + v1.y*m1.r2.y + v1.z*m1.r2.z, 
    //    v1.x*m1.r3.x + v1.y*m1.r3.y + v1.z*m1.r3.z 
    // };
}
