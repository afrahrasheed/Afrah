#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ingredients and price for espresso//
#define espresso_beans 8 // grams of coffee required//
#define espresso_water 30 // water (millimeter) required//
#define espresso_milk 0 // milk (millimeter) required//
#define espresso_chocolate 0 // chocolate (millimeter) required//
#define espresso_price 3.5 // price for one cup of espresso//

// Ingredients and price for cappuccino//
#define cappucino_beans 8 // grams of coffee required//
#define cappucino_water 30 // water (millimeter) required//
#define cappucino_milk 70 // milk (millimeter) required//
#define cappucino_chocolate 0 // chocolate (millimeter) required//
#define cappucino_price 4.5 // price for one cup of cappuccino//

// Ingredients and price for mocha//
#define mocha_beans 8  // grams of coffee required//
#define mocha_water 39 // water (millimeter) required//
#define mocha_milk 160 // milk (millimeter) required//
#define mocha_chocolate 30 // chocolate (millimeter) required//
#define mocha_price 5.5 // price for one cup of mocha//

// Maximum threshold capacity for ingredients//
#define bean_threshold 10 // maximum threshold for coffee beans//
#define water_threshold 50 // maximum threshold for water//
#define milk_threshold 20 // maximum threshold for milk//
#define chocolate_threshold 10 // maximum threshold for chocolate//

// Admin password for access//
#define admin_password "123456"

float total_amount = 0.0;

// Initial ingredient quantities//
int initial_coffee_beans = 70, initial_water = 120, initial_milk = 150, initial_chocolate = 80;

// Current ingredient quantities//
int coffee_beans = 70, water = 120, milk = 190, chocolate = 80;

void alert_if_needed() {  
    if (coffee_beans <= bean_threshold) { //Required coffee beans level is low//
        printf("Alert: Coffee beans low!\n");
    }
    if (water <= water_threshold) {  //Required water level is low//
        printf("Alert: Water low!\n");
    }
    if (milk <= milk_threshold) {  //Required milk level is low//
        printf("Alert: Milk low!\n");
    }
    if (chocolate <= chocolate_threshold) {  //Required chocolate syrup level is low//
        printf("Alert: Chocolate syrup low!\n");
    }
}

void display_coffees() { //Displaying the coffee type and price available to the customer//
    printf("%-12s %-12s\n", "Coffee Type", "Price (AED)"); 
    printf("%-12s %-12.2f\n", "Espresso", espresso_price);
    if (coffee_beans >= espresso_beans && water >= espresso_water) { //Checking if espresso ingredients are present//
        printf("Espresso is available.\n");
    } else {
        printf("Espresso Unavailable due to insufficient ingredients.\n");
    }
    
    printf("%-12s %-12.2f\n", "Cappuccino", cappucino_price); //Displaying the coffee type and price available to the customer//
    if (coffee_beans >= cappucino_beans && water >= cappucino_water && milk >= cappucino_milk) { //Checking if Cappucino ingredients are present//
        printf("Cappuccino is available.\n");
    } else {
        printf("Cappuccino Unavailable due to insufficient ingredients.\n");
    }
    
    printf("%-12s %-12.2f\n", "Mocha", mocha_price); //Displaying the coffee type and price available to the customer//
    //Checking if mocha ingredients are present//
    if (coffee_beans >= mocha_beans && water >= mocha_water && milk >= mocha_milk && chocolate >= mocha_chocolate) { 
        printf("Mocha is available.\n");
    } else {
        printf("Mocha Unavailable due to insufficient ingredients.\n");
    }
}

