onerror { resume }
transcript off
add wave -noreg -logic {/arbiter_rr_tb/clk}
add wave -noreg -logic {/arbiter_rr_tb/rst}
add wave -noreg -logic {/arbiter_rr_tb/req0}
add wave -noreg -logic {/arbiter_rr_tb/req1}
add wave -noreg -logic {/arbiter_rr_tb/req2}
add wave -noreg -logic {/arbiter_rr_tb/gnt0}
add wave -noreg -logic {/arbiter_rr_tb/gnt1}
add wave -noreg -logic {/arbiter_rr_tb/gnt2}
cursor "Cursor 1" 0ps  
transcript on
