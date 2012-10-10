#-- Lattice Semiconductor Corporation Ltd.
#-- Synplify OEM project file

#device options
set_option -technology MACHXO2
set_option -part LCMXO2_1200ZE
set_option -package TG144C
set_option -speed_grade -1

#compilation/mapping options
set_option -symbolic_fsm_compiler true
set_option -resource_sharing true

#use verilog 2001 standard option
set_option -vlog_std v2001

#map options
set_option -frequency 200
set_option -fanout_limit 100
set_option -auto_constrain_io true
set_option -disable_io_insertion false
set_option -retiming false; set_option -pipe false
set_option -force_gsr false
set_option -compiler_compatible true
set_option -dup false
set_option -frequency 1
set_option -default_enum_encoding default

#simulation options


#timing analysis options
set_option -num_critical_paths 3
set_option -num_startend_points 0

#automatic place and route (vendor) options
set_option -write_apr_constraint 0

#synplifyPro options
set_option -fixgatedclocks 3
set_option -fixgeneratedclocks 3
set_option -update_models_cp 0
set_option -resolve_multiple_driver 1

#-- add_file options
set_option -include_path {D:/Workspace/Heracles/Firmware/MachXO2}
add_file -verilog {C:/lscc/diamond/2.0/cae_library/synthesis/verilog/machxo2.v}
add_file -verilog {D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel.v}
add_file -verilog {D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel_tb.v}
add_file -verilog {D:/Workspace/Heracles/Firmware/MachXO2/StepperChannel.v}
add_file -verilog {D:/Workspace/Heracles/Firmware/MachXO2/StepperChannel_tb.v}
add_file -verilog {D:/Workspace/Heracles/Firmware/MachXO2/IncrementalEncoder.v}
add_file -verilog {D:/Workspace/Heracles/Firmware/MachXO2/IncrementalEncoder_tb.v}
add_file -verilog {D:/Workspace/Heracles/Firmware/MachXO2/AbsoluteEncoder.v}
add_file -verilog {D:/Workspace/Heracles/Firmware/MachXO2/PIDController.v}
add_file -verilog {D:/Workspace/Heracles/Firmware/MachXO2/Integrator.v}


#-- set result format/file last
project -result_file {D:/Workspace/Heracles/Firmware/MachXO2/Heracles/Heracles_Heracles.edi}

#-- error message log file
project -log_file {Heracles_Heracles.srf}

#-- set any command lines input by customer


#-- run Synplify with 'arrange HDL file'
project -run
