#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_RULES 20
#define MAX_LEN 100
typedef struct {
    char left;
    char right[MAX_RULES][MAX_LEN];
    int num_right;
} Production;
Production productions[MAX_RULES];
int num_productions = 0;
char non_terminals[MAX_RULES];
int num_non_terminals = 0;
char first[26][MAX_LEN];
char follow[26][MAX_LEN];
void add_to_set(char *set, char ch) {
    if (strchr(set, ch) == NULL) {
        int len = strlen(set);
        set[len] = ch;
        set[len + 1] = '\0';
    }
}
bool is_non_terminal(char c) {
    return (c >= 'A' && c <= 'Z');
}
void compute_first(char symbol) {
    int index = symbol - 'A';
    for (int i = 0; i < num_productions; i++) {
        if (productions[i].left == symbol) {
            for (int j = 0; j < productions[i].num_right; j++) {
                char *rhs = productions[i].right[j];
                if (strcmp(rhs, "E") == 0) {
                    add_to_set(first[index], 'E');
                    continue;
                }
                for (int k = 0; rhs[k] != '\0'; k++) {
                    if (!is_non_terminal(rhs[k])) {
                        add_to_set(first[index], rhs[k]);
                        break;
                    } else {
                        int next_index = rhs[k] - 'A';
                        if (strlen(first[next_index]) == 0) {
                            compute_first(rhs[k]);
                        } 
                        for (int m=0; first[next_index][m]; m++)
                        {
                            if (first[next_index][m] != 'E') {
                                add_to_set(first[index], first[next_index][m]);
                            }
                        } if (strchr(first[next_index], 'E') == NULL) {
                            break;
                        } if (k== strlen(rhs)-1) {
                            add_to_set(first[index], 'E');
                        }
                    }
                }
            }
        }
    }
}
void compute_follow(char symbol) {
    int index = symbol - 'A';
    if (symbol == productions[0].left) {
    add_to_set(follow[index], '$');
    }
    for (int i = 0; i < num_productions; i++) {
        for (int j = 0; j < productions[i].num_right; j++) {
            char *rhs = productions[i].right[j];
            for (int k = 0; rhs[k] != '\0'; k++) {
                if (rhs[k] == symbol) {
                    if (rhs[k + 1] == '\0') {
                    int left_index = productions[i].left - 'A';
                    for (int m = 0; follow[left_index][m]; m++) {
                    add_to_set(follow[index], follow[left_index][m]);
                    }
                    } else {
                        for (int m = k + 1; rhs[m] != '\0'; m++) {
                            if (!is_non_terminal(rhs[m])) {
                            add_to_set(follow[index], rhs[m]);
                            break;
                            } else {
                                int next_index = rhs[m] - 'A';
                                for (int n = 0; first[next_index][n]; n++) {
                                    if (first[next_index][n] != 'E') {
                                        add_to_set(follow[index], first[next_index][n]);
                                    }
                                } 
                                if (strchr(first[next_index], 'E') == NULL) {
                                    break;
                                } 
                                if (rhs[m+1] == '\0') {
                                    int left_index = productions[i].left - 'A';
                                    for (int n = 0; follow[left_index][n]; n++) {
                                        add_to_set(follow[index], follow[left_index][n]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void print_set(const char *set) {
    bool first_item = true;
    for (int i = 0; set[i]; i++) {
        if (!first_item) printf(", ");
        first_item = false;
        if (set[i] == 'E') {
            printf("Є");
        } else {
            printf("%c", set[i]);
        }
    }
    if (strlen(set) == 0) {
        printf("empty");
    }
}
int main() {
    printf("Enter productions (end with empty line):\n");
    printf("Format: S -> ACB|Cbb|Ba\n");
    char input[MAX_LEN];
    while (fgets(input, sizeof(input), stdin) && input[0] != '\n') {
        input[strcspn(input, "\n")] = 0;
        productions[num_productions].left = input[0];
        non_terminals[num_non_terminals++] = input[0];
        char *rhs = strstr(input, "->") + 2;
        while (*rhs == ' ') rhs++;
        char *alt = strtok(rhs, "|");
        while (alt) {
        while (*alt == ' ') alt++;
        strcpy(productions[num_productions].right[productions[num_productions].num_right++],
        alt);
        alt = strtok(NULL, "|");
        }
        num_productions++;
    }
    for (int i = 0; i < 26; i++) {
        first[i][0] = '\0';
        follow[i][0] = '\0';
    }
    for (int i = 0; i < num_non_terminals; i++) {
        compute_first(non_terminals[i]);
    }
    for (int i = 0; i < num_non_terminals; i++) {
        compute_follow(non_terminals[i]);
    }
    for (int pass = 0; pass < num_non_terminals; pass++) {
        for (int i = 0; i < num_non_terminals; i++) {
            compute_follow(non_terminals[i]);
        }
    }
    printf("\nFIRST sets:\n");
    for (int i = 0; i < num_non_terminals; i++) {
        printf("FIRST(%c) = { ", non_terminals[i]);
        print_set(first[non_terminals[i] - 'A']);
        printf(" }\n");
    }
    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < num_non_terminals; i++) {
        printf("FOLLOW(%c) = { ", non_terminals[i]);
        print_set(follow[non_terminals[i] - 'A']);
        printf(" }\n");
    }
    return 0;
}
/*OUTPUT
Enter productions (end with empty line):
Format: S -> ACB|Cbb|Ba
S->ACB|Cbb|Ba
A->da|BC
B->g|E
C->h|E


FIRST sets:
FIRST(S) = { d, g, h, Є, b, a }
FIRST(A) = { d, g, h, Є }
FIRST(B) = { g, Є }
FIRST(C) = { h, Є }

FOLLOW sets:
FOLLOW(S) = { $ }
FOLLOW(A) = { h, g, $ }
FOLLOW(B) = { $, a, h, g }
FOLLOW(C) = { g, $, b, h }
*/