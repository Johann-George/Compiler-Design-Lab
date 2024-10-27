#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAX_STATES 100
#define MAX_INPUTS 2
#define MAX_TRANSITIONS 10000
int dfa[MAX_STATES][MAX_INPUTS][MAX_STATES] = {0};
int go[MAX_TRANSITIONS][MAX_INPUTS] = {0};
int state_set[MAX_TRANSITIONS] = {0};
int arr[MAX_TRANSITIONS] = {0};
int final_states[MAX_STATES] = {0};
char input_string[1000];
int find_next_states(int nfa_state, int input_symbol, int num_states) {
    int combined_states = 0;
    for (int i = 0; i < num_states; i++) {
        if (dfa[nfa_state][input_symbol][i] == 1) {
            combined_states |= (1 << i);
        }
    } 
    return combined_states;
}
int main() {
    int num_states, num_final_states, num_transitions;
    int i, j, curr_state, next_state, state_index = 0, stf, flag, current_dfa_state;
    int initial_state, final_state_count, temp_state;
    int from_state, input_symbol, to_state;
    printf("\nEnter the number of NFA states: ");
    scanf("%d", &num_states);
    printf("\nInitializing states...\n");
    for (i = 0; i < num_states; i++) {
        state_set[(int)pow(2, i)] = 1;
    }
    printf("\nEnter the number of final states in NFA: ");
    scanf("%d", &num_final_states);
    printf("\nEnter the final state numbers: ");
    for (i = 0; i < num_final_states; i++) {
        scanf("%d", &final_states[i]);
    }
    printf("\nEnter the number of transitions in NFA: ");
    scanf("%d", &num_transitions);
    printf("\nEnter transitions as: from_state input_symbol to_state\n");
    for (i = 0; i < num_transitions; i++) {
        scanf("%d%d%d", &from_state, &input_symbol, &to_state);
        if (input_symbol == 0) {
            dfa[from_state][0][to_state] = 1;
        } else {
            dfa[from_state][1][to_state] = 1;
        }
    }
    printf("\nEnter the initial state of NFA: ");
    scanf("%d", &initial_state);
    initial_state = (1 << initial_state);
    printf("\nStarting DFA construction...\n");
    printf("\n%-10s%-10s%-15s\n", "State", "Input", "Next State");
    for (curr_state = 0; curr_state < (1 << num_states); curr_state++) {
        if (!state_set[curr_state]) continue;
        for (input_symbol = 0; input_symbol < MAX_INPUTS; input_symbol++) {
            stf = 0;
            for (i = 0; i < num_states; i++) {
                if (curr_state & (1 << i)) {
                    stf |= find_next_states(i, input_symbol, num_states);
                }
            } if (
            stf && !
            state_set[stf]) {
                arr[state_index++] = stf;
                state_set[stf] = 1;
            }
            go[curr_state][input_symbol] = stf;
            printf("%-10d%-10d%-15d\n", curr_state, input_symbol, stf);
        }
    }
    printf("\nEnter strings to check DFA acceptance (type 'exit' to stop):\n");
    while (1) {
        printf("\nEnter string: ");
        scanf("%s", input_string);
        if (strcmp(input_string, "exit") == 0) break;
        int len = strlen(input_string);
        current_dfa_state = initial_state;
        flag = 0;
        printf("\nProcessing string, following transitions...\n");
        printf("Initial state: %d\n", current_dfa_state);
        for (i = 0; i < len; i++) {
            current_dfa_state = go[current_dfa_state][input_string[i] - '0'];
            printf("%d -> ", current_dfa_state);
        }
        printf("\nFinal state: %d\n", current_dfa_state);
        for (i = 0; i < num_final_states; i++) {
            if (current_dfa_state & (1 << final_states[i])) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            printf("String Accepted\n");
        } 
        else {
            printf("String Rejected\n");
        }
    }
    return 0;
}