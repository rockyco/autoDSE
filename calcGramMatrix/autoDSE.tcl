# Define the range of input parameters
# Number of Cholesky decomposition kernels
set param0_range {4}
# Number of FFT kernels
set param1_range {1}
# Second stage II
#set param2_range {1 6 8}
set param2_range {1}
# First stage II
set param3_range {1}
# Matched filter II
set param4_range {1}
# Gram matrix II
set param5_range {1 2 4 6 8 10 12}
# Channel estimation II
set param6_range {1}

# Initialize variables to track the minimum first_node_value and corresponding parameters
set min_first_node_value 999999
set best_params ""

# Open the log file for writing
set log_file [open "results.log" "w"]

# Iterate over the combinations of input parameters
foreach param5 $param5_range {
    foreach param6 $param6_range {
        foreach param2 $param2_range {
            foreach param3 $param3_range {
                foreach param4 $param4_range {
                    foreach param0 $param0_range {                        
                        foreach param1 $param1_range {
                            # Execute tclsh updateParam.tcl
                            exec tclsh updateParam.tcl $param0 $param1 $param2 $param3 $param4 $param5 $param6

                            # Execute vitis_hls -f run_hls.tcl
                            exec vitis_hls -f run_hls.tcl

                            # Call readLUT.tcl to get the value of first_node_value
                            set first_node_value [exec tclsh readLUT.tcl]

                            # Call readClkCycle.tcl to get the value of total_execute_time
                            set total_execute_time [exec tclsh readClkCycle.tcl]

                            # Print the parameters and values
                            puts "param0: $param0, param1: $param1, param2: $param2, param3: $param3, param4: $param4, param5: $param5, param6: $param6, LUT_utilization: $first_node_value, total_execute_time: $total_execute_time"

                            # Log the parameters and values
                            puts $log_file "param0: $param0, param1: $param1, param2: $param2, param3: $param3, param4: $param4, param5: $param5, param6: $param6, LUT_utilization: $first_node_value, total_execute_time: $total_execute_time"

                            # Check if total_execute_time is less than 36000
                            if {$total_execute_time < 2000} {

                                # Check if the current first_node_value is the minimum
                                if {$first_node_value < $min_first_node_value} {
                                    set min_first_node_value $first_node_value
                                    set best_params "NUM_CHOLS: $param0, NUM_FFT_PE: $param1, BS_II: $param2, FS_II: $param3, MF_II: $param4, GM_II: $param5, CE_II: $param6"
                                }
                            } else {
                                # Log the parameters and values that exceed the total_execute_time threshold
                                puts $log_file "Exceeded total_execute_time threshold: $total_execute_time"
                                # Break out of the current loop
                                break
                            }
                        }
                    }
                }
            }
        }
    }
}

# Close the log file
close $log_file

# Print the results
puts "Minimum first_node_value: $min_first_node_value"
puts "Best parameters: $best_params"