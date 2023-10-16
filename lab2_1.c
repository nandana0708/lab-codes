//Program to remove single and multiline comments from a given ‘C’ file.

#include <stdio.h>
#include <stdbool.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFilename[100], outputFilename[100];
    char ch, nextChar;
    bool inSingleLineComment = false, inMultiLineComment = false;

    printf("Enter the input filename: ");
    scanf("%s", inputFilename);

    inputFile = fopen(inputFilename, "r");

    if (inputFile == NULL) {
        printf("File not found or unable to open.\n");
        return 1;
    }

    printf("Enter the output filename: ");
    scanf("%s", outputFilename);

    outputFile = fopen(outputFilename, "w");

    if (outputFile == NULL) {
        printf("Unable to create the output file.\n");
        fclose(inputFile);
        return 1;
    }

    while ((ch = fgetc(inputFile)) != EOF) {
        if (!inSingleLineComment && !inMultiLineComment) {
            if (ch == '/') {
                nextChar = fgetc(inputFile);
                if (nextChar == '/') {
                    inSingleLineComment = true;
                    continue;
                } else if (nextChar == '*') {
                    inMultiLineComment = true;
                    continue;
                } else {
                    fputc(ch, outputFile);
                    fputc(nextChar, outputFile);
                }
            } else {
                fputc(ch, outputFile);
            }
        } else if (inSingleLineComment) {
            if (ch == '\n') {
                inSingleLineComment = false;
                fputc(ch, outputFile);
            }
        } else if (inMultiLineComment) {
            if (ch == '*') {
                nextChar = fgetc(inputFile);
                if (nextChar == '/') {
                    inMultiLineComment = false;
                }
            }
        }
    }

    // Close both files
    fclose(inputFile);
    fclose(outputFile);

    printf("Comments removed and saved in '%s'.\n", outputFilename);

    return 0;
}

