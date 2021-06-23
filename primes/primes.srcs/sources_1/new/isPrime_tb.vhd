library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity isPrime_tb is
end;

architecture bench of isPrime_tb is

  component isPrime
      generic(N : positive := 4);
      Port ( dataIn : in STD_LOGIC_VECTOR (N-1 downto 0);
             dataOut : out STD_LOGIC_VECTOR (N-1 downto 0));
  end component;

  signal s_dataIn: STD_LOGIC_VECTOR (4-1 downto 0);
  signal s_dataOut: STD_LOGIC_VECTOR (4-1 downto 0);

begin

  -- Insert values for generic parameters !!
  uut: isPrime generic map ( N       =>  4)
                  port map ( dataIn  => s_dataIn,
                             dataOut => s_dataOut );

  stimulus: process
  begin
  
    -- Put initialisation code here
    s_dataIn <= x"A";
    
    wait for 10ns;
    
    s_dataIN <= x"F";
    
    wait for 10ns;
    
    s_dataIN <= x"B";
    
    wait for 10ns;
    
    s_dataIN <= x"7";
    
    wait for 10ns;
    
    s_dataIN <= x"9";
    
    wait for 10ns;
    
    s_dataIN <= x"D";
    
    wait for 10ns;
    
    s_dataIN <= x"0";
    
    wait for 10ns;
    
    s_dataIN <= x"1";
    
    wait for 10ns;

    -- Put test bench stimulus code here

    wait;
  end process;


end;