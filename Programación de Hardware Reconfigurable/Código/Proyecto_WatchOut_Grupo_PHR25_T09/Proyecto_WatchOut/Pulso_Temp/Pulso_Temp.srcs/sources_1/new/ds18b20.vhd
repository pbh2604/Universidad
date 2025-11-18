----------------------------------------------------------------------------
--	DS18B20.vhd - Modulo de comunicacion con el sensor de temperatura DS18B20
----------------------------------------------------------------------------
-- Autor:  		 			Pavel Gregar
-- Datum vytvoreni:    	15:11:15 11/29/2013
-- Modul:    				DS18B20 - Behavioral 
-- Projekt: 				Meteostanice
-- Cilove zarizeni: 		Nexys4
-- Pouzite nastroje:		Xilinx 14.6
----------------------------------------------------------------------------
--
----------------------------------------------------------------------------
-- Mediante la secuencia de comandos:	
-- CCh (SKIP ROM), 44h (CONVERT TEMPERATURE), CCh (SKIP ROM), BEh (READ SCRATCHPAD) 
-- se lee el contenido de la memoria scartchpad del sensor, que se envía para la
-- comprobación CRC a través del puerto dataOut
--
-- Puertos del modulo:
--
--		clk1m		- Reloj de 1MHz
--		crc_en		- Crontola el inicio del calculo de CRC a partir de los datos
--                    recibidos del sensor enviados al puerto dataOut
--		ds_data_bus	- 1-wire I/O, puerto de datos de E/S del sensor
--		dataOut	 	- señal de salida con datos que tienen el contenido de la memoria 
--
----------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity DS18B20 is
    port( 
        clk1m		    : in		std_logic;                       
        crc_en			: out		std_logic;
        dataOut			: out		std_logic_vector(71 downto 0);
        ds_data_bus		: inout	    std_logic 
    );
end DS18B20;

architecture Behavioral of DS18B20 is

    -- estados de FSM requeridos
    TYPE STATE_TYPE is (WAIT_800ms, RESET, PRESENCE, SEND, WRITE_BYTE, WRITE_LOW, WRITE_HIGH, GET_DATA, READ_BIT);
    -- estado actual de FSM
    signal state: STATE_TYPE;

    -- lectura datos de la memoria del sensor
    signal data	: std_logic_vector(71 downto 0);
    
    -- señal de reinicio sincrono
    signal S_reset	: std_logic;

    signal i : INTEGER RANGE 0 TO 799999;  -- contador
    
    -- inst. enviada para el sensor
    signal write_command    : std_logic_vector(7 downto 0);
    
    -- señal para la deteccion del sensor en el bus
    signal presence_signal	: std_logic;

    signal WRITE_BYTE_CNT	: INTEGER RANGE 0 TO 8	:= 0;	    -- contador para el bit enviado
    signal write_low_flag	: INTEGER RANGE 0 TO 2	:= 0;	    -- indicador de posicion en el estado WRITE_LOW
    signal write_high_flag	: INTEGER RANGE 0 TO 2	:= 0;	    --	indicador de posicion en el estado WRITE_HIGH
    signal read_bit_flag	: INTEGER RANGE 0 TO 3	:= 0;	-- indicador de posicion en el estado  READ_BIT
    signal GET_DATA_CNT		: INTEGER RANGE 0 TO 72	:= 0;	    -- contador de bits leidos

