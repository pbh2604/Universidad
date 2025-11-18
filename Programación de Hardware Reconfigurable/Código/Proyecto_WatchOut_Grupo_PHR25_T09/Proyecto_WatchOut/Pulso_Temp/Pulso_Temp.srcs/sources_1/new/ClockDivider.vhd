----------------------------------------------------------------------------
-- ClockDivider.vhd - Módulo para dividir la frecuencia del reloj
----------------------------------------------------------------------------
--
-- Este módulo genera una señal de reloj de salida con una frecuencia reducida
-- basada en un divisor configurable. Se utiliza para generar la señal de reloj
-- adecuada para la comunicación SPI con el convertidor analógico-digital.
--
-- Puertos del módulo:
--
--      clk_i  - Reloj de entrada del sistema de 100MHz
--      rst_i  - Señal de reset para inicializar el contador
--      ena_o  - Pulso de salida a la frecuencia dividida
--
----------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ClockDivider is
    generic (
        -- Para 100 MHz input clock y 500kHz salida: DIVISOR = 200
        DIVISOR : integer := 200
    );
    port (
        clk_i  : in  std_logic;
        rst_i  : in  std_logic;
        ena_o  : out std_logic  -- Pulso de 1 ciclo a la frecuencia deseada
    );
end ClockDivider;

architecture Behavioral of ClockDivider is
    signal count : integer range 0 to DIVISOR - 1 := 0;
    signal tick  : std_logic := '0';
begin

    process(clk_i)
    begin
        if rising_edge(clk_i) then
            if rst_i = '1' then
                count <= 0;
                tick  <= '0';
            elsif count = DIVISOR - 1 then
                count <= 0;
                tick  <= '1';
            else
                count <= count + 1;
                tick  <= '0';
            end if;
        end if;
    end process;

    ena_o <= tick;

end Behavioral;
