# High Performance Computing

A structured course repository covering the theory and practice of High Performance Computing — from low-level code optimization and sparse linear algebra to shared-memory parallelism (OpenMP), distributed-memory parallelism (MPI), and GPU programming (CUDA). Every module pairs reference material with working C/C++ implementations and applied scientific computing projects.

---

## Curriculum

| # | Module | Key Topics |
|---|--------|-----------|
| 1 | [Introduction](1.Introduccion/) | HPC history, supercomputer architectures, performance metrics |
| 2 | [Code Optimization](2.Optimizacion/) | Memory layout, cache effects, compiler flags (`-O0`/`-O2`/`-O3`), Makefiles |
| 3 | [Sparse Matrices](3.Matrices_Dispersas/) | CSR/COO storage formats, `.mat` I/O, benchmarking optimization levels |
| 4 | [Conjugate Gradient](4.Gradiente_Conjugado/) | Iterative solvers, dot-product implementations, parallel quiz |
| 5 | [Parallel Architectures](5.Arquitecturas_Paralelas/) | Flynn's taxonomy, memory models, first OpenMP contact, Midterm 1 |
| 6 | [OpenMP](6.OpenMP/) | Thread management, synchronization primitives, tasks, scheduling, Poisson 2D |
| 7 | [MPI](7.MPI/) | Point-to-point, collective operations, domain decomposition, Midterm 2 |
| 8 | [CUDA](8.CUDA/) | GPU architecture, kernel programming, shared memory, throughput benchmarks |
| 9 | [Final Project](9.FINALE/) | SVM classifier from scratch in C++ — serial vs. OpenMP parallel |

---

## Applied Projects

### Midterm 1 — Driven Harmonic Oscillator
`5.Arquitecturas_Paralelas/Parcial1/`

Numerical simulation of a damped oscillator under an external periodic force. Sweeps over multiple damping coefficients (γ = 0, 1, 2), exports timestep data to CSV, and generates phase-space plots with Python/Matplotlib.

**Stack:** C++, Python (Matplotlib)

---

### Electric Particle Simulation
`2.Optimizacion/Electrico/ParticleSimulation/`

Object-oriented N-body Coulomb simulation with a custom `Particle` class. Demonstrates the impact of memory access patterns and compiler optimization on runtime.

**Stack:** C++, Makefile

---

### Poisson 2D Solver — OpenMP Parallel Study
`6.OpenMP/Poisson/Taller_OpenMP_Poisson/`

Finite difference solver for the 2D Poisson equation, implemented in eight parallel variants and benchmarked against the serial baseline:

| Variant | OpenMP Construct |
|---------|-----------------|
| `poisson_serial.cpp` | Baseline |
| `poisson_parallel_for.cpp` | `#pragma omp parallel for` |
| `poisson_collapse.cpp` | `collapse(2)` |
| `poisson_schedule_static.cpp` | `schedule(static)` |
| `poisson_schedule_dynamic.cpp` | `schedule(dynamic)` |
| `poisson_sections.cpp` | `sections` |
| `poisson_atomic.cpp` | `atomic` |
| `poisson_critical.cpp` | `critical` |
| `poisson_task.cpp` | `task` |

**Stack:** C++, OpenMP, Python (result plotting)

---

### Midterm 2 — Advection-Diffusion & Electromagnetics with MPI
`7.MPI/Parcial2/`

**Lattice Boltzmann Method (LBM) — Fluid Dynamics**
Serial, OpenMP, and MPI implementations of LBM for 2D and 3D advection-diffusion problems with gas/solid thermal coupling on a 100×100 grid over 10,000 timesteps.

**FDTD — Electromagnetic Wave Propagation**
Finite Difference Time Domain (FDTD) solver for 1D/2D electromagnetic field evolution. Simulates `E` and `H` fields with physical constants (ε₀, μ₀, c), outputting field snapshots at each timestep. Progresses from serial to OpenMP to MPI domain decomposition.

**Stack:** C++, MPI, OpenMP, Python/Jupyter (visualization)

---

### Final Project — Parallel SVM Classifier
`9.FINALE/`

A Support Vector Machine classifier built from scratch in C++, trained with stochastic gradient descent. Implements L2 regularization, configurable learning rate, and epoch-level progress reporting. The serial implementation is replicated with an OpenMP parallel training loop and benchmarked on a real dataset.

```
src/
├── SVM.cpp / SVM.h          # SVM model (weights, bias, SGD training, L2 regularization)
├── Punto.cpp / Punto.h      # Feature-vector data point abstraction
└── Datos.cpp / Datos.h      # Dataset loader

src_omp/
└── SVMomp.cpp / SVMomp.h   # OpenMP-parallelized training loop
```

**Stack:** C++, OpenMP, Jupyter (performance analysis)

---

## Prerequisites

| Tool | Purpose |
|------|---------|
| `g++` ≥ 11 | C++ compilation |
| `gcc` | C compilation |
| OpenMP | Shared-memory parallelism (bundled with GCC) |
| OpenMPI or MPICH | Distributed-memory parallelism |
| NVIDIA CUDA Toolkit | GPU compilation via `nvcc` |
| `make` | Build automation |
| Python 3 + Matplotlib | Result plotting and visualization |

---

## Quick Start

**Serial C++**
```bash
g++ -O2 -o out file.cpp && ./out
```

**OpenMP**
```bash
g++ -O2 -fopenmp -o out file.cpp
OMP_NUM_THREADS=4 ./out
```

**MPI**
```bash
mpicxx -O2 -o out file.cpp
mpirun -np 4 ./out
```

**CUDA**
```bash
nvcc -O2 -o out kernel.cu && ./out
```

**Makefile** (where available)
```bash
make        # build default target
make clean  # remove binaries
```

---

## Repository Structure

```
HPC-High-Performance-Computing/
├── 1.Introduccion/              # Slides and reference PDFs
├── 2.Optimizacion/              # Memory/cache optimization + particle simulation
│   ├── Codigos_1/               #   Vectors, pointers, iteration ordering
│   ├── Codigos_2/ & 3/          #   Custom Vector class, memory benchmarks
│   ├── Ejemplo_make/            #   Makefile tutorial project
│   └── Electrico/               #   N-body Coulomb particle simulation
├── 3.Matrices_Dispersas/        # Sparse matrix I/O and optimization benchmarks
├── 4.Gradiente_Conjugado/       # Iterative solver implementations
├── 5.Arquitecturas_Paralelas/   # Parallel architecture intro + Midterm 1
│   └── Parcial1/                #   Driven harmonic oscillator simulation
├── 6.OpenMP/                    # OpenMP from hello-world to advanced task parallelism
│   ├── Codigos_1/ to 4/         #   Progressive examples (shared, private, reduction, tasks)
│   ├── Poisson/                 #   2D PDE solver — 9 parallelization strategies
│   └── Task/                    #   Task-based parallelism patterns
├── 7.MPI/                       # MPI fundamentals to domain decomposition
│   ├── Curso_1/                 #   Point-to-point: blocking and non-blocking
│   ├── Curso_2/                 #   Collectives, matrix multiplication, Game of Life
│   └── Parcial2/                #   LBM fluid dynamics + FDTD electromagnetics
├── 8.CUDA/                      # GPU programming fundamentals
│   └── Workshop/                #   CUDA vs serial vector-sum throughput benchmark
└── 9.FINALE/                    # Final project: SVM classifier — serial and parallel
    ├── src/                     #   Serial C++ implementation
    └── src_omp/                 #   OpenMP parallel implementation
```

---

## License

This repository is for educational purposes. All code is original coursework unless otherwise noted in individual files.
