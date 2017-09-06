#include <OpenCL/opencl.h>
#include <iostream>
using namespace std;

void PrintDeviceInfo(cl_device_id device)
{
  char queryBuffer[1024];
  int queryInt;
  cl_int clError;
  clError = clGetDeviceInfo(device, CL_DEVICE_NAME,
    sizeof(queryBuffer),
    &queryBuffer, NULL);
  printf("    CL_DEVICE_NAME: %s\n", queryBuffer);
  queryBuffer[0] = '\0';
  clError = clGetDeviceInfo(device, CL_DEVICE_VENDOR,
    sizeof(queryBuffer), &queryBuffer,
    NULL);
  printf("    CL_DEVICE_VENDOR: %s\n", queryBuffer);
  queryBuffer[0] = '\0';
  clError = clGetDeviceInfo(device, CL_DRIVER_VERSION,
    sizeof(queryBuffer), &queryBuffer,
    NULL);
  printf("    CL_DRIVER_VERSION: %s\n", queryBuffer);
  queryBuffer[0] = '\0';
  clError = clGetDeviceInfo(device, CL_DEVICE_VERSION,
    sizeof(queryBuffer), &queryBuffer,
    NULL);
  printf("    CL_DEVICE_VERSION: %s\n", queryBuffer);
  queryBuffer[0] = '\0';
  clError = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS,
    sizeof(int), &queryInt, NULL);
  printf("    CL_DEVICE_MAX_COMPUTE_UNITS: %d\n", queryInt);
  queryBuffer[0] = '\0';
  clError = clGetDeviceInfo(device, CL_KERNEL_WORK_GROUP_SIZE,
    sizeof(int), &queryInt, NULL);
  printf("    CL_KERNEL_WORK_GROUP_SIZE: %d\n", queryInt);
}

int main(void)
{
    int                 lError;
    cl_uint             lGPUCount   = 10;
    cl_device_id        lDeviceId[10];
    lError = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_ALL, lGPUCount, lDeviceId, &lGPUCount);
    //cout << "lError = " << lError << endl;
    for( cl_uint lGPUIndex = 0; lGPUIndex < lGPUCount; lGPUIndex++ )
    {
        cout << lGPUIndex << " Device Id " << lDeviceId[lGPUIndex] << endl;
        { // New scope.
            size_t lResult = 0;
            if (CL_SUCCESS == clGetDeviceInfo(lDeviceId[lGPUIndex], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(lResult), &lResult, NULL))
            {
                cout << "    Workgroup size = " << lResult << endl;
            }
            else
            {
                cerr << "    Unable to retrieve workgroup size!" << endl;
            }
        }
        { // New scope.
            cl_device_type lResult = 0;
            if (CL_SUCCESS == clGetDeviceInfo(lDeviceId[lGPUIndex], CL_DEVICE_TYPE, sizeof(lResult), &lResult, NULL))
            {
                switch (lResult)
                {
                    case CL_DEVICE_TYPE_CPU:
                        cout << "    Device type = CPU (" << lResult << ")" << endl;
                        break;
                    case CL_DEVICE_TYPE_GPU:
                        cout << "    Device type = GPU (" << lResult << ")" << endl;
                        break;
                    case CL_DEVICE_TYPE_ACCELERATOR:
                        cout << "    Device type = ACCELERATOR (" << lResult << ")" << endl;
                        break;
                    case CL_DEVICE_TYPE_DEFAULT:
                        cout << "    Device type = DEFAULT (" << lResult << ")" << endl;
                        break;
                    default:
                        cout << "    Device type = UNKNOWN (" << lResult << ")" << endl;
                        break;
                }
				PrintDeviceInfo(lDeviceId[lGPUIndex]);
            }
            else
            {
                cerr << "    Unable to retrieve device type!" << endl;
            }
        }
		cout << endl << endl;
    }
	cout << endl;
    return 0;
}
