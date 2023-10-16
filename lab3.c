#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 100

enum TokenType {
    OPERATOR,
    SPECIAL_SYMBOL,
    KEYWORD,
    NUMERIC_CONSTANT,
    STRING_LITERAL,
    IDENTIFIER
};

struct Token {
    int row;
    int column;
    enum TokenType type;
    char lexeme[MAX_TOKEN_LEN];
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '<' || c == '>';
}

bool isSpecialSymbol(char c) {
    return c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']';
}

bool isKeyword(char *word) {
    // List of some C keywords (you can add more)
    const char *keywords[] = {"int", "if", "else", "while", "for", "return", "void"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return true;
        }
    }

    return false;
}

bool isNumericConstant(char *word) {
    // Check if the word is a numeric constant (you can add more checks for different numeric formats)
    for (int i = 0; i < strlen(word); i++) {
        if (!isdigit(word[i])) {
            return false;
        }
    }
    return true;
}

bool isStringLiteral(char *word) {
    // Check if the word is a string literal (simplified check)
    return word[0] == '"' && word[strlen(word) - 1] == '"';
}

bool isIdentifier(char *word) {
    // Check if the word is an identifier (simplified check)
    return isalpha(word[0]) || word[0] == '_';
}

void getNextToken(FILE *inputFile, struct Token *token) {
    char c;
    char buffer[MAX_TOKEN_LEN];
    int bufferPos = 0;
    bool insideComment = false;
    int row = 1, col = 1;

    while ((c = fgetc(inputFile)) != EOF) {
        if (c == '\n') {
            row++;
            col = 1;
        } else {
            col++;
        }

        if (insideComment) {
            if (c == '*' && fgetc(inputFile) == '/') {
                insideComment = false;
            }
        } else {
            if (c == '/' && fgetc(inputFile) == '*') {
                insideComment = true;
            } else if (isOperator(c)) {
                if (bufferPos > 0) {
                    buffer[bufferPos] = '\0';
                    strcpy(token->lexeme, buffer);

                    if (isKeyword(buffer)) {
                        token->type = KEYWORD;
                    } else if (isNumericConstant(buffer)) {
                        token->type = NUMERIC_CONSTANT;
                    } else if (isStringLiteral(buffer)) {
                        token->type = STRING_LITERAL;
                    } else if (isIdentifier(buffer)) {
                        token->type = IDENTIFIER;
                    } else {
                        token->type = SPECIAL_SYMBOL;
                    }

                    token->row = row;
                    token->column = col - bufferPos;

                    fseek(inputFile, -1, SEEK_CUR); // Move the file pointer back by one character
                    return;
                }
                buffer[0] = c;
                buffer[1] = '\0';
                strcpy(token->lexeme, buffer);
                token->type = OPERATOR;
                token->row = row;
                token->column = col;
                return;
            } else if (isSpecialSymbol(c)) {
                if (bufferPos > 0) {
                    buffer[bufferPos] = '\0';
                    strcpy(token->lexeme, buffer);

                    if (isKeyword(buffer)) {
                        token->type = KEYWORD;
                    } else if (isNumericConstant(buffer)) {
                        token->type = NUMERIC_CONSTANT;
                    } else if (isStringLiteral(buffer)) {
                        token->type = STRING_LITERAL;
                    } else if (isIdentifier(buffer)) {
                        token->type = IDENTIFIER;
                    } else {
                        token->type = SPECIAL_SYMBOL;
                    }

                    token->row = row;
                    token->column = col - bufferPos;

                    fseek(inputFile, -1, SEEK_CUR); // Move the file pointer back by one character
                    return;
                }
                buffer[0] = c;
                buffer[1] = '\0';
                strcpy(token->lexeme, buffer);
                token->type = SPECIAL_SYMBOL;
                token->row = row;
                token->column = col;
                return;
            } else if (isalnum(c) || c == '_' || c == '"') {
                buffer[bufferPos++] = c;
            } else if (bufferPos > 0) {
                buffer[bufferPos] = '\0';
                strcpy(token->lexeme, buffer);

                if (isKeyword(buffer)) {
                    token->type = KEYWORD;
                } else if (isNumericConstant(buffer)) {
                    token->type = NUMERIC_CONSTANT;
                } else if (isStringLiteral(buffer)) {
                    token->type = STRING_LITERAL;
                } else if (isIdentifier(buffer)) {
                    token->type = IDENTIFIER;
                } else {
                    token->type = SPECIAL_SYMBOL;
                }

                token->row = row;
                token->column = col - bufferPos;

                fseek(inputFile, -1, SEEK_CUR); // Move the file pointer back by one character
                return;
            }
        }
    }

    // End of file reached
    token->type = -1; // No more tokens
}

int main() {
    FILE *inputFile;
    char inputFilename[100];
    struct Token token;

    printf("Enter the input filename: ");
    scanf("%s", inputFilename);

    inputFile = fopen(inputFilename, "r");

    if (inputFile == NULL) {
        printf("File not found or unable to open.\n");
        return 1;
    }

    while (true) {
        getNextToken(inputFile, &token);

        if (token.type == -1) {
            break; // No more tokens
        }

        printf("Row: %d, Column: %d, Token Type: %d, Lexeme: %s\n", token.row, token.column, token.type, token.lexeme);
    }

    // Close the input file
    fclose(inputFile);

    return 0;
}


