#include <stdio.h>
#include <stdlib.h>

int main()
{
    void stage_cu()
{
   // Writing instruction memory
   Xil_Out32(0x50001004, 0);
   Xil_Out32(0x50001000, 0xBE820404);
   Xil_Out32(0x50001004, 4);
   Xil_Out32(0x50001000, 0xBF810000);

   // Writing SGPRs for wavefront 1
   Xil_Out32(0x50002004, 0);
   Xil_Out32(0x50002008, 0x2A);
   Xil_Out32(0x5000200C, 0x18);
   Xil_Out32(0x50002010, 0xB);
   Xil_Out32(0x50002014, 0xE);
   Xil_Out32(0x50002000, 1);
   Xil_Out32(0x50002004, 16);
   Xil_Out32(0x50002008, 0x2C);
   Xil_Out32(0x5000200C, 0x8);
   Xil_Out32(0x50002010, 0x19);
   Xil_Out32(0x50002014, 0x2F);
   Xil_Out32(0x50002000, 1);
   Xil_Out32(0x50002004, 32);
   Xil_Out32(0x50002008, 0x1E);
   Xil_Out32(0x5000200C, 0x11);
   Xil_Out32(0x50002010, 0x0);
   Xil_Out32(0x50002014, 0x0);
   Xil_Out32(0x50002000, 1);

    return 0;
}
}
