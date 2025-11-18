library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity TopModule is
    Port (
        clk       : in  std_logic;                     -- reloj 100 MHz
        rst       : in  std_logic;                     -- reset
        ad_dout_i : in  std_logic;                     -- MISO del ADC
        seg       : out std_logic_vector(6 downto 0);  -- segmentos del 5641AS
        an_pulso  : out std_logic_vector(3 downto 0); 
        ad_ncs_o  : out std_logic;
        ad_clk_o  : out std_logic;
        ad_din_o  : out std_logic;
        an_temp   : out std_logic_vector (3 downto 0);
        a_to_g    : out std_logic_vector (6 downto 0);  -- segmentos display fpga
        DQ        : inout std_logic;
        DP        : out std_logic;
        LEDTER    : out std_logic_vector (2 downto 0)
    );
end TopModule;

architecture Behavioral of TopModule is
    -- Señales SPI / ADC
    signal sample_tick    : std_logic;
    signal spi_ena_sig    : std_logic;
    signal adc_data       : std_logic_vector(9 downto 0);
    signal adc_start      : std_logic := '1';
    signal adc_busy       : std_logic;
    signal adc_eoc        : std_logic;

    -- Señales de pulso
    signal bpm_raw        : unsigned(15 downto 0);
    signal ibi            : unsigned(15 downto 0);
    signal pulse_detected : std_logic;

    -- Latch para display
    signal bpm_disp       : unsigned(15 downto 0) := (others => '0');
    
    -- Señales de temperatura
    signal clk_50MHz : std_logic;
    signal CLK1MHZ	 : std_logic;
    signal DOK   	 : std_logic;
    signal REQUEST   : std_logic;
    signal DATA      : std_logic_vector(71 downto 0);
    signal DATA16    : std_logic_vector(15 downto 0);
    signal DATA12    : std_logic_vector(15 downto 0);
    signal DATA4     : std_logic_vector(3 downto 0);
    signal Y         : std_logic_vector(18 downto 0);
    signal X         : std_logic_vector(15 downto 0);
    signal W         : std_logic_vector(7 downto 0);

    -- COMPONENTES    
    component divider50MHz
        Port(
            clk_in  : in std_logic;
            clk_out : out std_logic
         );
    end component;
    
    component SampleTimer is
        Port ( 
            clk         : in std_logic;
            rst         : in std_logic;
            sample_tick : out std_logic 
           );
    end component;

    component MCP300x is
        Port (
            clk_i     : in  std_logic;    rst_i     : in  std_logic;
            start_i   : in  std_logic;    busy_o    : out std_logic;
            chn_i     : in  std_logic_vector(2 downto 0);
            single_i  : in  std_logic;    ena_i     : in  std_logic;
            eoc_o     : out std_logic;    data_o    : out std_logic_vector(9 downto 0);
            ad_ncs_o  : out std_logic;    ad_clk_o  : out std_logic;
            ad_din_o  : out std_logic;    ad_dout_i : in  std_logic
        );
    end component;

    component ClockDivider is
        generic ( DIVISOR : integer := 200 );
        Port ( 
            clk_i : in std_logic;
            rst_i : in std_logic;
            ena_o : out std_logic 
        );
    end component;

    component PulseProcessor is
        Port (
            clk            : in  std_logic;
            rst            : in  std_logic;
            sample_tick    : in  std_logic;
            senial         : in  unsigned(9 downto 0);
            bpm            : out unsigned(15 downto 0);
            ibi            : out unsigned(15 downto 0);
            pulse_detected : out std_logic
        );
    end component;

    component Display_7Seg_BPM is
        Port (
            clk : in  std_logic;
            bpm : in  std_logic_vector(15 downto 0);
            seg : out std_logic_vector(6 downto 0);
            an  : out std_logic_vector(3 downto 0)
        );
    end component;
    
    component DS18B20
        Port(
            clk1m       : in std_logic;    
            ds_data_bus : inout std_logic;      
            crc_en      : out std_logic;
            dataOut     : out std_logic_vector(71 downto 0)
        );
	end component;
	
	component divider1MHz
        Port(
            clk_in  : in std_logic;          
            clk_out : out std_logic
        );
	end component;

    component CRC
        Port(
            clk       : in std_logic;
            data_en   : in std_logic;
            dataIn    : in std_logic_vector(71 downto 0);          
            dataOut   : out std_logic_vector(15 downto 0);
            dataValid : out std_logic
        );
	end component;
	
	component Binary_To_BCD_16b
        Port(
            ENTERO   : in std_logic_vector(15 downto 0);
            POINT    : in std_logic_vector(3 downto 0);          
            BCD      : out std_logic_vector(18 downto 0);
            BCDPOINT : out std_logic_vector(7 downto 0)
        );
	end component;
	
	component X7seg
        Port(
            x      : in std_logic_vector(15 downto 0);
            clk    : in std_logic;
            clr    : in std_logic;          
            an     : out std_logic_vector(3 downto 0);
            a_to_g : out std_logic_vector(6 downto 0);
            dp     : out std_logic
        );
	end component;
	
