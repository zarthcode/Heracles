// A3988 Stepper channel

/// \todo Implement microstep morphing
/// \todo Implement variable microstepping (via vref adjustment)

module StepperChannel( step, dir, microstep, 
	phase1_I0, phase1_I1, phase1_phase,
	phase2_I0, phase2_I1, phase2_phase,
	modified_mode,
	morph_transition
	
	);
	
	input wire step;
	input wire dir;
	input wire [3:0] microstep;
	input wire modified_mode;		// Enables modified half-step sequencing (see A3988 datasheet)
	
	output reg phase1_I0, phase1_I1, phase1_phase;
	output reg phase2_I0, phase2_I1, phase2_phase;
	output reg morph_transition; 		// Indicates that the current position is on a quarter/half or half/full-step boundary.
	// Current sequence table position
	reg [3:0] sequence_position = 2;
	
	// Initial values
	initial begin
		phase1_I0 = modified_mode;
		phase1_I1 = 0;
		phase1_phase = 1;
		phase2_I0 = modified_mode;
		phase2_I1 = 0;
		phase2_phase = 1;
		morph_transition = 1;
	end
	// Each time a step is issued, move to the next sequence entry.
	always @ (posedge step)
		begin			
			
			// Determine next phase
			case(microstep)
				1:	// Full step (2,6,10,14)
					begin
						
						// sequence_position is unsigned, wrapping is automatic!
		
						if(dir)
								sequence_position = sequence_position + 4;
						else
							sequence_position = sequence_position - 4;						
						
					end
				2:	// Half step (0,2,4,6,8,10,12,14)
					begin
						
						// sequence_position is unsigned, wrapping is automatic!
						if(dir)
							sequence_position = sequence_position + 2;
						else
							sequence_position = sequence_position - 2;						
						
					end
				4:	// Quarter-step (1..16)
					begin
						
						// sequence_position is unsigned, wrapping is automatic!
						if(dir)
							sequence_position = sequence_position + 1;
						else
							sequence_position = sequence_position - 1;						
						
					end
			endcase
			
			// Output Step Sequence Settings (See A3988 datasheet)
			case (sequence_position)
				0:
					begin
						phase1_I0 = 1;
						phase1_I1 = 1;
						phase1_phase = 1'bx;	// Don't care
						
						phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 1;
						
						if(microstep == 4)
							morph_transition = 1;
						else
							morph_transition = 0;
					end
				1:
					begin
						phase1_I0 = 0;
						phase1_I1 = 1;
						phase1_phase = 1;
						
						phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 1;
						
						morph_transition = 0;
					end
				2:
					begin
						if((microstep == 2) && modified_mode)
							phase1_I0 = 1;
						else
							phase1_I0 = 0;
							
						phase1_I1 = 0;
						phase1_phase = 1;
						
						if((microstep == 2) && modified_mode)
							phase2_I0 = 1;
						else
							phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 1;
						
						morph_transition = 1;
					end
				3:
					begin
						phase1_I0 = 0;
						phase1_I1 = 0;
						phase1_phase = 1;
						
						phase2_I0 = 0;
						phase2_I1 = 1;
						phase2_phase = 1;
					
						morph_transition = 0;
					end
				4:
					begin
						phase1_I0 = 0;
						phase1_I1 = 0;
						phase1_phase = 1;
						
						phase2_I0 = 1;
						phase2_I1 = 1;
						phase2_phase = 1'bx;	// Don't care
						
						if(microstep == 4)
							morph_transition = 1;
						else
							morph_transition = 0;
					end
				5:
					begin
						phase1_I0 = 0;
						phase1_I1 = 0;
						phase1_phase = 1;
						
						phase2_I0 = 0;
						phase2_I1 = 1;
						phase2_phase = 0;
						
						morph_transition = 0;
					end
				6:
					begin
						if((microstep == 2) && modified_mode)
							phase1_I0 = 1;
						else
							phase1_I0 = 0;
							
						phase1_I1 = 0;
						phase1_phase = 1;
						
						if((microstep == 2) && modified_mode)
							phase2_I0 = 1;
						else
							phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 0;	  
						
						morph_transition = 1;
					end
				7:
					begin
						phase1_I0 = 0;
						phase1_I1 = 1;
						phase1_phase = 1;
						
						phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 0;
						
						morph_transition = 0;
					end
				8:
					begin
						phase1_I0 = 1;
						phase1_I1 = 1;
						phase1_phase = 1'bx;	// Don't care
						
						phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 0;
						
						if(microstep == 4)
							morph_transition = 1;
						else
							morph_transition = 0;
					end
				9:
					begin
						phase1_I0 = 0;
						phase1_I1 = 1;
						phase1_phase = 0;
						
						phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 0;	
						
						morph_transition = 0;
					end
				10:
					begin
						if((microstep == 2) && modified_mode)
							phase1_I0 = 1;
						else
							phase1_I0 = 0;
							
						phase1_I1 = 0;
						phase1_phase = 0;
						
						if((microstep == 2) && modified_mode)
							phase2_I0 = 1;
						else
							phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 0;
						
						morph_transition = 1;
						
					end
				11:
					begin
						phase1_I0 = 0;
						phase1_I1 = 0;
						phase1_phase = 0;
						
						phase2_I0 = 0;
						phase2_I1 = 1;
						phase2_phase = 0;
						
						morph_transition = 0;
					end
				12:
					begin
						phase1_I0 = 0;
						phase1_I1 = 0;
						phase1_phase = 0;
						
						phase2_I0 = 1;
						phase2_I1 = 1;
						phase2_phase = 1'bx;	// Don't care
						
						if(microstep == 4)
							morph_transition = 1;
						else
							morph_transition = 0;
					end
				13:
					begin
						phase1_I0 = 0;
						phase1_I1 = 0;
						phase1_phase = 0;
						
						phase2_I0 = 0;
						phase2_I1 = 1;
						phase2_phase = 1;	 
						
						morph_transition = 0;
					end
				14:
					begin
						if((microstep == 2) && modified_mode)
							phase1_I0 = 1;
						else
							phase1_I0 = 0;
							
						phase1_I1 = 0;
						phase1_phase = 0;
						
						if((microstep == 2) && modified_mode)
							phase2_I0 = 1;
						else
							phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 1;
						
						morph_transition = 1;
					end
				15:
					begin
						phase1_I0 = 0;
						phase1_I1 = 1;
						phase1_phase = 0;
						
						phase2_I0 = 0;
						phase2_I1 = 0;
						phase2_phase = 1; 
						
						morph_transition = 0;
					end
			endcase
			
		end
	
	
endmodule