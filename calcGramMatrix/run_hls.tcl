# Usage: vitis_hls -f <this_tcl_file.tcl>

# select what needs to run
set CSIM 0
set CSYNTH 1
set COSIM 1
set VIVADO_SYN 0
set VIVADO_IMPL 0
set SOLN "solution1"

# setup includes. Vitis_Libraries should be cloned at the same level of dstg_anti_jam
set XF_PROJ_ROOT "/home/jielei/Projects/Vitis_Libraries/solver"
#set INCL "-I${XF_PROJ_ROOT}/solver/L1/include"
#set INCL_TB "${INCL} -I${XF_PROJ_ROOT}/solver/L1/tests"


# setup hardware
set CLKP 300MHz
set XPART xczu28dr-ffvg1517-2-e
set_clock_uncertainty 12.5%

# setup project name based on this tcl file name
set PROJ [file rootname [file tail [ dict get [ info frame 0 ] file ]]]
puts "PROJ=${PROJ}"
# HLS


#edit the below line to match project
set basename "calcMatrixRhth"

open_project -reset proj_${basename}
set_top ${basename}


#add_files ${basename}.cpp -cflags "${INCL}"
add_files ${basename}.cpp
add_files -tb ${basename}_tb.cpp
add_files -tb reorderMatHin.txt
add_files -tb matrixRhth.txt


open_solution -reset "solution1"
set_part $XPART
create_clock -period $CLKP
set_clock_uncertainty 12.5%


#config_sdx -target none
#config_export -format syn_dcp -rtl vhdl -vivado_optimization_level 2 -vivado_phys_opt all -vivado_report_level 2 -version 1.0.2
config_rtl -reset control

#pick what needs to be setup - uncomment accordingly.
if {$CSIM == 1} {
  csim_design
}
if {$CSYNTH == 1} {
  csynth_design
}
if {$COSIM == 1} {
  cosim_design
  #cosim_design -trace_level all
}
if {$VIVADO_SYN == 1} {
  export_design -flow syn -rtl verilog
}
if {$VIVADO_IMPL == 1} {
  export_design -flow impl -rtl verilog -format syn_dcp
}

exit
