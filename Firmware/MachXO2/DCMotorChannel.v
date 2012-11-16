// DC Motor channel

module DCMotorChannel ( dir, coast, pwm_duty, pwm_period, clk, out_I0, out_I1, out_phase);
	// Inputs
	input dir, coast, pwm_duty, pwm_period, clk;
	
	wire dir;
	wire coast;
	wire [63:0] pwm_duty;
	wire [63:0] pwm_period;
	wire clk;
	
	// Outputs
	output reg out_I0, out_I1, out_phase;
	

	// Internal variable
	reg [63:0] pwm_position = 64'd0;
	
	// code
	always @ (posedge clk)
		begin
						
			// Update pwm output
			if (!coast && (pwm_duty != 0) && (pwm_position <= pwm_duty)) begin
				out_I0 <= 1'b1;
				out_I1 <= 1'b1;
				out_phase <= dir;
			end else begin
				// Turn off outputs
				out_I0 <= 1'b0;
				out_I1 <= 1'b0;
				out_phase <= dir;				
			end
			
			// Increment pwm_position
			pwm_position = pwm_position + 1;
			
			if(pwm_position >= pwm_period)
				pwm_position = 64'd0;
		end

endmodule
	