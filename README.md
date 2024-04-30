# Parallelized Monte Carlo Simulations of the Ising Model

## Overview
This project explores the parallelization of Monte Carlo simulations for the Ising model, a classical model of ferromagnetism in statistical mechanics. The goal is to investigate alternative Monte Carlo techniques and parallelization strategies to accelerate the simulation of spin systems and analyze their thermodynamic properties.

## Features
- Implementation of alternative Monte Carlo methods: Parallel Tempering, Cluster Algorithms, and Nested Sampling.
- Parallelization using multi-threading (OpenMP) and GPU acceleration (CUDA).
- Performance evaluation metrics: Execution time, Speedup, Efficiency, and Scalability.
- Visualization of simulation results and performance analysis.

## Installation
1. Clone the repository
2. Install required dependencies (e.g., OpenMP, CUDA, NumPy, Matplotlib).

## Usage
1. Compile the code using the provided Makefile
    - **Note:** The makefile must be run in linux due to the directory structure
## Performance Evaluation
- The following are the statistics gathered by the code during the time of execution:
    - Running Time (in milliseconds)
    - Number of Clusters
    - Cluster Labels
    - Value of N at runtime
    - Number of threads being used (Is only implemented in the parallelized scripts)
## Acknowledgments
- [OpenMP](https://www.openmp.org/) and [CUDA](https://developer.nvidia.com/cuda-toolkit) for parallel computing support.
