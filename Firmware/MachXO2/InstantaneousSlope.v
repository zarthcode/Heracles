// Slope/Derivative

module InstantaneousSlope #(parameter W = 64) (value, result, clk);
	
	
	// Inputs
	input wire [W-1:0] value;		// Value being measured/integrated.
	input wire clk;				// measument cue/timing.
	
	// Outputs
	output reg [W-1:0] result;	// Current result
	
	// Variables
	reg [W-1:0] prev_value;		// Storage of last-used value
	reg init;					// flag to ensure first inegration result isn't erroneous.
	
	initial begin
		
		init = 0;
		prev_value = 0;
		result = 0;
		
	end
	
	always @ (posedge clk) begin
		
		if(init) begin
			
			result = (value - prev_value); // / time
			prev_value = value;
			
		end
		else begin
			
			init = 1;
			prev_value = value;
			result = 0;
			
		end
		
	end
	
endmodule