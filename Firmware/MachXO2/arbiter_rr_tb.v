// Verilog round-robin arbiter testbench
module arbiter_rr_tb();
	
	reg 	clk;
	reg		rst;
	reg 	req0;
	reg 	req1;
	reg 	req2;
	wire 	gnt0;
	wire	gnt1;
	wire	gnt2;
	
	// Clock generator
	always #1 clk = ~clk;
		
		
	initial begin
		$dumpfile ("arbiter.vcd");
		$dumpfile();
		$display ("Starting Arbiter test.");
		clk = 0;
		rst = 1;
		req0 = 0;
		req1 = 0;
		req2 = 0;
		
		
		#10 rst = 0;
		
		repeat (1) @ (posedge clk);
		req0 <= 1;
		
		repeat (2) @ (posedge clk);
		req0 <= 0;
		
		repeat (2) @ (posedge clk);
		req0 <= 1;
		req1 <= 1;
		
		repeat (2) @ (posedge clk);
		req2 <= 1;
		req1 <= 0;
		
		repeat (2) @ (posedge clk);
		req2 <= 0;
		
		repeat (2) @ (posedge clk);
		req0 <= 0;
		
		#10 $finish;
		
	end
	
	// Connect the DUT
	arbiter_rr ThreeWayArbiter (
		clk,
		rst,
		req0,
		req1,
		req2,
		gnt0,
		gnt1,
		gnt2
	);
endmodule