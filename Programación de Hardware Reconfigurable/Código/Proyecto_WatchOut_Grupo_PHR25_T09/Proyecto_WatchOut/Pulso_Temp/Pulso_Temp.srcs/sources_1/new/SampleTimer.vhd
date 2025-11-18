----------------------------------------------------------------------------
-- SampleTimer.vhd - Módulo para generar un pulso de muestreo cada 2 ms
----------------------------------------------------------------------------
--
-- Este módulo genera una señal de tick cada 2 ms, que se utiliza para
-- sincronizar el muestreo de datos del sensor de pulso. La frecuencia de
-- muestreo es crucial para la medición precisa del ritmo cardíaco.
--
-- Puertos del módulo:
--
--      clk          - Reloj de sistema de 100 MHz
--      rst          - Señal de reset para inicializar el contador
--      sample_tick  - Pulso de salida generado cada 2 ms
--
----------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity SampleTimer is
    Port (
        clk         : in  std_logic;    -- reloj de sistema (ej: 50 MHz)
        rst         : in  std_logic;
        sample_tick : out std_logic     -- pulso cada 2 ms
    );
end SampleTimer;

architecture Behavioral of SampleTimer is
    constant TICK_CYCLES : integer := 200_000; -- 2ms @ 100MHz
    signal counter       : integer := 0;
begin
    process(clk)
    begin
        if rising_edge(clk) then
            if rst = '1' then
                counter <= 0;
                sample_tick <= '0';
            elsif counter = TICK_CYCLES - 1 then
                counter <= 0;
                sample_tick <= '1';
            else
                counter <= counter + 1;
                sample_tick <= '0';
            end if;
        end if;
    end process;
end Behavioral;