#include <stdio.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFilename[100], outputFilename[100];
    char ch;

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
        if (ch == ' ' || ch == '\t') {
            // Replace spaces and tabs with a single space
            fputc(' ', outputFile);
            while ((ch = fgetc(inputFile)) == ' ' || ch == '\t') {
                // Consume consecutive spaces and tabs
          }
        }
        fputc(ch, outputFile); //other chars
    }

    // Close both files
    fclose(inputFile);
    fclose(outputFile);

    printf("Spaces and tabs replaced and saved in '%s'.\n", outputFilename);

    return 0;
}

