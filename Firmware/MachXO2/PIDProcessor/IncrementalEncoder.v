
module IncrementalEncoder ( A, B, I, Position, DataBus, Reset, SetCPR, SetPosition);
	
	parameter buswidth = 32;	// This is a 32bit encoder.
	
	// Input
	input wire A, B, I;					// Movement pulses
	input wire Reset;					// Resets the component
	input wire SetCPR;					// Loads value from databus into CPR register
	input wire SetPosition;				// Loads value from databus into position register
	input wire EnableIndex;				// Enables index pulses.
	input wire [buswidth-1:0] DataBus;	// Used to load new values
	
	
	// Output
	output reg signed [buswidth-1:0] Position;		// Configurable
	
	// Internal variables
	reg [buswidth-1:0] CPR;		// CPR (Counts per revolution) setting
	reg CPR_enabled;			// flag that indicates the cpr should be used.
	reg Index_enabled; 			// flag that indicates that index should be used/enabled
	
	// Startup
	initial begin
		// Set position to 0, unknown CPR, 
		Position = 32'sd0;
		CPR = 32'd0;
		CPR_enabled = 0;
		Index_enabled = 0;
	end
	
	// Reset
	always @ (posedge Reset) begin
		
		// Set position to 0, unknown CPR, 
		Position = 32'sd0;
		CPR = 32'd0;
		CPR_enabled = 0;
		Index_enabled = 0;		
		
	end
	
	// SetCPR command
	always @ (posedge SetCPR) begin
		
		// Read value from bus, and place into CPR register
		CPR <= DataBus;
		
	end
	
	// SetPosition command
	always @ (posedge SetPosition) begin
		
		Position <= DataBus;
		
	end
	
	// Movement handlers
	
	always @ (posedge A) begin
		
		if (B)
			CW();	// Clockwise rotation.
		else
			CCW();	// Counter-clockwise rotation.
		
	end
	
	always @ (posedge B) begin
		
		if (A)
			CCW();	// Counter-clockwise rotation.
		else
			CW();	// Clockwise rotation.
		
	end
	
	always @ (negedge A) begin
		
		if (B)
			CCW();	// Counter-clockwise rotation.
		else
			CW();	// Clockwise rotation.
		
	end
	
	always @ (negedge B) begin
		
		if (A)
			CW();	// Clockwise rotation.
		else
			CCW();	// Counter-clockwise rotation.
		
	end
	
	// Zero-Index 
	always @ (posedge I) begin
		
		// Zero (center) position.
		if (Index_enabled) begin
			
			Position = 32'sd0;	// Set zero position.

			// \todo Determine missed counts/positional error

			// Disable index 
			// Index_enabled = 0;
			
		end

		/// \todo Check for CPR accuracy?
		/// \todo One-time Position-tuning
		/// \todo
	
	end
	
	/// Code to increment position reg. for clockwise motion
	task CW;
	begin
		
		if (CPR_enabled && (Position == CPR - 1))
			Position = 0;
		else
			Position = Position + 1;
		
	end	
	endtask
	
	/// Code to increment position reg. for counter-clockwise motion
	task CCW;
	begin
		
		if (CPR_enabled && (Position == 0))
			Position = CPR - 1;
		else
			Position = Position - 1;
		
	end
	endtask
	
endmodule