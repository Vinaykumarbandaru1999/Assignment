#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to decode hex data into ASCII
char* decodeHexToAscii(const char* hexData) {
    size_t len = strlen(hexData);
    if (len % 2 != 0) {
        // Hex data must have an even number of characters
        return NULL;
    }

    size_t asciiLen = len / 2;
    char* asciiData = (char*)malloc(asciiLen + 1);

    for (size_t i = 0; i < asciiLen; i++) {
        char hexByte[3];
        hexByte[0] = hexData[i * 2];
        hexByte[1] = hexData[i * 2 + 1];
        hexByte[2] = '\0';

        // Convert the hex byte to an integer
        int decimalValue;
        sscanf(hexByte, "%2x", &decimalValue);

        // Store the ASCII character in the result
        asciiData[i] = (char)decimalValue;
    }

    // Null-terminate the ASCII string
    asciiData[asciiLen] = '\0';

    return asciiData;
}

int main() {
    char hexData[101]; // Define a character array to store user input
    printf("Enter the hexadecimal data (up to 100 characters): ");
    scanf("%100[^\n]", hexData); // Read user input until a newline character

    char* parameter1 = hexData;
    char* parameter2 = strchr(hexData, '#'); // Find the first '#' character
    
    if (parameter2 != NULL) {
        *parameter2 = '\0'; // Null-terminate parameter1 at the first '#' character
        parameter2++; // Move parameter2 to the character after the first '#'
    } else {
        printf("Invalid input format. At least one '#' character is missing.\n");
        return 1;
    }

    char* parameter3 = strchr(parameter2, ' '); // Find the first space character
    
    if (parameter3 != NULL) {
        *parameter3 = '\0'; // Null-terminate parameter2 at the space character
        parameter3++; // Move parameter3 to the character after the space
    } else {
        printf("Invalid input format. A space character is missing.\n");
        return 1;
    }

    // Combine the last third and fourth elements of parameter1
    char combinedElements[3];
    int len = strlen(parameter1);
    if (len >= 4) {
        combinedElements[0] = parameter1[len - 4];
        combinedElements[1] = parameter1[len - 3];
        combinedElements[2] = '\0';
    } else {
        printf("Invalid Input format.\n");
        return 1;
    }

    if (strcmp(parameter3, combinedElements) == 0) {
        printf("Target ID and second least bit of arbitration Id are the same.\n");
        char* asciiData1 = decodeHexToAscii(parameter2);
        printf("Decoded ASCII data for databytes is: %s\n", asciiData1);
    } else {
        printf("Warning: Target Id doesn't match.\n");
    }

    return 0;
}
