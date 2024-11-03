#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define INITIAL_MAXN 1000

struct Node {
    int start, end;
    int length;
    int insertEdg[26];
    int suffixEdg;
};

struct Node *tree;
struct Node root1, root2;
int ptr;
char *s; // Pointer to dynamically allocate string
int currNode;
int maxNodes = INITIAL_MAXN;
int palindromeArray[INITIAL_MAXN][3]; // Use INITIAL_MAXN instead of PALINDROME_MAX
int palindromeCount = 0;

// Counting sort to sort palindromic substrings by length in descending order
void countingSortPalindromes(int palindromeArray[][3], int numPalindromes) {
    int maxLength = 0;

    // Find the maximum length in the palindromeArray
    for (int i = 0; i < numPalindromes; i++) {
        if (palindromeArray[i][2] > maxLength) {
            maxLength = palindromeArray[i][2];
        }
    }

    // Create count array
    int *count = (int *)calloc(maxLength + 1, sizeof(int));

    // Store the count of each length
    for (int i = 0; i < numPalindromes; i++) {
        count[palindromeArray[i][2]]++;
    }

    // Modify the count array for sorting in descending order
    for (int i = maxLength - 1; i >= 0; i--) {
        count[i] += count[i + 1];
    }

    // Output array to hold sorted elements
    int sortedPalindromes[INITIAL_MAXN][3];
    for (int i = 0; i < numPalindromes; i++) {
        int length = palindromeArray[i][2];
        sortedPalindromes[count[length] - 1][0] = palindromeArray[i][0];
        sortedPalindromes[count[length] - 1][1] = palindromeArray[i][1];
        sortedPalindromes[count[length] - 1][2] = palindromeArray[i][2];
        count[length]--;
    }

    // Copy sorted array back to palindromeArray
    for (int i = 0; i < numPalindromes; i++) {
        palindromeArray[i][0] = sortedPalindromes[i][0];
        palindromeArray[i][1] = sortedPalindromes[i][1];
        palindromeArray[i][2] = sortedPalindromes[i][2];
    }

    free(count);
}

// Function to insert a character at index idx
void insert(int idx) {
    int tmp = currNode;
    while (1) {
        int curLength = tree[tmp].length;
        if (idx - curLength >= 1 && s[idx] == s[idx - curLength - 1]) break;
        tmp = tree[tmp].suffixEdg;
    }

    if (tree[tmp].insertEdg[s[idx] - 'A'] != 0) {
        currNode = tree[tmp].insertEdg[s[idx] - 'A'];
        return;
    }

    if (ptr >= maxNodes - 1) {
        maxNodes *= 2;
        tree = realloc(tree, maxNodes * sizeof(struct Node));
        if (!tree) {
            perror("Failed to reallocate memory");
            exit(EXIT_FAILURE);
        }
    }

    ptr++;
    tree[tmp].insertEdg[s[idx] - 'A'] = ptr;
    tree[ptr].length = tree[tmp].length + 2;
    tree[ptr].end = idx;
    tree[ptr].start = idx - tree[ptr].length + 1;

    tmp = tree[tmp].suffixEdg;
    currNode = ptr;

    if (tree[currNode].length == 1) {
        tree[currNode].suffixEdg = 2;
        return;
    }

    while (1) {
        int curLength = tree[tmp].length;
        if (idx - curLength >= 1 && s[idx] == s[idx - curLength - 1]) break;
        tmp = tree[tmp].suffixEdg;
    }

    tree[currNode].suffixEdg = tree[tmp].insertEdg[s[idx] - 'A'];

    // Change this line to check for palindromes greater than 2
    if (tree[currNode].length > 2 && palindromeCount < INITIAL_MAXN) { 
        palindromeArray[palindromeCount][0] = tree[currNode].start;
        palindromeArray[palindromeCount][1] = tree[currNode].end;
        palindromeArray[palindromeCount][2] = tree[currNode].length;
        palindromeCount++;
    }
}

// Function to compress palindromes as per rules
void compressPalindrome(char str[], int length, int palindromeArray[][3], int numPalindromes) {
    int interval[INITIAL_MAXN] = {0}; // Use INITIAL_MAXN instead of MAX_LENGTH

    for (int i = 0; i < numPalindromes; i++) {
        int start = palindromeArray[i][0];
        int end = palindromeArray[i][1];
        int palindromeLength = palindromeArray[i][2];

        // Change the condition to compress palindromes greater than 2
        if (palindromeLength > 2 && interval[start] == 0 && interval[end] == 0) {
            if (palindromeLength % 2 == 0) {
                int mid1 = start + (palindromeLength / 2);
                int mid2 = mid1 + 1;
                str[mid1] = '.';
                str[mid2] = '.';

                for (int j = start; j < mid1; j++) str[j] = tolower(str[j]);
                for (int j = mid2 + 1; j <= end; j++) str[j] = '\0';
            } else {
                int mid = start + (palindromeLength + 1) / 2;
                for (int j = mid + 1; j <= end; j++) str[j] = '\0';
                str[mid] = '.';

                for (int j = start; j < mid; j++) str[j] = tolower(str[j]);
            }

            for (int j = start; j <= end; j++) interval[j] = 1;
        }
    }
}

// Function to write the compressed output to a file without spaces
void writeCompressedOutput(char str[], int length, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < length; i++) {
        if (str[i] != '\0') {
            fputc(str[i], file);
        }
    }

    fclose(file);
}

// Function to find, sort, and compress palindromic substrings from a file
void findAndCompressPalindromes(const char *inputFile, const char *outputFile) {
    FILE *file = fopen(inputFile, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    // Move to the end of the file to get the size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the string based on file size
    s = malloc(fileSize + 1); // +1 for null terminator
    if (!s) {
        perror("Failed to allocate memory for string");
        fclose(file);
        return;
    }

    if (!fgets(s, fileSize + 1, file)) {
        perror("Error reading from file");
        free(s);
        fclose(file);
        return;
    }
    fclose(file);

    s[strcspn(s, "\n")] = '\0'; // Remove newline character if present

    root1.length = -1;
    root1.suffixEdg = 1;
    root2.length = 0;
    root2.suffixEdg = 1;
    tree = malloc(maxNodes * sizeof(struct Node));
    if (!tree) {
        perror("Failed to allocate memory");
        free(s);
        exit(EXIT_FAILURE);
    }

    tree[1] = root1;
    tree[2] = root2;
    ptr = 2;
    currNode = 1;

    int l = strlen(s);
    for (int i = 0; i < l; i++) {
        insert(i);
    }

    countingSortPalindromes(palindromeArray, palindromeCount);

    compressPalindrome(s, l, palindromeArray, palindromeCount);
    writeCompressedOutput(s, l, outputFile);

    free(s);
    free(tree);
}

// Uncomment to test
/*int main() {
    findAndCompressPalindromes("input.txt", "compressed.txt");
    return 0;
}*/

