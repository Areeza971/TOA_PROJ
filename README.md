# TOA_PROJ


# DFA Minimization - TOA Project

This project implements DFA (Deterministic Finite Automaton) minimization in C++ using the partitioning method. The code identifies and merges equivalent states to produce a minimized DFA that accepts the same language as the original.

🛠️ Key Features
✅ Partition-Based Minimization Algorithm
Initially separates accepting and non-accepting states into partitions, then iteratively refines these groups based on transition behavior until no further splits are possible.

🔍 Detailed Partition Debugging
The code displays how states are split during each refinement step using transition signatures, aiding understanding of the minimization process.

🔧 Hardcoded Sample DFA
Demonstrates minimization on a built-in DFA with 6 states and 2 input symbols.

📄 File Description
main.cpp:
Contains the full implementation of:

DFA structure and transition representation

Partition refinement-based minimization

Sample DFA and test case

