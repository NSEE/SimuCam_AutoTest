// megafunction wizard: %ALTIOBUF%
// GENERATION: STANDARD
// VERSION: WM1.0
// MODULE: altiobuf_out 

// ============================================================
// File Name: spwc_spw_tx_altiobuf.v
// Megafunction Name(s):
// 			altiobuf_out
//
// Simulation Library Files(s):
// 			stratixiv
// ============================================================
// ************************************************************
// THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
//
// 18.1.0 Build 625 09/12/2018 SJ Standard Edition
// ************************************************************


//Copyright (C) 2018  Intel Corporation. All rights reserved.
//Your use of Intel Corporation's design tools, logic functions 
//and other software and tools, and its AMPP partner logic 
//functions, and any output files from any of the foregoing 
//(including device programming or simulation files), and any 
//associated documentation or information are expressly subject 
//to the terms and conditions of the Intel Program License 
//Subscription Agreement, the Intel Quartus Prime License Agreement,
//the Intel FPGA IP License Agreement, or other applicable license
//agreement, including, without limitation, that your use is for
//the sole purpose of programming logic devices manufactured by
//Intel and sold by Intel or its authorized distributors.  Please
//refer to the applicable agreement for further details.


//altiobuf_out DEVICE_FAMILY="Stratix IV" ENABLE_BUS_HOLD="FALSE" LEFT_SHIFT_SERIES_TERMINATION_CONTROL="FALSE" NUMBER_OF_CHANNELS=2 OPEN_DRAIN_OUTPUT="FALSE" PSEUDO_DIFFERENTIAL_MODE="FALSE" USE_DIFFERENTIAL_MODE="TRUE" USE_OE="FALSE" USE_TERMINATION_CONTROL="FALSE" datain dataout dataout_b
//VERSION_BEGIN 18.1 cbx_altiobuf_out 2018:09:12:13:04:24:SJ cbx_mgl 2018:09:12:13:10:36:SJ cbx_stratixiii 2018:09:12:13:04:24:SJ cbx_stratixv 2018:09:12:13:04:24:SJ  VERSION_END
// synthesis VERILOG_INPUT_VERSION VERILOG_2001
// altera message_off 10463


