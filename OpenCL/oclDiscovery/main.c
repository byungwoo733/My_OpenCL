#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h> // Header files

// Get num of Platforms
int main()
{
    cl_int status;
    cl_uint platforms_num;
    status = clGetPlatformIDs(0, NULL, &platforms_num);

    // Get all Platforms
    cl_platform_id* platforms=NULL;
    platforms = (cl_platform_id*)malloc(platforms_num*sizeof(cl_platform_id));
    status = clGetPlatformIDs(platforms_num, platforms, NULL);

    // Print platform name and vendor for each platform.
    for(cl_uint idx=0; idx<platforms_num;idx++){
        char buf[1000];

        // Print platform name and vendor
        status = clGetPlatformInfo(platforms[idx],CL_PLATFORM_NAME,
                                   sizeof(buf),buf,NULL);
        printf("PLATFORM_NAME:%s\n", buf);
        status = clGetPlatformInfo(platforms[idx],CL_PLATFORM_VENDOR,
                                   sizeof(buf), buf,NULL);
        printf("PLATFORM_VENDOR: %s\n",buf);

        // Get num of devices of the given platform
        cl_uint devices_num;
        status = clGetDeviceIDs(platforms[idx], CL_DEVICE_TYPE_ALL,
                                0, NULL, &devices_num);

        // Get all devices
        cl_device_id* devices=NULL;
        devices = (cl_device_id*)malloc(devices_num*sizeof(cl_device_id));
        status = clGetDevicesIDs(platforms[idx], CL_DEVICE_TYPE_ALL,
                                 devices_num,devices, NULL);

        for (cl_uint idy=0; idy<devices_num;idy++){ // Print device name, vendor, and types for each device.
            //Device name and type
            status = clGetDeviceInfo(devices[idy], CL_DEVICE_NAME,
                                     sizeof(buf),buf,NULL);
            printf("DEVICE_NAME: %s\n",buf);
            status = clGetDeviceInfo(devices[idy], CL_DEVICE_VENDOR,
                                     sizeof(buf),buf,NULL);
            printf("DEVICE_VENDOR:%s\n",buf);
            cl_device_type type;
            status = clGetDeviceInfo(devices[idy], CL_DEVICE_TYPE,
                                     sizeof(type),&type,NULL);

            if(type & CL_DEVICE_TYPE_CPU)
                printf("DEVICE_TYPE: %s\n", "CL_DEVICE_TYPE_CPU");
            if(type & CL_DEVICE_TYPE_GPU)
                printf("DEVICE_TYPE: %s\n", "CL_DEVICE_TYPE_GPU");
            if(type & CL_DEVICE_TYPE_ACCELERATOR)
                printf("DEVICE_TYPE: %s\n", "CL_DEVICE_TYPE_ACCELERATOR");
            if(type & CL_DEVICE_TYPE_DEFAULT)
                printf("DEVICE_TYPE: %s\n", "CL_DEVICE_TYPE_DEFAULT");
        }
        free(devices); // Do not forget to free dynamically allocated memory
    }
    free(platforms); // Do not forget to free dynamically allocated memory

    return 0;
}

/* OpenCL Data Type (built-in scalar) - ISO/IEC 9899:1999 (C99)
bool
char, uchar : cl_char, cl_uchar // 8-bit integer
short, ushort : cl_short, cl_ushort // 16-bit integer
int, uint : cl_int, cl_uint //32-bit integer
long, ulong : cl_long, cl_ulong //64-bit integer
float : cl_float // 32-bit float(single)
double : cl_double // 64-bit float(double)
half : cl_half // 16-bit float(half)

IEEE 754 single precision
IEEE 754 double precision
IEEE 754-2008 half precision
*/
