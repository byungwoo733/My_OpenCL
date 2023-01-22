#include <CL/cl.h>
#include <CL/opencl.h>

HelloWorld.cl:
    _kernel void hello_kernel(_global const float *a,
                              _global const float *b,
                              _global float *result)

{
    int gid = get_global_id(0);

    result[gid] = a[gid] + b[gid];
}

HelloWorld.cpp:

int main (int argc, char** argv)
{
    cl_context context =0;
    cl_commmand_queue commandQueue = 0;
    cl_program program = 0;
    cl device_id device = 0;
    cl_kernel kernel = 0;
    cl_mem memObjects[3] ={0,0,0};
    cl_int errNum;

    // Create OpenCL Text First Using Enable Platform
    context = CreateContext();
    if(context == NULL)
    {
        cerr << "Failed to create OpenCL context." << endl;
        return 1;
}

// about First Enable Device from OpenCL Text
// Create Instruction Queue
commandQueue = CreateCommandQueue(context, &device);
if (commandQueue == NULL)
{
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

// Create OpenCL Program from HelloWorld.cl Kernel source
program = CreateProgram(context, device, "HelloWorld.cl");
if(program == NULL)
{
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

// Create OpenCL Kernel
kernel = clCreateKernel(program, "hello_kernel", NULL);
if(kernel == NULL)
{
    cerr << "Failed to create kernel" << endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}


// Create Usage Memory Object in Kernel
// Firstly, Saving Factors about Kernel
// Create Host Memory Array
float result[ARRAY_SIZE];
float a[ARRAY_SIZE];
float b[ARRAY_SIZE];
for (int i = 0; i < ARRAY_SIZE; i++)
{
    a[i] = i;
    b[i] = i * 2;
}

if (!CreateMemObjects(context, memObjects, a, b))
{
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

// Setting to Kernel Factor
errNum = clSetKernelArg(kernel, 0,
                        sizeof(cl_mem), &memObjects[0]);
errNum = clSetKernelArg(kernel, 1, sizeof(cl.mem),
                        &memObjects[1]);
errNum = clSetKernelArg(kernel, 2, sizeof(cl.mem),
                        &memObjects[2]);
if (errNum != CL_SUCCESS)
{
    cerr << "Error setting kernel arguments." << endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

size_t globalWorkSize[1] = {ARRAY_SIZE};
size_t localWorkSize[1] = { 1 };

// Put in Queue for Running
errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);

if (errNum != CL_SUCCESS)
{
    cerr << "Error queuing kernel for execution." endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

// Out Buffer to Host Read Again
errNum = clEnqueueReadBuffer(commandQueue, memObjects[2],
                             CL_TRUE, 0, ARRAY_SIZE * sizeof(float),
                             result, 0, NULL, NULL);
                             )
if (errNum != CL_SUCCESS)
{
    cerr << "Error reading result buffer." << endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

// Result Buffer Output
for (int i = 0; i < ARRAY_SIZE; i++)
{
    cout << result[i] << " ";
}
cout << endl
cout << "Executed program successfully." << endl;

Cleanup (context, commandQueue, program, kernel, memObjects);

return 0;

}


// Platform Choice & Context create
cl_context CreateContext()
{
    cl_int errNum;
    cl_uint numPlatforms;
    cl_platform_id firstPlatformId;
    cl_context context = NULL;

    //First, Running OpenCL Platform Choice
    // this example, We simply First Usage Platform Choice
    // Generally, Asking about Available All Platform
    // The Most Available Platform Choice

    errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
    if (errNum != CL_SUCCESS || numPlatforms <= 0)
    {
        cerr << "Failed to find any OpenCL platforms." << endl;
        return NULL;
    }
    // Next, create OpenCL Context From Platform
    // GPU Based Context Create Trying, if it fails,
    // CPU Based Contest Create Trying
    cl_context_properties contextProperties[] =
    {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)firstPlatformId,
        0
    };
    context = clCreateContextFromType (contextProperties,
                                       CL_DEVICE_TYPE_GPU,
                                       NULL, NULL, &errNum);
    if (errNum != CL_SUCCESS)
    {
        cout << "Could not create GPU context, trying CPU..."
        << endl;
        context = clCreateContextFromType(contextProperties,
                                          CL_DEVICE_TYPE_CPU,
                                          NULL, NULL, &errNum);
        if (errNum != CL_SUCCESS)
        {
            cerr <<
            "Failed to create an OpenCL GPU or CPU context.";
            return NULL;
        }
    }

    return context;
}

// Device Choice, Create Command Queue
cl_command_queue CreateCommandQueue (cl_context context,
                                     cl_device_id *device)
{
    cl_int errNum;
    cl_device_id *devices;
    cl_command_queue commandQueue = NULL;
    size_t deviceBufferSize = -1;

    // First, Device Buffer Size Calculation
    errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL,
                              &deviceBufferSize);
    if (errNum != CL_SUCCESS)
    {
        cerr << "Failed call to
                clGetContextInfo(...,GL_CONTEXT_DEVICES,...)";
                return NULL;
    }

    if (deviceBufferSize <= 0)
    {
        cerr << "No devices available.";
        return NULL;
    }

    // Memory Assign about Device Buffer
    devices = new cl_device_id[deviceBufferSize /
                                sizeof(cl_device_id)];
    errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES,
                              devicesBufferSize, devices, NULL);
    if (errNum != CL_SUCCESS)
    {
        cerr << "Failed to get device IDs";
        return NULL;
    }

    // We simply choice First Available Device in This example
    // All Available Devices uses in Real Program,
    // OpenCL Device Asking Based The Best Performance Device Choice

    commandQueue = clCreateCommandQueue (context,
                                         devices[0], 0, NULL);
    if (commandQueue == NULL)
    {
        cerr << "Failed to create commandQueue for device 0";
        return NULL;
    }
    *device = devices[0];
    delete [] devices;
    return commandQueue;
}

// Kernel Source Stack & Program Object Build From DISC
cl_program CreateProgram(cl_context context, cl_device_id device,
                         const char* fileName)
{
    cl_int errNum;
    cl_program program;

    ifstream kernelFile(fileName, ios::in);
    if (!kernelFile.is_open())
    {
        cerr << "Failed to open file for reading: " << fileName << endl;
        return NULL;
    }

    ostringstream oss;
    oss << kernelFile.rdbuf();

    string srcStdStr = oss.str();
    const char *srcStr = srcStdStr.c_str();
    program = clCreateProgramWithSource(context, 1, (const char**)&srcStr, NULL, NULL);
    if (program == NULL)
    {
        cerr << "Failed to create CL program from source." << endl;
        return NULL;
    }

    errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (errNum != CL_SUCCESS)
    {
        // Decide Reason about Error.
        char buildLog[16834];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
                              sizeof(buildLog), buildLog, NULL);

        cerr << "Error in kernel: " << endl;
        cerr << buildLog;
        clReleaseProgram(program);
        return NULL;
    }

    return program;
}

