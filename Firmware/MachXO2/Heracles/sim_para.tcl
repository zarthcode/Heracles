lappend auto_path "C:/lscc/diamond/2.0/data/script"
package require simulation_generation
set ::bali::simulation::Para(PROJECT) {Heracles}
set ::bali::simulation::Para(PROJECTPATH) {D:/Workspace/Heracles/Firmware/MachXO2}
set ::bali::simulation::Para(FILELIST) {"D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel.v" "D:/Workspace/Heracles/Firmware/MachXO2/DCMotorChannel_tb.v" }
set ::bali::simulation::Para(GLBINCLIST) {}
set ::bali::simulation::Para(INCLIST) {"none" "none"}
set ::bali::simulation::Para(WORKLIBLIST) {"" "" }
set ::bali::simulation::Para(COMPLIST) {"VERILOG" "VERILOG" }
set ::bali::simulation::Para(SIMLIBLIST) {pmi_work ovi_machxo2}
set ::bali::simulation::Para(MACROLIST) {}
set ::bali::simulation::Para(SIMULATIONTOPMODULE) {DCMotorChannel_tb}
set ::bali::simulation::Para(SIMULATIONINSTANCE) {}
set ::bali::simulation::Para(LANGUAGE) {VERILOG}
set ::bali::simulation::Para(SDFPATH)  {}
::bali::simulation::ActiveHDL_Run
