// stepper channel test bench

module StepperChannel_tb();
	
	reg step_clk, direction, testmodified_mode;
	reg [3:0] testmicrostep_size;
	
	wire testphase1_I0, testphase1_I1, testphase1_phase;
	wire testphase2_I0, testphase2_I1, testphase2_phase;

	// Step sequence index
	reg [3:0] prev_sequence = 4'd2;
	reg [3:0] current_sequence = 4'd2;

	// step pulse generator
	always
		#1 step_clk = !step_clk;
		
	// Initialize DUT
	initial
	begin
		$display ("Starting test stepper channel.");
		
		step_clk = 0;
		direction = 0;
		testmicrostep_size = 1;
		testmodified_mode = 0;
		// current_sequence = get_sequence(testphase1_I0, testphase1_I1, testphase1_phase, testphase2_I0, testphase2_I1, testphase2_phase, testmodified_mode);
		
		// Setup monitor
		// $monitor ("Time = %d, 1/%d microstepping) = %d", $time, microstep_size);
		
		$monitor ("Time = %3d, sequence %d, (1/%d microstepping, direction = %b)", $time, current_sequence, testmicrostep_size, direction);
		
		// Full/half/qtr step tests
		repeat(3) begin					
			
			repeat (2) begin
				
				repeat (50) begin
		
					// Save previous phase sequence
					prev_sequence = current_sequence;
					
					#2;		// Pulse step
					
					// Evaluate current phase sequence
					current_sequence = get_sequence(testphase1_I0, testphase1_I1, testphase1_phase, testphase2_I0, testphase2_I1, testphase2_phase, testmodified_mode);
					
					// Check for correct transition.
					if(!correct_step(prev_sequence, current_sequence, direction, testmicrostep_size))
					begin
						$display ("FAILURE - Transitioned from sequence %d to %d", prev_sequence, current_sequence);
						$finish;				
					end
					
				end
				
				// Reverse direction
				direction = !direction;	  
				
			end			
			
			if(testmicrostep_size == 1)
				testmicrostep_size = 2;
			else if (testmicrostep_size  == 2)
				testmicrostep_size = 4;
		end	
		
		// Morphing test
		
		// Test complete
		$finish;
		
	end
	
	// Create DUT
	StepperChannel Test_CH (
		.step(step_clk),
		.dir(direction),
		.microstep(testmicrostep_size),
		.modified_mode(testmodified_mode),
		.phase1_I0(testphase1_I0),
		.phase1_I1(testphase1_I1),
		.phase1_phase(testphase1_phase),
		.phase2_I0(testphase2_I0),
		.phase2_I1(testphase2_I1),
		.phase2_phase(testphase2_phase)
		);
	
	// Phase sequence reverse lookup
	function [5:0] get_sequence;
		
		input phase1_I0, phase1_I1, phase1_phase, phase2_I0, phase2_I1, phase2_phase, modified_mode;
		
		// From A3988 datasheet
		casex({phase1_I0, phase1_I1, phase1_phase, phase2_I0, phase2_I1, phase2_phase})
			6'b11x001: get_sequence = 0;
			6'b011001: get_sequence = 1;
			6'bx01x01: 
				begin
					get_sequence = 2;	// MODIFIED
					
					if(modified_mode && (!phase1_I0 || !phase2_I0))
					begin
						$display ("INVALID phase state! (Modified sequence expected)");
						$finish;
					end
					else if(!modified_mode && (phase1_I0 || phase2_I0))
					begin
						$display ("INVALID phase state! (Modified sequence not expected)");
						$finish;
					end	
				end
			6'b001011: get_sequence = 3;
			6'b00111x: get_sequence = 4;
			6'b001010: get_sequence = 5;
			6'bx01x00:
				begin
					get_sequence = 6;	// MODIFIED
					
					if(modified_mode && (!phase1_I0 || !phase2_I0))
					begin
						$display ("INVALID phase state! (Modified sequence expected)");
						$finish;
					end
					else if(!modified_mode && (phase1_I0 || phase2_I0))
					begin
						$display ("INVALID phase state! (Modified sequence not expected)");
						$finish;
					end	
				end
			6'b011000: get_sequence = 7;
			6'b11x000: get_sequence = 8;
			6'b010000: get_sequence = 9;
			6'bx00x00:
				begin
					get_sequence = 10;	// MODIFIED
					
					if(modified_mode && (!phase1_I0 || !phase2_I0))
					begin
						$display ("INVALID phase state! (Modified sequence expected)");
						$finish;
					end
					else if(!modified_mode && (phase1_I0 || phase2_I0))
					begin
						$display ("INVALID phase state! (Modified sequence not expected)");
						$finish;
					end	
				end
			6'b000010: get_sequence = 11;
			6'b00011x: get_sequence = 12;
			6'b000011: get_sequence = 13;
			6'bx00x01:
				begin
					get_sequence = 14;	// MODIFIED
					
					if(modified_mode && (!phase1_I0 || !phase2_I0))
					begin
						$display ("INVALID phase state! (Modified sequence expected)");
						$finish;
					end
					else if(!modified_mode && (phase1_I0 || phase2_I0))
					begin
						$display ("INVALID phase state! (Modified sequence not expected)");
						$finish;
					end	
				end
			6'b010001: get_sequence = 15;
			default: 
			begin
				$display ("INVALID phase state! %b", {phase1_I0, phase1_I1, phase1_phase, phase2_I0, phase2_I1, phase2_phase});
				get_sequence = 6'bxxxxxx;
			end
		endcase						 				
		
	endfunction

	// Phase transition verification
	function correct_step;
		input start_seq, end_seq, direction, microstepping;

		reg [3:0] start_seq, end_seq, microstepping;
		reg [3:0] expected_seq;
		begin
			
			case(microstepping)
				1:	// Full step (3,7,11,15)
					begin
						
						// sequence_position is unsigned, wrapping is automatic!
						if(direction)
							expected_seq = start_seq + 4;
						else
							expected_seq = start_seq - 4;						
						
					end
				2:	// Half step (1,3,5,7,9,11,13,16)
					begin
						
						// sequence_position is unsigned, wrapping is automatic!
						if(direction)
							expected_seq = start_seq + 2;
						else
							expected_seq = start_seq - 2;						
						
					end
				4:	// Quarter-step (1..16)
					begin
						
						// sequence_position is unsigned, wrapping is automatic!
						if(direction)
							expected_seq = start_seq + 1;
						else
							expected_seq = start_seq - 1;						
						
					end
				
			endcase
			
			if(end_seq != expected_seq)
			begin
				correct_step = 0;
				$display("Expected transition to sequence %d", expected_seq);
			end
			else begin
				correct_step = 1;
			end
		end
	endfunction
endmodule