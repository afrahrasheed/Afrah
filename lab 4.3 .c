#include <iostream>
#include <iomanip>
#include <cstdlib> 
using namespace std;

void print_real(float number, int fieldspace, int precision);

template <typename T>
void update_scale(T& num1, T& num2) {
    
    num1 *= 2; //     we scale the numbers by multiplying them by 2
    num2 *= 2;
}

int main(void) {
    float a, b;
    
    // Ask the user to input two real numbers
    cout << "Please input two real numbers: ";
    cin >> a >> b;

   
    print_real(a, 7, 3);  // For example, width 7, precision 3
    print_real(b, 7, 3);  // For example, width 7, precision 3

    // Call the update_scale function to modify a and b
    update_scale(a, b);

    // Print the updated numbers
    print_real(a, 7, 3);  // Print the updated a
    print_real(b, 7, 3);  // Print the updated b

    return 0;
}

// Function to print the real number in fixed-point notation with given field and precision
void print_real(float number, int fieldspace, int precision) {
    cout << fixed << setw(fieldspace) << setprecision(precision) << number << endl;
}
