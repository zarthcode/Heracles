/*

	DC motor control module for the Allegro A3988/A3989

*/


module DCMotorChannel_Module (dir, pwm_duty, pwm_freq, coast, chEnable, out_I0, out_I1, out_Phase)
	
	wire ena;
	wire dir;
	wire coast;
	
	reg pwm_duty;
	reg pwm_freq;
	
	reg chEnable;


	wire out_I0;		// A3988 I0 pin
	wire out_I1;		// A3988 I1 pin
	wire out_Phase;		// A3988 PHASE pin


end module