//synthesis_resources = stratixiv_io_obuf 2 
//synopsys translate_off
`timescale 1 ps / 1 ps
//synopsys translate_on
module  spwc_spw_tx_altiobuf_iobuf_out
	( 
	datain,
	dataout,
	dataout_b) /* synthesis synthesis_clearbox=1 */;
	input   [1:0]  datain;
	output   [1:0]  dataout;
	output   [1:0]  dataout_b;

	wire  [1:0]   wire_obufa_i;
	wire  [1:0]   wire_obufa_o;
	wire  [1:0]   wire_obufa_obar;
	wire  [1:0]   wire_obufa_oe;
	wire  [1:0]  oe_w;

	stratixiv_io_obuf   obufa_0
	( 
	.i(wire_obufa_i[0:0]),
	.o(wire_obufa_o[0:0]),
	.obar(wire_obufa_obar[0:0]),
	.oe(wire_obufa_oe[0:0])
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.dynamicterminationcontrol(1'b0),
	.parallelterminationcontrol({14{1'b0}}),
	.seriesterminationcontrol({14{1'b0}})
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	// synopsys translate_off
	,
	.devoe(1'b1)
	// synopsys translate_on
	);
	defparam
		obufa_0.bus_hold = "false",
		obufa_0.open_drain_output = "false",
		obufa_0.shift_series_termination_control = "false",
		obufa_0.lpm_type = "stratixiv_io_obuf";
	stratixiv_io_obuf   obufa_1
	( 
	.i(wire_obufa_i[1:1]),
	.o(wire_obufa_o[1:1]),
	.obar(wire_obufa_obar[1:1]),
	.oe(wire_obufa_oe[1:1])
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_off
	`endif
	,
	.dynamicterminationcontrol(1'b0),
	.parallelterminationcontrol({14{1'b0}}),
	.seriesterminationcontrol({14{1'b0}})
	`ifndef FORMAL_VERIFICATION
	// synopsys translate_on
	`endif
	// synopsys translate_off
	,
	.devoe(1'b1)
	// synopsys translate_on
	);
	defparam
		obufa_1.bus_hold = "false",
		obufa_1.open_drain_output = "false",
		obufa_1.shift_series_termination_control = "false",
		obufa_1.lpm_type = "stratixiv_io_obuf";
	assign
		wire_obufa_i = datain,
		wire_obufa_oe = oe_w;
	assign
		dataout = wire_obufa_o,
		dataout_b = wire_obufa_obar,
		oe_w = {2{1'b1}};
endmodule //spwc_spw_tx_altiobuf_iobuf_out
//VALID FILE


// synopsys translate_off
`timescale 1 ps / 1 ps
// synopsys translate_on
module spwc_spw_tx_altiobuf (
	datain,
	dataout,
	dataout_b)/* synthesis synthesis_clearbox = 1 */;

	input	[1:0]  datain;
	output	[1:0]  dataout;
	output	[1:0]  dataout_b;

	wire [1:0] sub_wire0;
	wire [1:0] sub_wire1;
	wire [1:0] dataout = sub_wire0[1:0];
	wire [1:0] dataout_b = sub_wire1[1:0];

	spwc_spw_tx_altiobuf_iobuf_out	spwc_spw_tx_altiobuf_iobuf_out_component (
				.datain (datain),
				.dataout (sub_wire0),
				.dataout_b (sub_wire1));

endmodule

// ============================================================
// CNX file retrieval info
// ============================================================
// Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "Stratix IV"
// Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "1"
// Retrieval info: LIBRARY: altera_mf altera_mf.altera_mf_components.all
// Retrieval info: CONSTANT: INTENDED_DEVICE_FAMILY STRING "Stratix IV"
// Retrieval info: CONSTANT: enable_bus_hold STRING "FALSE"
// Retrieval info: CONSTANT: left_shift_series_termination_control STRING "FALSE"
// Retrieval info: CONSTANT: number_of_channels NUMERIC "2"
// Retrieval info: CONSTANT: open_drain_output STRING "FALSE"
// Retrieval info: CONSTANT: pseudo_differential_mode STRING "FALSE"
// Retrieval info: CONSTANT: use_differential_mode STRING "TRUE"
// Retrieval info: CONSTANT: use_oe STRING "FALSE"
// Retrieval info: CONSTANT: use_termination_control STRING "FALSE"
// Retrieval info: USED_PORT: datain 0 0 2 0 INPUT NODEFVAL "datain[1..0]"
// Retrieval info: USED_PORT: dataout 0 0 2 0 OUTPUT NODEFVAL "dataout[1..0]"
// Retrieval info: USED_PORT: dataout_b 0 0 2 0 OUTPUT NODEFVAL "dataout_b[1..0]"
// Retrieval info: CONNECT: @datain 0 0 2 0 datain 0 0 2 0
// Retrieval info: CONNECT: dataout 0 0 2 0 @dataout 0 0 2 0
// Retrieval info: CONNECT: dataout_b 0 0 2 0 @dataout_b 0 0 2 0
// Retrieval info: GEN_FILE: TYPE_NORMAL spwc_spw_tx_altiobuf.vhd TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL spwc_spw_tx_altiobuf.inc TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL spwc_spw_tx_altiobuf.cmp TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL spwc_spw_tx_altiobuf.bsf TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL spwc_spw_tx_altiobuf_inst.vhd TRUE
// Retrieval info: GEN_FILE: TYPE_NORMAL spwc_spw_tx_altiobuf_syn.v TRUE
// Retrieval info: LIB_FILE: stratixiv
