# Spring Workers – Producer Consumer Operating System Simulation 

---

## Project Description
This project is a simulation of a classic Operating Systems concept called the **Producer-Consumer Problem** using C and POSIX threads (pthreads).

It models a real-life scenario where multiple workers (pickers) collect fruits from a tree and place them into a shared crate, while another worker (loader) removes full crates and sends them to a truck.

---

## Features
- Multi-threading using `pthread`
- Synchronization using mutex and condition variables
- Simulation of shared buffer (crate)
- Producer-Consumer problem implementation
- Real-time console output of thread actions

---

## Concepts Used
- Multithreading
- Mutual Exclusion (Mutex)
- Condition Variables
- Shared Memory Synchronization
- Producer–Consumer Problem

---

## Roles in Simulation

### Pickers (Producers)
- Pick fruits from the tree
- Place them into the crate
- Wait when the crate is full

### Loader (Consumer)
- Waits until crate is full
- Loads crate into truck
- Empties crate for next cycle

---

## AI Assistance
This project was developed with the assistance of AI tools for guidance, debugging, and documentation support.

---

## How to Run

### Compile:
```bash
gcc program.c -o program -pthread
