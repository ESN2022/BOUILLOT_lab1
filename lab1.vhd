library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity lab1 is
	port(
			clk : in std_logic;
			reset : in std_logic;
			pio_0 : out std_logic_vector(7 downto 0);
			pio_1 : in std_logic_vector(3 downto 0)
	);
end lab1;


architecture arch of lab1 is

	component lab1_qsys is
        port (
            clk_clk 											: in std_logic := 'X';  -- clk
				reset_reset_n 									: in std_logic := 'X'; --reset_n
				pio_0_external_connection_export 		: out std_logic_vector(7 downto 0);
				pio_1_external_connection_export			: in std_logic_vector(3 downto 0) := (others => 'X')
        );
   end component lab1_qsys;
	begin

    u0 : component lab1_qsys
        port map (
            clk_clk => clk,
				reset_reset_n => reset,
				pio_0_external_connection_export => pio_0,
				pio_1_external_connection_export => pio_1
        );
end arch;
