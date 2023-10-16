#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
const char *cKeywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

bool isCKeyword(const char *word) {
    int numKeywords = sizeof(cKeywords) / sizeof(cKeywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, cKeywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    FILE *inputFile;
    char inputFilename[100];
    char word[100];

    printf("Enter the input filename: ");
    scanf("%s", inputFilename);

    inputFile = fopen(inputFilename, "r");

    if (inputFile == NULL) {
        printf("File not found or unable to open.\n");
        return 1;
    }

    while (fscanf(inputFile, "%s", word) != EOF) {
        if (isCKeyword(word)) {
            // Convert the keyword to uppercase and print it
            for (int i = 0; word[i]; i++) {
                word[i] = toupper(word[i]);
            }
            printf("%s ", word);
        }
    }

    // Close the input file
    fclose(inputFile);

    return 0;
}

