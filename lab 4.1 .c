#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 256

// Function to check if a string represents a valid float
int is_valid_float(const char* str) {
    char* endptr;
    strtod(str, &endptr);
    return *endptr == '\0'; // Ensure the entire string is converted to a float
}

// Function to process the file and filter out invalid floats
void process_file(const char* input_filename, const char* output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return;
    }

    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return;
    }

    char line[MAX_LENGTH];
    int invalid_count = 0;

    // Read the input file line by line
    while (fgets(line, sizeof(line), input_file)) {
        // Check if the line contains a valid float
        if (is_valid_float(line)) {
            // Write the valid float to the output file
            fprintf(output_file, "%s", line);
        } else {
            invalid_count++;  // Increment the counter for invalid values
        }
    }

    fclose(input_file);  // Close the input file
    fclose(output_file); // Close the output file

    printf("Number of invalid values found: %d\n", invalid_count);  // Display the count of invalid values
}

int main() {
    const char* input_filename = "data";  // Input file is "data"
    const char* output_filename = "valid_data.txt";  // Output file is "valid_data.txt"

    process_file(input_filename, output_filename);

    return 0;
}
