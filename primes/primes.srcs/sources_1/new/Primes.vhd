library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Primes is
    generic(N : positive := 8);
    Port ( limit : in STD_LOGIC_VECTOR(N-1 downto 0);
           outPrimes : out STD_LOGIC_VECTOR (N-1 downto 0));
end Primes;

architecture Behavioral of Primes is
    signal s_count : integer range 0 to N;
    signal s_limit : integer;
    
begin
    s_limit <= TO_INTEGER(unsigned(limit));
    
    process(s_limit)
        
        variable flag : std_logic;
        variable v_count : integer range 0 to N;
        
        begin
            v_count := 0;
            for i in 2 to 100 loop
            
                if (i >= s_limit) then
                    exit;
                end if;
                
                flag := '0';
                for j in 2 to i-1 loop
                    if (i mod j = 0) then
                        flag := '1';
                        exit;
                    end if;
                end loop;
                if (flag = '0') then
                    v_count := v_count + 1;
                end if;
            end loop;
            s_count <= v_count;
    end process;
    
    outPrimes <= std_logic_vector(TO_UNSIGNED(s_count, N));
end Behavioral;