----------------------------------------------------------------------------
--	divider1MHz.vhd - Módulo para dividir la frecuencia del reloj a 1 MHz
----------------------------------------------------------------------------
-- Autor:  		 			Pavel Gregar
-- Datum vytvoreni:    	11:07:24 11/27/2013
-- Modul:    				divider1MHz - Behavioral 
-- Projekt: 				Meteostanice
-- Cilove zarizeni: 		Nexys4
-- Pouzite nastroje:		Xilinx 14.6
----------------------------------------------------------------------------
--
----------------------------------------------------------------------------
--	Este modulo se utiliza para dividir el reloj de los sensores DS18B20, DHT11, 
-- DHT22 y ADT7420. La señal de salida de los sensores tiene una frecuencia de 1MHz.
--         				
-- Puertos del modulo:
--
--		clk_in			- Reloj de 100 MHz
--		clk_out			- Reloj dividido clk_in/100 = 1 MHz.
--
----------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity divider1MHz is
    Port ( clk_in 	: IN	STD_LOGIC;
           clk_out 	: OUT	STD_LOGIC
	 );
end divider1MHz;

architecture Behavioral of divider1MHz is

SIGNAL count: INTEGER RANGE 0 to 99; 

begin

	-- Proceso para dividir el ciclo de reloj 1/100
	process (clk_in)
	begin
		if (rising_edge(clk_in)) then
			count <= count + 1;				
			if (count = 49) then		    --	fin del contador
				count <= 0;						
				clk_out <= '1';				-- configuracion de la señal de salida
			else
				clk_out <= '0';				-- anulacion de la señal de salida
			end if;
		end if;
	end process;

end Behavioral;
