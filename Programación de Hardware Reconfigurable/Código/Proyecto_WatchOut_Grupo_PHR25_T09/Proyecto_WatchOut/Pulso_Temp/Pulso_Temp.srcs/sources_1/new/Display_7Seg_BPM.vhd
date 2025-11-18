----------------------------------------------------------------------------
-- Display_7Seg_BPM.vhd - Módulo para controlar un display de 7 segmentos
----------------------------------------------------------------------------
--
-- Este módulo se encarga de convertir la señal de BPM (latidos por minuto)
-- en una representación visual en un display de 7 segmentos. Utiliza multiplexación
-- para mostrar cada dígito de forma secuencial, permitiendo la visualización
-- de valores numéricos de 0 a 9999 en el display.
--
-- Puertos del módulo:
--
--      clk - Reloj del sistema
--      bpm - Valor de latidos por minuto a mostrar
--      seg - Señales de salida para los segmentos del display
--      an  - Señales de salida para seleccionar el ánodo del display
--
----------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity Display_7Seg_BPM is
    Port (
        clk : in  std_logic;
        bpm : in  std_logic_vector(15 downto 0);
        seg : out std_logic_vector(6 downto 0);
        an  : out std_logic_vector(3 downto 0)
    );
end Display_7Seg_BPM;

architecture Behavioral of Display_7Seg_BPM is
    signal cnt : std_logic_vector(15 downto 0) := (others => '0');
    signal sel : std_logic_vector(1 downto 0) := "00";
    signal digit : std_logic_vector(3 downto 0);
    signal d_th, d_h, d_t, d_u : std_logic_vector(3 downto 0);
begin

    -- Contador de tiempo para multiplexado (~1 kHz)
    process(clk)
    begin
        if rising_edge(clk) then
            cnt <= cnt + 1;
            sel <= cnt(15 downto 14);  -- Rota cada ~1ms (con clk=100MHz)
        end if;
    end process;

    -- División en dígitos decimales (0-9999)
    process(bpm)
        variable value : integer := 0;
        variable thou, hund, ten, unit : integer;
    begin
        value := conv_integer(bpm);
        thou := value / 1000;
        hund := (value / 100) mod 10;
        ten  := (value / 10) mod 10;
        unit := value mod 10;

        d_th <= conv_std_logic_vector(thou, 4);
        d_h  <= conv_std_logic_vector(hund, 4);
        d_t  <= conv_std_logic_vector(ten, 4);
        d_u  <= conv_std_logic_vector(unit, 4);
    end process;

    -- Selección de dígito y ánodo activo
    process(sel)
    begin
        case sel is
            when "00" =>
                digit <= d_u;
                an <= "1110"; -- Activa an[0] (DIG4)
            when "01" =>
                digit <= d_t;
                an <= "1101"; -- Activa an[1] (DIG3)
            when "10" =>
                digit <= d_h;
                an <= "1011"; -- Activa an[2] (DIG2)
            when others =>
                digit <= d_th;
                an <= "1111"; -- No activa an[3] (DIG1 ignorado)
        end case;
    end process;

    -- Conversión binario -> 7 segmentos
    process(digit)
    begin
        case digit is
            when "0000" => seg <= "0111111"; -- 0: Enciende todos los segmentos excepto g
            when "0001" => seg <= "0000110"; -- 1: Enciende segmentos b y c
            when "0010" => seg <= "1011011"; -- 2: Enciende segmentos a, b, g, e, d
            when "0011" => seg <= "1001111"; -- 3: Enciende segmentos a, b, g, c, d
            when "0100" => seg <= "1100110"; -- 4: Enciende segmentos f, g, b, c
            when "0101" => seg <= "1101101"; -- 5: Enciende segmentos a, f, g, c, d
            when "0110" => seg <= "1111101"; -- 6: Enciende segmentos a, f, g, e, c, d
            when "0111" => seg <= "0000111"; -- 7: Enciende segmentos a, b, c
            when "1000" => seg <= "1111111"; -- 8: Enciende todos los segmentos
            when "1001" => seg <= "1101111"; -- 9: Enciende segmentos a, b, c, d, f, g
            when others => seg <= "0000000"; -- Apaga todos los segmentos
        end case;
    end process;

end Behavioral;
