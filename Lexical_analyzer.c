#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    PUNCTUATION,
    WHITESPACE,
    UNKNOWN
} TokenType;

const char *keywords[] = {"int", "return"};
const char *operators = "+-*/";
const char *punctuation = ";,()";

char keywordsList[100][100];
char identifiersList[100][100];
char numbersList[100][100];
char operatorsList[100][100];
char punctuationList[100][100];
int keywordCount = 0, identifierCount = 0, numberCount = 0, operatorCount = 0, punctuationCount = 0;

TokenType getTokenType(const char *token) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return KEYWORD;
        }
    }
    if (strchr(operators, token[0]) && strlen(token) == 1) {
        return OPERATOR;
    }
    if (strchr(punctuation, token[0]) && strlen(token) == 1) {
        return PUNCTUATION;
    }
    if (isdigit(token[0])) {
        for (int i = 1; i < strlen(token); i++) {
            if (!isdigit(token[i])) {
                return UNKNOWN;
            }
        }
        return NUMBER;
    }
    if (isalpha(token[0]) || token[0] == '_') {
        for (int i = 1; i < strlen(token); i++) {
            if (!isalnum(token[i]) && token[i] != '_') {
                return UNKNOWN;
            }
        }
        return IDENTIFIER;
    }
    return UNKNOWN;
}

void storeToken(TokenType type, const char *token) {
    switch (type) {
        case KEYWORD: strcpy(keywordsList[keywordCount++], token); break;
        case IDENTIFIER: strcpy(identifiersList[identifierCount++], token); break;
        case NUMBER: strcpy(numbersList[numberCount++], token); break;
        case OPERATOR: strcpy(operatorsList[operatorCount++], token); break;
        case PUNCTUATION: strcpy(punctuationList[punctuationCount++], token); break;
        default: break;
    }
}

void tokenize(const char *input) {
    int i = 0;
    while (input[i] != '\0') {
        if (isspace(input[i])) {
            i++;
            continue;
        }
        char token[100];
        int tokenLength = 0;
        
        if (isalpha(input[i]) || input[i] == '_') {
            while (isalnum(input[i]) || input[i] == '_') {
                token[tokenLength++] = input[i++];
            }
        } else if (isdigit(input[i])) {
            while (isdigit(input[i])) {
                token[tokenLength++] = input[i++];
            }
        } else if (strchr(operators, input[i])) {
            token[tokenLength++] = input[i++];
        } else if (strchr(punctuation, input[i])) {
            token[tokenLength++] = input[i++];
        } else {
            token[tokenLength++] = input[i++];
        }
        
        token[tokenLength] = '\0';
        TokenType type = getTokenType(token);
        storeToken(type, token);
    }
}

void printTokensInColumns() {
    printf("%-15s %-15s %-15s %-15s %-15s\n", "Keyword", "Identifier", "Number", "Operator", "Punctuation");
    int maxRows = keywordCount;
    if (identifierCount > maxRows) 
        maxRows = identifierCount;
    if (numberCount > maxRows) 
        maxRows = numberCount;
    if (operatorCount > maxRows) 
        maxRows = operatorCount;
    if (punctuationCount > maxRows) 
        maxRows = punctuationCount;

    for (int i = 0; i < maxRows; i++) {
        if (i < keywordCount) printf("%-15s ", keywordsList[i]); 
        else printf("%-15s ", "");
        if (i < identifierCount) printf("%-15s ", identifiersList[i]); 
        else printf("%-15s ", "");
        if (i < numberCount) printf("%-15s ", numbersList[i]); 
        else printf("%-15s ", "");
        if (i < operatorCount) printf("%-15s ", operatorsList[i]); 
        else printf("%-15s ", "");
        if (i < punctuationCount) printf("%-15s ", punctuationList[i]); 
        else printf("%-15s ", "");
        printf("\n");
    }
}

int main() {
    
    char input[1000];
    printf("Enter the input: ");
    fgets(input, 1000, stdin);
    input[strcspn(input, "\n")] = '\0';
    printf("Input program: %s\n", input);
    tokenize(input);
    printTokensInColumns();
    
    return 0;
}
