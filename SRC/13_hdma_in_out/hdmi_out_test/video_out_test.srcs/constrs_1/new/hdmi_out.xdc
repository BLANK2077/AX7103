set_property PACKAGE_PIN M13 [get_ports vout_clk]
set_property PACKAGE_PIN V14 [get_ports {vout_data[0]}]
set_property PACKAGE_PIN H14 [get_ports {vout_data[1]}]
set_property PACKAGE_PIN J14 [get_ports {vout_data[2]}]
set_property PACKAGE_PIN K13 [get_ports {vout_data[3]}]
set_property PACKAGE_PIN K14 [get_ports {vout_data[4]}]
set_property PACKAGE_PIN L13 [get_ports {vout_data[5]}]
set_property PACKAGE_PIN L19 [get_ports {vout_data[6]}]
set_property PACKAGE_PIN L20 [get_ports {vout_data[7]}]
set_property PACKAGE_PIN K17 [get_ports {vout_data[8]}]
set_property PACKAGE_PIN J17 [get_ports {vout_data[9]}]
set_property PACKAGE_PIN L16 [get_ports {vout_data[10]}]
set_property PACKAGE_PIN K16 [get_ports {vout_data[11]}]
set_property PACKAGE_PIN L14 [get_ports {vout_data[12]}]
set_property PACKAGE_PIN L15 [get_ports {vout_data[13]}]
set_property PACKAGE_PIN M15 [get_ports {vout_data[14]}]
set_property PACKAGE_PIN M16 [get_ports {vout_data[15]}]
set_property PACKAGE_PIN L18 [get_ports {vout_data[16]}]
set_property PACKAGE_PIN M18 [get_ports {vout_data[17]}]
set_property PACKAGE_PIN N18 [get_ports {vout_data[18]}]
set_property PACKAGE_PIN N19 [get_ports {vout_data[19]}]
set_property PACKAGE_PIN M20 [get_ports {vout_data[20]}]
set_property PACKAGE_PIN N20 [get_ports {vout_data[21]}]
set_property PACKAGE_PIN L21 [get_ports {vout_data[22]}]
set_property PACKAGE_PIN M21 [get_ports {vout_data[23]}]
set_property PACKAGE_PIN V13 [get_ports vout_de]
set_property PACKAGE_PIN T15 [get_ports vout_hs]
set_property PACKAGE_PIN J19 [get_ports hdmi_nreset]
set_property PACKAGE_PIN T14 [get_ports vout_vs]
set_property PACKAGE_PIN E16 [get_ports hdmi_scl]
set_property PACKAGE_PIN F16 [get_ports hdmi_sda]

set_property IOSTANDARD LVCMOS33 [get_ports vout_clk]
set_property IOSTANDARD LVCMOS33 [get_ports {vout_data[*]}]
set_property IOSTANDARD LVCMOS33 [get_ports vout_de]
set_property IOSTANDARD LVCMOS33 [get_ports vout_hs]
set_property IOSTANDARD LVCMOS33 [get_ports hdmi_nreset]
set_property IOSTANDARD LVCMOS33 [get_ports vout_vs]
set_property IOSTANDARD LVCMOS33 [get_ports hdmi_scl]
set_property IOSTANDARD LVCMOS33 [get_ports hdmi_sda]


set_property IOSTANDARD LVCMOS33 [get_ports {key[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {key[0]}]

set_property SLEW FAST [get_ports {vout_data[*]}]
set_property SLEW FAST [get_ports vout_de]
set_property SLEW FAST [get_ports vout_hs]
set_property SLEW FAST [get_ports vout_vs]
set_property IOSTANDARD DIFF_SSTL15 [get_ports sys_clk_p]
set_property PACKAGE_PIN R4 [get_ports sys_clk_p]
set_property PACKAGE_PIN E13 [get_ports {key[1]}]
set_property PACKAGE_PIN J21 [get_ports {key[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {led[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {led[1]}]
set_property PACKAGE_PIN B13 [get_ports {led[0]}]
set_property PACKAGE_PIN C13 [get_ports {led[1]}]