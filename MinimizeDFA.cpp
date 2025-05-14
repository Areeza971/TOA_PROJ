#include <iostream>
using namespace std;

const int MAX_STATES = 10;
const int MAX_ALPHABETS = 5;

int states, alphabets;
char alpha[MAX_ALPHABETS];
char stateList[MAX_STATES];
char transition[MAX_STATES][MAX_ALPHABETS];
int isFinal[MAX_STATES];
char initialState;

// Helper to find index of a state
int getStateIndex(char state) {
    for (int i = 0; i < states; i++) {
        if (stateList[i] == state)
            return i;
    }
    return -1;
}

// Check if two states are distinguishable
void minimizeDFA() {
    bool distinguishable[MAX_STATES][MAX_STATES] = {false};

    // Step 1: Mark pairs where one is final and the other is not
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < i; j++) {
            if (isFinal[i] != isFinal[j]) {
                distinguishable[i][j] = true;
            }
        }
    }

    // Step 2: Iteratively mark distinguishable pairs
    bool updated;
    do {
        updated = false;
        for (int i = 0; i < states; i++) {
            for (int j = 0; j < i; j++) {
                if (distinguishable[i][j])
                    continue;
                for (int k = 0; k < alphabets; k++) {
                    int iNext = getStateIndex(transition[i][k]);
                    int jNext = getStateIndex(transition[j][k]);

                    if (iNext == -1 || jNext == -1)
                        continue;

                    if (iNext == jNext)
                        continue;

                    int a = max(iNext, jNext);
                    int b = min(iNext, jNext);
                    if (distinguishable[a][b]) {
                        distinguishable[i][j] = true;
                        updated = true;
                        break;
                    }
                }
            }
        }
    } while (updated);

    // Step 3: Print equivalent state groups
    bool printed[MAX_STATES] = {false};

    cout << "\nEquivalent States (Minimized Groups):\n";
    for (int i = 0; i < states; i++) {
        if (printed[i]) continue;
        cout << "{ " << stateList[i];
        for (int j = 0; j < states; j++) {
            if (i != j && !distinguishable[max(i, j)][min(i, j)]) {
                cout << ", " << stateList[j];
                printed[j] = true;
            }
        }
        printed[i] = true;
        cout << " }\n";
    }
}

int main() {
    cout << "Enter number of states: ";
    cin >> states;

    cout << "Enter number of alphabets: ";
    cin >> alphabets;

    for (int i = 0; i < alphabets; i++) {
        cout << "Enter alphabet " << i + 1 << ": ";
        cin >> alpha[i];
    }

    for (int i = 0; i < states; i++) {
        if (i == 0) {
            cout << "Enter initial state (A-Z): ";
            cin >> stateList[i];
            initialState = stateList[i];
        } else {
            cout << "Enter state (A-Z): ";
            cin >> stateList[i];
        }

        cout << "Is this a Final state? (1 = yes, 0 = no): ";
        cin >> isFinal[i];

        for (int j = 0; j < alphabets; j++) {
            cout << "Transition for " << stateList[i] << " on " << alpha[j] << ": ";
            cin >> transition[i][j];
        }
    }
    
   
    minimizeDFA();

    return 0;
}
