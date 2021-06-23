library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity isPrime_v1_0_S00_AXIS is
	generic (
		-- Users to add parameters here

		-- User parameters ends
		-- Do not modify the parameters beyond this line

		-- AXI4Stream sink: Data Width
		C_S_AXIS_TDATA_WIDTH	: integer	:= 32
	);
	port (
		-- Users to add ports here
        dataValid : out std_logic;
        isPrimeOut : out std_logic_vector(C_S_AXIS_TDATA_WIDTH-1 downto 0);
        byteEnable : out std_logic_vector((C_S_AXIS_TDATA_WIDTH/8)-1 downto 0);
        lastWord : out std_logic;
        readEnabled : in std_logic;
		-- User ports ends
		-- Do not modify the ports beyond this line

		-- AXI4Stream sink: Clock
		S_AXIS_ACLK	: in std_logic;
		-- AXI4Stream sink: Reset
		S_AXIS_ARESETN	: in std_logic;
		-- Ready to accept data in
		S_AXIS_TREADY	: out std_logic;
		-- Data in
		S_AXIS_TDATA	: in std_logic_vector(C_S_AXIS_TDATA_WIDTH-1 downto 0);
		-- Byte qualifier
		S_AXIS_TSTRB	: in std_logic_vector((C_S_AXIS_TDATA_WIDTH/8)-1 downto 0);
		-- Indicates boundary of last packet
		S_AXIS_TLAST	: in std_logic;
		-- Data is in valid
		S_AXIS_TVALID	: in std_logic
	);
end isPrime_v1_0_S00_AXIS;

architecture arch_imp of isPrime_v1_0_S00_AXIS is
    
    signal s_ready : std_logic;
    signal s_dataValid : std_logic;
    --signal s_dataIn, s_dataOut : std_logic_vector(C_S_AXIS_TDATA_WIDTH-1 downto 0);
    signal s_dataIn, s_dataOut : std_logic_vector(8-1 downto 0);
    
    component isPrime is
        generic(N : positive := 4);
        Port ( dataIn : in STD_LOGIC_VECTOR (N-1 downto 0);
               dataOut : out STD_LOGIC_VECTOR (N-1 downto 0));
    end component isPrime;
    	
begin
    
    is_prime: isPrime generic map (N       =>  8) --C_S_AXIS_TDATA_WIDTH
                  port map ( dataIn  => s_dataIn,
                             dataOut => s_dataOut );
    
    s_ready <= (not s_dataValid) or readEnabled;
    
    process(S_AXIS_ACLK)
    begin
        if rising_edge (S_AXIS_ACLK) then
            if (S_AXIS_ARESETN = '0') then
                s_dataValid <= '0';
                isPrimeOut <= (others => '0');
            
            elsif(S_AXIS_TVALID = '1') then
                if(s_ready = '1') then
                    s_dataValid <= '1';
                    s_dataIn <= S_AXIS_TDATA(8-1 downto 0);
                    
                    if (S_AXIS_TSTRB = "1111") then
                        isPrimeOut(C_S_AXIS_TDATA_WIDTH-1 downto 8) <= (others => '0');
                        isPrimeOut(8-1 downto 0) <= s_dataOut;
                    end if;
                    
                    byteEnable(0) <= S_AXIS_TSTRB(3);
                    byteEnable(1) <= S_AXIS_TSTRB(2);
                    byteEnable(2) <= S_AXIS_TSTRB(1);
                    byteEnable(3) <= S_AXIS_TSTRB(0);
                    
                    lastWord <= S_AXIS_TLAST;
                end if;
            
            elsif(readEnabled = '1') then
                s_dataValid <= '0';
            end if;
            
        end if;
    end process;
    
    dataValid <= s_dataValid;
    S_AXIS_TREADY <= s_ready;

end arch_imp;
