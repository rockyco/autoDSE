# Multiple User MIMO-OFDM Transceiver Project

## Overview

This project focuses on the development of a multiple user MIMO-OFDM transceiver. Specifically, it provides a component of the receiver that implements the functionality of a Gram Matrix with a 2-D scale of 8x8. The project includes an automated design space exploration (DSE) framework using TCL scripts to optimize hardware architecture.

## Purpose

The primary goal of this project is to balance the tradeoff between resource cost and latency improvement by adjusting parallelism parameters. The automated DSE framework aims to find the optimal hardware architecture that minimizes resource usage while meeting the target latency constraints.

## Components

1. **updateParam.tcl**: Defines the parallelism parameters for each individual module.
2. **run_hls.tcl**: Executes the Vitis HLS tool to build the HLS project, conduct RTL synthesis, and perform RTL simulation.
3. **readLUT.tcl**: Extracts the exact value of LUT usage.
4. **readClkCycle.tcl**: Extracts the exact value of latency.

## Automated Design Space Exploration

The DSE framework automates the process of exploring different hardware configurations by varying the parallelism parameters. It evaluates each configuration based on LUT resource utilization and latency, aiming to find the optimal balance.

## How to Run the Project

### Prerequisites

- Vitis HLS tool installed
- TCL interpreter installed

### Steps to Execute

1. **Clone the Repository**
   ```sh
   git clone <repository_url>
   cd <repository_directory>
   ```

2. **Set Up Parameters**
   Edit the `updateParam.tcl` script to define the range of parallelism parameters for each module.

3. **Run the Automated DSE Framework**
   Execute the following command to start the design space exploration:
   ```sh
   tclsh autoDSE.tcl
   ```

4. **Review Results**
   The results, including LUT utilization and latency for each configuration, will be logged in `results.log`.

### Example Execution

```sh
# Clone the repository
git clone http://github.com/rockyco/autoDSE
cd <repository_directory>

# Run the automated DSE framework
tclsh autoDSE.tcl

# Check the results
cat results.log
```

## Conclusion

This project demonstrates an automated approach to optimizing hardware architecture for a multiple user MIMO-OFDM transceiver. By leveraging TCL scripts and the Vitis HLS tool, it efficiently explores the design space to find the optimal configuration that balances resource usage and latency.

For more details, refer to the individual TCL scripts and the `results.log` file generated during execution.