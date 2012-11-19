// Verilog Motor Phase
module MotorPhase(reset, clk, addr_bus, I0_bus, I1_bus, Phase_bus, I0_out, I1_out, Phase_out);
	
	parameter phase_address = 0;
	
	output wire I0_out;
	output wire I1_out;
	output wire Phase_out;
	
	input wire I0_bus;
	input wire I1_bus;
	input wire Phase_bus;
	input wire reset;
	input wire clk;
	
	reg I0;
	reg I1;
	reg Phase;
	
	input [4:0] addr_bus;
	
	always @ (posedge reset or posedge clk)
		if (reset) begin
			I0 <= 0;
			I1 <= 0;
			Phase <= 0;
		end else if (addr_bus == phase_address) begin
			I0 <= I0_bus;
			I1 <= I1_bus;
			Phase <= Phase_bus;
		end
	
	assign I0_out = I0;
	assign I1_out = I1;
	assign Phase_out = Phase;
	
endmodule