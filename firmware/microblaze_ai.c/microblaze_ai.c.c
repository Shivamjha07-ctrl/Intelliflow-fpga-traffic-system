#include <stdio.h>
#include <xparameters.h>
#include <xgpio.h>
#include <xil_io.h>
#include <sleep.h>

#define TRAFFIC_AXI_BASEADDR   XPAR_TRAFFIC_AXI_SLAVE_0_S_AXI_BASEADDR

XGpio Gpio;

int main()
{
    u32 sensors;
    u8 density_M1, density_M2, density_S;
    u8 emergency, pedestrian, night_mode;

    XGpio_Initialize(&Gpio, XPAR_AXI_GPIO_0_DEVICE_ID);
    XGpio_SetDataDirection(&Gpio, 1, 0xFFFFFFFF);

    u32 m1_history[4] = {0, 0, 0, 0};
    u8 hist_idx = 0;
    u32 avg_M1;

    while(1)
    {
        sensors = XGpio_DiscreteRead(&Gpio, 1);
        density_M1  = sensors & 0x3;
        density_M2  = (sensors >> 2) & 0x3;
        density_S   = (sensors >> 4) & 0x3;
        emergency   = (sensors >> 6) & 0x1;
        pedestrian  = (sensors >> 7) & 0x1;
        night_mode  = (sensors >> 8) & 0x1;

        m1_history[hist_idx] = density_M1;
        hist_idx = (hist_idx + 1) % 4;
        avg_M1 = (m1_history[0] + m1_history[1] + m1_history[2] + m1_history[3]) >> 2;

        u32 w1 = 2, w2 = 1, w3 = 1, max_g = 15;
        if (avg_M1 >= 2) {
            w1 = 3; w2 = 1; w3 = 1;
        }
        if (avg_M1 == 3) {
            w1 = 4; w2 = 1; w3 = 0;
        }

        Xil_Out32(TRAFFIC_AXI_BASEADDR + 0x00, w1);
        Xil_Out32(TRAFFIC_AXI_BASEADDR + 0x04, w2);
        Xil_Out32(TRAFFIC_AXI_BASEADDR + 0x08, w3);
        Xil_Out32(TRAFFIC_AXI_BASEADDR + 0x0C, max_g);

        xil_printf("Density M1: %d, Avg: %d, Weights: %d,%d,%d\n", density_M1, avg_M1, w1, w2, w3);

        sleep(1);
    }

    return 0;
}