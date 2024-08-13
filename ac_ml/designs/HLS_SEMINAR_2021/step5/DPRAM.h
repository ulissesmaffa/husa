/**************************************************************************
 *                                                                        *
 *  Catapult(R) Machine Learning Reference Design Library                 *
 *                                                                        *
 *  Software Version: 1.8                                                 *
 *                                                                        *
 *  Release Date    : Sun Jul 16 19:01:51 PDT 2023                        *
 *  Release Type    : Production Release                                  *
 *  Release Build   : 1.8.0                                               *
 *                                                                        *
 *  Copyright 2021 Siemens                                                *
 *                                                                        *
 **************************************************************************
 *  Licensed under the Apache License, Version 2.0 (the "License");       *
 *  you may not use this file except in compliance with the License.      * 
 *  You may obtain a copy of the License at                               *
 *                                                                        *
 *      http://www.apache.org/licenses/LICENSE-2.0                        *
 *                                                                        *
 *  Unless required by applicable law or agreed to in writing, software   * 
 *  distributed under the License is distributed on an "AS IS" BASIS,     * 
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or       *
 *  implied.                                                              * 
 *  See the License for the specific language governing permissions and   * 
 *  limitations under the License.                                        *
 **************************************************************************
 *                                                                        *
 *  The most recent version of this package is available at github.       *
 *                                                                        *
 *************************************************************************/
#ifndef __INCLUDED_DPRAM_H__
#define __INCLUDED_DPRAM_H__

// SystemC memory model of DPRAM
// Generated by Catapult memory generator
// Generated by:   michaelf
// Generated date: Sat Feb  6 09:43:59 2021

// The following classes have been defined:
//     class DPRAM a 0 delay "structural" model of the RAM

//     class DPRAM_model<TLM/SYN>::mem<T,size,TLM/SYN>
//         A memory model that can be instanced and used for simulation and synthesis

//     class DPRAM_model<TLM/SYN>::rd_port<T,size,TLM/SYN>
//         a model of an external port with read capability

//     class DPRAM_model<TLM/SYN>::wr_port<T,size,TLM/SYN>
//         a model of an external port with write capability

#include <ccs_types.h>
#ifndef NO_ASSERTS
#include <assert.h>
#endif

#pragma map_to_operator DPRAM
template <
  int ram_id,
  int words,
  int width,
  int addr_width>
class DPRAM : public sc_module
{
public:
  sc_out< sc_lv<width> >   Q;
  sc_in< bool >   RCLK;
  sc_in< bool >   WCLK;
  sc_in< bool >   RCSN;
  sc_in< bool >   WCSN;
  sc_in< bool >   WEN;
  sc_in< sc_lv<width> >   D;
  sc_in< sc_lv<addr_width> >   RA;
  sc_in< sc_lv<addr_width> >   WA;

  #if !defined(__SYNTHESIS__)
  sc_signal<sc_lv<width> > mem[words];
  #endif

  SC_CTOR(DPRAM) :
    Q("Q")
    ,RCLK("RCLK")
    ,WCLK("WCLK")
    ,RCSN("RCSN")
    ,WCSN("WCSN")
    ,WEN("WEN")
    ,D("D")
    ,RA("RA")
    ,WA("WA") {
    SC_METHOD(seq_proc_1);
    dont_initialize();
    sensitive << RCLK.pos();
    SC_METHOD(seq_proc_2);
    dont_initialize();
    sensitive << WCLK.pos();
  }

  void seq_proc_1() {
    #if !defined(__SYNTHESIS__)
    int address;
    // write X
    // read
    if ( (RCSN==0) ) {
      vector_to_type( RA.read(), false, &address );
      #if !defined(NO_ASSERTS) && !defined(__SYNTHESIS__)
      assert( address>=0 && address <words );
      #endif
      Q.write( mem[address] );
    } else { Q.write( sc_lv< width>() ); }

    // write
    #endif
  }