// OpenCL Kernel Create
kernel = clCreateKernel (program, "hello_kernel", NULL);
if (kernel == NULL);
{
    cerr << "Failed to create kernel" << endl;
    Cleanup (context, commandQueue, program, kernel, memObjects);
    return 1;
}

// Create Using Memory Object to Parameter About Kernel
// Firstly, Using for Kernel Parameter Saving
// Host Memory Array Create
float result[ARRAY_SIZE];
float a[ARRAY_SIZE];
float b[ARRAY_SIZE];
for (int i = 0; i < ARRAY_SIZE; i++)
{
    a[i] = (float)i;
    b[i] = (float(i * 2);
}

if (!CreateMemObjects(context, memObjects, a, b))
{
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

// Memory Object Create
bool CreateMemObjects(cl_context context, cl_mem memObjects[3],
                      float *a, float *b)
{
    memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY |
                                   CL_MEM_COPY_HOST_PTR,
                                   sizeof(float) *ARRAY_SIZE, a, NULL);
    memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY |
                                   CL_MEM_COPY_HOST_PTR,
                                   sizeof(float) *ARRAY_SIZE, b, NULL);
    memObjects[2] = clCreateBuffer(context, CL_MEM_READ_ONLY |
                                   CL_MEM_COPY_HOST_PTR,
                                   sizeof(float) *ARRAY_SIZE, NULL, NULL);

    if (memObjects[0] == NULL || memObjects[1] == NULL ||
        memObjects[2] == NULL)
    {
        cerr << "Error creating memory objects." << endl;
        return false;
    }

    return true;
}

// Running Kernel
// Kernel Parameter (result, a, b) Setting
errNum = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);
errNum |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &memObjects[2]);
if (errNum != CL_SUCCESS)
{
    cerr << "Error setting kernel arguments." << endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

size_t globalWorkSize[l] = {ARRAY_SIZE};
size_t localWorkSize[l] = { 1 };

// Put kernel in Queue for Running
errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
                                globalWorkSize, localWorkSize,
                                0, NULL, NULL);
if (errNum != CL_SUCCESS)
{
    cerr << "Error queuing kernel for execution." << endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

// Output Buffer Read to Host
errNum = clEnqueueReadBuffer(commandQueue, memObjects[2],
                             CL_TRUE,0,
                             ARRAY_SIZE * sizeof(float, result,
                             0, NULL, NULL);
if (errNum != CL_SUCCESS)
{
    cerr << "Error queuing kernel for execution." << endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
}

// Result Buffer Output
for(int i = 0; i < ARRAY_SIZE; i++)
{
    cout << result[i] << " ";
}










/*
// We choice First Enable Device simply in this example
// it use All Devices in Real Program or OpenCL Device Asking Based We will choice The Best Device.

commandQueue = clCreateCommandQueue(context, device[0], 0, NULL);
if (commandQueue == NULL)
{
    cerr << "Failed to create commandQueue for device 0";
    return NULL;
}
*/


