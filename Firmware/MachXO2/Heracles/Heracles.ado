setenv SIM_WORKING_FOLDER .
set newDesign 0
if {![file exists "D:/Workspace/Heracles/Firmware/MachXO2/Heracles/Heracles.adf"]} { 
	design create Heracles "D:/Workspace/Heracles/Firmware/MachXO2"
  set newDesign 1
}
design open "D:/Workspace/Heracles/Firmware/MachXO2/Heracles"
cd "D:/Workspace/Heracles/Firmware/MachXO2"
designverincludedir -clear
designverlibrarysim -PL -clear
designverlibrarysim -L -clear
designverlibrarysim -PL pmi_work
designverlibrarysim ovi_machxo2
designverdefinemacro -clear
if {$newDesign == 0} { 
  removefile -Y -D *
}
addfile "D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel.v"
addfile "D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel_tb.v"
	vlib "D:/Workspace/Heracles/Firmware/MachXO2/Heracles/work"
set worklib work
adel -all
vlog "D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel.v"
vlog "D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel_tb.v"
module DCMotorChannel_tb
