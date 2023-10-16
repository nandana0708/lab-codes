//reverse the file contents and store in another file
//display the size of file 

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char inputFilename[100], outputFilename[100];
    char ch;
    long fileSize = 0;

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

    // Calculate the size of the input file
    fseek(inputFile, 0, SEEK_END); //end of file
    fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET); //beg of file

    // Read the input file character by character, reverse, and write to the output file
    char* buffer = (char*)malloc(fileSize);

    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    fread(buffer, sizeof(char), fileSize, inputFile);

    for (int i = fileSize - 1; i >= 0; i--) {
        fwrite(&buffer[i], sizeof(char), 1, outputFile);
    }

    free(buffer);

    // Close both files
    fclose(inputFile);
    fclose(outputFile);

    printf("File contents reversed and stored in '%s'.\n", outputFilename);
    printf("Size of the output file: %ld bytes\n", fileSize);

    return 0;
}

