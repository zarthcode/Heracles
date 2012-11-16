
module PIDController (ctrl_input, ctrl_setpoint, ctrl_output, clk, enable, Kp, Ki, Kd );
	
	parameter W=64;				// Bit width
	
	// Inputs
	
	input ctrl_input;		// PID Input
	input ctrl_setpoint;	// PID Setpoint
	
	input clk;		// PID clock.
	input enable;	// Indicates that pid is enabled.
	
	input [W-1:0] Kp;		// Kp tuning parameter;
	input [W-1:0] Ki;		// Ki tuning parameter;
	input [W-1:0] Kd;		// Kd tuning parameter;
	
	
	// Outputs
	output ctrl_output;		// PID output
	
	// Internal registers/variables/state
	reg enabled;
	
	
	// Initialization
	initial begin
		
	end
	
	// Enable
	always @ (posedge enable) begin
		
		
	end
	
	// Disable
	always @ (negedge enable) begin
	
	end
	
	// PID Clock event
	always @ (posedge clk) begin
		if(enable) begin
			
			
		end
		else begin
			
			
			
		end
	end
	
endmodule