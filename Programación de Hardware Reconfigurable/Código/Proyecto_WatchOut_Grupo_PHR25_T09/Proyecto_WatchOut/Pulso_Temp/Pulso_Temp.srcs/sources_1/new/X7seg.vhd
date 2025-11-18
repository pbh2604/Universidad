----------------------------------------------------------------------------
-- X7seg.vhd - Modulo para controlar un display de 7 segmentos de 4 dígitos
----------------------------------------------------------------------------
--
----------------------------------------------------------------------------
-- Este módulo se utiliza para controlar un display de 7 segmentos de 4 dígitos.
-- Toma una entrada de 16 bits y muestra su valor en formato hexadecimal en el
-- display. Además, maneja la multiplexación de los dígitos y el punto decimal.
--
-- Puertos del módulo:
--
--      x: entrada de 16 bits, valor hexadecimal a mostrar en el display
--      clk: entrada de reloj para la sincronización
--      clr: entrada para limpiar o reiniciar el contador del divisor de reloj
--      an: salida de 4 bits, selecciona qué dígito del display está activo
--      a_to_g: salida de 7 bits, controla los segmentos del display (a-g)
--      dp: salida de 1 bit, controla el punto decimal del display
--
----------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity X7seg is
    Port ( x : in  STD_LOGIC_VECTOR (15 downto 0);
           clk : in  STD_LOGIC;
           clr : in  STD_LOGIC;
           an : out  STD_LOGIC_VECTOR (3 downto 0);
           a_to_g : out  STD_LOGIC_VECTOR (6 downto 0);
           dp : out STD_LOGIC);
end X7seg;

architecture Behavioral of X7seg is

    signal s: std_logic_vector(1 downto 0);              -- señal para seleccionar el digito actual
    signal digit: std_logic_vector(3 downto 0);          -- valor del digito actual
    signal aen: std_logic_vector(3 downto 0);            
    signal clkdiv: std_logic_vector(19 downto 0);        -- contador para dividir la frecuencia del reloj

begin
    s <= clkdiv(19 downto 18);
    aen <= "1111";
    
    mux44: process (s,x)
    begin
        case s is
            when "00" => digit <= x(3 downto 0);           -- los 4 bits menos significativos
            when "01" => digit <= x(7 downto 4);           -- los siguientes 4 bits
            when "10" => digit <= x(11 downto 8);          -- los siguientes 4 bits
            when others => digit <= x(15 downto 12);       -- los 4 bits mas significativos
        end case;
        end process;
        
    -- proceso para convertir el valor hexadecimal a representacion en 7 segmentos
    hex7seg: process(digit)
    begin 
        case digit is
            when X"0" => a_to_g <= "0000001"; --0
            when X"1" => a_to_g <= "1001111"; --1
            when X"2" => a_to_g <= "0010010"; --2
            when X"3" => a_to_g <= "0000110"; --3
            when X"4" => a_to_g <= "1001100"; --4
            when X"5" => a_to_g <= "0100100"; --5
            when X"6" => a_to_g <= "0100000"; --6
            when X"7" => a_to_g <= "0001101"; --7
            when X"8" => a_to_g <= "0000000"; --8
            when X"9" => a_to_g <= "0000100"; --9
            when X"A" => a_to_g <= "0001000"; --A
            when X"B" => a_to_g <= "1100000"; --B
            when X"C" => a_to_g <= "0110001"; --C
            when X"D" => a_to_g <= "1000010"; --D
            when X"E" => a_to_g <= "0110000"; --E
            when others => a_to_g <= "0111000"; --F
        end case;
    end process;
    
    -- proceso para seleccionar que digito del display esta activo
    ancode: process(s, aen)
    begin
        an <= "1111";
        dp <= '1';
        if aen(conv_integer(s)) = '1' then
            an(conv_integer(s)) <= '0';      -- activa el digito seleccionado
            if s = "10" then                 -- activa el punto decimal solo para el tercer digito
                dp <= '0';                   -- encender el punto decimal
            end if;
        end if;
    end process;
    
    -- proceso para dividir la frecuencia del reloj y crear una multiplexacion
    clkdivider: process(clk,clr)
    begin
        if clr = '1' then
            clkdiv <= (others => '0');
        elsif rising_edge(clk) then
            clkdiv <= clkdiv + 1;
        end if;
    end process;
end Behavioral;