begin

	-- Proceso de comunicacion con el sensor DS18B20
	process(clk1m)

	-- salida de datos cuando se detecta error en el bus
	CONSTANT PRESENCE_ERROR_DATA	: std_logic_vector(71 downto 0):= "101010101010101010101010101010101010101010101010101010101010101010101010";

	VARIABLE bit_cnt	: INTEGER RANGE 0 TO 71;	-- bit recien leido
	VARIABLE flag		: INTEGER RANGE 0 TO 5;		-- flag para enviar comando

	begin
		if rising_edge(clk1m) then
			case	state is
				when RESET =>													
					S_reset <= '0';											-- reinicio de la señal
					if (i = 0) then 
						ds_data_bus <= '0';									--	inicio del pulso de reinicio
					elsif (i = 485) then 
						ds_data_bus <= 'Z';									-- liberacion del bus
					elsif (i = 550) then
						presence_signal <= ds_data_bus;						 
					elsif (i = 1000) then 
						state <= PRESENCE;									-- transicion al estado PRESENCE	
					end if;
			
				when PRESENCE =>															
					-- sensor detectado en el bus
					if (presence_signal = '0' and ds_data_bus = '1') then		
						S_reset <= '1';										-- reset citace / reiniciar comillas?
						state	  <= SEND;									-- transicion al estado SEND
					else													-- sensor no detectado
						S_reset	<= '1';										-- reset citace / reiniciar comillas?
						dataOut 	<= PRESENCE_ERROR_DATA;								
						crc_en	<= '1';										-- iniciar calculo CRC
						state		<= WAIT_800ms;							-- transicion al estado WAIT_800ms
					end if;

				when SEND =>		-- enviar comandos al sensor				
					-- secuencia de comandos enviados controlados por el flag
					if (flag = 0) then													
						flag := 1;
						write_command <="11001100"; 						-- comando CCh - SKIP ROM
						state 		  <= WRITE_BYTE;						-- transición al estado WRITE_BYTE
					elsif (flag = 1) then											
						flag := 2;
						write_command <="01000100"; 						-- comando 44h - CONVERT TEMPERATURE
						state 		  <= WRITE_BYTE;						-- transición al estado WRITE_BYTE
					elsif (flag = 2) then									
						flag := 3;	
						state <= WAIT_800ms; 								-- transición al estado WAIT_800ms, espera a la finalización del comando 44h
					elsif (flag = 3) then												
						flag := 4;
						write_command <="11001100"; 						-- comando CCh - SKIP ROM
						state			  <= WRITE_BYTE;					-- transición al estado WRITE_BYTE
					elsif (flag = 4) then												
						flag := 5;
						write_command <="10111110"; 						-- comando BEh - READ SCRATCHPAD
						state			  <= WRITE_BYTE;					-- transición al estado WRITE BYTE
					elsif (flag = 5) then											
						flag := 0;											
						state <= GET_DATA;									-- transicion al estado GET_DATA
					end if;

				when WAIT_800ms => 
                    CRC_en <= '0';                                          -- reinicio del flag para iniciar el cálculo CRC
                    S_reset <= '0';                                         -- inicio del contador
                    if (i = 799999) then                                    -- fin del período del contador
                        S_reset <= '1'; 
                        state <= RESET;                                     -- retorno al estado RESET
                    end if;

				when GET_DATA =>                                            -- estado para leer la memoria scratchpad
                    case GET_DATA_CNT is 
                        when 0 to 71 =>                                     
                            ds_data_bus <= '0';                             -- inicio de la lectura en el bus
                            GET_DATA_CNT <= GET_DATA_CNT + 1;       
                            state <= READ_BIT;                              -- transición al estado READ_BIT
                        when 72 =>                                          -- memoria leída (72 bits)
                            bit_cnt := 0; 
                            GET_DATA_CNT <= 0; 
                            dataOut <= data(71 downto 0);                   -- envío de datos leídos al puerto de salida
                            CRC_en <= '1'; 
                            state <= WAIT_800ms;                            -- retorno al estado WAIT_800ms
                        when others =>                                      -- error en el estado GET_DATA
                            read_bit_flag <= 0; 
                            GET_DATA_CNT <= 0; 
                    end case;

				when READ_BIT =>                                            -- estado para leer el bit
                    -- secuencia de lectura de bits controlada por el flag read_bit_flag
                    case read_bit_flag is 
                        when 0 => 
                            read_bit_flag <= 1;
                        when 1 =>
                            ds_data_bus <= 'Z';                             -- liberación del bus para recibir el bit del sensor
                            S_reset <= '0'; 
                            if (i = 13) then                                -- espera 14 us
                                S_reset <= '1'; 
                                read_bit_flag <= 2;
                            end if;
                        when 2 =>                                           -- recepción de la muestra de datos del bus
                            data(bit_cnt) <= ds_data_bus;                   -- almacenamiento de la muestra de datos en el registro
                            bit_cnt := bit_cnt + 1; 
                            read_bit_flag <= 3;
                        when 3 =>                                           -- finalización del slot de tiempo
                            S_reset <= '0'; 
                            if (i = 63) then                                -- espera 62 us
                                S_reset <= '1'; 
                                read_bit_flag <= 0;                         
                                state <= GET_DATA;                          -- retorno al estado GET_DATA
                            end if;
                        when others =>                                      -- error en el estado READ_BIT
                            read_bit_flag <= 0; 
                            bit_cnt := 0; 
                            GET_DATA_CNT <= 0; 
                            state <= RESET;                                 -- reinicio del sensor
                    end case;


				when WRITE_BYTE =>                                          -- estado para escribir un byte de datos en el bus
                    -- secuencia de escritura de un byte de datos controlada por el contador WRITE_BYTE_CNT
                    case WRITE_BYTE_CNT is 
                        when 0 to 7 =>                                      -- envío de bits 0-7
                            if (write_command(WRITE_BYTE_CNT) = '0') then   -- bit enviado tiene valor lógico 0
                                state <= WRITE_LOW;                         -- transición al estado WRITE_LOW
                            else                                            -- bit enviado tiene valor lógico 1
                                state <= WRITE_HIGH;                        -- transición al estado WRITE_HIGH
                            end if;
                            WRITE_BYTE_CNT <= WRITE_BYTE_CNT + 1; 
                        when 8 =>                                           -- envío del byte completado
                            WRITE_BYTE_CNT <= 0; 
                            state <= SEND;                                  -- transicion al estado SEND
                        when others =>                                      -- error en el estado WRITE_BYTE
                            WRITE_BYTE_CNT <= 0; 
                            write_low_flag <= 0; 
                            write_high_flag <= 0; 
                            state <= RESET;
                    end case;


				when WRITE_LOW =>                                      -- estado para escribir lógico 0 en el bus
                    -- slot de tiempo para escribir lógico 0 controlado por el flag write_low_flag
                    case write_low_flag is 
                        when 0 => 
                            ds_data_bus <= '0'; 
                            S_reset <= '0'; 
                            if (i = 59) then                            -- espera 60 us
                                S_reset <= '1'; 
                                write_low_flag <= 1;
                            end if;
                        when 1 =>                                       -- liberación del bus para finalizar el slot de tiempo
                            ds_data_bus <= 'Z';                         -- liberación del bus
                            S_reset <= '0'; 
                            if (i = 3) then                             -- espera 4 us para estabilizar el bus
                                S_reset <= '1'; 
                                write_low_flag <= 2;
                            end if;
                        when 2 =>                                       -- fin de la escritura lógico 0
                            write_low_flag <= 0; 
                            state <= WRITE_BYTE;                        -- transicion al estado WRITE_BYTE
                        when others =>                                  -- error en la escritura lógico 0
                            WRITE_BYTE_CNT <= 0; 
                            write_low_flag <= 0; 
                            state <= RESET; 
                    end case;


				when WRITE_HIGH =>                                      -- estado para escribir lógico 1 en el bus
                    -- slot de tiempo para escribir lógico 1 controlado por el flag write_high_flag
                    case write_high_flag is 
                        when 0 => 
                            ds_data_bus <= '0'; 
                            S_reset <= '0'; 
                            if (i = 9) then                             -- espera 10 us
                                S_reset <= '1'; 
                                write_high_flag <= 1;
                            end if;
                        when 1 =>                                       -- liberación del bus para finalizar el slot de tiempo
                            ds_data_bus <= 'Z';                         -- liberación del bus
                            S_reset <= '0'; 
                            if (i = 53) then                            -- espera 54 us
                                S_reset <= '1'; 
                                write_high_flag <= 2;
                            end if;
                        when 2 =>                                       -- fin de la escritura lógico 1
                            write_high_flag <= 0; 
                            state <= WRITE_BYTE;                        -- transicion al estado WRITE_BYTE
                        when others =>                                  -- error en la escritura lógico 1
                            WRITE_BYTE_CNT <= 0; 
                            write_high_flag <= 0; 
                            state <= RESET; 
                    end case;


				when others =>											-- error FSM
					state <= RESET;										-- reinicio del sensor
					
			end case;
		end if;
	end process;

	-- Proceso de contador con reinicio sincronico
	process(clk1m, S_reset)

	begin
		if (rising_edge(clk1m)) then
			if (S_reset = '1')then		    -- reinicio del contador
				i <= 0;						
			else
				i <= i + 1;					
			end if;
		end if;
	end process;

end Behavioral;