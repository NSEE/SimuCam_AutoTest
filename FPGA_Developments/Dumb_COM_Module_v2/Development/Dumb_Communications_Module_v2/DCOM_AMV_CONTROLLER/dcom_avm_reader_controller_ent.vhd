
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

use work.dcom_avm_data_pkg.all;

entity dcom_avm_reader_controller_ent is
	port(
		clk_i                        : in  std_logic;
		rst_i                        : in  std_logic;
		tmr_stop_i                   : in  std_logic;
		tmr_start_i                  : in  std_logic;
		controller_rd_start_i        : in  std_logic;
		controller_rd_reset_i        : in  std_logic;
		controller_rd_auto_restart_i : in  std_logic;
		controller_rd_initial_addr_i : in  std_logic_vector(63 downto 0);
		controller_rd_length_bytes_i : in  std_logic_vector(31 downto 0);
		controller_wr_busy_i         : in  std_logic;
		avm_master_rd_status_i       : in  t_dcom_avm_data_master_rd_status;
		data_buffer_full_i           : in  std_logic;
		be_buffer_full_i             : in  std_logic;
		controller_rd_busy_o         : out std_logic;
		avm_master_rd_control_o      : out t_dcom_avm_data_master_rd_control;
		data_buffer_wrdata_o         : out std_logic_vector(63 downto 0);
		data_buffer_wrreq_o          : out std_logic;
		be_buffer_wrdata_o           : out std_logic_vector(7 downto 0);
		be_buffer_wrreq_o            : out std_logic
	);
end entity dcom_avm_reader_controller_ent;

