#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read the ASCII PGM file //
int readPGMText(const char* filename, unsigned char** pixels, int* width, int* height) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return -1;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Read the PGM header (P2) //
    fgets(line, sizeof(line), file); // Read the comment line //
    fscanf(file, "%d %d", width, height); // Read width and height of the image
    fgets(line, sizeof(line), file); // Read max gray value (usually 255) //

    // Allocate memory for storing the image pixels //
    *pixels = (unsigned char*)malloc(*width * *height * sizeof(unsigned char));
    if (*pixels == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    // Read the pixel values from the file //
    for (int i = 0; i < (*width * *height); i++) {
        fscanf(file, "%hhu", &(*pixels)[i]);
    }

    fclose(file);
    return 0;
}

// Function to write the PGM file in text format //
int writePGMText(const char* filename, unsigned char* pixels, int width, int height) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Unable to open file for writing");
        return -1;
    }

    fprintf(file, "P2\n# comment\n%d %d\n255\n", width, height);
    for (int i = 0; i < width * height; i++) {
        fprintf(file, "%d ", pixels[i]);
        if ((i + 1) % width == 0) {
            fprintf(file, "\n");
        }
    }

    fclose(file);
    return 0;
}

// Function to write the PGM file in binary format //
int writePGMBinary(const char* filename, unsigned char* pixels, int width, int height) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Unable to open file for writing");
        return -1;
    }

    fprintf(file, "P5\n# comment\n%d %d\n255\n", width, height);
    fwrite(pixels, sizeof(unsigned char), width * height, file);

    fclose(file);
    return 0;
}

// Function to embed the secret image into the cover image //
void embedLSB(unsigned char* coverPixels, unsigned char* secretPixels, unsigned char* stegoPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        unsigned char coverPixel = coverPixels[i];
        unsigned char secretPixel = secretPixels[i];

        // Replace the 4 least significant bits (LSB) of the cover pixel with the upper 4 bits of the secret pixel //
        stegoPixels[i] = (coverPixel & 0xF0) | ((secretPixel >> 4) & 0x0F);
    }
}

// Function to extract the secret image from the stego image //
void extractLSB(unsigned char* stegoPixels, unsigned char* extractedSecretPixels, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        unsigned char stegoPixel = stegoPixels[i];
        // Extract the 4 least significant bits of the stego pixel and shift them to the most significant position //
        extractedSecretPixels[i] = (stegoPixel & 0x0F) << 4;
    }
}

int main() {
    int width = 512, height = 512;
    unsigned char *coverPixels, *secretPixels, *stegoPixels, *extractedSecretPixels;

    // Read the cover and secret images //
    if (readPGMText("baboon.pgm", &coverPixels, &width, &height) != 0) return -1;
    if (readPGMText("farm.pgm", &secretPixels, &width, &height) != 0) return -1;

    // Allocate memory for the stego image and extracted secret image //
    stegoPixels = (unsigned char*)malloc(width * height * sizeof(unsigned char));
    if (stegoPixels == NULL) {
        perror("Memory allocation failed for stego image");
        free(coverPixels);
        free(secretPixels);
        return -1;
    }

    extractedSecretPixels = (unsigned char*)malloc(width * height * sizeof(unsigned char));
    if (extractedSecretPixels == NULL) {
        perror("Memory allocation failed for extracted secret image");
        free(coverPixels);
        free(secretPixels);
        free(stegoPixels);
        return -1;
    }

    // Embed the secret image into the cover image //
    embedLSB(coverPixels, secretPixels, stegoPixels, width, height);

    // Write the stego image to a binary PGM file //
    if (writePGMBinary("stego_image_bin.pgm", stegoPixels, width, height) != 0) return -1;

    // Extract the secret image from the stego image //
    extractLSB(stegoPixels, extractedSecretPixels, width, height);

    // Write the extracted secret image to a text PGM file //
    if (writePGMText("extracted_secret.pgm", extractedSecretPixels, width, height) != 0) return -1;

    // Free dynamically allocated memory //
    free(coverPixels);
    free(secretPixels);
    free(stegoPixels);
    free(extractedSecretPixels);

    return 0;
}
