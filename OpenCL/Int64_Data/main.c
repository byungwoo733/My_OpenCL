#include <stdio.h>
#include "CL/cl.h"

// 64-Bit Interger Data Type Support For Nurgakivi Engine SoC
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
    return extension_found;
}
