#include "linear.hh"
#include <math.h>

/*
vec3_t vec3_t::operator+(const vec3_t& other) {
    vec3_t v {
        this->x + other.x,
        this->y + other.y,
        this->z + other.z
    };
    return v;
}
vec3_t vec3_t::operator-(const vec3_t& other) {
    vec3_t v = {
        this->x - other.x,
        this->y - other.y,
        this->z - other.z
    };
    return v;
}
vec3_t vec3_t::operator*(const vec3_t& other) {
    vec3_t v = {
        this->x * other.x,
        this->y * other.y,
        this->z * other.z
    };
    return v;
}
// _vec3 operator/(const _vec3& other);

float vec3_t::dot(const vec3_t& other) {
    return (this->x*other.x + this->y*other.y + this->z*other.z);
}

vec3_t vec3_t::cross(const vec3_t& other) {
    vec3_t v = {
        this->y*other.z - this->z*other.y,
        this->x*other.z - this->z*other.x,
        this->y*other.x - this->x*other.y
    };
    return v;
}
vec3_t vec3_t::vec3_normalize() {
    float dist = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
    vec3_t v = {
        this->x / dist,
        this->y / dist,
        this->z / dist
    };
    return v;
}
vec3_t vec3_t::operator*(const mat3_t& m) {
    vec3_t v = {
       this->x*m.r1.x + this->y*m.r1.y + this->z*m.r1.z, 
       this->x*m.r2.x + this->y*m.r2.y + this->z*m.r2.z,
       this->x*m.r3.x + this->y*m.r3.y + this->z*m.r3.z 
    };

    return v;
}




//old stuff

#pragma warning(Deprecated)
vec3_t vec3_add(vec3_t v1, vec3_t v2) {
    vec3_t v = {
        v1.x + v2.x,
        v1.y + v2.y,
        v1.z + v2.z
    };

    return v;
}

vec3_t vec3_sub(vec3_t v1, vec3_t v2) {
    vec3_t v = {
        v1.x - v2.x,
        v1.y - v2.y,
        v1.z - v2.z
    };

    return v;
}

vec3_t vec3_mul(vec3_t v1, vec3_t v2) {
    vec3_t v = {
        v1.x * v2.x,
        v1.y * v2.y,
        v1.z * v2.z
    };

    return v;
}

vec3_t vec3_div(vec3_t v1, vec3_t v2) {
    vec3_t v = {
        v1.x / v2.x,
        v1.y / v2.y,
        v1.z / v2.z
    };

    return v;
}

float vec3_dot(vec3_t v1, vec3_t v2) {
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

vec3_t vec3_cross(vec3_t v1, vec3_t v2) {
    vec3_t v = {
        v1.y*v2.z - v1.z*v2.y,
        v1.x*v2.z - v1.z*v2.x,
        v1.y*v2.x - v1.x*v2.y
    };    

    return v;
}

vec3_t vec3_normalize(vec3_t v) {
    float dist = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    vec3_t ret = {
        v.x / dist,
        v.y / dist,
        v.z / dist
    };

    return ret;
}

vec3_t vec3_mul_mat3(vec3_t v1, mat3_t m1) {
    vec3_t v = {
       v1.x*m1.r1.x + v1.y*m1.r1.y + v1.z*m1.r1.z, 
       v1.x*m1.r2.x + v1.y*m1.r2.y + v1.z*m1.r2.z, 
       v1.x*m1.r3.x + v1.y*m1.r3.y + v1.z*m1.r3.z 
    };

    return v;
}

mat3_t mat3_translate(vec3_t v)
{
    mat3_t m = {
        { 1.0f, 0.0f, v.x },
        { 0.0f, 1.0f, v.y },
        { 0.0f, 0.0f, v.z }
    };

    return m;
}

mat3_t mat3_scale(vec3_t v)
{
    mat3_t m = {
        { v.x, 0.0f, 0.0f },
        { 0.0f, v.y, 0.0f },
        { 0.0f, 0.0f, v.z }
    };

    return m;
}

mat3_t mat3_rotate_x(float a)
{
    float csin = sin(a);
    float ccos = cos(a);

    mat3_t rot = {
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, ccos, csin },
        { 0.0f,-csin, ccos }    
    };

    return rot;
}

mat3_t mat3_rotate_y(float a)
{
    float csin = sin(a);
    float ccos = cos(a);

    mat3_t rot = {
        { ccos, 0.0f, csin },
        { 0.0f, 1.0f, 0.0f },
        {-csin, 0.0f, ccos }
    };

    return rot;
}

mat3_t mat3_rotate_z(float a)
{
    float csin = sin(a);
    float ccos = cos(a);

    mat3_t rot = {
        { ccos, csin, 0.0f },
        {-csin, ccos, 0.0f },
        { 0.0f, 0.0f, 1.0f }
    };

    return rot;
}
*/