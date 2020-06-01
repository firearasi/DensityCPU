#include "count3D.h"
#include "readfile.h"
#include "utility.h"

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
//#include "camera.h"
//#include "render.h"

#include "main3ddata.h"

#include <fstream>
#include "readfile.h"
#include "vec3.h"
#include <thread>
#include <mutex>

#define TX 32
#define TY 32

using namespace std;


extern int divUp(int a, int b);

int* density;




int main3DData(string srcfilename, float radius, float granularity, float xstretch, float ystretch, float zstretch)
{
    std::vector<float3> pc = read_yxz(srcfilename);

    //int x0=15;
    //int y0=15;
    //int z0=15;


    aabb box = point_cloud_bounds(pc);
    //int m=(int)(box.max().x-box.min().x)/x0+1;
    //int n=(int)(box.max().y-box.min().y)/y0+1;
    //int p=(int)(box.max().z-box.min().z)/z0+1;
    box.print();


    //float3* d_pc;
    int len = pc.size();

   /* CudaSafeCall(cudaMallocManaged(&d_pc, len * sizeof(float3)));
    CudaSafeCall(cudaMemcpy(d_pc, &pc[0], len * sizeof(float3), cudaMemcpyHostToDevice));*/

    float x1, y1, z1, x2, y2, z2;
    x1 = box.min().x;
    x2 = box.max().x + 1;
    y1 = box.min().y;
    y2 = box.max().y + 1;
    z1 = box.min().z;
    z2 = box.max().z + 1;

    printf("Bounds:(%f,%f,%f)-(%f,%f,%f)\n", x1, y1, z1, x2, y2, z2);

    int dx, dy, dz;
    dx = (int)((x2 - x1) / granularity);
    dy = (int)((y2 - y1) / granularity);
    dz = (int)((z2 - z1) / granularity);

    float x_interval = (float)(x2 - x1) / (float)dx;
    float y_interval = (float)(y2 - y1) / (float)dy;
    float z_interval = (float)(z2 - z1) / (float)dz;

    int total = dx * dy * dz;
    printf("Number of pixels: %d\n", total);
//    const dim3 blockSize(TX, TY);
//    const dim3 gridSize(divUp(total, TX), divUp(len, TY));
//
        
//
//    CudaSafeCall(cudaMallocManaged(&density, total * sizeof(int)));
    density = new int[total];
    
//
//    int* d_mutex = 0;
//    CudaSafeCall(cudaMallocManaged((void**)&d_mutex, total * sizeof(int)));
//    CudaSafeCall(cudaMemset(d_mutex, 0, total * sizeof(int)));
//
//    countDensityKernel << <gridSize, blockSize >> > (density, dx, dy, dz, d_pc, len, x1, y1, z1, x2, y2, z2, radius, d_mutex);
//    CudaCheckError();
//    CudaSafeCall(cudaDeviceSynchronize());
//
//
//    printf("dx=%d,dy=%d,dz=%d, intervals=(%f,%f,%f)\n", dx, dy, dz, x_interval, y_interval, z_interval);
//#if 1
//    //Ð´½øÎÄ¼þ
//    char filename[50], filename1[50], filename2[50];
//    char filename3[50], filename4[50];
//
//    sprintf_s(filename, "%s.csv", srcfilename.c_str());
//    sprintf_s(filename1, "%s.raw", srcfilename.c_str());
//    sprintf_s(filename2, "%s.mhd", srcfilename.c_str());
//    sprintf_s(filename3, "%s.points", srcfilename.c_str());
//    sprintf_s(filename4, "%s.settings", srcfilename.c_str());
//
//    ofstream file, file1;
//    file.open(filename);
//    file1.open(filename1, ios::binary);
//    file << "x,y,z,density" << endl;
//    for (int pixel_index = 0; pixel_index < total; pixel_index++)
//    {
//        int zi = pixel_index % dz;
//        int yi = (pixel_index / dz) % dy;
//        int xi = pixel_index / (dz * dy);
//        float x = x1 + (float)(x2 - x1) / (float)dx * xi;
//        float y = y1 + (float)(y2 - y1) / (float)dy * yi;
//        float z = z1 + (float)(z2 - z1) / (float)dz * zi;
//        //file<<x<<","<<y<<","<<z<<","<<density[pixel_index]<<endl;
//        file << xi << "," << yi << "," << zi << "," << density[pixel_index] << endl;
//    }
//
//    for (int k = 0; k < dz; k++)
//    {
//        for (int j = 0; j < dy; j++)
//        {
//            for (int i = 0; i < dx; i++)
//            {
//                int pixel_index = i * dy * dz + j * dz + k;
//                unsigned short d = (unsigned short)density[pixel_index];
//                file1.write((const char*)&d, sizeof(unsigned short));
//            }
//        }
//    }
//    //76,140,21,7
//
//    file.close();
//    file1.close();
//
//    ofstream file2;
//    file2.open(filename2);
//    file2 << "ObjectType = Image" << endl;
//    file2 << "NDims = 3" << endl;
//    file2 << "BinaryData = True" << endl;
//    file2 << "BinaryDataByteOrderMSB = False" << endl;
//    file2 << "CompressedData = False" << endl;
//    file2 << "TransformMatrix = -1 0 0 0 1 0 0 0 -1" << endl;
//    file2 << "Offset = 0 0 0" << endl;
//    file2 << "CenterOfRotation = 0 0 0" << endl;
//    file2 << "AnatomicalOrientation = LAS" << endl;
//    file2 << "ElementSpacing = " << xstretch << " " << ystretch << " " << zstretch << endl;
//    file2 << "ITK_InputFilterName = MetaImageIO" << endl;
//    file2 << "DimSize = " << dx << " " << dy << " " << dz << endl;
//    file2 << "ElementType = MET_SHORT" << endl;
//    file2 << "ElementDataFile = " << filename1 << endl;
//
//
//    file2.close();
//#endif
//
//    ofstream file3;
//    file3.open(filename3);
//    for (float3 v : pc)
//    {
//        float x, y, z;
//        //x = (v.x - x1) / granularity;
//        //y = (v.y - y1) / granularity;
//        //z = (v.z - z1) / granularity;
//        x = v.x;
//        y = v.y;
//        z = v.z;
//        file3 << x << "," << y << "," << z << std::endl;
//    }
//
//
//    file3.close();
//
//    ofstream file4;
//    file4.open(filename4);
//    file4 << x1 << "," << y1 << "," << z1 << std::endl;
//    file4 << x2 << "," << y2 << "," << z2 << std::endl;
//    file4 << radius << "," << granularity << std::endl;
//    file4.close();
//
//    float3 centroid = make_float3(0.5 * (box.min().x + box.max().x),
//        0.5 * (box.min().y + box.max().y),
//        0.5 * (box.min().z + box.max().z));
//    //float3 origin = make_float3(-2200,1098,2210);
//    float3 origin = make_float3(500, 2300, 2210);
//    //float3 origin=make_float3(600,1100,4300);
//    float3 unitY = make_float3(0, 1, 0);
//
//    fprintf(stderr, "Centroid: (%f,%f,%f)\n", centroid.x, centroid.y, centroid.z);
//
//
//    CudaSafeCall(cudaFree(density));
std::mutex mtx;
std::thread* thds[100];
    for (int i = 0; i < 100; i++) {
        thds[i]=new std::thread([i, &mtx]() {
            for (int j = 0; j < 100; j++) {
                std::lock_guard<std::mutex> lock(mtx);
                std::cout << "(" << i << "," << j << ")" << std::endl;
            }
        });
    }
    char c;
    std::cin >> c;
    delete[] density;
//    CudaSafeCall(cudaFree(d_pc));
//
    return 0;
}
