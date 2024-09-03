#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack structure to hold operators and operands
typedef struct {
    int top;
    char items[MAX][MAX];
} Stack;

void push(Stack* s, char* item) {
    if (s->top < MAX - 1) {
        strcpy(s->items[++(s->top)], item);
    } else {
        printf("Stack overflow\n");
        exit(1);
    }
}

char* pop(Stack* s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    } else {
        printf("Stack underflow\n");
        exit(1);
    }
}

int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Function to generate intermediate code
void generate_intermediate_code(char* expression) {
    Stack operatorStack, operandStack;
    operatorStack.top = -1;
    operandStack.top = -1;
    char temp[MAX];
    int i = 0, j = 0, temp_var = 1;
    char result[MAX];

    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            temp[j++] = expression[i];
        } else if (expression[i] == '+' || expression[i] == '-' || 
                   expression[i] == '*' || expression[i] == '/') {
            temp[j] = '\0';
            if (j != 0) {
                push(&operandStack, temp);
                j = 0;
            }

            while (operatorStack.top != -1 && precedence(operatorStack.items[operatorStack.top][0]) >= precedence(expression[i])) {
                char operator = pop(&operatorStack)[0];
                char* op2 = pop(&operandStack);
                char* op1 = pop(&operandStack);
                sprintf(result, "t%d", temp_var++);
                printf("%s = %s %c %s\n", result, op1, operator, op2);
                push(&operandStack, result);
            }

            temp[0] = expression[i];
            temp[1] = '\0';
            push(&operatorStack, temp);
        }
        i++;
    }

    if (j != 0) {
        temp[j] = '\0';
        push(&operandStack, temp);
    }

    while (operatorStack.top != -1) {
        char operator = pop(&operatorStack)[0];
        char* op2 = pop(&operandStack);
        char* op1 = pop(&operandStack);
        sprintf(result, "t%d", temp_var++);
        printf("%s = %s %c %s\n", result, op1, operator, op2);
        push(&operandStack, result);
    }

    if (operandStack.top == 0) {
        printf("Result = %s\n", pop(&operandStack));
    } else {
        printf("Error in expression.\n");
    }
}

int main() {
    char expression[MAX];
    printf("Enter a simple arithmetic expression: ");
    scanf("%s", expression);

    generate_intermediate_code(expression);

    return 0;
}
