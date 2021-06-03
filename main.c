#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>


typedef struct {
    uint8_t value : 6;
} b64char_t;

char* base64_dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * Map 6-bit base64 character (0-64) to ascii value (A-Za-z0-9+/)
 */
char map6BitValueToAsciiChar(b64char_t b64char) {
    if (b64char.value < 64) {
        return base64_dictionary[b64char.value];
    }
    
    return '=';
}

int main(int argc, char** argv) {
    
    if (argc != 2) {
        printf("Needs 2 arguments! %d were provided.\n", argc - 1);
        return -1;
    }
    char* filename = argv[1];
    printf("Converting file: %s\n", filename);
    
    // Open and verify file
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open input file for reading: %s\n", filename);
        return -1;
    }
    
    // Read contents of file, 6 bits at a time
    int finished = 0;
    while (1) {
        // Pull in 3 bytes at a time (24 bits)
        uint8_t bytes[3];
        size_t bytesRead = fread(bytes, 1, 3, fp);
        
        if (bytesRead == 0) {
            break;
        }
        
        // Backfill missing bytes, if any
        if (bytesRead == 1) {
            bytes[1] = 0;
            bytes[2] = 0;
            finished = 1;
            // printf("Only read 1 of 3 bytes. ");
        }
        
        if (bytesRead == 2) {
            bytes[2] = 0;
            finished = 1;
            // printf("Only read 2 of 3 bytes. ");
        }
        
        // Print bytes
        // printf("Read 3 bytes:\n");
        for (int i = 0; i < 3; i++) {
            uint8_t mask = 0b10000000;
            for (int j = 0; j < 8; j++) {
                // printf("%d", (bytes[i] & mask) != 0);
                mask = mask >> 1;
            }
            // printf(" ");
        }
        // printf("\n");
        
        // Read in groups of 6
        b64char_t b64char1 = {(bytes[0] >> 2)};
        b64char_t b64char2 = {(((bytes[0] << 4) & 0b00110000) | ((bytes[1] & 0b11110000) >> 4))};
        b64char_t b64char3 = {(((bytes[1] << 2) & 0b00111100) | ((bytes[2] & 0b11000000) >> 6))};
        b64char_t b64char4 = {(bytes[2] & 0b00111111)};
        
        for (b64char_t mask = {0b100000}; mask.value > 0; mask.value = mask.value >> 1) {
            // printf("%d", (b64char1.value & mask.value) != 0);
        }
        // printf("\n");
        
        for (b64char_t mask = {0b100000}; mask.value > 0; mask.value = mask.value >> 1) {
            // printf("%d", (b64char2.value & mask.value) != 0);
        }
        // printf("\n");
        
        for (b64char_t mask = {0b100000}; mask.value > 0; mask.value = mask.value >> 1) {
            // printf("%d", (b64char3.value & mask.value) != 0);
        }
        // printf("\n");
        
        for (b64char_t mask = {0b100000}; mask.value > 0; mask.value = mask.value >> 1) {
            // printf("%d", (b64char4.value & mask.value) != 0);
        }
        // printf("\n");
        
        // Translate characters, using dictionary
        printf("%c", map6BitValueToAsciiChar(b64char1));
        printf("%c", map6BitValueToAsciiChar(b64char2));

        if (bytesRead == 3) {
            printf("%c", map6BitValueToAsciiChar(b64char3));
            printf("%c", map6BitValueToAsciiChar(b64char4));
        }
        
        if (bytesRead == 2) {
            printf("%c", map6BitValueToAsciiChar(b64char3));
            printf("=");
        }
        
        if (bytesRead == 1) {
            printf("=");
            printf("=");
        }
        
        // printf("\n");
        
        if (finished) {
            break;
        }
    }
    
    
    fclose(fp);
    
    return 0;
}