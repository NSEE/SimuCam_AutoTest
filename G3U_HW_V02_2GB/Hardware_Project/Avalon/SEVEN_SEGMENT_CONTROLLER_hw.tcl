# TCL File Generated by Component Editor 16.1
# Thu Feb 16 10:57:05 BRST 2017
# DO NOT MODIFY


# 
# SEVEN_SEGMENT_CONTROLLER "SEVEN_SEGMENT_CONTROLLER" v1.0
#  2017.02.16.10:57:05
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module SEVEN_SEGMENT_CONTROLLER
# 
set_module_property DESCRIPTION ""
set_module_property NAME SEVEN_SEGMENT_CONTROLLER
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME SEVEN_SEGMENT_CONTROLLER
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL SEVEN_SEG_TOP
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file SEVEN_SEG_REGISTER.vhd VHDL PATH SEVEN_SEGMENT/SEVEN_SEG_REGISTER.vhd
add_fileset_file DOUBLE_DABBLE_8BIT.vhd VHDL PATH SEVEN_SEGMENT/DOUBLE_DABBLE_8BIT.vhd
add_fileset_file SEVEN_SEG_DPS.vhd VHDL PATH SEVEN_SEGMENT/SEVEN_SEG_DPS.vhd
add_fileset_file SEVEN_SEG_TOP.vhd VHDL PATH SEVEN_SEG_TOP.vhd TOP_LEVEL_FILE

add_fileset SIM_VHDL SIM_VHDL "" ""
set_fileset_property SIM_VHDL TOP_LEVEL SEVEN_SEG_TOP
set_fileset_property SIM_VHDL ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property SIM_VHDL ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file SEVEN_SEG_REGISTER.vhd VHDL PATH SEVEN_SEGMENT/SEVEN_SEG_REGISTER.vhd
add_fileset_file DOUBLE_DABBLE_8BIT.vhd VHDL PATH SEVEN_SEGMENT/DOUBLE_DABBLE_8BIT.vhd
add_fileset_file SEVEN_SEG_DPS.vhd VHDL PATH SEVEN_SEGMENT/SEVEN_SEG_DPS.vhd
add_fileset_file SEVEN_SEG_TOP.vhd VHDL PATH SEVEN_SEG_TOP.vhd TOP_LEVEL_FILE


# 
# parameters
# 


# 
# display items
# 


# 
# connection point SSDP_avalon_slave
# 
add_interface SSDP_avalon_slave avalon end
set_interface_property SSDP_avalon_slave addressUnits WORDS
set_interface_property SSDP_avalon_slave associatedClock SSDP_CLK
set_interface_property SSDP_avalon_slave associatedReset SSDP_RST
set_interface_property SSDP_avalon_slave bitsPerSymbol 8
set_interface_property SSDP_avalon_slave burstOnBurstBoundariesOnly false
set_interface_property SSDP_avalon_slave burstcountUnits WORDS
set_interface_property SSDP_avalon_slave explicitAddressSpan 0
set_interface_property SSDP_avalon_slave holdTime 0
set_interface_property SSDP_avalon_slave linewrapBursts false
set_interface_property SSDP_avalon_slave maximumPendingReadTransactions 0
set_interface_property SSDP_avalon_slave maximumPendingWriteTransactions 0
set_interface_property SSDP_avalon_slave readLatency 0
set_interface_property SSDP_avalon_slave readWaitTime 1
set_interface_property SSDP_avalon_slave setupTime 0
set_interface_property SSDP_avalon_slave timingUnits Cycles
set_interface_property SSDP_avalon_slave writeWaitTime 0
set_interface_property SSDP_avalon_slave ENABLED true
set_interface_property SSDP_avalon_slave EXPORT_OF ""
set_interface_property SSDP_avalon_slave PORT_NAME_MAP ""
set_interface_property SSDP_avalon_slave CMSIS_SVD_VARIABLES ""
set_interface_property SSDP_avalon_slave SVD_ADDRESS_GROUP ""

add_interface_port SSDP_avalon_slave AVALON_SLAVE_ADDRESS address Input 1
add_interface_port SSDP_avalon_slave AVALON_SLAVE_WRITEDATA writedata Input 32
add_interface_port SSDP_avalon_slave AVALON_SLAVE_WRITE write Input 1
set_interface_assignment SSDP_avalon_slave embeddedsw.configuration.isFlash 0
set_interface_assignment SSDP_avalon_slave embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment SSDP_avalon_slave embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment SSDP_avalon_slave embeddedsw.configuration.isPrintableDevice 0


# 
# connection point SSDP_CLK
# 
add_interface SSDP_CLK clock end
set_interface_property SSDP_CLK clockRate 0
set_interface_property SSDP_CLK ENABLED true
set_interface_property SSDP_CLK EXPORT_OF ""
set_interface_property SSDP_CLK PORT_NAME_MAP ""
set_interface_property SSDP_CLK CMSIS_SVD_VARIABLES ""
set_interface_property SSDP_CLK SVD_ADDRESS_GROUP ""

add_interface_port SSDP_CLK CLK clk Input 1


# 
# connection point SSDP_RST
# 
add_interface SSDP_RST reset end
set_interface_property SSDP_RST associatedClock SSDP_CLK
set_interface_property SSDP_RST synchronousEdges DEASSERT
set_interface_property SSDP_RST ENABLED true
set_interface_property SSDP_RST EXPORT_OF ""
set_interface_property SSDP_RST PORT_NAME_MAP ""
set_interface_property SSDP_RST CMSIS_SVD_VARIABLES ""
set_interface_property SSDP_RST SVD_ADDRESS_GROUP ""

add_interface_port SSDP_RST RST reset Input 1


# 
# connection point SSDP_conduit
# 
add_interface SSDP_conduit conduit end
set_interface_property SSDP_conduit associatedClock SSDP_CLK
set_interface_property SSDP_conduit associatedReset SSDP_RST
set_interface_property SSDP_conduit ENABLED true
set_interface_property SSDP_conduit EXPORT_OF ""
set_interface_property SSDP_conduit PORT_NAME_MAP ""
set_interface_property SSDP_conduit CMSIS_SVD_VARIABLES ""
set_interface_property SSDP_conduit SVD_ADDRESS_GROUP ""

add_interface_port SSDP_conduit SEVEN_SEG_DSP0_OUT ssdp0 Output 8
add_interface_port SSDP_conduit SEVEN_SEG_DSP1_OUT ssdp1 Output 8

