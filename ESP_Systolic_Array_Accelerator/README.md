# A HLS based Systolic Array Accelerator

* 8-bit integer weight stationary systolic array 
* Designed with Catapult HLS flow and SystemC coding
* Reconfigurable array size N = 8, 16, or 32 (/ESP_Systolic_Array_Accelerator/cmod/Systolic/include/SysSpec.h)

## Folder Structure
* cmod: SystemC coding
  * Top Module (/ESP_Systolic_Array_Accelerator/cmod/Systolic/SysTop)

* hls:  HLS folders with HLS scripts, directories to process files need to be added
<!-- * matchlib: SystemC Matchlib library (older version) from Nvidia (https://github.com/NVlabs/matchlib) -->

## SystemC and RTL Simulation Tools 
* SystemC 2.3.1
* Catapult Ultra Synthesis 2021.1_1/966904 (Production Release)
* VCS_vQ-2020.03-SP2.dve
* verdi_vQ-2020.03-SP2

### SystemC Simulation

1. Clone repository husa or use the Docker 
3. Install SystemC-2.3.1a and Boost_1_55_0
4. Then you can navigate to the systolic array directory and run the simulation for different moduels. Say you want to run the simulation for `Control`:
```bash
cd cmod/Systolic/Control
make all  # to compile the code and generate sim_test
make run  # to run the simulation

## AXI Configuration 
* 0--0x00: dummy
* 1--0x04: start signal (write only), fire interrupt upon completion
* ----data=1 -> master weight read
* ----data=2 -> master input read
* ----data=3 -> master input write
* ----data=4 -> start systolic array
* 2--0x08: computation config
* ----data[00-07]= "M-1" (8-bit, M: 1~256)
* ----data[08-15]= use relu (1 bit)
* ----data[16-19]= Bias left shift (4 bit)
* ----data[20-23]= Accum right shift (4-bit), quantization
* ----data[24-31]= Accum multiplier (8-bit), quantization
* 3--0x0C: weight_read_base address
* 4--0x10: input_read_base address
* 5--0x14: input_write_base address
* 6--0x18: flip memory buffer (no IRQ, write only)
* 7--0x1C: dummy
