// AD8804 TrimDAC controller

// This module will (eventually) track all 12 DAC registers and update when necessary.
// Consult AD8804 datasheet, fig 15b
module TrimDAC( latch, address, dac_value, busy, clk, clk_o, sdi_o, cs_o );
	
	input wire	 		latch;
	input wire [3:0]	address;
	input wire [7:0]	dac_value;

	input wire			clk;	// 5ns

	// Device outputs
	output sdi_o;
	output cs_o;
	output clk_o;		// Device clock (t_ch = t_cl = 15ns; 33.33MHz)
	
	// Internal state
	
	reg [11:0] 	serial_data;	// 4-bit address, 8-bit data
	reg [3:0]	position;		// Current transfer bit.
	reg [3:0]	tx_step;			// Transfer in progress
	output wire busy;
	
	reg cs;
	
	always @ (posedge latch) begin
		if (~busy) begin
			
			// Latch address and data
			serial_data <= {address, dac_value};
			// Set mask to address MSB
		
			// Latch busy
			tx_step <= 4'd1;
			busy <= 0;
			
		end
	end
	
	// 5ns clk needed.
	always @ (posedge clk) begin
		
		if (busy)
			case (tx_step)
		
				// Assert CS low
				1:
				begin
					cs_o <= 0;
				end
				// Wait for t_css (10ns)
				2:
				
				// clk_o up
				3:
				
				// Present data on SDI
				4:
				
				// Wait for t_ds (5ns)
				5:
				
				// Wait for t_ch
				6:
				
				// clk_o down
				7:
				
				// Wait for t_cl
				8:
				
				// clk_o high
				9:
				
				// Wait for t_dh (5ns)
				10:
				
				// Ensure t_csh has passed (20ns)
				11:
				
				// Assert CS high
				12:
				
				// Remain high for t_csw (10ns)
				13:
					
				// Value is within 1/2 LSB (from CS high)
				14:
				begin
					busy <= 0;
				end
				// Do nothing
				default:

			end
			tx_step = tx_step + 1;
			
		end
		
	end
	
endmodule