-- megafunction wizard: %ALTIOBUF%
-- GENERATION: STANDARD
-- VERSION: WM1.0
-- MODULE: altiobuf_in 

-- ============================================================
-- File Name: ftdi_in_io_buffer_3b.vhd
-- Megafunction Name(s):
-- 			altiobuf_in
--
-- Simulation Library Files(s):
-- 			stratixiv
-- ============================================================
-- ************************************************************
-- THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
--
-- 18.1.0 Build 625 09/12/2018 SJ Standard Edition
-- ************************************************************


--Copyright (C) 2018  Intel Corporation. All rights reserved.
--Your use of Intel Corporation's design tools, logic functions 
--and other software and tools, and its AMPP partner logic 
--functions, and any output files from any of the foregoing 
--(including device programming or simulation files), and any 
--associated documentation or information are expressly subject 
--to the terms and conditions of the Intel Program License 
--Subscription Agreement, the Intel Quartus Prime License Agreement,
--the Intel FPGA IP License Agreement, or other applicable license
--agreement, including, without limitation, that your use is for
--the sole purpose of programming logic devices manufactured by
--Intel and sold by Intel or its authorized distributors.  Please
--refer to the applicable agreement for further details.


--altiobuf_in CBX_AUTO_BLACKBOX="ALL" DEVICE_FAMILY="Stratix IV" ENABLE_BUS_HOLD="FALSE" NUMBER_OF_CHANNELS=3 USE_DIFFERENTIAL_MODE="FALSE" USE_DYNAMIC_TERMINATION_CONTROL="FALSE" datain dataout
--VERSION_BEGIN 18.1 cbx_altiobuf_in 2018:09:12:13:04:24:SJ cbx_mgl 2018:09:12:13:10:36:SJ cbx_stratixiii 2018:09:12:13:04:24:SJ cbx_stratixv 2018:09:12:13:04:24:SJ  VERSION_END

 LIBRARY stratixiv;
 USE stratixiv.all;

--synthesis_resources = stratixiv_io_ibuf 3 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  ftdi_in_io_buffer_3b_iobuf_in_c5i IS 
	 PORT 
	 ( 
		 datain	:	IN  STD_LOGIC_VECTOR (2 DOWNTO 0);
		 dataout	:	OUT  STD_LOGIC_VECTOR (2 DOWNTO 0)
	 ); 
 END ftdi_in_io_buffer_3b_iobuf_in_c5i;

 ARCHITECTURE RTL OF ftdi_in_io_buffer_3b_iobuf_in_c5i IS

	 SIGNAL  wire_ibufa_i	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 SIGNAL  wire_ibufa_o	:	STD_LOGIC_VECTOR (2 DOWNTO 0);
	 COMPONENT  stratixiv_io_ibuf
	 GENERIC 
	 (
		bus_hold	:	STRING := "false";
		differential_mode	:	STRING := "false";
		simulate_z_as	:	STRING := "Z";
		lpm_type	:	STRING := "stratixiv_io_ibuf"
	 );
	 PORT
	 ( 
		dynamicterminationcontrol	:	IN STD_LOGIC := '0';
		i	:	IN STD_LOGIC := '0';
		ibar	:	IN STD_LOGIC := '0';
		o	:	OUT STD_LOGIC
	 ); 
	 END COMPONENT;
 BEGIN

	dataout <= wire_ibufa_o;
	wire_ibufa_i <= datain;
	loop0 : FOR i IN 0 TO 2 GENERATE 
	  ibufa :  stratixiv_io_ibuf
	  GENERIC MAP (
		bus_hold => "false",
		differential_mode => "false"
	  )
	  PORT MAP ( 
		i => wire_ibufa_i(i),
		o => wire_ibufa_o(i)
	  );
	END GENERATE loop0;

 END RTL; --ftdi_in_io_buffer_3b_iobuf_in_c5i
--VALID FILE


LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY ftdi_in_io_buffer_3b IS
	PORT
	(
		datain		: IN STD_LOGIC_VECTOR (2 DOWNTO 0);
		dataout		: OUT STD_LOGIC_VECTOR (2 DOWNTO 0)
	);
END ftdi_in_io_buffer_3b;


ARCHITECTURE RTL OF ftdi_in_io_buffer_3b IS

	SIGNAL sub_wire0	: STD_LOGIC_VECTOR (2 DOWNTO 0);



	COMPONENT ftdi_in_io_buffer_3b_iobuf_in_c5i
	PORT (
			datain	: IN STD_LOGIC_VECTOR (2 DOWNTO 0);
			dataout	: OUT STD_LOGIC_VECTOR (2 DOWNTO 0)
	);
	END COMPONENT;

BEGIN
	dataout    <= sub_wire0(2 DOWNTO 0);

	ftdi_in_io_buffer_3b_iobuf_in_c5i_component : ftdi_in_io_buffer_3b_iobuf_in_c5i
	PORT MAP (
		datain => datain,
		dataout => sub_wire0
	);



END RTL;

-- ============================================================
-- CNX file retrieval info
-- ============================================================
-- Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "Stratix IV"
-- Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "1"
-- Retrieval info: LIBRARY: altera_mf altera_mf.altera_mf_components.all
-- Retrieval info: CONSTANT: INTENDED_DEVICE_FAMILY STRING "Stratix IV"
-- Retrieval info: CONSTANT: enable_bus_hold STRING "FALSE"
-- Retrieval info: CONSTANT: number_of_channels NUMERIC "3"
-- Retrieval info: CONSTANT: use_differential_mode STRING "FALSE"
-- Retrieval info: CONSTANT: use_dynamic_termination_control STRING "FALSE"
-- Retrieval info: USED_PORT: datain 0 0 3 0 INPUT NODEFVAL "datain[2..0]"
-- Retrieval info: USED_PORT: dataout 0 0 3 0 OUTPUT NODEFVAL "dataout[2..0]"
-- Retrieval info: CONNECT: @datain 0 0 3 0 datain 0 0 3 0
-- Retrieval info: CONNECT: dataout 0 0 3 0 @dataout 0 0 3 0
-- Retrieval info: GEN_FILE: TYPE_NORMAL ftdi_in_io_buffer_3b.vhd TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL ftdi_in_io_buffer_3b.inc TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL ftdi_in_io_buffer_3b.cmp TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL ftdi_in_io_buffer_3b.bsf TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL ftdi_in_io_buffer_3b_inst.vhd TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL ftdi_in_io_buffer_3b_syn.v TRUE
-- Retrieval info: LIB_FILE: stratixiv