  void seq_proc_2() {
    #if !defined(__SYNTHESIS__)
    int address;
    // write X
    if ((WCSN==0) && (WEN==0)) {
      vector_to_type( WA.read(), false, &address );
      #if !defined(NO_ASSERTS) && !defined(__SYNTHESIS__)
      assert( address>=0 && address <words );
      #endif
      mem[address] = D.read();
    }

    // read
    // write
    if ((WCSN==0) && (WEN==0)) {
      vector_to_type( WA.read(), false, &address );
      #if !defined(NO_ASSERTS) && !defined(__SYNTHESIS__)
      assert( address>=0 && address <words );
      #endif
      mem[address] = D.read();
    }

    #endif
  }

  #if !defined(__SYNTHESIS__)
  // NOTE: this method is intended for use by testbenches only. It is not synthesizable!
  sc_lv< width> tb_read( int address ) const {
    #ifndef NO_ASSERTS
    assert( address>=0 && address < words);
    #endif
    return mem[address];
  }

  // NOTE: this method is intended for use by testbenches only. It is not synthesizable!
  void tb_write( int address, sc_lv<width> data ) {
    #ifndef NO_ASSERTS
    assert( address>=0 && address < words);
    #endif
    mem[address] = data;
  }

  #endif
};

template <abstraction_t source_abstraction = AUTO>
class DPRAM_model
{
public:
  #if defined(__SYNTHESIS__)
  template <class T, unsigned int size, abstraction_t impl_abstraction = SYN> class mem {};
private:
  template <class T, unsigned int size, abstraction_t impl_abstraction = SYN> class rd_local;
  template <class T, unsigned int size, abstraction_t impl_abstraction = SYN> class wr_local;
public:
  template <class T, unsigned int size, abstraction_t impl_abstraction = SYN> class rd_port;
  template <class T, unsigned int size, abstraction_t impl_abstraction = SYN> class wr_port;

  #elif defined (CCS_DUT_CYCLE) || defined (CCS_DUT_RTL)
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? SYN : source_abstraction>
  class mem {};
private:
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? SYN : source_abstraction>
  class rd_local;
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? SYN : source_abstraction>
  class wr_local;
public:
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? SYN : source_abstraction>
  class rd_port;
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? SYN : source_abstraction>
  class wr_port;

  #else
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? P2P_DEFAULT_VIEW
            : source_abstraction> class mem {};
private:
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? P2P_DEFAULT_VIEW
            : source_abstraction> class rd_local;
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? P2P_DEFAULT_VIEW
            : source_abstraction> class wr_local;
public:
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? P2P_DEFAULT_VIEW
            : source_abstraction> class rd_port;
  template <class T, unsigned int size, abstraction_t impl_abstraction = (source_abstraction==AUTO) ? P2P_DEFAULT_VIEW
            : source_abstraction> class wr_port;

  #endif

  // ***********************************************
  // TLM TLM TLM TLM TLM TLM TLM TLM TLM TLM TLM TLM
  //    This code is only for TLM simulation only
  // ***********************************************

  template <class T, unsigned int size>
  class mem <T,size,TLM>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
  public:
    void write (ac_int<addr_width,false> addr, T data=0) {
      wr_port_instance.reset_chk.test();
      #ifndef NO_ASSERTS
      assert( addr>=0 && addr<size );
      #endif
      array[addr] = data;
    };

    T read ( ac_int<addr_width,false> addr ) {
      #ifndef NO_ASSERTS
      assert( addr>=0 && addr<size );
      #endif
      rd_port_instance.reset_chk.test();
      return array[addr];
    }

    T &operator [] (int index) {
      #ifndef NO_ASSERTS
      assert( index>=0 && index<size );
      #endif
      return array[index];
    }

    const T &operator [] (int index) const {
      #ifndef NO_ASSERTS
      assert( index>=0 && index<size );
      #endif
      return array[index];
    }

    // NOTE: this method is intended for use by testbenches only. It is not synthesizable!
    T tb_read( int address ) const {
      #ifndef NO_ASSERTS
      assert( address>=0 && address <size );
      #endif
      return array[address];
    }

    // NOTE: this method is intended for use by testbenches only. It is not synthesizable!
    void tb_write( int address, T data ) {
      #ifndef NO_ASSERTS
      assert( address>=0 && address <size );
      #endif
      array[address] = data;
    }

