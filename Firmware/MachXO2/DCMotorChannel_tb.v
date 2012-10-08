// DC Motor channel test bench

module DCMotorChannel_tb();
	
	reg  direction, coast, clk;
	reg [63:0] test_duty, test_period;
	
	wire test_I0, test_I1, test_phase;

	// Clock generator
	always
		#1 clk = !clk;
		
	// Initialize DUT
	initial
	begin
		$display ("Starting test DC channel.");
		clk = 0;
		direction = 0;
		coast = 0;
		test_duty = 64'd0;
		test_period = 64'd100;
		
		// Repeat 5 times
		repeat (21) begin
			
			$monitor ("Time = %d, duty cycle = %d, period = %d", $time, test_duty, test_period);
			
			// Initialize
			direction = 0;
			clk = 0;
			coast = 0;
			#1000;
			
			// Reverse direction
			direction = !direction;
			#1000;
			
			// Coast
			coast = 1;
			#1000;
			
			// Increase duty cycle for next phase
			$display ("Increasing duty cycle.");
			if((test_duty + 5) >= test_period)
				test_duty = test_period;
			else
				test_duty = test_duty + 5;
			
			
		end
		
		// Test complete
		#1 $finish;
		
	end
	
	// Create DUT
	DCMotorChannel Test_CH (
		.dir(direction),
		.coast(coast),
		.pwm_duty(test_duty),
		.pwm_period(test_period),
		.clk(clk),
		.out_I0(test_I0),
		.out_I1(test_I1),
		.out_phase(test_phase)
		);
		

	
	
	
endmodule