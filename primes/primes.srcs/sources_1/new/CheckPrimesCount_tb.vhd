library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity checkPrimeCounter_tb is
end;

architecture bench of checkPrimeCounter_tb is

  component checkPrimeCounter
      generic(N : positive := 4);
      Port ( dataIn : in STD_LOGIC_VECTOR (N-1 downto 0);
             countOut : out STD_LOGIC_VECTOR (N-1 downto 0));
  end component;

  signal s_dataIn: STD_LOGIC_VECTOR (4-1 downto 0);
  signal s_countOut: STD_LOGIC_VECTOR (4-1 downto 0);

begin

  -- Insert values for generic parameters !!
  uut: checkPrimeCounter generic map ( N        =>  4)
                            port map ( dataIn   => s_dataIn,
                                       countOut => s_countOut );

  stimulus: process
  begin
  
    -- Put initialisation code here
    s_dataIn <= x"A";
    
    wait for 10ns;
    
    s_dataIn <= x"7";

    -- Put test bench stimulus code here

    wait;
  end process;


end;
