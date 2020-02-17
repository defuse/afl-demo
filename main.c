#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// THIS CODE INTENTIONALLY CONTAINS NUMEROUS VULNERABILITIES. DO NOT USE IT!

/*
 * (Broken) parser for a simple data storage format. The file is made up of
 * records in sequence, where each record has the form:
 * 
 *  - 1-byte "type"
 *  - 2-byte "length"
 *  - n-byte payload
 *
 * Valid types are:
 *  - 0: string data
 *  - 1: 16-bit integer
 */

#define TYPE_STRING 0
#define TYPE_INT 1

int printNextRecord(FILE *fptr);

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: ./parse <file>\n");
        return -1;
    }

    FILE *fptr = fopen(argv[1], "r");

    while (printNextRecord(fptr) == 0) {

    }

    fclose(fptr);
}

int printStringRecord(FILE *fptr) {
    unsigned int c;
    unsigned int len;

    // BUG 1: Doesn't check c != EOF

    // Read the length
    c = fgetc(fptr);
    len = c << 8;
    c = fgetc(fptr);
    len = len + c;

    // BUG 2: Doesn't check for malloc returning NULL.
    char *buffer = malloc(len + 1);

    for (int i = 0; i < len; i++) {
        buffer[i] = fgetc(fptr);
    }
    buffer[len] = 0;

    // Bug 3: Strings in the file can contain null bytes and have strlen(buffer) < len.
    char *uppercase = malloc(strlen(buffer) + 1);
    for (int i = 0; i < len; i++) {
        uppercase[i] = toupper(buffer[i]);
    }

    // Bug 4: we forgot to null-terminate uppercase.

    printf("String record converted to upper case: [%s]\n", uppercase);

    return 0;
}

int printIntRecord(FILE *fptr) {
    // Skip over the length field.
    fgetc(fptr); fgetc(fptr);

    unsigned int c;
    unsigned int value;
    c = fgetc(fptr);
    if (c == EOF) { return 1; }
    value = c << 8;
    c = fgetc(fptr);
    if (c == EOF) { return 1; }
    value = value + c;

    printf("Integer record: [%d]\n", value);

    return 0;
}

// Returns 1 if EOF was reached, 0 otherwise.
int printNextRecord(FILE *fptr) {
    int type = fgetc(fptr);
    if (type == EOF) {
        return 1;
    }

    switch (type) {
        case TYPE_STRING:
            printf("About to parse a string...\n");
            return printStringRecord(fptr);
        case TYPE_INT:
            printf("About to parse an int...\n");
            return printIntRecord(fptr);
        default:
            printf("Unknown record type.\n");
    }

    return 0;
}
