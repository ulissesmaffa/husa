# enable struct field names to be preserved in the RTL
set enable_preserve_fields 1

set sfd [file dir [info script]]

options defaults

# Due to CAT34509, the new struct layout option does not work with the axi4_segment.h
# for VHDL SCVerify. So this script disables VHDL output.

options set /Output/OutputVHDL false

options set /Input/CppStandard c++11
if {$enable_preserve_fields} {
  options set /Input/CompilerFlags { "-DFORCE_AUTO_PORT=Connections::DIRECT_PORT" -DSEGMENT_BURST_SIZE=16}
} else {
  options set /Input/CompilerFlags { -DSEGMENT_BURST_SIZE=16}
}
options set /Input/SearchPath {$MGC_HOME/shared/examples/matchlib/toolkit/include} -append
options set /Input/SearchPath {$MGC_HOME/shared/pkgs/matchlib/cmod/include} -append
options set /Input/SearchPath {$MGC_HOME/shared/pkgs/boostpp/pp/include} -append

project new
flow package require /DesignWrapper
flow package require /SCVerify
# Set to a non-zero number to enable automatic random stall injection on handshake interfaces
#flow package option set /SCVerify/AUTOWAIT 0
# Allow initial toggle of reset
#flow package option set /SCVerify/ENABLE_RESET_TOGGLE true
# Turn on to enable systematic STALL_FLAG toggling (requires STALL_FLAG directive to be set)
#flow package option set /SCVerify/ENABLE_STALL_TOGGLE true

flow package require /VSCode
flow package require /QuestaSIM
flow package option set /QuestaSIM/ENABLE_CODE_COVERAGE true
flow package option set /QuestaSIM/MSIM_DOFILE $sfd/msim.do

solution file add "$sfd/testbench.cpp" -type C++

if {$enable_preserve_fields} {
  directive set -STRUCT_LAYOUT c_style
  directive set -PRESERVE_STRUCTS true
  solution options set /Output/VerilogStructFormat packed
}

go analyze
directive set -DESIGN_HIERARCHY dma

go compile
solution library add nangate-45nm_beh -- -rtlsyntool OasysRTL -vendor Nangate -technology 045nm

go libraries
directive set -CLOCKS {clk {-CLOCK_PERIOD 2.0}}

go assembly
go architect
go allocate
go extract

