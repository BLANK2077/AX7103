# 
# Synthesis run script generated by Vivado
# 

namespace eval rt {
    variable rc
}
set rt::rc [catch {
  uplevel #0 {
    set ::env(BUILTIN_SYNTH) true
    source $::env(HRT_TCL_PATH)/rtSynthPrep.tcl
    rt::HARTNDb_resetJobStats
    rt::HARTNDb_resetSystemStats
    rt::HARTNDb_startSystemStats
    rt::HARTNDb_startJobStats
    set rt::cmdEcho 0
    rt::set_parameter writeXmsg true
    rt::set_parameter enableParallelHelperSpawn true
    set ::env(RT_TMP) "D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/tmp"
    if { [ info exists ::env(RT_TMP) ] } {
      file delete -force $::env(RT_TMP)
      file mkdir $::env(RT_TMP)
    }

    rt::delete_design

    set rt::partid xc7a100tfgg484-2

    set rt::multiChipSynthesisFlow false
    source $::env(SYNTH_COMMON)/common_vhdl.tcl
    set rt::defaultWorkLibName xil_defaultlib

    set rt::useElabCache false
    if {$rt::useElabCache == false} {
      rt::read_verilog -sv -include {
    d:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/bd/PCIe/ipshared/bcea/hdl/verilog
    d:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/bd/PCIe/ipshared/9c7f
    d:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/bd/PCIe/ipshared/7e3a/hdl
  } {
      C:/Xilinx/Vivado/2017.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv
      C:/Xilinx/Vivado/2017.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv
    }
      rt::read_verilog -include {
    d:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/bd/PCIe/ipshared/bcea/hdl/verilog
    d:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/bd/PCIe/ipshared/9c7f
    d:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/bd/PCIe/ipshared/7e3a/hdl
  } {
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_util_ds_buf_0_0_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_xdma_0_1_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_clk_wiz_0_0_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_mig_7series_0_0_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_rst_mig_7series_0_100M_0_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_xbar_0_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_proc_sys_reset_0_0_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_auto_cc_0_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_auto_us_1_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_auto_cc_1_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/PCIe_auto_us_0_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/afifo_64i_32o_2048_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/realtime/afifo_32i_64o_4096_stub.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/bd/PCIe/hdl/PCIe.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/bd/PCIe/hdl/PCIe_wrapper.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/aq_axi_master.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/color_bar.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/frame_fifo_read.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/frame_fifo_write.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/frame_read_write.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/i2c_master/i2c_config.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/i2c_master/timescale.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/i2c_master/i2c_master_defines.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/i2c_master/i2c_master_bit_ctrl.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/i2c_master/i2c_master_byte_ctrl.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/i2c_master/i2c_master_top.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/lut_hdmi.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/video_timing_data.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/video_write_req_gen.v
      D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/PCIe.srcs/sources_1/new/Pcie_ddr3.v
    }
      rt::read_vhdl -lib xpm C:/Xilinx/Vivado/2017.2/data/ip/xpm/xpm_VCOMP.vhd
      rt::filesetChecksum
    }
    rt::set_parameter usePostFindUniquification false
    set rt::top Pcie_ddr3
    set rt::reportTiming false
    rt::set_parameter elaborateOnly true
    rt::set_parameter elaborateRtl true
    rt::set_parameter eliminateRedundantBitOperator false
    rt::set_parameter writeBlackboxInterface true
    rt::set_parameter merge_flipflops true
    rt::set_parameter srlDepthThreshold 3
    rt::set_parameter rstSrlDepthThreshold 4
# MODE: 
    rt::set_parameter webTalkPath {}
    rt::set_parameter enableSplitFlowPath "D:/exam_pcie_xilinx/pcieax7103x4_128ddr3/.Xil/Vivado-7128-ALINX000008-PC/"
    set ok_to_delete_rt_tmp true 
    if { [rt::get_parameter parallelDebug] } { 
       set ok_to_delete_rt_tmp false 
    } 
    if {$rt::useElabCache == false} {
        set oldMIITMVal [rt::get_parameter maxInputIncreaseToMerge]; rt::set_parameter maxInputIncreaseToMerge 1000
        set oldCDPCRL [rt::get_parameter createDfgPartConstrRecurLimit]; rt::set_parameter createDfgPartConstrRecurLimit 1
      rt::run_rtlelab -module $rt::top
        rt::set_parameter maxInputIncreaseToMerge $oldMIITMVal
        rt::set_parameter createDfgPartConstrRecurLimit $oldCDPCRL
    }

    set rt::flowresult [ source $::env(SYNTH_COMMON)/flow.tcl ]
    rt::HARTNDb_stopJobStats
    if { $rt::flowresult == 1 } { return -code error }

    if { [ info exists ::env(RT_TMP) ] } {
      if { [info exists ok_to_delete_rt_tmp] && $ok_to_delete_rt_tmp } { 
        file delete -force $::env(RT_TMP)
      }
    }


  set hsKey [rt::get_parameter helper_shm_key] 
  if { $hsKey != "" && [info exists ::env(BUILTIN_SYNTH)] && [rt::get_parameter enableParallelHelperSpawn] && [info exists rt::doParallel] && $rt::doParallel} { 
     $rt::db killSynthHelper $hsKey
  } 
  rt::set_parameter helper_shm_key "" 
    source $::env(HRT_TCL_PATH)/rtSynthCleanup.tcl
  } ; #end uplevel
} rt::result]

if { $rt::rc } {
  $rt::db resetHdlParse
  set hsKey [rt::get_parameter helper_shm_key] 
  if { $hsKey != "" && [info exists ::env(BUILTIN_SYNTH)] && [rt::get_parameter enableParallelHelperSpawn] && [info exists rt::doParallel] && $rt::doParallel} { 
     $rt::db killSynthHelper $hsKey
  } 
  source $::env(HRT_TCL_PATH)/rtSynthCleanup.tcl
  return -code "error" $rt::result
}