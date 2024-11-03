#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

#define MAXN 1000 // Adjust as needed
#define ARRAY_SIZE 120 // Reduced ARRAY_SIZE for debugging
#define ITERATIONS 5 // Number of iterations for averaging

// Function to generate a palindrome of a given length
void generatePalindrome(char *str, int length) {
    int mid = length / 2;

    // Fill the first half of the palindrome
    for (int i = 0; i < mid; i++) {
        str[i] = 'a' + (i % 26);  // Cycle through 'a' to 'z'
    }

    // If the length is odd, add a middle character
    if (length % 2 != 0) {
        str[mid] = 'a' + (mid % 26);
        mid++;
    }

    // Fill the second half of the palindrome
    for (int i = mid; i < length; i++) {
        str[i] = str[length - i - 1];
    }

    str[length] = '\0'; // Null-terminate the string
}

// Node structure for storing palindromic tree information
struct Node {
    int start, end;
    int length;
    int insertEdg[26];
    int suffixEdg;
};

struct Node tree_c[MAXN + 1];
int currNode_c, ptr_c;
char s_c[MAXN + 1];

// Optimized function to insert a character at index idx
void insert_c(int idx) {
    int tmp = currNode_c;

    // Find the longest suffix palindrome that can be extended
    while (1) {
        int curLength = tree_c[tmp].length;
        if (idx - curLength >= 1 && s_c[idx] == s_c[idx - curLength - 1])
            break;
        tmp = tree_c[tmp].suffixEdg;
    }

    // Check if this palindrome already exists
    if (tree_c[tmp].insertEdg[s_c[idx] - 'a'] != 0) {
        currNode_c = tree_c[tmp].insertEdg[s_c[idx] - 'a'];
        return;
    }

    // Create a new node for the palindrome
    ptr_c++;
    if (ptr_c >= MAXN) {
        fprintf(stderr, "Error: Exceeded maximum node limit.\n");
        exit(1);
    }

    tree_c[tmp].insertEdg[s_c[idx] - 'a'] = ptr_c;
    tree_c[ptr_c].length = tree_c[tmp].length + 2;
    tree_c[ptr_c].end = idx;
    tree_c[ptr_c].start = idx - tree_c[ptr_c].length + 1;
    currNode_c = ptr_c;

    // Set suffix edge for the new node
    if (tree_c[currNode_c].length == 1) {
        tree_c[currNode_c].suffixEdg = 2;  // Link to the empty root
        return;
    }

    // Find the correct suffix link for the new palindrome
    tmp = tree_c[tmp].suffixEdg;
    while (1) {
        int curLength = tree_c[tmp].length;
        if (idx - curLength >= 1 && s_c[idx] == s_c[idx - curLength - 1])
            break;
        tmp = tree_c[tmp].suffixEdg;
    }

    // Set the suffix edge for the current node
    tree_c[currNode_c].suffixEdg = tree_c[tmp].insertEdg[s_c[idx] - 'a'];
}

// Function to find distinct palindromic substrings and calculate time

double findDistinctPalindromicSubstrings(const char* inputString) {
    strcpy(s_c, inputString);
    int l = strlen(s_c);

    // Initialize tree with two root nodes
    struct Node root1 = {0, 0, -1, {0}, 1};
    struct Node root2 = {0, 0, 0, {0}, 1};
    tree_c[1] = root1;
    tree_c[2] = root2;
    ptr_c = 2;
    currNode_c = 1;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Insert each character into the palindromic tree
    for (int i = 0; i < l; i++) {
        insert_c(i);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double totalTime = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;

    return totalTime;
}


// Function to plot performance of palindrome finding
void plotPalindromePerformance() {
    char *palindromes[ARRAY_SIZE];
    double time_taken[ARRAY_SIZE];

    // Generate palindrome strings of increasing lengths
    for (int i = 0; i < ARRAY_SIZE; i++) {
        int length = 10 + (10 * i);
        palindromes[i] = (char *)malloc((length + 1) * sizeof(char));
        if (!palindromes[i]) {
            fprintf(stderr, "Memory allocation failed for palindrome of length %d\n", length);
            return;
        }
        generatePalindrome(palindromes[i], length);
    }

    // Measure the average time taken for each palindrome length
    for (int i = 0; i < ARRAY_SIZE; i++) {
        double totalTime = 0.0; // To accumulate time for averaging
        for (int j = 0; j < ITERATIONS; j++) {
            totalTime += findDistinctPalindromicSubstrings(palindromes[i]);
        }
        time_taken[i] = totalTime / ITERATIONS; // Calculate average time
        free(palindromes[i]); // Free allocated memory
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

    fprintf(gnuplotPipe, "set title 'Palindrome Length vs Time Taken'\n");
    fprintf(gnuplotPipe, "set xlabel 'Palindrome Length'\n");
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
    plotPalindromePerformance(); // Call the function to plot performance
    return 0;
}


