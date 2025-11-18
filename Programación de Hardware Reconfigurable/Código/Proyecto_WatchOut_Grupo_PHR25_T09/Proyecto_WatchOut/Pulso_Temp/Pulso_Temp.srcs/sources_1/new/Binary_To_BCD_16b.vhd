----------------------------------------------------------------------------
--	Binary_To_BCD_16b.vhd - Modulo para convertir numeros binarios a BCD
----------------------------------------------------------------------------
--
----------------------------------------------------------------------------
-- Este modulo se utiliza para convertir un numero binario de 16 bits en un 
-- formato BCD. Ademas, maneja una entrada de 4 bits que representa la parte 
-- fraccionaria de un numero y la convierte a un formato BDC de 8 bits.
--
-- Puertos del modulo:
--
--      ENTERO: entrada de 16 bits, numero binario entero
--      POINT: entrada de 4 bits, la parte fraccionaria de un numero binario
--      BCD: salida de 19 bits, numero entero convertido a formato BCD
--      BCDPOINT: salida de 8 bits, la parte fraccionaria convertida a formato BCD
--
---------------------------------------------------------------------------- 
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL; 
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Binary_To_BCD_16b is
PORT (
      ENTERO    : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
		POINT     : IN STD_LOGIC_VECTOR(3 DOWNTO 0);	
		 BCD      : OUT STD_LOGIC_VECTOR(18 DOWNTO 0);
		 BCDPOINT : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
		 );
		
end Binary_To_BCD_16b;

architecture Behavioral of Binary_To_BCD_16b is

    signal temper: std_logic_vector(3 downto 0);
    signal point_out: std_logic_vector(7 downto 0);
    
begin

    temper  <= POINT;
    BCDPOINT<= point_out;

	with temper select				  
		  point_out<= "0000"&"0000" when "0000",--0
						  "0000"&"0110" when "0001",--0.0625
						  "0001"&"0010" when "0010",--0.125
						  "0001"&"1001" when "0011",--0.1875 =0.19
						  "0010"&"0101" when "0100",--0.25
						  "0011"&"0101" when "0101",--0.31
						  "0011"&"1000" when "0110",--0.375  =0.38
						  "0100"&"0100" when "0111",--0.4375 =0.44
						  "0101"&"0000" when "1000",--0.5
						  "0101"&"0110" when "1001",--0.5625
						  "0110"&"0011" when "1010",--0.625 =0.63
						  "0110"&"1001" when "1011",--0.6875 =0.69
						  "0111"&"0101" when "1100",--0.75
						  "1000"&"0001" when "1101",--0.8125
						  "1000"&"1000" when "1110",--0.875	 =0.88
						  "1001"&"0100" when "1111",--0.9375	 =0.94	
						  "0000"&"0000" when others;		  	

    BCD1: PROCESS(ENTERO) 
        VARIABLE Z:STD_LOGIC_VECTOR(34 DOWNTO 0);      
    BEGIN 
        FOR I IN 0 TO 34 LOOP 
        Z(I):='0'; 
        END LOOP;  
        
        Z(18 DOWNTO 3):=ENTERO; 
        FOR I IN 0 TO 12 LOOP 
            -- ajusta el primer grupo de 4 bits si es mayor que 4
            IF Z(19 DOWNTO 16) > 4 THEN 
            Z(19 DOWNTO 16):= Z(19 DOWNTO 16)+3; 
            END IF;  
            -- ajusta el segundo grupo de 4 bits si es mayor que 4
            IF Z(23 DOWNTO 20) > 4 THEN 
            Z(23 DOWNTO 20):= Z(23 DOWNTO 20)+3; 
            END IF;  
            -- ajusta el tercer grupo de 4 bits si es mayor que 4
            IF Z(27 DOWNTO 24) > 4 THEN 
            Z(27 DOWNTO 24):= Z(27 DOWNTO 24)+3; 
            END IF; 
            -- ajusta el cuarto grupo de 4 bits si es mayor que 4
            IF Z(31 DOWNTO 28) > 4 THEN 
            Z(31 DOWNTO 28):= Z(31 DOWNTO 28)+3; 
            END IF; 
        
        Z(34 DOWNTO 1):= Z(33 DOWNTO 0); 
        
     END LOOP;  
     BCD <= Z(34 DOWNTO 16); 
     END PROCESS;
end Behavioral;