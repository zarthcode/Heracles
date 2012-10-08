#-- Lattice Semiconductor Corporation Ltd.
#-- Synplify OEM project file D:/Workspace/Heracles/Firmware/MachXO2/Heracles/launch_synplify.tcl
#-- Written on Wed Oct  3 22:46:18 2012

project -close
set filename "D:/Workspace/Heracles/Firmware/MachXO2/Heracles/Heracles_syn.prj"
if ([file exists "$filename"]) {
	project -load "$filename"
	project_file -remove *
	} else {
	project -new "$filename"
}

#device options
set_option -technology MACHXO2
set_option -part LCMXO2_1200ZE
set_option -package TG144C
set_option -speed_grade -1

#-- add_file options
set_option -include_path "D:/Workspace/Heracles/Firmware/MachXO2"
add_file -verilog "C:/lscc/diamond/2.0/cae_library/synthesis/verilog/machxo2.v"
add_file -verilog "D:/Workspace/Heracles/Firmware/MachXO2/EncoderCounter.v"
add_file -verilog "D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel.v"
add_file -verilog "D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel_tb.v"
project -result_file {D:/Workspace/Heracles/Firmware/MachXO2/Heracles/Heracles.edi}
project -save "$filename"
