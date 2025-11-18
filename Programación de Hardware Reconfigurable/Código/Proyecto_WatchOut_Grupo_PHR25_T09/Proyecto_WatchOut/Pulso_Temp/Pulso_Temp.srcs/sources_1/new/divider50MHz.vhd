----------------------------------------------------------------------------
-- divider50MHz.vhd - Módulo para dividir la frecuencia del reloj a 50 MHz
----------------------------------------------------------------------------
--
-- Este módulo se encarga de dividir la frecuencia de un reloj de entrada
-- por dos, generando una señal de reloj de salida a 50 MHz. Se utiliza
-- para proporcionar una señal de reloj adecuada para otros módulos del sistema
-- que requieren una frecuencia de operación menor.
--
-- Puertos del módulo:
--
--      clk_in  - Reloj de entrada del sistema
--      clk_out - Reloj de salida a 50 MHz
--
----------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity divider50MHz is
    Port ( clk_in  : in  STD_LOGIC;
           clk_out : out STD_LOGIC);
end divider50MHz;

architecture Behavioral of divider50MHz is
    signal clk_div : STD_LOGIC := '0';
begin
    process(clk_in)
    begin
        if rising_edge(clk_in) then
            clk_div <= not clk_div;  -- Toggle para dividir por 2
        end if;
    end process;

    clk_out <= clk_div;
end Behavioral;
