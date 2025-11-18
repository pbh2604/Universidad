## Clock input 100 MHz (pin W5)
set_property PACKAGE_PIN W5 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]
create_clock -period 10.000 -name sys_clk_pin -waveform {0.000 5.000} -add [get_ports clk]

## Reset input (BTN center - pin U18)
set_property PACKAGE_PIN U18 [get_ports rst]
set_property IOSTANDARD LVCMOS33 [get_ports rst]

## SPI signals to/from MCP3004
##ad_dout_i = MISO (input from MCP)
set_property PACKAGE_PIN A16 [get_ports ad_dout_i]
set_property IOSTANDARD LVCMOS33 [get_ports ad_dout_i]

# ad_clk_o = SPI clock (output to MCP)
set_property PACKAGE_PIN B16 [get_ports ad_clk_o]
set_property IOSTANDARD LVCMOS33 [get_ports ad_clk_o]

# ad_din_o = MOSI (output to MCP)
set_property PACKAGE_PIN B15 [get_ports ad_din_o]
set_property IOSTANDARD LVCMOS33 [get_ports ad_din_o]

# ad_ncs_o = Chip Select (output to MCP)
set_property PACKAGE_PIN A14 [get_ports ad_ncs_o]
set_property IOSTANDARD LVCMOS33 [get_ports ad_ncs_o]

## 7-segment display segmentos (a-g) - display externo
set_property PACKAGE_PIN P17 [get_ports {seg[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[0]}]

set_property PACKAGE_PIN L17 [get_ports {seg[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[1]}]

set_property PACKAGE_PIN N17 [get_ports {seg[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[2]}]

set_property PACKAGE_PIN M18 [get_ports {seg[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[3]}]

set_property PACKAGE_PIN K17 [get_ports {seg[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[4]}]

set_property PACKAGE_PIN M19 [get_ports {seg[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[5]}]

set_property PACKAGE_PIN P18 [get_ports {seg[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {seg[6]}]

set_property PACKAGE_PIN L2 [get_ports {an_pulso[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {an_pulso[0]}]

set_property PACKAGE_PIN J2 [get_ports {an_pulso[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {an_pulso[1]}]

set_property PACKAGE_PIN G2 [get_ports {an_pulso[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {an_pulso[2]}]

set_property PACKAGE_PIN K3 [get_ports {an_pulso[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {an_pulso[3]}]

## DS18B20 DQ pin on Pmod JA1
set_property PACKAGE_PIN J1 [get_ports DQ]
set_property IOSTANDARD LVCMOS33 [get_ports DQ]

set_property PACKAGE_PIN V7 [get_ports DP]
set_property IOSTANDARD LVCMOS33 [get_ports DP]

set_property PACKAGE_PIN N1 [get_ports {LEDTER[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDTER[0]}]

set_property PACKAGE_PIN M1 [get_ports {LEDTER[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDTER[1]}]

set_property PACKAGE_PIN M3 [get_ports {LEDTER[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LEDTER[2]}]

## 7-segment display fpga
set_property PACKAGE_PIN W7 [get_ports {a_to_g[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {a_to_g[6]}]
set_property PACKAGE_PIN W6 [get_ports {a_to_g[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {a_to_g[5]}]
set_property PACKAGE_PIN U8 [get_ports {a_to_g[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {a_to_g[4]}]
set_property PACKAGE_PIN V8 [get_ports {a_to_g[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {a_to_g[3]}]
set_property PACKAGE_PIN U5 [get_ports {a_to_g[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {a_to_g[2]}]
set_property PACKAGE_PIN V5 [get_ports {a_to_g[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {a_to_g[1]}]
set_property PACKAGE_PIN U7 [get_ports {a_to_g[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {a_to_g[0]}]

set_property PACKAGE_PIN U2 [get_ports {an_temp[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {an_temp[0]}]
set_property PACKAGE_PIN U4 [get_ports {an_temp[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {an_temp[1]}]
set_property PACKAGE_PIN V4 [get_ports {an_temp[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {an_temp[2]}]
set_property PACKAGE_PIN W4 [get_ports {an_temp[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {an_temp[3]}]