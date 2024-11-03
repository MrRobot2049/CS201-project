#include <mpg123.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

#define BUFFER_SIZE 4096

// Function to map frequency to a custom character
const char* get_note_from_frequency(double frequency) {
    static const char *note_names[] = {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"
    };
    
    int note_index = (int)(12 * (log2(frequency / 440.0)) + 69) % 12;
    return note_names[(note_index + 12) % 12]; // Ensure wrapping
}

// Simple function to calculate the frequency from audio samples
double calculate_frequency(const short *buffer, size_t length, int sample_rate) {
    double sum = 0.0;
    for (size_t i = 0; i < length; i++) {
        sum += abs(buffer[i]);
    }
    return (sum / length) / (sample_rate / 2); // Placeholder frequency estimation
}

// Function to generate a unique file name like decoded.txt, decoded(1).txt, etc.
void generate_unique_filename(char *filename, size_t size) {
    int count = 0;
    FILE *file;

    snprintf(filename, size, "Music_Note_1.txt");
    file = fopen(filename, "r");

    while (file != NULL) {
        fclose(file);
        count++;
        snprintf(filename, size, "Music_Note_%d.txt", count);
        file = fopen(filename, "r");
    }
}

// Function to decode MP3 and perform basic pitch detection
void decode_mp3_to_notes(const char *mp3_file, FILE *output_file) {
    mpg123_handle *mpg_handle;
    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;
    int channels, encoding;
    long rate;

    mpg123_init();
    mpg_handle = mpg123_new(NULL, NULL);
    if (mpg_handle == NULL || mpg123_open(mpg_handle, mp3_file) != MPG123_OK) {
        printf("Error initializing MPG123 library or opening file.\n");
        mpg123_exit();
        return;
    }
    mpg123_getformat(mpg_handle, &rate, &channels, &encoding);

    while (mpg123_read(mpg_handle, buffer, BUFFER_SIZE, &bytes_read) == MPG123_OK) {
        const short *pcm_data = (const short *)buffer;
        size_t length = bytes_read / sizeof(short);

        double frequency = calculate_frequency(pcm_data, length, rate);
        const char *note = get_note_from_frequency(frequency);

        fprintf(output_file, "%s", note);
    }

    mpg123_close(mpg_handle);
    mpg123_delete(mpg_handle);
    mpg123_exit();
}

// Function to process spaces in the decoded file and replace them with space counts
void process_spaces_in_file(const char *filename) {
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) {
        printf("Error opening file for reading: %s\n", filename);
        return;
    }

    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error opening temporary file.\n");
        fclose(input_file);
        return;
    }

    int space_count = 0;
    char ch;
    while ((ch = fgetc(input_file)) != EOF) {
        if (ch == ' ') {
            space_count++;
        } else {
            if (space_count > 0) {
                if (space_count > 1) {
                    fprintf(temp_file, "%d ", space_count);
                } else {
                    fputc(' ', temp_file);
                }
                space_count = 0;
            }
            fputc(ch, temp_file);
        }
    }

    if (space_count > 0) {
        fprintf(temp_file, "%d", space_count);
    }

    fclose(input_file);
    fclose(temp_file);

    remove(filename);
    rename("temp.txt", filename);
}

// Function to read a text file and write its content to the decoded file
void read_text_file(const char *text_file, FILE *output_file) {
    FILE *file = fopen(text_file, "r");
    if (file == NULL) {
        printf("Error opening text file: %s\n", text_file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        fputs(line, output_file);
    }

    fclose(file);
}

// Main function to convert music notes from either text or MP3 file
void music_notes_converter(const char *input_file) {
    char output_filename[256];

    generate_unique_filename(output_filename, sizeof(output_filename));

    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Error opening output file for writing: %s\n", output_filename);
        return;
    }

    const char *dot = strrchr(input_file, '.');
    if (dot != NULL) {
        if (strcmp(dot, ".mp3") == 0) {
            decode_mp3_to_notes(input_file, output_file);
        } else if (strcmp(dot, ".txt") == 0) {
            read_text_file(input_file, output_file);
        } else {
            printf("Unsupported file type: %s\n", dot);
            fclose(output_file);
            return;
        }
    } else {
        printf("No file extension found.\n");
        fclose(output_file);
        return;
    }

    fclose(output_file);
    process_spaces_in_file(output_filename);
}

int main() {
    music_notes_converter("testcase4.mp3");
    music_notes_converter("testcase5.mp3");
    music_notes_converter("testcase6.mp3");
    return 0;
}

