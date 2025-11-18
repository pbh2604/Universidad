----------------------------------------------------------------------------
--	CRC.vhd - Modulo para comprobar los datos CRC del sensor DS18B20
----------------------------------------------------------------------------
-- Autor:  		 			Pavel Gregar
-- Datum vytvoreni:    	16:10:51 02/04/2014
-- Modul:    				CRC - Behavioral 
-- Projekt: 				Meteostanice
-- Cilove zarizeni: 		Nexys4
-- Pouzite nastroje:		Xilinx 14.6
----------------------------------------------------------------------------
--
----------------------------------------------------------------------------
--	Este modulo se utiliza para calcular el CRC de los datos recibidos del 
-- sensor DS18B20 segun la ecuacion:
-- CRC = x^8 + x^5 + x^4 + 1 mediante la LFSR y su comparacion con el CRC recibido.
-- El modulo se activa con un flanco ascendente en el puerto data_en.
--
-- Puertos del modulo:
--
--		clk				- Reloj de 100 MHz 
--		data_en			- iniciar el calculo de la suma de comprobacion
--		dataIn			- datos de entrada y CRC enviado
--		dataOut			- datos de salida (temperatura medida / error de CRC)
--		dataValid		- indicacion de finalizacion de la verificacion CRC de los datos recibidos
--
---------------------------------------------------------------------------- 
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity CRC is
    Port (	clk			: IN	STD_LOGIC;
				data_en		: IN	STD_LOGIC;
				dataIn 		: IN	STD_LOGIC_VECTOR (71 downto 0);
				dataOut	 	: OUT	STD_LOGIC_VECTOR (15 downto 0);
				dataValid	: OUT STD_LOGIC
	 );
end CRC;

architecture Behavioral of CRC is

    -- datos recibidos del sensor + CRC recibido
    SIGNAL data : STD_LOGIC_VECTOR(71 downto 0);
    
    -- estados FSM
    TYPE STATE_TYPE IS (IDLE, CRC_CALC, CRC_CHECK);
    SIGNAL crc_state: STATE_TYPE;


begin

	-- Proceso para el cálculo y verificación CRC de los datos recibidos
	process(clk)
	
	CONSTANT DATA_WIDTH_C	: INTEGER := 72;
	VARIABLE i : integer range 0 to DATA_WIDTH_C := 0;
	
	-- registro auxiliar para el calculo CRC
	VARIABLE CRC_temp			: STD_LOGIC_VECTOR(7 downto 0);
	-- registro CRC calculado
	VARIABLE CRC_val			: STD_LOGIC_VECTOR(7 downto 0);
	-- error CRC
	CONSTANT CRC_ERROR_C 		: STD_LOGIC_VECTOR(15 downto 0) := "0111111111111111";
	-- datos salida, sensor no conectado
	CONSTANT PRESENCE_ERROR_C 	: STD_LOGIC_VECTOR(15 downto 0) := "0011111111111111";
	-- datos de entrada, sensor no conectado 
	CONSTANT PRESENCE_ERROR_DATA_C : STD_LOGIC_VECTOR(71 downto 0) := "101010101010101010101010101010101010101010101010101010101010101010101010";
	
	begin
		if (rising_edge(clk)) then
			-- FSM que controla 
			case (crc_state) is
				when IDLE =>									 
					dataValid <= '0';								-- anulación de la señal que indica la finalización del cálculo CRC
					if (data_en = '1') then							-- solicitar calculo CRC
						crc_state <= CRC_CALC;						-- transicion al estado CRC_CALC
					end if;

				when CRC_CALC =>										
					if (i < DATA_WIDTH_C) then						-- inserción de datos en el registro de desplazamiento
						-- calculo CRC utilizando LFSR
						CRC_temp(7):= dataIn(i) XOR CRC_val(0);
						CRC_temp(2):= CRC_val(3) XOR (dataIn(i) XOR CRC_val(0));
						CRC_temp(3):= CRC_val(4) XOR (dataIn(i) XOR CRC_val(0));
						CRC_val(0) := CRC_val(1);
						CRC_val(1) := CRC_val(2);
						CRC_val(2) := CRC_temp(2);
						CRC_val(3) := CRC_temp(3);
						CRC_val(4) := CRC_val(5);
						CRC_val(5) := CRC_val(6);
						CRC_val(6) := CRC_val(7);
						CRC_val(7) := CRC_temp(7);
						i:=i+1;											
					else
						crc_state <= CRC_CHECK;						-- transicion al estado CRC_CHECK
					end if;

				when CRC_CHECK =>										
					if (CRC_val = "00000000") then				    -- CRC recibido coincide con el calculado
						dataOut <= dataIn(15 downto 0); 			-- contiene la temperatura medida
					else											-- CRC no coincide
						if (dataIn /= PRESENCE_ERROR_DATA_C) then	-- datos entrada contienen datos del sensor 
							dataOut <= CRC_ERROR_C; 				
						else
							dataOut <= PRESENCE_ERROR_C;			-- sensor no conectado
						end if;
					end if;
					CRC_temp := "00000000";						
					CRC_val := "00000000";						
					i := 0;									
					dataValid <= '1';								-- finalizacion del calculo CRC
					crc_state <= IDLE;								-- retorno al estado IDLE
			end case;
		end if;
	end process;

end Behavioral;