  public:
    mem(const char *name = "unnamed_")
      : rd_port_instance(*this, ccs_concat(name,"rd"))
      , wr_port_instance(*this, ccs_concat(name,"wr"))
    {}

    void reset_read() {
      rd_port_instance.reset();
    }

    void reset_write() {
      wr_port_instance.reset();
    }

    void RCLK(sc_in<bool> &RCLK_arg) {
      rd_port_instance.clock_ok();
    }
    void RCLK(sc_signal<bool> &RCLK_arg) {
      rd_port_instance.clock_ok();
    }

    void WCLK(sc_in<bool> &WCLK_arg) {
      wr_port_instance.clock_ok();
    }
    void WCLK(sc_signal<bool> &WCLK_arg) {
      wr_port_instance.clock_ok();
    }

    rd_local<T,size,TLM> rd_port_instance;
    wr_local<T,size,TLM> wr_port_instance;
  private:
    T array[size];
    friend class rd_local<T,size,TLM>;
    friend class wr_local<T,size,TLM>;
  };

private:
  template <class T, unsigned int size>
  class rd_local<T,size,TLM>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
    p2p_checker reset_chk;
    p2p_checker clock_chk;
    void clock_ok() {clock_chk.ok();}

  public:
    rd_local (mem<T,size,TLM> &my_parent, const char *name)
      : reset_chk( name, "call reset()", "access this memory")
      , clock_chk( name, "bind the clock port", "access this memory")
      , parent(my_parent)
    {}

    void reset() {reset_chk.ok();}

    const T &operator [] (int index) const {
      reset_chk.test();
      clock_chk.test();
      #ifndef NO_ASSERTS
      assert( index>=0 && index<size );
      #endif
      return parent.array[index];
    }

    T read ( ac_int<addr_width,false> addr ) {
      reset_chk.test();
      clock_chk.test();
      #ifndef NO_ASSERTS
      assert( addr>=0 && addr<size );
      #endif
      return parent.read(addr);
    }

  private:
    mem<T,size,TLM> &parent;
    friend class mem<T,size,TLM>;
  };

  template <class T, unsigned int size>
  class wr_local<T,size,TLM>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
    p2p_checker reset_chk;
    p2p_checker clock_chk;
    void clock_ok() {clock_chk.ok();}

  public:
    wr_local (mem<T,size,TLM> &my_parent, const char *name)
      : reset_chk( name, "call reset()", "access this memory")
      , clock_chk( name, "bind the clock port", "access this memory")
      , parent(my_parent)
    {}

    void reset() {reset_chk.ok();}

    T &operator [] (int index) {
      reset_chk.test();
      clock_chk.test();
      return parent.array[index];
    }

    const T &operator [] (int index) const {
      reset_chk.test();
      clock_chk.test();
      #ifndef NO_ASSERTS
      assert( index>=0 && index<size );
      #endif
      return parent.array[index];
    }

    void write (ac_int<addr_width,false> addr, T data=0) {
      reset_chk.test();
      clock_chk.test();
      #ifndef NO_ASSERTS
      assert( addr>=0 && addr<size );
      #endif
      parent.array[addr] = data;
    };

  private:
    mem<T,size,TLM> &parent;
    friend class mem<T,size,TLM>;
  };