architecture RTL of dcom_avm_reader_controller_ent is

	type t_dcom_avm_reader_controller_fsm is (
		STOPPED,                        -- avm reader controller is stopped
		IDLE,                           -- avm reader controller is in idle
		AVM_WAITING,                    -- avm reader is waiting the avm bus be released
		BUFFER_WAITING,                 -- waiting windowing buffer 
		READ_START,                     -- start of a avm read
		READ_WAITING,                   -- wait for avm read to finish
		BUFFER_WRITE,                   -- write windowing buffer
		FINISHED                        -- avm reader controller is finished
	);

	signal s_dcom_avm_reader_controller_state : t_dcom_avm_reader_controller_fsm;

	signal s_rd_addr_cnt : unsigned(60 downto 0); -- 2^64 bytes of address / 8 bytes per word = 2^61 words of addr
	signal s_rd_data_cnt : unsigned(28 downto 0); -- 2^32 bytes of maximum length / 8 bytes per read = 2^29 maximum read length

	constant c_RD_ADDR_OVERFLOW_VAL : unsigned((s_rd_addr_cnt'length - 1) downto 0) := (others => '1');

	signal s_auto_restart : std_logic;

begin

	p_dcom_avm_reader_controller : process(clk_i, rst_i) is
		variable v_dcom_avm_reader_controller_state : t_dcom_avm_reader_controller_fsm := STOPPED;
	begin
		if (rst_i = '1') then
			-- fsm state reset
			s_dcom_avm_reader_controller_state <= STOPPED;
			v_dcom_avm_reader_controller_state := STOPPED;
			-- internal signals reset
			s_rd_addr_cnt                      <= to_unsigned(0, s_rd_addr_cnt'length);
			s_rd_data_cnt                      <= to_unsigned(0, s_rd_data_cnt'length);
			s_auto_restart                     <= '0';
			-- outputs reset
			controller_rd_busy_o               <= '0';
			avm_master_rd_control_o            <= c_DCOM_AVM_DATA_MASTER_RD_CONTROL_RST;
			data_buffer_wrdata_o               <= (others => '0');
			data_buffer_wrreq_o                <= '0';
			be_buffer_wrdata_o                 <= (others => '0');
			be_buffer_wrreq_o                  <= '0';
		elsif rising_edge(clk_i) then

			-- States Transition --
			-- States transitions FSM
			case (s_dcom_avm_reader_controller_state) is

				-- state "STOPPED"
				when STOPPED =>
					-- avm reader controller is stopped
					-- default state transition
					s_dcom_avm_reader_controller_state <= STOPPED;
					v_dcom_avm_reader_controller_state := STOPPED;
					-- default internal signal values
					s_rd_addr_cnt                      <= to_unsigned(0, s_rd_addr_cnt'length);
					s_rd_data_cnt                      <= to_unsigned(0, s_rd_data_cnt'length);
					s_auto_restart                     <= '0';
					-- conditional state transition
					-- check if a start was issued
					if (tmr_start_i = '1') then
						-- start issued, go to idle
						s_dcom_avm_reader_controller_state <= IDLE;
						v_dcom_avm_reader_controller_state := IDLE;
					end if;

				-- state "IDLE"
				when IDLE =>
					-- avm reader controller is in idle
					-- default state transition
					s_dcom_avm_reader_controller_state <= IDLE;
					v_dcom_avm_reader_controller_state := IDLE;
					-- default internal signal values
					s_rd_addr_cnt                      <= to_unsigned(0, s_rd_addr_cnt'length);
					s_rd_data_cnt                      <= to_unsigned(0, s_rd_data_cnt'length);
					s_auto_restart                     <= '0';
					-- conditional state transition
					-- check if a read start or a auto restart were requested
					if ((controller_rd_start_i = '1') or (s_auto_restart = '1')) then
						-- read start requested
						-- set read parameters
						-- set the read addr counter to the (read initial addr / 8)
						s_rd_addr_cnt <= unsigned(controller_rd_initial_addr_i(63 downto 3));
						-- set the read data counter to the (read data length / 8)
						s_rd_data_cnt <= unsigned(controller_rd_length_bytes_i(31 downto 3));
						-- check if the read data length is aligned to 8 bytes and is not already zero
						if ((controller_rd_length_bytes_i(2 downto 0) = "000") and (s_rd_data_cnt /= 0)) then
							-- the read data length is aligned to 8 bytes and is not already zero
							-- decrement the read data counter
							s_rd_data_cnt <= s_rd_data_cnt - 1;
						end if;
						-- check if the avm writer controller is busy (using the avm bus)
						if (controller_wr_busy_i = '1') then
							-- the avm writer controller is busy (using the avm bus)
							-- go to avm waiting
							s_dcom_avm_reader_controller_state <= AVM_WAITING;
							v_dcom_avm_reader_controller_state := AVM_WAITING;
						else
							-- the avm writer controller is free (not using the avm bus)
							-- go to buffer waiting
							s_dcom_avm_reader_controller_state <= BUFFER_WAITING;
							v_dcom_avm_reader_controller_state := BUFFER_WAITING;
						end if;
					end if;

				-- state "AVM_WAITING"
				when AVM_WAITING =>
					-- avm reader is waiting the avm bus be released
					-- default state transition
					s_dcom_avm_reader_controller_state <= AVM_WAITING;
					v_dcom_avm_reader_controller_state := AVM_WAITING;
					-- default internal signal values
					s_auto_restart                     <= '0';
					-- conditional state transition
					-- check if the avm writer controller is free (not using the avm bus)
					if (controller_wr_busy_i = '0') then
						-- the avm writer controller is free (not using the avm bus)
						-- go to buffer waiting
						s_dcom_avm_reader_controller_state <= BUFFER_WAITING;
						v_dcom_avm_reader_controller_state := BUFFER_WAITING;
					end if;

				-- state "BUFFER_WAITING"
				when BUFFER_WAITING =>
					-- waiting windowing buffer
					-- default state transition
					s_dcom_avm_reader_controller_state <= BUFFER_WAITING;
					v_dcom_avm_reader_controller_state := BUFFER_WAITING;
					-- default internal signal values
					s_auto_restart                     <= '0';
					-- conditional state transition
					-- check if the data buffer and be buffer are not full and the avm read can start
					if ((data_buffer_full_i = '0') and (be_buffer_full_i = '0') and (avm_master_rd_status_i.rd_able = '1')) then
						-- the tx data buffer is ready to be written and not full and the avm read can start
						-- go to read start
						s_dcom_avm_reader_controller_state <= READ_START;
						v_dcom_avm_reader_controller_state := READ_START;
					end if;

				-- state "READ_START"
				when READ_START =>
					-- start of a avm read
					-- default state transition
					s_dcom_avm_reader_controller_state <= READ_WAITING;
					v_dcom_avm_reader_controller_state := READ_WAITING;
					-- default internal signal values
					s_auto_restart                     <= '0';
				-- conditional state transition

				-- state "READ_WAITING"
				when READ_WAITING =>
					-- wait for avm read to finish
					-- default state transition
					s_dcom_avm_reader_controller_state <= READ_WAITING;
					v_dcom_avm_reader_controller_state := READ_WAITING;
					-- default internal signal values
					s_auto_restart                     <= '0';
					-- conditional state transition
					-- check if the avm read have valid data (is finished)
					if (avm_master_rd_status_i.rd_valid = '1') then
						-- avm read have valid data (is finished)
						-- update read addr counter
						-- check if the read addr counter will overflow
						if (s_rd_addr_cnt = c_RD_ADDR_OVERFLOW_VAL) then
							-- the read addr counter will overflow
							-- clear the read addr counter
							s_rd_addr_cnt <= to_unsigned(0, s_rd_addr_cnt'length);
						else
							-- the read addr counter will not overflow
							-- increment the read addr counter
							s_rd_addr_cnt <= s_rd_addr_cnt + 1;
						end if;
						-- go to write buffer
						s_dcom_avm_reader_controller_state <= BUFFER_WRITE;
						v_dcom_avm_reader_controller_state := BUFFER_WRITE;
					end if;

				-- state "BUFFER_WRITE"
				when BUFFER_WRITE =>
					-- write windowing buffer
					-- default state transition
					s_dcom_avm_reader_controller_state <= FINISHED;
					v_dcom_avm_reader_controller_state := FINISHED;
					-- default internal signal values
					s_auto_restart                     <= '0';
					-- conditional state transition
					-- check if there is more data to be read
					if (s_rd_data_cnt /= 0) then
						-- there is more data to be read
						-- decrement read data counter
						s_rd_data_cnt <= s_rd_data_cnt - 1;
						-- check if the data buffer and be buffer are not full and the avm read can start
						if ((data_buffer_full_i = '0') and (be_buffer_full_i = '0') and (avm_master_rd_status_i.rd_able = '1')) then
							-- the rx data buffer is ready to be written and not full and the avm read can start
							-- go to read start
							s_dcom_avm_reader_controller_state <= READ_START;
							v_dcom_avm_reader_controller_state := READ_START;
						else
							-- the windowing buffer is locked
							-- go to buffer waiting
							s_dcom_avm_reader_controller_state <= BUFFER_WAITING;
							v_dcom_avm_reader_controller_state := BUFFER_WAITING;
						end if;
					end if;

				-- state "FINISHED"
				when FINISHED =>
					-- avm reader controller is finished
					-- default state transition
					s_dcom_avm_reader_controller_state <= IDLE;
					v_dcom_avm_reader_controller_state := IDLE;
					-- default internal signal values
					s_rd_addr_cnt                      <= to_unsigned(0, s_rd_addr_cnt'length);
					s_rd_data_cnt                      <= to_unsigned(0, s_rd_data_cnt'length);
					s_auto_restart                     <= '0';
					-- conditional state transition
					-- check if an auto restart was commanded
					if (controller_rd_auto_restart_i = '1') then
						-- set the auto restart flag
						s_auto_restart <= '1';
					end if;

				-- all the other states (not defined)
				when others =>
					s_dcom_avm_reader_controller_state <= STOPPED;
					v_dcom_avm_reader_controller_state := STOPPED;

			end case;

			-- check if a stop was issued
			if (tmr_stop_i = '1') then
				-- a stop was issued
				-- go to stopped
				s_dcom_avm_reader_controller_state <= STOPPED;
				v_dcom_avm_reader_controller_state := STOPPED;
			-- check if a reset was requested
			elsif (controller_rd_reset_i = '1') then
				-- a reset was requested
				-- go to idle
				s_dcom_avm_reader_controller_state <= IDLE;
				v_dcom_avm_reader_controller_state := IDLE;
				-- clear auto restart flag
				s_auto_restart                     <= '0';
			end if;

			-- Output Generation --
			-- Default output generation
			controller_rd_busy_o    <= '0';
			avm_master_rd_control_o <= c_DCOM_AVM_DATA_MASTER_RD_CONTROL_RST;
			data_buffer_wrdata_o    <= (others => '0');
			data_buffer_wrreq_o     <= '0';
			be_buffer_wrdata_o      <= (others => '0');
			be_buffer_wrreq_o       <= '0';
			-- Output generation FSM
			case (v_dcom_avm_reader_controller_state) is

				-- state "STOPPED"
				when STOPPED =>
					-- avm reader controller is stopped
					-- default output signals
					null;
				-- conditional output signals

				-- state "IDLE"
				when IDLE =>
					-- avm reader controller is in idle
					-- default output signals
					null;
				-- conditional output signals

				-- state "AVM_WAITING"
				when AVM_WAITING =>
					-- avm reader is waiting the avm bus be released
					-- default output signals
					controller_rd_busy_o <= '1';
				-- conditional output signals

				-- state "BUFFER_WAITING"
				when BUFFER_WAITING =>
					-- waiting windowing buffer
					-- default output signals
					controller_rd_busy_o <= '1';
				-- conditional output signals

				-- state "READ_START"
				when READ_START =>
					-- start of a avm read
					-- default output signals
					controller_rd_busy_o                            <= '1';
					avm_master_rd_control_o.rd_req                  <= '1';
					avm_master_rd_control_o.rd_address(63 downto 3) <= std_logic_vector(s_rd_addr_cnt);
					avm_master_rd_control_o.rd_address(2 downto 0)  <= (others => '0');
				-- conditional output signals

				-- state "READ_WAITING"
				when READ_WAITING =>
					-- wait for avm read to finish
					-- default output signals
					controller_rd_busy_o <= '1';
				-- conditional output signals

				-- state "BUFFER_WRITE"
				when BUFFER_WRITE =>
					-- write windowing buffer
					-- default output signals
					controller_rd_busy_o <= '1';
					data_buffer_wrdata_o <= avm_master_rd_status_i.rd_data;
					data_buffer_wrreq_o  <= '1';
					be_buffer_wrdata_o   <= (others => '1');
					be_buffer_wrreq_o    <= '1';
				-- conditional output signals

				-- state "FINISHED"
				when FINISHED =>
					-- avm reader controller is finished
					-- default output signals
					controller_rd_busy_o <= '1';
					-- conditional output signals

			end case;

		end if;
	end process p_dcom_avm_reader_controller;

end architecture RTL;
