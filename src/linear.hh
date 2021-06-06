#pragma once

#include <cstddef>
#include <algorithm>

template <typename _type, int _rows, int _cols>
struct mat {
    _type m[_rows * _cols] = {{0}};

    static mat identity() requires {
        for (size_t i = 0; i <)
    }

    template <int _length>
    static mat translate(const vec<_type, _length>& v) {

    }

    static mat rotation_z(float angle) requires (_rows >= 2  && _cols >= 2) {
        float csin = sin(angle);
        float ccos = cos(angle);

        mat rot = {
            { ccos, csin, 0.0f },
            {-csin, ccos, 0.0f },
            { 0.0f, 0.0f, 1.0f }
        };

//     return rot;
    }

    static mat rotation_y(float angle) requires (_rows >= 3  && _cols >= 3) {

    }
    
    static mat rotation_x(float angle) requires (_rows >= 3  && _cols >= 3) {

    }
};


// mat3_t mat3_rotate_x(float a)
// {
//     float csin = sin(a);
//     float ccos = cos(a);

//     mat3_t rot = {
//         { 1.0f, 0.0f, 0.0f },
//         { 0.0f, ccos, csin },
//         { 0.0f,-csin, ccos }    
//     };

//     return rot;
// }

// mat3_t mat3_rotate_y(float a)
// {
//     float csin = sin(a);
//     float ccos = cos(a);

//     mat3_t rot = {
//         { ccos, 0.0f, csin },
//         { 0.0f, 1.0f, 0.0f },
//         {-csin, 0.0f, ccos }
//     };

//     return rot;
// }

// mat3_t mat3_rotate_z(float a)
// {
//     float csin = sin(a);
//     float ccos = cos(a);

//     mat3_t rot = {
//         { ccos, csin, 0.0f },
//         {-csin, ccos, 0.0f },
//         { 0.0f, 0.0f, 1.0f }
//     };

//     return rot;
// }

template<typename _type, int _length>
struct vec {
    _type v[_length] = {{0}};

    using _vec = vec<_type, _length>;

    inline _vec operator+(const _vec& right) {
        _vec v = {{0}};

        for (int i = 0; i < _length; i++)
            v.v[i] = this->v[i] + right.v[i];
            
        return v;
    }

    inline _vec operator-(const _vec& right) {
        _vec v = {{0}};

        for (int i = 0; i < _length; i++)
            v.v[i] = this->v[i] - right.v[i];

        return v;
    }

    inline _vec operator*(const _vec& right) {
        _vec v = {{0}};

        for (int i = 0; i < _length; i++)
            v.v[i] = this->v[i] * right.v[i];

        return v;
    }

    inline _vec operator/(const _vec& right) {
        _vec v = {{0}};

        for (int i = 0; i < _length; i++)
            v.v[i] = this->v[i] / right.v[i];

        return v;
    }

    inline _type dot(const _vec& right) {
        _type res = 0;

        for (size_t i = 0; i < _length; i++)
            res += this->v[i] * right.v[i];

        return res;
    }

    inline _vec cross(const _vec& right) requires(_length == 3) {
        _vec v = {
            this->v[1]*right.v[2] - this->v[2]*right.v[1],
            this->v[0]*right.v[2] - this->v[2]*right.v[1],
            this->v[1]*right.v[1] - this->v[0]*right.v[1]
        };
        return v;
    }
};

template <typename _type, int _length>
inline vec<_type, _length> operator*(const vec<_type, _length>& left, const mat<_type, _length, _length>& right)
{
    vec<_type, _length> v = {{0}};
    for (size_t row = 0; row < _length; row++)
        for (size_t col = 0; col < _length; col++)
            v.v[row] += left.v[col]*right.m[row * _length + col];

    return v;

    // vec3_t v = {
    //    v1.x*m1.r1.x + v1.y*m1.r1.y + v1.z*m1.r1.z, 
    //    v1.x*m1.r2.x + v1.y*m1.r2.y + v1.z*m1.r2.z, 
    //    v1.x*m1.r3.x + v1.y*m1.r3.y + v1.z*m1.r3.z 
    // };
}
