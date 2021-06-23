----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 06/18/2021 04:44:28 PM
-- Design Name: 
-- Module Name: checkPrimeCounter - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity checkPrimeCounter is
    generic(N : positive := 4);
    Port ( dataIn : in STD_LOGIC_VECTOR (N-1 downto 0);
           countOut : out STD_LOGIC_VECTOR (N-1 downto 0));
end checkPrimeCounter;

architecture Behavioral of checkPrimeCounter is
    signal s_count : integer range 0 to N;
    signal s_limit : integer;
    
begin
    s_limit <= TO_INTEGER(unsigned(dataIn));
    
    process(s_limit)
        variable v_count : integer range 0 to N;
        variable flag : std_logic;
    begin
        v_count := 0;
        for i in 2 to 50 loop
            if (i >= s_limit) then
                exit;
            end if;       
            flag := '0';
            if (s_limit mod i = 0) then
                flag := '1';
                exit;
            end if;
        end loop;
        if (flag = '0') then
            v_count := v_count + 1;
        end if;
        s_count <= v_count;
    
    end process;
    
    countOut <= std_logic_vector(TO_UNSIGNED(s_count, N));
    
end Behavioral;
