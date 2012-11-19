// Heracles Device
module Heracles_top(
	output wire osc_clk,
	
	output wire M1_1_I0, output wire M1_1_I1, output wire M1_1_Phase,
	output wire M1_2_I0, output wire M1_2_I1, output wire M1_2_Phase,
	output wire M1_3_I0, output wire M1_3_I1, output wire M1_3_Phase,
	output wire M1_4_I0, output wire M1_4_I1, output wire M1_4_Phase,
	
	input wire M1_1_Step,
	input wire M1_1_Dir,
	input wire M1_1_MS1,
	input wire M1_1_MS2,
	
	input wire M1_2_Step,
	input wire M1_2_Dir,
	input wire M1_2_MS1,
	input wire M1_2_MS2,
	
	);
	
	// Registers
	
		wire Reset;	// Global reset function. (Requires high fan-out)
		
	// Internal Oscillator
		defparam OSCH_inst.NOM_FREQ = "2.08";		//  This is the default frequency

		OSCH OSCH_inst( .STDBY(0), 	// 0=Enabled, 1=Disabled also Disabled with Bandgap=OFF
                .OSC(osc_clk),			/// \todo Make this an external, high-precision clock.
                .SEDSTDBY(0));		//  (Simulation purposes) this signal is not required if not using SED - see TN1199 for more details.

	// Motion clock
	
		wire motion_clk;
		
	// Motion calculations occur  100nS
		
	// A3988 MotorPhase bus
	
		wire [4:0] MotorPhase_addr_bus;
		wire MotorPhase_I0;
		wire MotorPhase_I1;
		wire MotorPhase_Phase;

		// module MotorPhase(reset, addr_bus, I0_bus, I1_bus, Phase_bus, I0_out, I1_out, Phase_out);
		MotorPhase #(0) M1_1(
			.reset(Reset),
			.clk(osc_clk),
			.addr_bus(MotorPhase_addr_bus),
			.I0_bus(MotorPhase_I0),
			.I1_bus(MotorPhase_I1),
			.Phase_bus(MotorPhase_Phase));
			// I0_out, I1_out and Phase_out must be connected!
			
		MotorPhase #(1) M1_2(
			.reset(Reset),
			.clk(osc_clk),
			.addr_bus(MotorPhase_addr_bus),
			.I0_bus(MotorPhase_I0),
			.I1_bus(MotorPhase_I1),
			.Phase_bus(MotorPhase_Phase));
			// I0_out, I1_out and Phase_out must be connected!
		
		MotorPhase #(2) M1_3(
			.reset(Reset),
			.clk(osc_clk),
			.addr_bus(MotorPhase_addr_bus),
			.I0_bus(MotorPhase_I0),
			.I1_bus(MotorPhase_I1),
			.Phase_bus(MotorPhase_Phase));
			// I0_out, I1_out and Phase_out must be connected!
		
		MotorPhase #(3) M1_4(
			.reset(Reset),
			.clk(osc_clk),
			.addr_bus(MotorPhase_addr_bus),
			.I0_bus(MotorPhase_I0),
			.I1_bus(MotorPhase_I1),
			.Phase_bus(MotorPhase_Phase));
			// I0_out, I1_out and Phase_out must be connected!
	
	
	// Encoders (0..23)
	
		wire [15:0] DataBus;
	
		parameter encoder_width = 24;
		
		// module IncrementalEncoder (A, B, I, Position, DataBus, Reset, SetCPR, SetPosition);
		
		IncrementalEncoder #(16) E1(A1, B1, I1, Position1, DataBus, .Reset(Reset), SetCPR, SetPosition);
		IncrementalEncoder #(16) E2(A2, B2, I2, Position2, DataBus, .Reset(Reset), SetCPR, SetPosition);
		IncrementalEncoder #(16) E3(A3, B3, I3, Position3, DataBus, .Reset(Reset), SetCPR, SetPosition);
		IncrementalEncoder #(16) E4(A4, B4, I4, Position4, DataBus, .Reset(Reset), SetCPR, SetPosition);
		
		
	// DAC - FIFO
	
		
		
	
	// TrimDAC Module - continually empties FIFO into the 2 TrimDAC devices
	
		
	
	// State RAM
	
		// Current Base Address (0-23)
		// Number of configured addresses
	
	// PID Controller
		
		reg [3:0] PID_State = 4'd0;
		
		always @ (posedge osc_clk) begin
			case (PID_State)
			
			4'd0:	// 0. Reset
			// 1. Load values from memory?
				begin
					
					
				end
			
			// 2. Evaluate encoder delta
			4'd1:
				// 3. Calculate speed
				// 4. Calculate acceleration
			// 5. Evaluate current movement command
				// Determine error PID
			// 6. Determine required movement
			// 7. Update DAC?
			// 8. Store values to memory
			endcase
		end
	// Stepper Controller
	
	// DC Motor Controller
	
	// BLDC Controller
	
	
	
endmodule