begin
    -- Implementacion Pulsometro
    -- Generación de sample_tick (2 ms)
    timer_inst: SampleTimer
        port map(
            clk         => clk,
            rst         => rst,
            sample_tick => sample_tick
        );

    -- Lógica SPI / ADC
    adc_inst: MCP300x
        port map(
            clk_i     => clk,
            rst_i     => rst,
            start_i   => adc_start,
            busy_o    => adc_busy,
            chn_i     => "000",
            single_i  => '1',
            ena_i     => spi_ena_sig,
            eoc_o     => adc_eoc,
            data_o    => adc_data,
            ad_ncs_o  => ad_ncs_o,
            ad_clk_o  => ad_clk_o,
            ad_din_o  => ad_din_o,
            ad_dout_i => ad_dout_i
        );

    -- Clock divider para SPI
    clkdiv_inst: ClockDivider
        generic map(DIVISOR => 200)
        port map(
            clk_i => clk,
            rst_i => rst,
            ena_o => spi_ena_sig
        );

    -- Procesador de pulso
    pulse_inst: PulseProcessor
        port map(
            clk            => clk,
            rst            => rst,
            sample_tick    => sample_tick,
            senial         => unsigned(adc_data),
            bpm            => bpm_raw,
            ibi            => ibi,
            pulse_detected => pulse_detected
        );

    -- Latch BPM para display
    process(clk)
    begin
        if rising_edge(clk) then
            if rst = '1' then
                bpm_disp <= (others => '0');
            elsif pulse_detected = '1' then
                bpm_disp <= bpm_raw;
            end if;
        end if;
    end process;

    disp_inst: Display_7Seg_BPM
        port map(
            clk => clk,
            bpm => std_logic_vector(bpm_disp),
            seg => seg,
            an => an_pulso
        );
        
    -- implementacion temperatura
    U0: divider50MHz 
        port map(
        clk_in => clk,
        clk_out => clk_50MHz
        );
    
    U1: DS18B20 
        port map(
            clk1m => CLK1MHZ,
            crc_en => DOK,
            dataOut => DATA,
            ds_data_bus => DQ
        );
    
    U2: divider1MHz 
        port map(
            clk_in => clk_50MHz,
            clk_out => CLK1MHZ
        );
	
	U3: CRC 
	   port map(
		clk => CLK1MHZ,
		data_en => DOK,
		dataIn => DATA,
		dataOut => DATA16,
		dataValid =>REQUEST 
	   );
	   
    DATA12 <= "0000" & DATA16(15 DOWNTO 4 );
    DATA4 <= DATA16(3 DOWNTO 0 );
    
    LEDTER(0) <= '1' when (unsigned(DATA12) > X"1F") or ((unsigned(DATA12) = X"1F") and (unsigned(DATA4) > X"0")) else '0';
    
    LEDTER(1) <= '1' when ((unsigned(DATA12) < X"1F") or ((unsigned(DATA12) = X"1F") and (unsigned(DATA4) <= X"0"))) and (unsigned(DATA12) >= X"1A") else '0';
    
    LEDTER(2) <= '1' when (unsigned(DATA12) < X"1A") else '0';
	
	U4: Binary_To_BCD_16b 
	   port map(
            ENTERO => DATA12,
            POINT => DATA4,
            BCD => Y,
            BCDPOINT => W 
        );

    X( 3 downto 0 )   <= W( 3 downto 0 );
    X( 7 downto 4 )   <= W( 7 downto 4 );     		
    X( 11 downto 8 )  <= Y( 3 downto 0 );     
    X( 15 downto 12 ) <= Y( 7 downto 4 );     			
		
	U5: X7seg 
	   port map(
		x => X,
		clk => clk_50MHz,
		clr => rst,
		an => an_temp,
		a_to_g =>a_to_g, 
		dp => DP
	   );
end Behavioral;
