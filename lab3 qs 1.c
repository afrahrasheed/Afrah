//QUESTION 1 LAB 3//


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isValid(const int arr[], int length, int pos) {
    return pos >= 0 && pos < length;
}

void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("Invalid position\n");
        return;
    }

    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
}

void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length, pos) || pos >= length) {
        printf("Invalid position\n");
        return;
    }

    for (int i = length - 1; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos] = value;
}

void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: Invalid \n");
        return;
    }

    int idx = 0;
    for (int r = 0; r < nRows; r++) {
        for (int c = 0; c < nCols; c++) {
            arr2d[r][c] = arr[idx++];
        }
    }
}

void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    for (int r = 0; r < nRows; r++) {
        for (int c = 0; c < nCols; c++) {
            mat_transp[c][r] = mat[r][c];
        }
    }
}

bool found_duplicate(int arr[], int length) { 
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int length = 5;
    int pos, value;

    printf("Array before removal: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    pos = 2; 
    remove_element(arr, length, pos);
    length--; 
    printf("Array after removal: ");
    for (int i = 0; i < length; i++) {  
        printf("%d ", arr[i]);
    }
    printf("\n");

    value = 80;
    pos = 2; 
    insert_element(arr, length, pos, value); 

    printf("Array after insertion: ");
    for (int i = 0; i < length + 1; i++) {  // After insertion, length increases by 1
        printf("%d ", arr[i]);
    }
    printf("\n");

    int arr2d[3][2]; 
    int arr1d[6] = {10, 20, 30, 40, 50, 60};
    reshape(arr1d, 6, 3, 2, arr2d);

    printf("Reshaped 2D array (3x2):\n");
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 2; c++) {
            printf("%d ", arr2d[r][c]);
        }
        printf("\n");
    }

    int mat[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int mat_transp[3][2];

    trans_matrix(2, 3, mat, mat_transp);

    printf("Transposed matrix:\n");
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 2; c++) {
            printf("%d ", mat_transp[r][c]);
        }
        printf("\n");
    }

    int arr_with_dup[6] = {1, 2, 3, 4, 5, 6};
    if (found_duplicate(arr_with_dup, 6)) {
        printf("Duplicates found in the array.\n");
    } else {
        printf("No duplicates found in the array.\n");
    }

    return 0;
}
