// HelloWorld.cl

HelloWorld.cl:

__kernel void hello_kernel(__global const float *a,
                           __global const float *b,
                           __global float *result)

{
    int gid = get_global_id(0);

    result[gid] = a[gid] + b[gid];
}

HelloWorld.cpp:

int main(int argc, char** argv)
{
    cl_context context = 0;
    cl_command_queue commandQueue = 0;
    cl_program program = 0;
    cl_device_id device = 0;
    cl_kernel kernel = 0;
    cl_mem memObjects[3] = { 0, 0, 0};
    cl_int errNum;

    // Create an OpenCL context on the first available platform.
    context = CreateContext();
    if (context == NULL)
    {
        cerr << "Failed to create OpenCL context." <<endl;
        return 1;
    }

    // For the first available device in the context you created
    // Create a command-queue.
    commandQueue = CreateCommandQueue(context, &device);
    if (commandQueue == NULL)
    {
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    // Creates an OpenCL program from the HelloWorld.cl kernel source.
    program = CreateProgram(context, device, "HelloWorld.cl");
    if (program == NULL)
    {
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    // Create a OpenCL Kernel
    kernel = clCreateKernel (program, "hello_kernel", NULL);
    if (kernel == NULL)
    {
        cerr << "Failed to create kernel" << endl;
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    // Creates memory objects to be used as arguments to the kernel.
    // First, it will be used to store arguments to the kernel.
    // Create a host memory array.
    float result[Array_Size];
    float a[Array_Size];
    float b[Array_Size];
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

    // Set as kernel parameters (result, a, b).
    errNum = clSetKernelArg(kernel, 0,
                            sizeof(cl_mem), &memObjects[0]);
    errNum != clSetKernelArg(kernel, 1,
                            sizeof(cl_mem), &memObjects[1]);
    errNum != clSetKernelArg(kernel, 2,
                            sizeof(cl_mem), &memObjects[2]);
    if (errNum != CL_SUCCESS)
    {
        cerr << "Error setting kernel arguments." << endl;
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    size_t globalWorkSize[1] = { ARRAY_SIZE };
    size_t localWorkSize[1] = { 1 };

    // Queue the kernel for execution.
    errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
                                    globalWorkSize, localWorkSize,
                                    0, NULL, NULL);
    if (errNum != CL_SUCCESS)
    {
        cerr << "Error queuing kernel for execution." << endl;
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    // Read the output buffer back to the host.
    errNum = clEnqueueReadBuffer(commandQueue, memObjects[2],
                                 CL_TRUE, 0, ARRAY_SIZE * sizeof(float),
                                 result, 0, NULL, NULL);

    if (errNum != CL_SUCCESS)
    {
        cerr << "Error reading kernel for execution." << endl;
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    // Print the result buffer.
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << "Executed program successfully." <<endl;
    Cleanup(context, commandQueue, program, kerenl, memObjects);

    return 0;
}