public:
  template <class T, unsigned int size>
  class rd_port<T,size,TLM>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
    p2p_checker reset_chk;

  public:
    rd_port(const char *name = "unnamed_")
      : reset_chk(name, "call reset()", "access this port")
      , chan_ptr(0)
      , port_ptr(0)
    {}

    T read(unsigned int addr) {
      reset_chk.test();
      if ( bound_to_port )
      { return port_ptr->read(addr); }
      else
      { return chan_ptr->read(addr); }
    }

    const T &operator [] (int index) {
      reset_chk.test();
      return (bound_to_port? (*port_ptr)[index] : (*chan_ptr)[index]);
    }

    void reset() {reset_chk.ok();}

    void operator() (rd_local<T,size,TLM> &c) {
      chan_ptr = &c;
      c.reset(); // Supress reset error on bound memory
      bound_to_port = false;
    }

    void operator() (rd_port<T,size,TLM> &c) {
      port_ptr = &c;
      c.reset(); // Supress reset error on bound port
      bound_to_port = true;
    }

    void operator() (mem<T,size,TLM> &m) {
      chan_ptr = &m.rd_port_instance;
      chan_ptr->reset(); // Supress reset error on bound memory
      bound_to_port = false;
    }

  private:
    bool bound_to_port;
    rd_local<T,size,TLM> *chan_ptr;
    rd_port<T,size,TLM> *port_ptr;
  };

  template <class T, unsigned int size>
  class wr_port<T,size,TLM>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
    p2p_checker reset_chk;

  public:
    wr_port(const char *name = "unnamed_")
      : reset_chk(name, "call reset()", "access this port")
      , chan_ptr(0)
      , port_ptr(0)
    {}

    void write(unsigned int addr, T data ) {
      reset_chk.test();
      if ( bound_to_port )
      { port_ptr->write(addr,data); }
      else
      { chan_ptr->write(addr,data); }
    }

    T &operator [] (int index) {
      reset_chk.test();
      return (bound_to_port? (*port_ptr)[index] : (*chan_ptr)[index]);
    }

    void reset() {reset_chk.ok();}

    void operator() (wr_local<T,size,TLM> &c) {
      chan_ptr = &c;
      c.reset(); // Supress reset error on bound memory
      bound_to_port = false;
    }

    void operator() (wr_port<T,size,TLM> &c) {
      port_ptr = &c;
      c.reset(); // Supress reset error on bound port
      bound_to_port = true;
    }

    void operator() (mem<T,size,TLM> &m) {
      chan_ptr = &m.wr_port_instance;
      chan_ptr->reset(); // Supress reset error on bound memory
      bound_to_port = false;
    }

  private:
    bool bound_to_port;
    wr_local<T,size,TLM> *chan_ptr;
    wr_port<T,size,TLM> *port_ptr;
  };

  // ***********************************************
  // SYN SYN SYN SYN SYN SYN SYN SYN SYN SYN SYN SYN
  // Synthesis code
  // ***********************************************

private:
  template <class T, unsigned int size>
  class rd_local<T,size,SYN>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
    p2p_checker reset_chk;
    p2p_checker clock_chk;
    class mem_ref
    {
    public:
      mem_ref( rd_local<T,size,SYN> &my_parent, ac_int<addr_width,false> addr)
        : address(addr), parent(my_parent) {}

      operator T() const { return parent.read(address); }

      inline mem_ref operator = ( const mem_ref &val ) { return operator = ((T)val); }

    private:
      ac_int<addr_width,false> address;
      rd_local<T,size,SYN> &parent;
    };

    void clock_ok() {clock_chk.ok();}

  public:
    rd_local( const char *name)
      : reset_chk( name, "call reset()", "access this memory")
      , clock_chk( name, "bind the clock port", "access this memory")
      , Q(ccs_concat(name,"Q"))
      , RCSN(ccs_concat(name,"RCSN"))
      , RA(ccs_concat(name,"RA"))
    {}

