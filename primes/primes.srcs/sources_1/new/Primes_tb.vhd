library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Primes_tb is
end;

architecture bench of Primes_tb is
    
    component Primes
        generic(N : positive := 8);
        Port ( limit : in STD_LOGIC_VECTOR(N-1 downto 0);
             outPrimes : out STD_LOGIC_VECTOR (N-1 downto 0)
            );
    end component;

    signal s_limit : STD_LOGIC_VECTOR(3 downto 0);
    signal s_outPrimes : STD_LOGIC_VECTOR (3 downto 0);

begin

    -- Insert values for generic parameters !!
    uut: Primes generic map ( N       =>  4 )
                 port map ( limit     => s_limit,
                            outPrimes => s_outPrimes );
    
    stimulus: process
    begin
    
    -- Put initialisation code here
    s_limit <= x"A";
    
    wait for 10ns;
    
    s_limit <= x"F";
    wait for 10ns;
    
    -- Put test bench stimulus code here
    
    wait;
    end process;


end;