void order_coffee() {
    int choice, confirm;
    float payment;
    
    while (1) {
        display_coffees();
        //Asking user for coffee type required//
        printf("Select coffee type (1: Espresso, 2: Cappuccino, 3: Mocha, 0: Exit): ");
        scanf("%d", &choice); //Assigning the user choice to int choice//

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                if (coffee_beans < espresso_beans || water < espresso_water) {
                    printf("Espresso Unavailable.\n"); //Unavaible due to insufficient ingredients available//
                    continue;
                }
                printf("You selected Espresso, price: %.2f AED\n", espresso_price);
                break;
            case 2:
                if (coffee_beans < cappucino_beans || water < cappucino_water || milk < cappucino_milk) {
                    printf("Cappuccino Unavailable.\n"); //Unavaible due to insufficient ingredients available//
                    continue;
                }
                printf("You selected Cappuccino, price: %.2f AED\n", cappucino_price);
                break;
            case 3:
                if (coffee_beans < mocha_beans || water < mocha_water || milk < mocha_milk || chocolate < mocha_chocolate) {
                    printf("Mocha Unavailable.\n"); //Unavaible due to insufficient ingredients available//
                    continue;
                }
                printf("You selected Mocha, price: %.2f AED\n", mocha_price);
                break;
            default:
                printf("Invalid selection.\n"); //Shows invalid if user types an invalid response//
                continue;
        }

        printf("Confirm selection? (1: Yes, 0: No): ");
        scanf("%d", &confirm);
        if (confirm == 0) {
            continue;
        }

        payment = 0.0;
        while (payment < (choice == 1 ? espresso_price : (choice == 2 ? cappucino_price : mocha_price))) {
            float coin;
            printf("Insert coin (1 or 0.5 AED): "); //Only accepts coins 1 or 0.5 AED//
            scanf("%f", &coin);
            if (coin != 1.0 && coin != 0.5) {  //Invalid coin if it not equal to 1 or 0.5AED//
                printf("Invalid coin. Please insert a valid one.\n");
                continue;
            }
            payment += coin;  //Assinging coin value to payment value//
        }

        printf("You paid: %.2f AED\n", payment);
        total_amount += (choice == 1 ? espresso_price : (choice == 2 ? cappucino_price : mocha_price));

        // Update ingredients//
        coffee_beans -= (choice == 1 ? espresso_beans : (choice == 2 ? cappucino_beans : mocha_beans));
        water -= (choice == 1 ? espresso_water : (choice == 2 ? cappucino_water : mocha_water));
        milk -= (choice == 1 ? espresso_milk : (choice == 2 ? cappucino_milk : mocha_milk));
        chocolate -= (choice == 1 ? espresso_chocolate : (choice == 2 ? cappucino_chocolate : mocha_chocolate));

        printf("Enjoy your coffee!\n");
        alert_if_needed();
    }
}

//Function to let the admin reset the ingredients in the vending machine//
void reset_ingredients() {
    coffee_beans = initial_coffee_beans;
    water = initial_water;
    milk = initial_milk;
    chocolate = initial_chocolate;
    printf("Ingredients have been reset to their initial quantities.\n");
}

void admin_mode() {
    char password[55]; //Upto 55 characters can be entered//
    while (1) {
        printf("Enter admin password: ");
        scanf("%s", password); //Assign the password entered to the password variable//
        
        if (strcmp(password, admin_password) != 0) { //Comparing between the password entered with the correct password//
            printf("Password incorrect. Exiting Admin mode.\n");
            return;
        }

        while (1) {
            printf("1: Display ingredient quantities\n"); //Admin choice to display ingredients quantities//
            printf("2: Replenish ingredients\n"); //Admin mode to replenish ingredients in the machine//
            printf("3: Change coffee price\n"); //Admin mode to change the coffee price//
            printf("4: Reset ingredients\n"); //Admin mode to reset the ingredients//
            printf("0: Exit Admin Mode\n"); //To exit the admin mode, have to enter password again to access admin mode//
            
            int choice;
            scanf("%d", &choice); //Admin selection from the reset options//
            if (choice == 0) {
                break;
            }

            switch (choice) {
                case 1:
                    printf("Ingredients:\n"); 
                    printf("Coffee Beans: %d grams\n", coffee_beans); //Display of the available coffee beans//
                    printf("Water: %d ml\n", water); //Display of the available water//
                    printf("Milk: %d ml\n", milk); //Display of the available milk//
                    printf("Chocolate Syrup: %d ml\n", chocolate); //Display of the available chocolate syrup//
                    printf("Total Sales Amount: %.2f AED\n", total_amount); //Display of the total sales amount made//
                    break;
                    
                case 2:
                    coffee_beans = rand() % 100 + 50; // Randomly reset to between 50-149//
                    water = rand() % 100 + 50; // Randomly reset to between 50-149//
                    milk = rand() % 100 + 50; // Randomly reset to between 50-149//
                    chocolate = rand() % 100 + 50; // Randomly reset to between 50-149//
                    printf("Ingredients replenished randomly.\n");
                    break;
                    
                case 3: {
                    float new_price; //Updated price for coffee//
                    printf("Enter new price for Espresso: ");
                    scanf("%f", &new_price);
                    printf("New price for Espresso is: %.2f AED\n", new_price);
                    break;
                }
                case 4:
                    reset_ingredients(); //case to reset the ingredients in the machine//
                    break;
                default:
                    printf("Invalid selection.\n");
            }
        }
    }
}

int main() { //Main menu presented to user//
    while (1) {
        printf("1: Order a coffee\n");
        printf("2: Admin mode\n");
        printf("3: Exit\n");
        int option;
        scanf("%d", &option);
        switch (option) { 
            case 1: // Option 1 to order coffee//
                order_coffee();
                break;
            case 2: // Option 2 to access admin mode//
                admin_mode();
                break;
            case 3: // Option 3 to exit the application//
                printf("Exiting the application.\n");
                return (0);
        }
    }
}