#pragma remove_out_reg
#pragma design modulario
    T read (ac_int<addr_width,false> addr) {
      reset_chk.test();
      clock_chk.test();
      sc_lv<addr_width> temp_addr;
      type_to_vector(addr, (signedtype?true:false), temp_addr);
      RCSN.write(0);
      RA.write( temp_addr );
#pragma hls_unroll
      for (int lcnt=0; lcnt<1; lcnt++) { wait(); }
      #if defined(CALYPTO_SC)
      wait(); // Account for unreg outputs for SLEC
      #elif !defined(__SYNTHESIS__)
      wait(0.3, SC_NS);  // Account for unreg outputs in simulation
      #endif
      RCSN.write(1);
      #if !defined(CALYPTO_SC)
      // Return outputs to don't care to save area
      sc_lv<data_width> dc;
      RA.write( dc );
      #endif
      T return_data;
      vector_to_type(Q.read(), (signedtype?true:false), &return_data);
      return return_data;
    }

    mem_ref operator [] (int index) {
      mem_ref write_ref(*this, index);
      return write_ref;
    }

    void reset() {
      RCSN.write(1);
      RA.write(sc_dt::Log_0);
      reset_chk.ok();
    }

    sc_signal< sc_lv<data_width> > Q;
    sc_signal< bool > RCSN;
    sc_signal< sc_lv<addr_width> > RA;
  private:
    friend class mem<T,size,SYN>;
  };

  template <class T, unsigned int size>
  class wr_local<T,size,SYN>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
    p2p_checker reset_chk;
    p2p_checker clock_chk;
    class mem_ref
    {
    public:
      mem_ref( wr_local<T,size,SYN> &my_parent, ac_int<addr_width,false> addr)
        : address(addr), parent(my_parent) {}

      inline mem_ref operator = ( T val ) {
        parent.write(address,val);
        return *this;
      }

      inline mem_ref operator = ( const mem_ref &val ) { return operator = ((T)val); }

    private:
      ac_int<addr_width,false> address;
      wr_local<T,size,SYN> &parent;
    };

    void clock_ok() {clock_chk.ok();}

  public:
    wr_local( const char *name)
      : reset_chk( name, "call reset()", "access this memory")
      , clock_chk( name, "bind the clock port", "access this memory")
      , WCSN(ccs_concat(name,"WCSN"))
      , WEN(ccs_concat(name,"WEN"))
      , D(ccs_concat(name,"D"))
      , WA(ccs_concat(name,"WA"))
    {}

#pragma remove_out_reg
#pragma design modulario
    void write (ac_int<addr_width,false> addr, T data=0) {
      reset_chk.test();
      clock_chk.test();
      sc_lv<data_width> temp_data;
      type_to_vector(data, (signedtype?true:false), temp_data);
      sc_lv<addr_width> temp_addr;
      type_to_vector(addr, (signedtype?true:false), temp_addr);
      WCSN.write(0);
      WEN.write(0);
      WA.write( temp_addr );
      D.write( temp_data );
#pragma hls_unroll
      for (int lcnt=0; lcnt<1; lcnt++) { wait(); }
      #if defined(CALYPTO_SC)
      wait(); // Account for unreg outputs for SLEC
      #elif !defined(__SYNTHESIS__)
      wait(0.3, SC_NS);  // Account for unreg outputs in simulation
      #endif
      WCSN.write(1);
      WEN.write(1);
      #if !defined(CALYPTO_SC)
      // Return outputs to don't care to save area
      sc_lv<data_width> dc;
      D.write( dc );
      WA.write( dc );
      #endif
    }

    mem_ref operator [] (int index) {
      mem_ref write_ref(*this, index);
      return write_ref;
    }

    void reset() {
      WCSN.write(1);
      WEN.write(1);
      WA.write(sc_dt::Log_0);
      D.write(sc_dt::Log_0);
      reset_chk.ok();
    }

    sc_signal< bool > WCSN;
    sc_signal< bool > WEN;
    sc_signal< sc_lv<data_width> > D;
    sc_signal< sc_lv<addr_width> > WA;
  private:
    friend class mem<T,size,SYN>;
  };

