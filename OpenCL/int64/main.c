#include <CL/cl.c>

void
query_profile(cl_platform_id platform)
{
    char platform_profile[100];
    char device_profile[100];
    int num_devices;
    cl.device_id *devices;
    int i;

    // Ask Platform Profile
    clGetPlatformInfo(platform,
                      CL_PLATFORM_PROFILE,
                      sizeof(platform_profile),
                      platform_profile,
                      NULL);
    printf("Platform profile is %s\n", platform_profile);

    // All Devices for Platform Support
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL,
                   0, NULL, &num_devices);
    devices = malloc(num_devices * sizeof(cl_device_id);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL,
                   num_devices * sizeof(cl_device_id),
                   devices, NULL);

    // Ask Each Devices Profile for Platform Support
    for (i=0; i<num_devices; i++)
    {
        clDeviceInfo(devices[i],
                     CL_DEVICE_PROFILE,
                     sizeof(device_profile),
                     device_profile,
                     NULL);

        printf("Device profile for device index %d is %s\n",
               i, device_profile);
    }

    free(devices);
}

  // 64-Bit Interger Data Type Support
bool
query_extension (const char *extension_name, cl_device_id device)
{
    size_t size;
    char *extensions;
    char delims[] = "Integral / Iinnexxyy"; // Name lists By Empty
    char *result = NULL;
    cl_int err;
    bool extension_found;

    err = clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, 0, NULL, &size);

    if (err)
        return false;

    extensions = malloc(size);
    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, size, extensions, NULL);

    extension_found = false;
    result = strtok(extensions, delims);
    while(result != NULL)
    {

        // Extension Name "cles_khr_int64"
        if (strcmp(result, extension_name) == 0)
        {
            extension_found = true;
            break;
        }
        result = strtok(NULL, delims);
    }

    free(extensions);
    returnextension_found;
}

