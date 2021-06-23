
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity isPrime is
    generic(N : positive := 4);
    Port ( dataIn : in STD_LOGIC_VECTOR (N-1 downto 0);
           dataOut : out STD_LOGIC_VECTOR (N-1 downto 0));
end isPrime;

architecture Behavioral of isPrime is
    signal s_limit : integer;
    signal s_isPrime : std_logic_vector(dataIn'length-1 downto 0);
    
begin
    s_limit <= TO_INTEGER(unsigned(dataIn));
    
    process(s_limit, dataIn)
        variable flag : std_logic;
    begin
        flag := '0';
        
        if(s_limit <= 1) then
            flag := '1';
        end if;
        
        for i in 2 to 49/2 loop
            if (i >= s_limit) then
                exit;
            end if;       
            if (s_limit mod i = 0) then
                flag := '1';
                exit;
            end if;
        end loop;
        
        if (flag = '0') then
            s_isPrime <= dataIn;
        else
            s_isPrime <= (others => '0'); 
        end if;
    
    end process;
    
    dataOut <= s_isPrime;
end Behavioral;
