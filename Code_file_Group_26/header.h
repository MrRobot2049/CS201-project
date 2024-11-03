#ifndef HEADER_H
#define HEADER_H

const char* get_note_from_frequency(double frequency);
double calculate_frequency(const short *buffer, size_t length, int sample_rate);
void generate_unique_filename(char *filename, size_t size);
void decode_mp3_to_notes(const char *mp3_file, FILE *output_file);
void process_spaces_in_file(const char *filename);
void read_text_file(const char *text_file, FILE *output_file);
void music_notes_converter(const char *input_file);
float compare_files(const char *file1, const char *file2);
void Decompress(const char *input_filename);
char *process_file_input(const char *filename);
void process_input(char *input, char **result, size_t *current_size);
void create_palindrome(char *input, int is_full_palindrome, char *str);
void append_result(char **result, const char *new_string, size_t *current_size);
int counter(const char *filename);
void percent_compression(const char *compressed_file, const char *decompressed_file);
void generate_unique_filename_2(char *filename, size_t size);
int comparePalindromes(const void *a, const void *b);
void insert(int idx);
void compressPalindrome(char str[], int length, int palindromeArray[][3], int numPalindromes);
void writeCompressedOutput(char str[], int length, const char *filename) ;
void findAndCompressPalindromes(const char *inputFile, const char *outputFile);






#endif
