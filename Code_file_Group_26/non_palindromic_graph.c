#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

#define MAXN 1000 // Adjust as needed
#define ARRAY_SIZE 120 // Reduced ARRAY_SIZE for debugging
#define ITERATIONS 10 // Number of iterations for averaging

// Function to generate a non-palindrome of a given length
void generateNonPalindrome(char *str, int length) {
    for (int i = 0; i < length; i++) {
        str[i] = 'a' + (i % 26); // Cycle through 'a' to 'z'
    }
    str[length] = '\0';

    // Ensure it's not a palindrome by modifying one character if necessary
    if (length > 1 && str[0] == str[length - 1]) {
        str[length - 1] = (str[length - 1] == 'a') ? 'b' : 'a';
    }
}

// Structure for storing palindromic tree information
struct PalindromeNode {
    int start, end;
    int length;
    int insertEdg[26];
    int suffixEdg;
};

struct PalindromeNode palindromeTree[MAXN + 1];
int currentNode, nodePointer;
char inputStringBuffer[MAXN + 1];

// Optimized function to insert a character at index idx
void insert_2(int idx) {
    int tmp = currentNode;

    // Find the longest suffix palindrome that can be extended
    while (1) {
        int curLength = palindromeTree[tmp].length;
        if (idx - curLength >= 1 && inputStringBuffer[idx] == inputStringBuffer[idx - curLength - 1])
            break;
        tmp = palindromeTree[tmp].suffixEdg;
    }

    // Check if this palindrome already exists
    if (palindromeTree[tmp].insertEdg[inputStringBuffer[idx] - 'a'] != 0) {
        currentNode = palindromeTree[tmp].insertEdg[inputStringBuffer[idx] - 'a'];
        return;
    }

    // Create a new node for the palindrome
    nodePointer++;
    if (nodePointer >= MAXN) {
        fprintf(stderr, "Error: Exceeded maximum node limit.\n");
        exit(1);
    }

    palindromeTree[tmp].insertEdg[inputStringBuffer[idx] - 'a'] = nodePointer;
    palindromeTree[nodePointer].length = palindromeTree[tmp].length + 2;
    palindromeTree[nodePointer].end = idx;
    palindromeTree[nodePointer].start = idx - palindromeTree[nodePointer].length + 1;
    currentNode = nodePointer;

    // Set suffix edge for the new node
    if (palindromeTree[currentNode].length == 1) {
        palindromeTree[currentNode].suffixEdg = 2;  // Link to the empty root
        return;
    }

    // Find the correct suffix link for the new palindrome
    tmp = palindromeTree[tmp].suffixEdg;
    while (1) {
        int curLength = palindromeTree[tmp].length;
        if (idx - curLength >= 1 && inputStringBuffer[idx] == inputStringBuffer[idx - curLength - 1])
            break;
        tmp = palindromeTree[tmp].suffixEdg;
    }

    // Set the suffix edge for the current node
    palindromeTree[currentNode].suffixEdg = palindromeTree[tmp].insertEdg[inputStringBuffer[idx] - 'a'];
}

// Function to find distinct palindromic substrings and calculate time
double findDistinctPalindromicSubstrings(const char* inputString) {
    strcpy(inputStringBuffer, inputString);
    int l = strlen(inputStringBuffer);

    // Initialize tree with two root nodes
    struct PalindromeNode root1 = {0, 0, -1, {0}, 1};
    struct PalindromeNode root2 = {0, 0, 0, {0}, 1};
    palindromeTree[1] = root1;
    palindromeTree[2] = root2;
    nodePointer = 2;
    currentNode = 1;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Insert each character into the palindromic tree
    for (int i = 0; i < l; i++) {
        insert_2(i);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double totalTime = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;

    return totalTime;
}

// Function to generate data and plot a graph
void plotNonPalindromePerformance() {
    char *nonPalindromes[ARRAY_SIZE];
    double time_taken[ARRAY_SIZE];

    // Generate non-palindromic strings of increasing lengths
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int length = 10 + (10 * i);
        nonPalindromes[i] = (char *)malloc((length + 1) * sizeof(char));
        if (!nonPalindromes[i]) {
            fprintf(stderr, "Memory allocation failed for non-palindrome of length %d\n", length);
            return;
        }
        generateNonPalindrome(nonPalindromes[i], length);
    }

    // Measure the average time taken for each non-palindromic length
    for (int i = 0; i < ARRAY_SIZE; i++) {
        double totalTime = 0.0; // To accumulate time for averaging
        for (int j = 0; j < ITERATIONS; j++) {
            totalTime += findDistinctPalindromicSubstrings(nonPalindromes[i]);
        }
        time_taken[i] = totalTime / ITERATIONS; // Calculate average time
        free(nonPalindromes[i]); // Free allocated memory
    }
    
    int x[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        x[i] = (i + 1) * 10;
    }

    // Plotting results with GNUPlot
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL) {
        fprintf(stderr, "Error opening pipe to GNUPlot.\n");
        return;
    }

    fprintf(gnuplotPipe, "set title 'Non-Palindrome Length vs Time Taken'\n");
    fprintf(gnuplotPipe, "set xlabel 'String Length'\n");
    fprintf(gnuplotPipe, "set ylabel 'Time (microseconds)'\n");
    fprintf(gnuplotPipe, "plot '-' with linespoints title 'Data'\n");

    for (int i = 0; i < ARRAY_SIZE; i++) {
        fprintf(gnuplotPipe, "%d %f\n", x[i], time_taken[i]);
    }

    fprintf(gnuplotPipe, "e\n");
    fflush(gnuplotPipe);
    pclose(gnuplotPipe);
}

// Main function to call plot function
int main() {
    plotNonPalindromePerformance();
    return 0;
}

