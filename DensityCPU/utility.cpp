#include "utility.h"
#include <limits>
#include <algorithm>
#include "vec3.h"

// 找出点云的上下界

int divUp(int a, int b) { return (a + b - 1) / b; }

aabb point_cloud_bounds(const std::vector<float3>& pc)
{
    float3 lower, upper;

    lower.x = std::numeric_limits<float>::max();
    upper.x = std::numeric_limits<float>::min();
    lower.y = std::numeric_limits<float>::max();
    upper.y = std::numeric_limits<float>::min();
    lower.z = std::numeric_limits<float>::max();
    upper.z = std::numeric_limits<float>::min();

    for (float3 pt : pc)
    {
        lower.x = std::min(lower.x, pt.x);
        upper.x = std::max(upper.x, pt.x);

        lower.y = std::min(lower.y, pt.y);
        upper.y = std::max(upper.y, pt.y);

        lower.z = std::min(lower.z, pt.z);
        upper.z = std::max(upper.z, pt.z);
    }

    return aabb(lower, upper);
}

const float3 color0 = make_float3(0, 0, 0);
const float3 color2 = make_float3(0, 0, 1);
const float3 color4 = make_float3(0, 1, 1);
const float3 color6 = make_float3(0, 1, 0);
const float3 color8 = make_float3(1, 1, 0);
const float3 color10 = make_float3(1, 0, 0);


float3 heat_color(float value, float max_value)
{
    if (max_value < 1.0)
        return color0;
    float pct = value / max_value;
    float t;
    if (pct < 0.20)
    {
        t = (pct - 0.0) / (0.20 - 0.0);
        return lerp(color0, color2, t);
    }
    if (pct < 0.40)
    {
        t = (pct - 0.20) / (0.40 - 0.20);
        return lerp(color2, color4, t);
    }
    if (pct < 0.50)
    {
        t = (pct - 0.40) / (0.50 - 0.40);
        return lerp(color4, color6, t);
    }
    if (pct < 0.70)
    {
        t = (pct - 0.50) / (0.70 - 0.50);
        return lerp(color6, color8, t);
    }
    if (pct < 1.00)
    {
        t = (pct - 0.70) / (1.00 - 0.70);
        return lerp(color8, color10, t);
    }
    else
        return color10;
}


const float4 colorf0 = make_float4(0, 0, 0, 0.2);
const float4 colorf2 = make_float4(0, 0, 1, 0.4);
const float4 colorf4 = make_float4(0, 1, 1, 0.6);
const float4 colorf6 = make_float4(0, 1, 0, 0.7);
const float4 colorf8 = make_float4(1, 1, 0, 0.8);
const float4 colorf10 = make_float4(1, 0, 0, 0.9);


float4 heat_color4(float value, float max_value)
{
    if (max_value < 1.0)
        return colorf0;
    float pct = value / max_value;
    float t;
    if (pct < 0.20)
    {
        t = (pct - 0.0) / (0.20 - 0.0);
        return lerp(colorf0, colorf2, t);
    }
    if (pct < 0.40)
    {
        t = (pct - 0.20) / (0.40 - 0.20);
        return lerp(colorf2, colorf4, t);
    }
    if (pct < 0.50)
    {
        t = (pct - 0.40) / (0.50 - 0.40);
        return lerp(colorf4, colorf6, t);
    }
    if (pct < 0.70)
    {
        t = (pct - 0.50) / (0.70 - 0.50);
        return lerp(colorf6, colorf8, t);
    }
    if (pct < 1.00)
    {
        t = (pct - 0.70) / (1.00 - 0.70);
        return lerp(colorf8, colorf10, t);
    }
    else
        return colorf10;
}

