onerror { resume }
transcript off
add wave -noreg -logic {/DCMotorChannel_tb/clk}
add wave -noreg -logic {/DCMotorChannel_tb/coast}
add wave -noreg -logic {/DCMotorChannel_tb/direction}
add wave -noreg -logic {/DCMotorChannel_tb/test_phase}
add wave -noreg -logic {/DCMotorChannel_tb/test_I0}
add wave -noreg -logic {/DCMotorChannel_tb/test_I1}
cursor "Cursor 1" 60.001ns  
transcript on
