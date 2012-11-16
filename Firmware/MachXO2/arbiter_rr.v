// Round-robin 3-way arbiter
module arbiter_rr(clk, rst, request0, request1, request2, grant0, grant1, grant2);
	
	// Declarations
	input wire		clk;
	input wire		rst;
	input wire		request0;
	input wire		request1;
	input wire		request2;
	output wire		grant0;
	output wire		grant1;
	output wire		grant2;	
	
	// Internal registers
	reg				lgrant0;
	reg				lgrant1;
	reg				lgrant2;	
	
	reg				reqmask0;
	reg				reqmask1;
	reg				maskflag;
	
	reg				edgeflag;
	wire	[1:0]	mask;	 
	wire			busy;
	wire			beginflag;
	
	
	// Arbiter Logic
	always @ (posedge clk)
		if (rst) begin		// Reset - Clear all.
			lgrant0 <= 0;
			lgrant1 <= 0;
			lgrant2 <= 0;
		end else begin		// Locking
			lgrant0 <=	(~busy & request0 & ~reqmask1 & ~reqmask0 & ~request1 & ~request2)	// Lowest priority
					|	(~busy & request0 & ~reqmask1 & reqmask0 & ~request2)				// Second in line, behind 2
					|	(~busy & request0 & reqmask1 & ~reqmask0)							// Highest priority
					|	(busy & lgrant0);													// Busy/Locked
					
					
			lgrant1 <=	(~busy & request1 & ~reqmask1 & ~reqmask0)							// Highest priority
					|	(~busy & request1 & ~reqmask1 & reqmask0 & ~request0 & ~request2)	// Lowest priority
					|	(~busy & request1 & reqmask1 & ~reqmask0 & ~request0)				// Second in line, behind 0
					|	(busy & lgrant1);													// Busy/Locked
			
			
			lgrant2 <=	(~busy & request2 & ~reqmask1 & ~reqmask0 & ~request1)				// Second in line, behind 1
					|	(~busy & request2 & ~reqmask1 & reqmask0)							// Highest priority
					|	(~busy & request2 & reqmask1 & ~reqmask0 & ~request0 & ~request1)	// Lowest priority
					|	(busy & lgrant2);													// Busy/Locked
		end
		
	// State machine
	assign beginflag = (request0 | request1 |request2) & ~busy;
	always @ (posedge clk)
		begin
			maskflag <= (beginflag & ~edgeflag & ~maskflag);
			edgeflag <= (beginflag & ~edgeflag & maskflag)
						| (beginflag & edgeflag & ~maskflag);
		end
	
	// Busy/Lock Flag
	assign busy = (request0 & lgrant0)
				| (request1 & lgrant1)
				| (request2 & lgrant2);
				
	// Priority Mask
	assign mask = {lgrant2, lgrant1};
	
	// Previous request mask
	always @ (posedge clk)
		if (rst) begin
			reqmask0 <= 0;
			reqmask1 <= 0;
		end else if(maskflag) begin
			reqmask0 <= mask[0];
			reqmask1 <= mask[1];
		end else begin
			reqmask0 <= reqmask0;
			reqmask1 <= reqmask1;
		end

	
	// Drive outputs
	assign grant0 = lgrant0;
	assign grant1 = lgrant1;
	assign grant2 = lgrant2;
	
endmodule