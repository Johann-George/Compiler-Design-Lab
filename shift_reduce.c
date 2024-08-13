#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK 100
#define MAX_INPUT 100

typedef enum
{
    NUM,
    PLUS,
    MULT,
    END
} TokenType;

typedef struct
{
    TokenType type;
    int value;
} Token;

Token stack[MAX_STACK];
int top = -1;
Token input[MAX_INPUT];
int current = 0;

void print_token(Token t)
{
    switch (t.type)
    {
    case NUM:
        printf("%d", t.value);
        break;
    case PLUS:
        printf("+");
        break;
    case MULT:
        printf("*");
        break;
    case END:
        printf("$");
        break;
    }
}

void print_stack()
{
    printf("Stack: ");
    for (int i = 0; i <= top; i++)
    {
        print_token(stack[i]);
        printf(" ");
    }
    printf("\n");
}

void print_input()
{
    printf("Input: ");
    for (int i = current; input[i].type != END; i++)
    {
        print_token(input[i]);
        printf(" ");
    }
    printf("$\n");
}

void shift()
{
    stack[++top] = input[current++];
    printf("Shift: ");
    print_token(stack[top]);
    printf("\n");
}

int reduce()
{
    if (top >= 2 && stack[top].type == NUM && stack[top - 1].type == PLUS && stack[top - 2].type == NUM)
    {
        printf("Reduce: E -> E + E\n");
        stack[top - 2].value += stack[top].value;
        top -= 2;
        return 1;
    }
    else if (top >= 2 && stack[top].type == NUM && stack[top - 1].type == MULT && stack[top - 2].type == NUM)
    {
        printf("Reduce: E -> E * E\n");
        stack[top - 2].value *= stack[top].value;
        top -= 2;
        return 1;
    }
    return 0;
}

void parse()
{
    printf("Parsing process:\n");
    while (input[current].type != END || top > 0)
    {
        print_stack();
        print_input();

        if (input[current].type == END && top == 0)
        {
            break;
        }

        if (top == -1 || input[current].type == NUM ||
            (input[current].type == MULT && stack[top].type != MULT) ||
            (input[current].type == PLUS && stack[top].type == NUM))
        {
            shift();
        }
        else if (!reduce())
        {
            printf("Error: Invalid expression\n");
            return;
        }

        printf("\n");
    }
    printf("Parsing complete.\n");
    if (top == 0 && stack[0].type == NUM)
    {
        printf("Result: %d\n", stack[0].value);
    }
    else
    {
        printf("Error: Invalid expression\n");
    }
}

void lexer(char *expr)
{
    int i = 0;
    int j = 0;
    while (expr[i] != '\0')
    {
        if (isdigit(expr[i]))
        {
            input[j].type = NUM;
            input[j].value = expr[i] - '0';
            j++;
        }
        else if (expr[i] == '+')
        {
            input[j].type = PLUS;
            j++;
        }
        else if (expr[i] == '*')
        {
            input[j].type = MULT;
            j++;
        }
        i++;
    }
    input[j].type = END;
}

int main()
{
    char expr[MAX_INPUT];
    printf("Enter an arithmetic expression: ");
    fgets(expr, MAX_INPUT, stdin);
    expr[strcspn(expr, "\n")] = 0;

    lexer(expr);
    parse();

    return 0;
}