public:
  template <class T, unsigned int size>
  class mem <T,size,SYN>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
    class mem_ref
    {
    public:
      mem_ref( mem<T,size,SYN> &my_parent, ac_int<addr_width,false> addr)
        : address(addr), parent(my_parent) {}

      operator T() const { return parent.read(address); }

      inline mem_ref operator = ( T val ) {
        parent.write(address,val);
        return *this;
      }

      inline mem_ref operator = ( const mem_ref &val ) { return operator = ((T)val); }

    private:
      ac_int<addr_width,false> address;
      mem<T,size,SYN> &parent;
    };

  public:
    mem ( const char *name = "unnamed_")
      : RAM(ccs_concat(name, "RAM"))
      , rd_port_instance(ccs_concat(name,"rd"))
      , wr_port_instance(ccs_concat(name,"wr")) {
      RAM.Q(rd_port_instance.Q);
      RAM.RCSN(rd_port_instance.RCSN);
      RAM.RA(rd_port_instance.RA);
      RAM.WCSN(wr_port_instance.WCSN);
      RAM.WEN(wr_port_instance.WEN);
      RAM.D(wr_port_instance.D);
      RAM.WA(wr_port_instance.WA);
    }

    rd_local<T,size,SYN> rd_port_instance;
    wr_local<T,size,SYN> wr_port_instance;

    void RCLK(sc_in<bool> &RCLK_arg) {
      RAM.RCLK(RCLK_arg);
      rd_port_instance.clock_ok();
    }
    void RCLK(sc_signal<bool> &RCLK_arg) {
      RAM.RCLK(RCLK_arg);
      rd_port_instance.clock_ok();
    }

    void WCLK(sc_in<bool> &WCLK_arg) {
      RAM.WCLK(WCLK_arg);
      wr_port_instance.clock_ok();
    }
    void WCLK(sc_signal<bool> &WCLK_arg) {
      RAM.WCLK(WCLK_arg);
      wr_port_instance.clock_ok();
    }


    T read ( ac_int<addr_width,false> addr ) {
      return rd_port_instance.read( addr );
    }

    void write (ac_int<addr_width,false> addr, T data=0) {
      wr_port_instance.write( addr, data );
    }

    mem_ref operator [] (int index) {
      mem_ref write_ref(*this, index);
      return write_ref;
    }

    void reset_read() {
      rd_port_instance.reset();
    }

    void reset_write() {
      wr_port_instance.reset();
    }

    // NOTE: this method is intended for use by testbenches only. It is not synthesizable!
    T tb_read(int address) const {
      #ifndef NO_ASSERTS
      assert( address>=0 && address<size );
      #endif
      T return_data;
      vector_to_type( RAM.tb_read(address), (signedtype?true:false), &return_data);
      return return_data;
    }

    // NOTE: this method is intended for use by testbenches only. It is not synthesizable!
    void tb_write( int address, T val) {
      #ifndef NO_ASSERTS
      assert( address>=0 && address<size );
      #endif
      sc_lv<data_width> temp_data;
      type_to_vector(val, (signedtype?true:false), temp_data);
      RAM.tb_write(address, temp_data);
    }

  private:
    DPRAM<0, size, data_width, addr_width> RAM;
  };

  template <class T, unsigned int size>
  class rd_port<T,size,SYN>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
    p2p_checker reset_chk;

    class mem_ref
    {
    public:
      mem_ref( rd_port<T,size,SYN> &my_parent, ac_int<addr_width,false> addr)
        : address(addr), parent(my_parent) {}

      operator T() const { return parent.read(address); }

      inline mem_ref operator = ( const mem_ref &val ) { return operator = ((T)val); }

    private:
      ac_int<addr_width,false> address;
      rd_port<T,size,SYN> &parent;
    };

  public:
    rd_port( const char *name = "unnamed_")
      : reset_chk( name, "call reset()", "access this memory")
      , Q(ccs_concat(name,"Q"))
      , RCSN(ccs_concat(name,"RCSN"))
      , RA(ccs_concat(name,"RA"))
    {}

