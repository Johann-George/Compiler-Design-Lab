#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const char *input;
int pos = 0;


bool S();
bool L();
bool L_prime();

bool match(char expected) {
    if (input[pos] == expected) {
        pos++;
        return true;
    }
    return false;
}

bool S() {
    if (match('(')) {
        if (L() && match(')')) {
            return true;
        }
        return false;
    } else if (match('a')) {
        return true;
    }
    return false;
}

bool L() {
    if (S()) {
        return L_prime();
    }
    return false;
}

bool L_prime() {
    if (match(',')) {
        if (S()) {
            return L_prime();
        }
        return false;
    }
    
    return true;
}

bool parse(const char *str) {
    input = str;
    pos = 0;
    if (S() && input[pos] == '\0') {
        return true;
    }
    return false;
}

int main() {
    
    char test1[100];
    char test2[100];
    printf("Enter first input:");
    fgets(test1,100,stdin);
    test1[strcspn(test1, "\n")] = '\0';

    printf("Enter second input:");
    fgets(test2,100,stdin);
    test2[strcspn(test2, "\n")] = '\0';
    
    printf("Input 1: %s\n", parse(test1) ? "String is accepted" : "String is not accepted");
    printf("Input 2: %s\n", parse(test2) ? "String is accepted" : "String is not accepted");

    return 0;
}
