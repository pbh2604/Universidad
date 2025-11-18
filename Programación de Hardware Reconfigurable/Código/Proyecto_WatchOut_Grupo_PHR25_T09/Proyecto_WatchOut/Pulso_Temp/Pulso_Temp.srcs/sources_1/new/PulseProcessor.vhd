----------------------------------------------------------------------------
-- PulseProcessor.vhd - Módulo para procesar la señal del pulso cardíaco
----------------------------------------------------------------------------
--
-- Este módulo procesa la señal del sensor de pulso para detectar latidos,
-- calcular el intervalo entre latidos (IBI) y determinar la frecuencia
-- cardíaca en latidos por minuto (BPM). Utiliza un umbral para detectar
-- los latidos y un período refractario para evitar falsas detecciones.
--
-- Puertos del módulo:
--
--      clk             -  Reloj del sistema
--      rst             -  Señal de reset para inicializar el módulo
--      sample_tick     -  Pulso de muestreo cada 2 ms
--      senial          -  Señal de entrada del sensor de pulso
--      pulse_detected  -  Indica si se ha detectado un latido
--      ibi             -  Intervalo entre latidos
--      bpm             -  Frecuencia cardíaca en latidos por minuto
--
----------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity PulseProcessor is
    Port (
        clk            : in  std_logic;
        rst            : in  std_logic;
        sample_tick    : in  std_logic;
        senial         : in  unsigned(9 downto 0);
        pulse_detected : out std_logic;
        ibi            : out unsigned(15 downto 0);
        bpm            : out unsigned(15 downto 0)
    );
end PulseProcessor;

architecture Behavioral of PulseProcessor is
    constant THRESHOLD         : unsigned(9 downto 0) := to_unsigned(550, 10); -- Ajusta según el sensor
    constant MAX_BEATS         : integer := 4;
    constant REFRACTORY_PERIOD : unsigned(15 downto 0) := to_unsigned(250, 16); -- Mayor para filtrar ruido
    constant SAMPLE_PERIOD_MS  : integer := 2; -- Si sample_tick equivale a 2 ms

    type ibi_array_t is array (0 to MAX_BEATS-1) of unsigned(15 downto 0);
    signal ibi_buffer    : ibi_array_t := (others => (others => '0'));
    signal buffer_index  : integer range 0 to MAX_BEATS-1 := 0;
    signal beat_count    : integer range 0 to MAX_BEATS := 0;

    signal sample_counter : unsigned(15 downto 0) := (others => '0');
    signal last_beat_time : unsigned(15 downto 0) := (others => '0');
    signal ibi_reg        : unsigned(15 downto 0) := (others => '0');
    signal bpm_reg        : unsigned(15 downto 0) := (others => '0');
    signal prev_signal    : unsigned(9 downto 0)  := (others => '0');
    signal detected       : std_logic := '0';
begin

    process(clk)
        variable sum     : integer := 0;
        variable avg_ibi : integer := 0;
        variable current_ibi : unsigned(15 downto 0);
    begin
        if rising_edge(clk) then
            if rst = '1' then
                sample_counter <= (others => '0');
                last_beat_time <= (others => '0');
                ibi_reg        <= (others => '0');
                bpm_reg        <= (others => '0');
                buffer_index   <= 0;
                beat_count     <= 0;
                detected       <= '0';
                for i in 0 to MAX_BEATS-1 loop
                    ibi_buffer(i) <= (others => '0');
                end loop;
            elsif sample_tick = '1' then
                sample_counter <= sample_counter + 1;
                detected <= '0';

                -- Detección de flanco de subida sobre el umbral
                if senial > THRESHOLD and prev_signal <= THRESHOLD then
                    if (sample_counter - last_beat_time) > REFRACTORY_PERIOD then          -- evita detectar multiples latidos, ya sea por el ruido
                        -- calculo del IBI
                        current_ibi := sample_counter - last_beat_time;
                        ibi_reg     <= current_ibi;
                        ibi_buffer(buffer_index) <= current_ibi;
                        last_beat_time <= sample_counter;
                        detected    <= '1';

                        if beat_count < MAX_BEATS then
                            beat_count <= beat_count + 1;
                        end if;

                        sum := 0;
                        for i in 0 to MAX_BEATS - 1 loop
                            if i < beat_count then
                                sum := sum + to_integer(ibi_buffer(i));
                            end if;
                        end loop;

                        if beat_count > 0 then
                            avg_ibi := sum / beat_count;
                        else
                            avg_ibi := to_integer(current_ibi);
                        end if;

                        -- calculo del BPM
                        if avg_ibi > 0 then
                            bpm_reg <= to_unsigned(60000 / (avg_ibi * SAMPLE_PERIOD_MS), 16);
                        end if;

                        if buffer_index = MAX_BEATS - 1 then
                            buffer_index <= 0;
                        else
                            buffer_index <= buffer_index + 1;
                        end if;
                    end if;
                end if;

                prev_signal <= senial;
            end if;
        end if;
    end process;

    pulse_detected <= detected;
    ibi            <= ibi_reg;
    bpm            <= bpm_reg;

end Behavioral;