#pragma remove_out_reg
#pragma design modulario
    T read (ac_int<addr_width,false> addr) {
      reset_chk.test();
      sc_lv<addr_width> temp_addr;
      type_to_vector(addr, (signedtype?true:false), temp_addr);
      RCSN.write(0);
      RA.write( temp_addr );
#pragma hls_unroll
      for (int lcnt=0; lcnt<1; lcnt++) { wait(); }
      #if defined(CALYPTO_SC)
      wait(); // Account for unreg outputs for SLEC
      #elif !defined(__SYNTHESIS__)
      wait(0.3, SC_NS);  // Account for unreg outputs in simulation
      #endif
      RCSN.write(1);
      #if !defined(CALYPTO_SC)
      // Return outputs to don't care to save area
      sc_lv<data_width> dc;
      RA.write( dc );
      #endif
      T return_data;
      vector_to_type(Q.read(), (signedtype?true:false), &return_data);
      return return_data;
    }

    void reset() {
      RCSN.write(1);
      RA.write(sc_dt::Log_0);
      reset_chk.ok();
    }

    sc_in< sc_lv<data_width> > Q;
    sc_out< bool > RCSN;
    sc_out< sc_lv<addr_width> > RA;

    mem_ref operator [] (int index) {
      mem_ref write_ref(*this, index);
      return write_ref;
    }

    template <class C> void bind( C &c ) {
      Q(c.Q);
      RCSN(c.RCSN);
      RA(c.RA);
    }

    template <class C> void operator() (C &c) {
      bind(c);
    }

    void operator() (mem<T,size,SYN> &m) {
      Q(m.rd_port_instance.Q);
      RCSN(m.rd_port_instance.RCSN);
      RA(m.rd_port_instance.RA);
    }

  };


  template <class T, unsigned int size>
  class wr_port<T,size,SYN>
  {
    enum {
      addr_width = nbits<size-1>::val,
      signedtype = mc_typedef_T_traits<T>::issigned,
      data_width = mc_typedef_T_traits<T>::bitwidth
    };
    p2p_checker reset_chk;

    class mem_ref
    {
    public:
      mem_ref( wr_port<T,size,SYN> &my_parent, ac_int<addr_width,false> addr)
        : address(addr), parent(my_parent) {}

      inline mem_ref operator = ( T val ) {
        parent.write(address,val);
        return *this;
      }

      inline mem_ref operator = ( const mem_ref &val ) { return operator = ((T)val); }

    private:
      ac_int<addr_width,false> address;
      wr_port<T,size,SYN> &parent;
    };

  public:
    wr_port( const char *name = "unnamed_")
      : reset_chk( name, "call reset()", "access this memory")
      , WCSN(ccs_concat(name,"WCSN"))
      , WEN(ccs_concat(name,"WEN"))
      , D(ccs_concat(name,"D"))
      , WA(ccs_concat(name,"WA"))
    {}

#pragma remove_out_reg
#pragma design modulario
    void write (ac_int<addr_width,false> addr, T data=0) {
      reset_chk.test();
      sc_lv<data_width> temp_data;
      type_to_vector(data, (signedtype?true:false), temp_data);
      sc_lv<addr_width> temp_addr;
      type_to_vector(addr, (signedtype?true:false), temp_addr);
      WCSN.write(0);
      WEN.write(0);
      WA.write( temp_addr );
      D.write( temp_data );
#pragma hls_unroll
      for (int lcnt=0; lcnt<1; lcnt++) { wait(); }
      #if defined(CALYPTO_SC)
      wait(); // Account for unreg outputs for SLEC
      #elif !defined(__SYNTHESIS__)
      wait(0.3, SC_NS);  // Account for unreg outputs in simulation
      #endif
      WCSN.write(1);
      WEN.write(1);
      #if !defined(CALYPTO_SC)
      // Return outputs to don't care to save area
      sc_lv<data_width> dc;
      D.write( dc );
      WA.write( dc );
      #endif
    }

    void reset() {
      WCSN.write(1);
      WEN.write(1);
      WA.write(sc_dt::Log_0);
      D.write(sc_dt::Log_0);
      reset_chk.ok();
    }

    sc_out< bool > WCSN;
    sc_out< bool > WEN;
    sc_out< sc_lv<data_width> > D;
    sc_out< sc_lv<addr_width> > WA;

    mem_ref operator [] (int index) {
      mem_ref write_ref(*this, index);
      return write_ref;
    }

    template <class C> void bind( C &c ) {
      WCSN(c.WCSN);
      WEN(c.WEN);
      D(c.D);
      WA(c.WA);
    }

    template <class C> void operator() (C &c) {
      bind(c);
    }

    void operator() (mem<T,size,SYN> &m) {
      WCSN(m.wr_port_instance.WCSN);
      WEN(m.wr_port_instance.WEN);
      D(m.wr_port_instance.D);
      WA(m.wr_port_instance.WA);
    }

  };

};
#endif // ifndef __INCLUDED_DPRAM_H__


