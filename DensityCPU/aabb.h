#ifndef AABBH
#define AABBH

#include <iostream>
#include <vector>
#include <float.h>
#include "ray.h"
#define ffmin(a,b) ((a) < (b) ? (a) : (b))
#define ffmax(a,b) ((a) > (b) ? (a) : (b))


class aabb {
public:
    aabb() {}
    aabb(const float3& a, const float3& b)
    {
        _min.x = ffmin(a.x, b.x);
        _min.y = ffmin(a.y, b.y);
        _min.z = ffmin(a.z, b.z);
        _max.x = ffmax(a.x, b.x);
        _max.y = ffmax(a.y, b.y);
        _max.z = ffmax(a.z, b.z);

    }
    float3 min() const { return _min; }
    float3 max() const { return _max; }

    /*
    static aabb surrounding_box(aabb box0, aabb box1)
    {
        float3 small, large;
        small.x=ffmin(box0.min().x, box1.min().x);
        small.y=ffmin(box0.min().y, box1.min().y);
        small.z=ffmin(box0.min().z, box1.min().z);

       large.x = ffmax(box0.max().x, box1.max().x);
       large.y = ffmax(box0.max().y, box1.max().y),
       large.z = ffmax(box0.max().z, box1.max().z);

        return aabb(small, large);
    }
    */

    bool hit(ray r, float tmin, float tmax, float& t0, float& t1) const
    {
        float3 o = r.origin();
        float3 d = r.direction();

        {
            float invD = 1.0f / d.x;
            t0 = (min().x - o.x) * invD;
            t1 = (max().x - o.x) * invD;
            if (invD < 0.0f)
            {
                float temp = t0;
                t0 = t1;
                t1 = temp;
            }
            tmin = ffmax(tmin, t0);
            tmax = ffmin(tmax, t1);
            if (tmax <= tmin)
                return false;
        }
        {
            float invD = 1.0f / d.y;
            float t0 = (min().y - o.y) * invD;
            float t1 = (max().y - o.y) * invD;
            if (invD < 0.0f)
            {
                float temp = t0;
                t0 = t1;
                t1 = temp;
            }
            tmin = ffmax(tmin, t0);
            tmax = ffmin(tmax, t1);
            if (tmax <= tmin)
                return false;
        }
        {
            float invD = 1.0f / d.z;
            float t0 = (min().z - o.z) * invD;
            float t1 = (max().z - o.z) * invD;
            if (invD < 0.0f)
            {
                float temp = t0;
                t0 = t1;
                t1 = temp;
            }
            tmin = ffmax(tmin, t0);
            tmax = ffmin(tmax, t1);
            if (tmax <= tmin)
                return false;
        }

        return true;
    }

    bool contains(float3 pt);
    void print()
    {
        std::cerr << "(" << _min.x << ", " << _min.y << ", " << _min.z << ") - ";
        std::cerr << "(" << _max.x << ", " << _max.y << ", " << _max.z << ")\n";

    }
    void printf()
    {
        //printf("(%f,%f,%f)-(%f,%f,%f)\n",_min.x,_min.y,_min.z,_max.x,_max.y,_max.z);
    }
    float3 _min;
    float3 _max;
    float density;
};

class aabb_mesh {
public:
    aabb_mesh(const float3& a, const float3& b, int _m, int _n, int _p)
        :box(a, b), m(_m), n(_n), p(_p) {}
    int count_density_for_point_cloud(std::vector<float3>* pc, int i, int j, int k);
    aabb box;
    int m, n, p;
};


#endif
