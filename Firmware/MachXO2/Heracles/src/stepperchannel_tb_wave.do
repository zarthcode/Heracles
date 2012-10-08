onerror { resume }
transcript off
add wave -noreg -logic {/StepperChannel_tb/step_clk}
add wave -noreg -logic {/StepperChannel_tb/direction}
add wave -noreg -logic {/StepperChannel_tb/testmodified_mode}
add wave -noreg -logic {/StepperChannel_tb/testphase1_I0}
add wave -noreg -logic {/StepperChannel_tb/testphase1_I1}
add wave -noreg -logic {/StepperChannel_tb/testphase1_phase}
add wave -noreg -logic {/StepperChannel_tb/testphase2_I0}
add wave -noreg -logic {/StepperChannel_tb/testphase2_I1}
add wave -noreg -logic {/StepperChannel_tb/testphase2_phase}
cursor "Cursor 1" 0ps  
transcript on
