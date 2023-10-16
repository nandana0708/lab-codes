#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TableLength 30

enum tokenType {
    EOFILE = -1,
    LESS_THAN,
    LESS_THAN_OR_EQUAL,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL,
    EQUAL,
    NOT_EQUAL
};

struct token {
    char *lexeme;
    int index;
    unsigned int rowno, colno; // row number, column number.
    enum tokenType type;
};

struct ListElement {
    struct token tok;
    struct ListElement *next;
};

struct ListElement *TABLE[TableLength];

void Initialize() {
    for (int i = 0; i < TableLength; i++) {
        TABLE[i] = NULL;
    }
}

void Display() {
    for (int i = 0; i < TableLength; i++) {
        struct ListElement *current = TABLE[i];
        while (current != NULL) {
            printf("Index %d: Lexeme: %s, Index: %d, Type: %d\n", i, current->tok.lexeme, current->tok.index, current->tok.type);
            current = current->next;
        }
    }
}

int HASH(char *str) {
    // Develop an OpenHash function on a string.
    int sum = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        sum += (int)str[i];
    }
    return sum % TableLength;
}

int SEARCH(char *str) {
    // Write a search routine to check whether a lexeme exists in the Symbol table.
    // Returns 1 if the lexeme is found, else returns 0.
    int val = HASH(str);
    struct ListElement *current = TABLE[val];

    while (current != NULL) {
        if (strcmp(current->tok.lexeme, str) == 0) {
            return 1; // Lexeme found
        }
        current = current->next;
    }

    return 0; // Lexeme not found
}

void INSERT(struct token tk) {
    if (SEARCH(tk.lexeme) == 1) {
        return; // Before inserting, we check if the element is already present.
    }

    int val = HASH(tk.lexeme);
    struct ListElement *cur = (struct ListElement *)malloc(sizeof(struct ListElement));
    cur->tok = tk;
    cur->next = NULL;

    if (TABLE[val] == NULL) {
        TABLE[val] = cur; // No collision.
    } else {
        struct ListElement *ele = TABLE[val];
        while (ele->next != NULL) {
            ele = ele->next; // Add the element at the end in the case of a collision.
        }
        ele->next = cur;
    }
}

int main() {
    // Initialize the symbol table
    Initialize();

    // Sample token
    struct token sample_token;
    sample_token.lexeme = "example";
    sample_token.index = 1;
    sample_token.rowno = 2;
    sample_token.colno = 3;
    sample_token.type = LESS_THAN;

    // Insert the sample token
    INSERT(sample_token);

    // Display the symbol table
    Display();

    return 0;
}

