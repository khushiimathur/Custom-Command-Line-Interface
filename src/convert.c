#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to convert text to binary
void textToBinary(const char *inputFile, const char *outputFile) {
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "wb");
    if (!input || !output) {
        printf("Error: Could not open file(s).\n");
        return;
    }

    char ch;
    while ((ch = fgetc(input)) != EOF) {
        fwrite(&ch, sizeof(char), 1, output);
    }

    fclose(input);
    fclose(output);
    printf("Text to binary conversion completed.\n");
}

// Function to convert binary to text
void binaryToText(const char *inputFile, const char *outputFile) {
    FILE *input = fopen(inputFile, "rb");
    FILE *output = fopen(outputFile, "w");
    if (!input || !output) {
        printf("Error: Could not open file(s).\n");
        return;
    }

    char ch;
    while (fread(&ch, sizeof(char), 1, input) == 1) {
        fputc(ch, output);
    }

    fclose(input);
    fclose(output);
    printf("Binary to text conversion completed.\n");
}

// Function to convert text to hex
void textToHex(const char *inputFile, const char *outputFile) {
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "w");
    if (!input || !output) {
        printf("Error: Could not open file(s).\n");
        return;
    }

    char ch;
    while ((ch = fgetc(input)) != EOF) {
        fprintf(output, "%02X ", (unsigned char)ch);
    }

    fclose(input);
    fclose(output);
    printf("Text to hex conversion completed.\n");
}

// Function to convert text to Base64
void textToBase64(const char *inputFile, const char *outputFile) {
    static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(outputFile, "w");
    if (!input || !output) {
        printf("Error: Could not open file(s).\n");
        return;
    }

    unsigned char buffer[3];
    int bytesRead;

    while ((bytesRead = fread(buffer, 1, 3, input)) > 0) {
        fprintf(output, "%c", base64_table[buffer[0] >> 2]);
        fprintf(output, "%c", base64_table[((buffer[0] & 0x03) << 4) | (buffer[1] >> 4)]);
        if (bytesRead > 1)
            fprintf(output, "%c", base64_table[((buffer[1] & 0x0F) << 2) | (buffer[2] >> 6)]);
        else
            fprintf(output, "=");
        if (bytesRead > 2)
            fprintf(output, "%c", base64_table[buffer[2] & 0x3F]);
        else
            fprintf(output, "=");
    }

    fclose(input);
    fclose(output);
    printf("Text to Base64 conversion completed.\n");
}

// Main function to handle user commands
int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <input_file> <output_file> <mode>\n", argv[0]);
        printf("Modes: -tobinary, -totext, -tohex, -tobase64\n");
        return 1;
    }

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];
    const char *mode = argv[3];

    if (strcmp(mode, "-tobinary") == 0) {
        textToBinary(inputFile, outputFile);
    } else if (strcmp(mode, "-totext") == 0) {
        binaryToText(inputFile, outputFile);
    } else if (strcmp(mode, "-tohex") == 0) {
        textToHex(inputFile, outputFile);
    } else if (strcmp(mode, "-tobase64") == 0) {
        textToBase64(inputFile, outputFile);
    } else {
        printf("Error: Invalid mode. Use -tobinary, -totext, -tohex, or -tobase64.\n");
    }

    return 0;
}