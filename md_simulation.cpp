#include <mpi.h>
#include <cuda_runtime.h>
#include <iostream>
#include <vector>

#define NUM_PARTICLES 1000
#define TIME_STEPS 100

// Particle structure
struct Particle {
    float x, y, z;  // Position
    float vx, vy, vz;  // Velocity
};

// CUDA kernel to calculate forces (a simple placeholder function)
__global__ void compute_forces(Particle* particles, float* forces, int num_particles) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < num_particles) {
        // Just a simple example: particles interact with each other
        forces[idx] = particles[idx].vx * particles[idx].vx + particles[idx].vy * particles[idx].vy + particles[idx].vz * particles[idx].vz;
    }
}

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize particles and forces
    std::vector<Particle> particles(NUM_PARTICLES);
    std::vector<float> forces(NUM_PARTICLES);

    // Assign random values to particles (for simplicity)
    if (rank == 0) {
        for (int i = 0; i < NUM_PARTICLES; ++i) {
            particles[i].x = static_cast<float>(rand()) / RAND_MAX;
            particles[i].y = static_cast<float>(rand()) / RAND_MAX;
            particles[i].z = static_cast<float>(rand()) / RAND_MAX;
            particles[i].vx = static_cast<float>(rand()) / RAND_MAX;
            particles[i].vy = static_cast<float>(rand()) / RAND_MAX;
            particles[i].vz = static_cast<float>(rand()) / RAND_MAX;
        }
    }

    // Broadcast particle data to all nodes
    MPI_Bcast(particles.data(), NUM_PARTICLES * sizeof(Particle), MPI_BYTE, 0, MPI_COMM_WORLD);

    // Allocate memory on GPU
    Particle* d_particles;
    float* d_forces;
    cudaMalloc(&d_particles, NUM_PARTICLES * sizeof(Particle));
    cudaMalloc(&d_forces, NUM_PARTICLES * sizeof(float));

    cudaMemcpy(d_particles, particles.data(), NUM_PARTICLES * sizeof(Particle), cudaMemcpyHostToDevice);

    // Launch the CUDA kernel
    compute_forces<<<(NUM_PARTICLES + 255) / 256, 256>>>(d_particles, d_forces, NUM_PARTICLES);

    cudaMemcpy(forces.data(), d_forces, NUM_PARTICLES * sizeof(float), cudaMemcpyDeviceToHost);

    // MPI reduce to sum forces across all nodes
    float total_force = 0.0f;
    MPI_Reduce(forces.data(), &total_force, NUM_PARTICLES, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "Total force: " << total_force << std::endl;
    }

    // Clean up
    cudaFree(d_particles);
    cudaFree(d_forces);

    MPI_Finalize();
    return 0;
}
