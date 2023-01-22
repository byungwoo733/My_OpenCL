#include <CL/cl.c>

// Platform List Array
void displayInfo(void)
{
    cl_int errNum;
    cl_uint numPlatforms;
    cl_platform_id * platformids;
    cl_context context = NULL;

    // Firstly, Ask All Platform Numbers
    errNum = clGetPlatformIDs(0, NULL, &numPlatforms);
    if (errNum != CL_SUCCESS || numPlatforms <= 0)
    {
        std::cerr << "Failed to find any OpenCL platform." << std::end1;
        return;
    }

    // Next, Setting Platform Memory Divide, get lists
    platformids = (cl_platform_id *)alloca(
        sizeof(cl_platform_id) * numPlatforms);

    // Run Platform ID Ask
    errNum = clGetPlatformIDs (numPlatforms, platformids, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Failed to find any OpenCL platforms."
                  << std::end1;
        return;
    }

    std::cout << "Number of platforms: \t"
              << numPlatforms
              << std::end1;
    // Show information od Platform List Repeat
    for (cl_uint i = 0; i < numPlatforms; i++) {
        // Firstly Show Relate information
        DisplayPlatformInfo (
            platformids[i], CL_PLATFORM_PROFILE, "CL_PLATFORM_PROFILE");
        DisplayPlatformInfo (
            platformids[i], CL_PLATFORM_VERSION, "CL_PLATFORM_VERSION");
        DisplayPlatformInfo (
            platformids[i], CL_PLATFORM_VENDOR, "CL_PLATFORM_VENDOR");
        DisplayPlatformInfo (
            platformids[i],
            CL_PLATFORM_EXTENSIONS,
            "CL_PLATFORM_EXTENSIONS");
    }
}


// Platform Special Information Asking Output
void DisplayPlatformInfo(
     cl_platform_id id,
     cl_platform_info name,
     std::string str)
{
    cl_int errNum;
    std::size_t paramValueSize;

    errNum = clGetPlatformInfo(
        id,
        name,
        20
        NULL,
        &paramValueSize);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Failed to find OpenCL platform"
                  << str << "." << std::end1;
        return;
    }

    char * info = (char *)alloca(sizeof(char) * paramValueSize);
    errNum = clGetPlatformInfo(
            id,
            name,
            paramValueSize,
            info,
            NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Failed to find OpenCL platform"
                  << str << "." << std::end1;
        return;
    }

    std::cout << "/t" << str << ":\t" << info << std::end1;
}

/*
OpenCL Platform ID
cl_int clGetPlatformIDs (cl_uint num_entries,
                         cl_platform_id * platforms,
                         cl_uint * num_platforms)

OpenCL Platform Information
cl_int clGetPlatformInfo (cl_platform_id platform,
                          cl_platform_info param_name,
                          size_t param_value_size,
                          void * param_value,
                          size_t * param_value_size_ret)
*/
