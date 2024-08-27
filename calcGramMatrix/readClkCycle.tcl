# Define the file path
set file_path "./proj_calcMatrixRhth/solution1/sim/report/verilog/lat.rpt"

# Initialize a variable to hold the value of $TOTAL_EXECUTE_TIME
set total_latency 0

# Open the file and read its contents line by line
set file [open $file_path r]
while {[gets $file line] >= 0} {
    # Check if the line contains $TOTAL_EXECUTE_TIME
    if {[regexp {^\$TOTAL_EXECUTE_TIME\s*=\s*"(\d+)"} $line match value]} {
        # Convert the extracted value to an integer
        set total_latency [expr {$value + 0}]
        break
    }
}
close $file

# Print the extracted value
puts $total_latency

# Return the extracted value
return $total_latency