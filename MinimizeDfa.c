#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

// DFA structure definition
struct DFA {
    int numStates;
    int numSymbols;
    int transitions[100][100];
    set<int> acceptingStates;
};

// ANSI color codes for terminal output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

// Print the DFA details (states and transitions)
void printDFA(const DFA& dfa) {
    cout << "States:\n";
    for (int i = 0; i < dfa.numStates; ++i) {
        if (i == 0) {
            cout << CYAN << "Initial State: " << i << RESET << endl;
        } else if (dfa.acceptingStates.count(i)) {
            cout << GREEN << "Accepting State: " << i << RESET << endl;
        } else {
            cout << RED << "Rejected State: " << i << RESET << endl;
        }
    }

    cout << "\nTransitions:\n";
    for (int i = 0; i < dfa.numStates; ++i) {
        for (int j = 0; j < dfa.numSymbols; ++j) {
            cout << "  State " << i << " --[" << j << "]--> State " << dfa.transitions[i][j] << endl;
        }
    }
    cout << endl;
}

// Minimize the given DFA using partitioning method
DFA minimizeDFA(const DFA& dfa) {
    // Step 1: Initialize partitions (accepting vs non-accepting states)
    set<int> partitions[2];
    int stateGroup[100];

    for (int i = 0; i < dfa.numStates; ++i) {
        if (dfa.acceptingStates.count(i)) {
            partitions[1].insert(i);
            stateGroup[i] = 1;
        } else {
            partitions[0].insert(i);
            stateGroup[i] = 0;
        }
    }

    // Display initial partitioning
    cout << "Initial Partitions (Accepting vs Non-Accepting):\n";
    for (int i = 0; i < 2; ++i) {
        cout << "Partition " << i << ": ";
        for (int s : partitions[i]) {
            cout << s << " ";
        }
        cout << endl;
    }

    // Step 2: Refine partitions based on transition signatures
    bool updated = true;
    while (updated) {
        updated = false;
        set<int> newPartitions[100];
        int newStateGroup[100];
        int partitionCount = 0;

        for (int p = 0; p < 2; ++p) {
            map<string, set<int>> splitter;

            for (int state : partitions[p]) {
                string signature;
                for (int s = 0; s < dfa.numSymbols; ++s) {
                    signature += to_string(stateGroup[dfa.transitions[state][s]]) + ",";
                }
                splitter[signature].insert(state);
            }

            cout << "Splits for partition " << p << ":\n";
            for (const auto& part : splitter) {
                cout << "Signature: " << part.first << " -> ";
                for (int s : part.second) {
                    cout << s << " ";
                }
                cout << endl;
            }

            for (const auto& part : splitter) {
                for (int state : part.second) {
                    newPartitions[partitionCount].insert(state);
                    newStateGroup[state] = partitionCount;
                }
                partitionCount++;
            }
        }

        if (partitionCount != 2)
            updated = true;

        for (int i = 0; i < partitionCount; ++i) {
            partitions[i] = newPartitions[i];
        }
    }

    // Step 3: Build the minimized DFA from partitions
    DFA minDFA;
    minDFA.numStates = 0;
    minDFA.numSymbols = dfa.numSymbols;
    minDFA.acceptingStates.clear();

    for (int i = 0; i < 100; ++i) {
        if (partitions[i].empty()) continue;

        int rep = *partitions[i].begin();
        for (int s = 0; s < dfa.numSymbols; ++s) {
            minDFA.transitions[i][s] = stateGroup[dfa.transitions[rep][s]];
        }

        for (int state : partitions[i]) {
            if (dfa.acceptingStates.count(state)) {
                minDFA.acceptingStates.insert(i);
                break;
            }
        }
        minDFA.numStates++;
    }

    return minDFA;
}

// Main function
int main() {
    // Step 0: Define the DFA
    DFA dfa;
    dfa.numStates = 6;
    dfa.numSymbols = 2;

    // Define transitions
    dfa.transitions[0][0] = 1; dfa.transitions[0][1] = 0;
    dfa.transitions[1][0] = 2; dfa.transitions[1][1] = 3;
    dfa.transitions[2][0] = 4; dfa.transitions[2][1] = 5;
    dfa.transitions[3][0] = 2; dfa.transitions[3][1] = 3;
    dfa.transitions[4][0] = 5; dfa.transitions[4][1] = 4;
    dfa.transitions[5][0] = 5; dfa.transitions[5][1] = 0;

    // Define accepting states
    dfa.acceptingStates = {4, 5};

    // Print original DFA
    cout << "Original DFA:\n";
    printDFA(dfa);

    // Minimize and print minimized DFA
    DFA minDFA = minimizeDFA(dfa);
    cout << "Minimized DFA:\n";
    printDFA(minDFA);

    return 0;
}
