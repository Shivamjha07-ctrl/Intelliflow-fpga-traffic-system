# Intelliflow FPGA Traffic System

AI-Assisted FPGA traffic management reference design: Verilog RTL, AXI4-configurable weights, MicroBlaze helper firmware, UART & VGA visualization.

## Highlights
- Adaptive green-time computation via [`sensor_fusion`](src/sensor_fusion.v/sensor fusion.txt) and AXI-configurable weights [`traffic_axi_slave`](src/traffic_axi_slave.v/traffic axi slave.txt).
- Trend detection with exponential moving average filters [`ema_filter`](src/ema_filter.v/ema filter.txt).
- Ultrasonic sensor interface and density decoding [`ultrasonic_sensor`](src/ultrasonic_sensor.v/ultra sonic sensor.txt).
- Top-level FPGA integration in [`final_top`](src/final_top.v/final_top.txt) (VGA, seven-seg, UART, traffic core).
- VGA rendering pipeline: [`vga_top`](src/vga_top.v/vga top.txt) → [`vga_sync`](src/vga_sync.v/vga_sync.txt) → [`vga_draw`](src/vga_draw.v/vga_draw.txt).
- UART transmitter for telemetry: [`uart_tx`](src/uart_tx.v/uart.txt).
- Seven-segment display multiplexer: [`seven_seg_mux`](src/seven_seg_mux.v/seven seg mux.txt).
- Power gating of FSM when idle: [`power_manager`](src/power_manager.v/power manager.txt).
- Clock divider utility: [`clock_divider`](src/clock_divider.v/clock divider.txt).

## Files & key modules
- Top-level: [`final_top`](src/final_top.v/final_top.txt)  
- Traffic controller core: [`Traffic_Light_Controller`](src/Traffic_Light_Controller.v/traffic light controller.txt)  
- Sensor processing: [`sensor_fusion`](src/sensor_fusion.v/sensor fusion.txt), [`ema_filter`](src/ema_filter.v/ema filter.txt)  
- I/O & peripherals: [`ultrasonic_sensor`](src/ultrasonic_sensor.v/ultra sonic sensor.txt), [`uart_tx`](src/uart_tx.v/uart.txt), [`seven_seg_mux`](src/seven_seg_mux.v/seven seg mux.txt)  
- VGA: [`vga_top`](src/vga_top.v/vga top.txt), [`vga_sync`](src/vga_sync.v/vga_sync.txt), [`vga_draw`](src/vga_draw.v/vga_draw.txt)  
- AXI slave config: [`traffic_axi_slave`](src/traffic_axi_slave.v/traffic axi slave.txt)  
- Utilities: [`power_manager`](src/power_manager.v/power manager.txt), [`clock_divider`](src/clock_divider.v/clock divider.txt)  
- FPGA constraints: [constraints/constraints_clean.xdc](constraints/constraints_clean.xdc/constraints clean xdc.txt) (Basys‑3 pinout)  
- MicroBlaze helper firmware: [firmware/microblaze_ai.c](firmware/microblaze_ai.c/microblaze_ai.c.c)  
- Testbenches: [tb/Traffic_Light_Controller_TB.v/traffic ligt controller tb.txt](tb/Traffic_Light_Controller_TB.v/traffic ligt controller tb.txt), [tb/Traffic_Light_Controller_TB.v/tb ultrasonic.sv.txt](tb/Traffic_Light_Controller_TB.v/tb ultrasonic.sv.txt)

## Quick start

Simulation (simple, using Icarus/Verilog simulator)
1. Add all RTL and the testbench files to your simulator.
2. Run the traffic controller testbench (example):
   - Use your simulator of choice and set the top-level testbench to the TB file in `tb/…`.
   - Observe waveforms or $display output from the testbenches.

FPGA (Vivado / Basys‑3)
1. Create a Vivado project and add sources:
   - Add RTL files listed above (start with [`final_top`](src/final_top.v/final_top.txt)).
2. Add constraints file:
   - Use [constraints/constraints_clean.xdc](constraints/constraints_clean.xdc/constraints clean xdc.txt) for Basys‑3 pin mapping.
3. Synthesize, implement and generate bitstream.
4. Program the board and run MicroBlaze helper firmware (optional):
   - Build and run [firmware/microblaze_ai.c](firmware/microblaze_ai.c/microblaze_ai.c.c) on a MicroBlaze or external controller to drive AXI weights.

Notes
- The AXI slave defaults provide sensible weights but can be updated at runtime via AXI writes ([`traffic_axi_slave`](src/traffic_axi_slave.v/traffic axi slave.txt)).
- VGA visuals run from [`vga_top`](src/vga_top.v/vga top.txt); seven-seg and UART modules provide local status telemetry.
- Testbenches are available under `tb/` for unit verification.

License
- See repository root. (No explicit license file included; add one if needed.)

