#ifndef float3_H
#define float3_H
#include <math.h>


class float3 {
public:
    float x;
    float y;
    float z;
    float3() :x(0), y(0), z(0) {}
    float3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
    float3(const float3& b) :x(b.x), y(b.y), z(b.z) {}
};

class float4 {
public:
    float x;
    float y;
    float z;
    float w;
    float4(float x_, float y_, float z_, float w_) :x(x_), y(y_), z(z_), w(w_) {}
};

inline float3 make_float3(float x, float y, float z) {
    return float3(x, y, z);
}

inline float4 make_float4(float x, float y, float z, float w) {
    return float4(x, y, z, w);
}


inline   float3 unit_vector(const float3& v) {
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return make_float3(v.x / length, v.y / length, v.z / length);
}

inline   float dot(const float3& v1, const float3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline   float3 cross(const float3& v1, const float3& v2) {
    return make_float3((v1.y * v2.z - v1.z * v2.y),
        (-(v1.x * v2.z - v1.z * v2.x)),
        (v1.x * v2.y - v1.y * v2.x));
}

inline   float3 operator+(const float3& v1, const float3& v2) {
    return make_float3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline   float3 operator-(const float3& v1, const float3& v2) {
    return make_float3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}



inline   float3 operator*(float t, const float3& v) {
    return make_float3(t * v.x, t * v.y, t * v.z);
}


inline   float3 lerp(const float3& a, const float3& b, float t)
{
    return (1 - t) * a + t * b;
}

inline   float length(const float3& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline   float3 minus(const float3& v1, const float3& v2) {
    return make_float3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline   float4 operator+(const float4& v1, const float4& v2) {
    return float4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

inline   float4 operator-(const float4& v1, const float4& v2) {
    return float4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}



inline   float4 operator*(float t, const float4& v) {
    return float4(t * v.x, t * v.y, t * v.z, t * v.w);
}


inline   float4 lerp(const float4& a, const float4 b, float t)
{
    return (1 - t) * a + t * b;
}

#endif // float3_H
