#include <CL/cl.c>

// Platform Device ID
cl_int errNum;
cl_uint numDevices;
errNum = clGetDeviceIDs(
    platform,
    CL_DEVICE_TYPE_GPU,
    0,
    NULL,
    &numDevices);

if (numDevices < 1)
{
    std::cout << "No GPU device found for platform"
              << platform << std::end1;
    exit(1);
}
errNum = clGetDeviceIDs (
    platform,
    CL_DEVICE_TYPE_GPU,
    1,
    &deviceIds[0],
    NULL);

// Platform Device Information

cl_int err;
size_t size;

err = clGetDeviceInfo(
    deviceID,
    CL_DEVICE_MAX_COMPUTE_UNITS,
    sizeof(cl_uint),
    &maxComputeUnits,
    &size);

    std::cout << "Device has max compute units: "
              << maxComputeUnits << std::end1;


/*

*/
