-- Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2017.2 (win64) Build 1909853 Thu Jun 15 18:39:09 MDT 2017
-- Date        : Mon Nov 13 14:21:48 2017
-- Host        : ALINX000008-PC running 64-bit Service Pack 1  (build 7601)
-- Command     : write_vhdl -force -mode synth_stub
--               D:/demo_AX7103/20_dual_ov5640_an5642_hdmi/dual_ov5640_an5642_hdmi.srcs/sources_1/ip/sys_pll/sys_pll_stub.vhdl
-- Design      : sys_pll
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a100tfgg484-2
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity sys_pll is
  Port ( 
    clk_out1 : out STD_LOGIC;
    clk_out2 : out STD_LOGIC;
    reset : in STD_LOGIC;
    locked : out STD_LOGIC;
    clk_in1 : in STD_LOGIC
  );

end sys_pll;

architecture stub of sys_pll is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clk_out1,clk_out2,reset,locked,clk_in1";
begin
end;
