# Parallelized Monte Carlo Simulations of the Ising Model

## Overview
This project explores the parallelization of Monte Carlo simulations for the Ising model, a classical model of ferromagnetism in statistical mechanics. The goal is to investigate the parallelization of popular Ising algorithms.

## Features
- Implementation of alternative Monte Carlo method algorithms: Metropolis, Swedsen-Wang, and Wolff.
- Parallelization using multi-threading (OpenMP).
- Performance evaluation metrics: Execution time, Speedup, Efficiency.
- Visualization of simulation results and performance analysis.

## Installation
1. Clone the repository
2. Install required dependencies (OpenMP).
**Note** It is preferred that the OS you use is Linux as this repo is not guaranteed to work in any other OS.

### SCC
If running on the SCC, you can run the repo by:
1. Clone the repository
2. Navigate to the source folder and run `make`. All of the compiled files will be in the bin folder
    - Run a file like Ising_Heat with the following: `./Ising_Heat`
3. To run multiple threads for the parallelized files you can:
    - Enter `export OMP_NUM_THREADS=2` into the terminal (sets # of threads to be used)
        - Note: You will need to run this command every time you want to change the number of threads.
    - Run a Parallelized file like Ising_Heat_Parallel with: `./Ising_Heat_Parallel`
    - If you need help running the code, refer to the following page on the SCC: [OpenMP on the SCC](https://www.bu.edu/tech/support/research/software-and-programming/programming/multiprocessor/)

## Usage
1. Compile the code using the provided Makefile
    - **Note:** The makefile must be run in Linux due to the directory structure
## Performance Evaluation
- The following are the statistics gathered by the code during the time of execution:
    - Running Time (in milliseconds)
    - Number of Clusters
    - Cluster Labels
    - Value of N at runtime (size of the grid)
    - Value of Beta
    - Number of threads being used (Is only implemented in the parallelized scripts)
All of these statistics are recorded in an Excel file except for the Cluster Labels.
## Acknowledgments
- [OpenMP](https://www.openmp.org/) for parallel computing support.
