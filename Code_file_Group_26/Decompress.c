#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"header.h"

#define INITIAL_SIZE 1000 // Initial size for dynamic allocation
#define FILENAME_SIZE 50  // Size for the filename buffer

// Function to generate a unique filename
void generate_unique_filename_2(char *filename, size_t size) {
    int count = 1;
    FILE *file;

    snprintf(filename, size, "Decompressed_file_%d.txt", count);
    file = fopen(filename, "r");

    while (file != NULL) {
        fclose(file);
        count++;
        snprintf(filename, size, "Decompressed_file_%d.txt", count);
        file = fopen(filename, "r");
    }
}

// Function to append the generated result to the result array
void append_result(char **result, const char *new_string, size_t *current_size) {
    if (strlen(*result) + strlen(new_string) + 1 > *current_size) {
        *current_size *= 2; // Double the size
        *result = realloc(*result, *current_size);
        if (*result == NULL) {
            perror("Failed to reallocate memory");
            exit(1);
        }
    }
    strcat(*result, new_string);
}

// Function to create palindromes based on the segment type
void create_palindrome(char *input, int is_full_palindrome, char *str) {
    int len = strlen(input);
    strcpy(str, input); // Copy the initial part

    if (is_full_palindrome) {
        for (int i = len - 1; i >= 0; i--) {
            str[len++] = str[i];
        }
    } else {
        for (int i = len - 2; i >= 0; i--) {
            str[len++] = str[i];
        }
    }
    str[len] = '\0'; // Null terminate the final string
}

// Function to process individual segments with uppercase handling
void process_input(char *input, char **result, size_t *current_size) {
    char str[100]; // Temporary string to hold the processed input
    char temp[50]; // Temporary buffer for the current segment
    int temp_index = 0;
    
    for (int i = 0; input[i] != '\0'; i++) {
        // If we find a dot, process the segment collected so far
        if (input[i] == '.') {
            // Check for double dot
            int is_full_palindrome = (input[i + 1] == '.');
            if (is_full_palindrome) i++; // Skip the second dot for double dot case

            temp[temp_index] = '\0'; // Null-terminate the segment in temp
            if (temp_index > 0) { // Process temp only if it's non-empty
                if (strpbrk(temp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") != NULL) {
                    append_result(result, temp, current_size); // Append as-is if it has uppercase
                } else {
                    create_palindrome(temp, is_full_palindrome, str); // Generate palindrome if lowercase
                    append_result(result, str, current_size);
                }
            }
            temp_index = 0; // Reset temp for the next segment
        } else if (isupper(input[i])) {
            // Append uppercase characters directly to result
            char uppercase_str[2] = {input[i], '\0'};
            append_result(result, uppercase_str, current_size);
        } else {
            // Collect lowercase characters in temp
            temp[temp_index++] = input[i];
        }
    }

    // Final check to process any remaining lowercase characters at the end
    temp[temp_index] = '\0'; // Null-terminate the remaining characters in temp
    if (temp_index > 0) {
        if (strpbrk(temp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") != NULL) {
            append_result(result, temp, current_size); // Append as-is if it has uppercase
        } else {
            create_palindrome(temp, 0, str); // Generate odd-length palindrome if lowercase
            append_result(result, str, current_size);
        }
    }
}
void toUpperCase(char *str){
    int i = 0;
    while(str[i] != '\0'){
        str[i] = toupper(str[i]);
        i++;
    }
}

// Function to process the file input and return the final result as a dynamically allocated string
char *process_file_input(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    size_t current_size = INITIAL_SIZE; // Start with initial buffer size
    char *result = (char *)malloc(current_size * sizeof(char));
    if (result == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }
    result[0] = '\0'; // Initialize as an empty string

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline if present
        process_input(line, &result, &current_size); // Process and append to result
    }

    fclose(file);
    toUpperCase(result);
    return result; // Return the dynamically allocated result
}

// New function compress that takes only the input filename
void Decompress(const char *input_filename) {
    // Process the file and get the concatenated result
    char *result = process_file_input(input_filename);
    if (result == NULL) {
        fprintf(stderr, "Failed to process input file.\n");
        return; // Exit if file processing failed
    }

    // Generate a unique filename for the output
    char output_filename[FILENAME_SIZE];
    generate_unique_filename_2(output_filename, FILENAME_SIZE);

    // Write the result to the output file
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error creating output file");
        free(result);
        return;
    }
    fprintf(output_file, "%s\n", result);
    fclose(output_file);

    printf("Final result written to %s\n", output_filename);

    // Free the allocated memory
    free(result);
}
