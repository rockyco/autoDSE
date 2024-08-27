# Check if the correct number of arguments is provided
if {[llength $argv] != 7} {
    puts "Usage: tclsh updateParam.tcl <PP0> <PP1> <PP2> <PP3> <PP4> <PP5> <PP6>"
    exit 1
}

# Get the values from the command-line arguments
set PP0 [lindex $argv 0]
set PP1 [lindex $argv 1]
set PP2 [lindex $argv 2]
set PP3 [lindex $argv 3]
set PP4 [lindex $argv 4]
set PP5 [lindex $argv 5]
set PP6 [lindex $argv 6]

set file_path "rx_frame.hpp"

set updates {
    {92 "#define NUM_CHOLS $PP0  // Number of Cholesky decomposition kernels"}
    {93 "#define NUM_FFT_PE $PP1  // Number of FFT kernels"}
    {96 "#define BS_II $PP2  // Second stage II"}
    {97 "#define FS_II $PP3  // First stage II"}
    {98 "#define MF_II $PP4  // Matrix filter II"}
    {99 "#define GM_II $PP5  // Generate matrix II"}
    {100 "#define CE_II $PP6  // Channel estimation II"}
}

set file [open $file_path r]
set content [read $file]
close $file

set lines [split $content "\n"]
foreach update $updates {
    set line_number [lindex $update 0]
    set new_line [subst [lindex $update 1]]
    lset lines $line_number $new_line
}

set new_content [join $lines "\n"]

set file [open $file_path w]
puts -nonewline $file $new_content
close $file
