/* Weight setup with master port to
 * actively request data from other memory
 * --master read request is triggered by controller
 * --no master write request
 */

#ifndef __WEIGHT_AXI_H__
#define __WEIGHT_AXI_H__

#include <nvhls_connections.h>
#include <nvhls_int.h>
#include <nvhls_vector.h>
#include <systemc.h>

#include "../include/AxiSpec.h"
#include "../include/SysSpec.h"

SC_MODULE(WeightAxi) {
  const static int N = spec::N;
  // number of read for (DATA_WIDTH) 128-bit axi,
  // should be smaller than maxBurstSize
  //
  // (N byte >> 3)*(N+1) row,
  //   N rows of weight and 1 row of bias
  // N = 32 => 132 => 131
  // N = 16 => 34  => 33
  // N = 8  => 9   => 8

  // append -1 to match Axi Len format
  //  # of data = AxLEN[7:0] + 1
  //  rd_len should not exceed 255 (MAX_BURST_SIZE)
  // Currently only support 1 burst read
  const static int rd_len = (spec::N) * (spec::N + 1) / (DATA_WIDTH / 8) - 1;

public:
  sc_in_clk clk;
  sc_in<bool> rst;

  // Axi Master Interface
  typename spec::AxiData::axi4_data::read::template master<> if_data_rd;
  typename spec::AxiData::axi4_data::write::template master<> if_data_wr;

  // 32 bit start signal to indicate base address
  Connections::In<NVUINT32> start; // start with base_addr
  Connections::Out<spec::InputType>
      weight_in_vec[N];          // output weight_in_vec or systolic array
  Connections::Out<bool> rd_IRQ; // rd_IRQ -> IRQ[0]

  typename spec::AxiData::axi4_data::AddrPayload addr_pld;
  typename spec::AxiData::axi4_data::ReadPayload data_pld;

  SC_HAS_PROCESS(WeightAxi);
  WeightAxi(sc_module_name name_)
      : sc_module(name_), if_data_rd("if_data_rd"), if_data_wr("if_data_wr") {
    SC_THREAD(WeightAxiRun);
    sensitive << clk.pos();
    NVHLS_NEG_RESET_SIGNAL_IS(rst);
  }

  void WeightAxiRun() {
// Reset
#pragma hls_unroll yes
    for (int i = 0; i < N; i++) {
      weight_in_vec[i].Reset();
    }
    start.Reset();
    if_data_rd.reset();
    if_data_wr.reset();
    rd_IRQ.Reset();

    while (1) {
      NVUINT32 base_addr;
      base_addr = start.Pop(); // Start signal with base addr

      // Master read request if_data_read.ar push
      addr_pld.addr = base_addr; // (1) base addr
      addr_pld.len = rd_len;     // (2) read length

      // Blocking Push
      if_data_rd.ar.Push(addr_pld);

      NVUINT4 col_ctr = 0; // col counter

      // Needs to ensure that we can recieve weight every cycle
#pragma hls_pipeline_init_interval 1
      for (int i = 0; i <= rd_len; i++) {
        data_pld = if_data_rd.r.Pop(); // pop for each received data

        // cout << hex << data_pld.data << endl;
        // when N >= DATA_WIDTH / 8, needs to read multiple times
        if (N >= DATA_WIDTH / 8) {
          int num_read_per_row = N / (DATA_WIDTH / 8);
#pragma hls_unroll yes
          for (int j = 0; j < DATA_WIDTH / 8; j++) {
            spec::InputType tmp = nvhls::get_slc<8>(data_pld.data, 8 * j);
            weight_in_vec[j + col_ctr * 8].Push(tmp);
          }

          col_ctr++;
          if (col_ctr == num_read_per_row)
            col_ctr = 0;
          wait();
        }
        // N < DATA_WIDTH / 8
        // write to weight_in_vec multiple times with one data read
        else {
          int num_row_per_read = (DATA_WIDTH / 8) / N;

          for (int row = 0; row < num_row_per_read; row++) {
#pragma hls_unroll yes
            for (int j = 0; j < N; j++) {
              spec::InputType tmp =
                  nvhls::get_slc<8>(data_pld.data, 8 * (j + row * N));
              weight_in_vec[j].Push(tmp);
            }
            wait(); // TODO: might need to wait for more cycles
          }
        }
      }

      // Complete master read request, send IRQ back
      rd_IRQ.Push(1);
      wait();
    }
  }
};

#endif
