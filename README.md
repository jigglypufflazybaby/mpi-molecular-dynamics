# Molecular Dynamics Simulation using OpenMPI and CUDA

## Overview

This project demonstrates a **Molecular Dynamics (MD)** simulation utilizing **OpenMPI** for parallel computation across multiple nodes and **CUDA** for GPU acceleration. The simulation computes forces between particles in a system, updates their positions over time, and allows for scalable parallelization, making it efficient for large systems of particles.

The primary goal is to model particle interactions, apply basic physics principles to simulate molecular systems, and leverage high-performance computing (HPC) techniques using OpenMPI and CUDA.

## Features

- **Particle Interactions:** Calculates forces between particles using simple physics models.
- **Parallelism:** Uses **OpenMPI** for distributed computing across multiple nodes or CPUs.
- **GPU Acceleration:** Uses **CUDA** to accelerate force calculations on the GPU.
- **Scalability:** The simulation can scale across multiple nodes for large-scale molecular dynamics simulations.

## Installation

### Prerequisites
Before running this project, ensure that you have the following software installed:

- **CUDA Toolkit:** Required to compile and run GPU-accelerated code.
- **OpenMPI:** Required for parallel computing and distributing the workload across multiple processors.
- **C++ Compiler:** A C++ compiler (e.g., `g++` or `mpic++` for OpenMPI) is needed to compile the source code.

### Steps to Install

1. **Install CUDA Toolkit**
   Follow the installation guide for the [CUDA Toolkit](https://developer.nvidia.com/cuda-downloads) appropriate for your operating system.

2. **Install OpenMPI**
   - On **Ubuntu/Debian**:
     ```bash
     sudo apt-get install openmpi-bin openmpi-common libopenmpi-dev
     ```
   - On **macOS** (using Homebrew):
     ```bash
     brew install open-mpi
     ```

3. **Clone the Repository**
   Clone the repository to your local machine:
   ```bash
   git clone https://github.com/your-username/mpi-cuda-molecular-dynamics.git
   cd mpi-cuda-molecular-dynamics

Usage
Compile the Code
To compile the C++ source code, use the following command:

bash
Copy code
mpic++ -o md_simulation md_simulation.cpp -lcuda
This will create an executable file md_simulation that is ready to run.

Run the Simulation
To run the simulation, use mpirun to launch the program with multiple processes. For example, to run with 4 processes:

bash
Copy code
mpirun -np 4 ./md_simulation
You can adjust the number of processes based on the number of available CPU cores or nodes.

Input and Output
Input: The input consists of initial particle data (position, velocity) that can be generated randomly or read from an external file (e.g., .xyz, .pdb).
Output: The simulation calculates forces and updates particle positions. Results can be stored in files, such as .dat or .xyz, depending on the desired output format.
File Formats
.cpp: C++ source code file containing the simulation logic.
.xyz: A simple text-based format for storing atomic coordinates and simulation data.
.dat: A generic data format used to store simulation results like forces and energies.
Contributing
Feel free to fork this project, create an issue, or submit a pull request if you'd like to contribute to the project! Contributions are welcome, especially for optimizing the simulation, adding more complex force models, or improving GPU utilization.

License
This project is licensed under the MIT License - see the LICENSE file for details.


---

### Key Sections:
- **Overview**: Describes what the project does and its goals.
- **Features**: Lists the main features and functionality of the simulation.
- **Installation**: Instructions to install CUDA, OpenMPI, and dependencies.
- **Usage**: How to compile and run the program.
- **Input and Output**: Describes file formats for input/output.
- **Contributing**: Encourages contributions from other developers.
- **License**: Specifies licensing terms (you can modify it if you're using a different license).

This README will help others understand how to set up and use your project, and will also be useful if you're collaborating with others or sharing it publicly on GitHub.
