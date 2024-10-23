#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ingredients and price for espresso//
#define espresso_beans 8 //grams of coffee required//
#define espresso_water 30 //water (millimeter) required//
#define espresso_milk 0 //milk (millimeter) required//
#define espresso_chocolate 0 //chocolate (millimeter) required//
#define espresso_price 3.5 //price for one cup of espresso//

//ingredients and price for cappucino//
#define cappucino_beans 8 //grams of coffee required//
#define cappucino_water 30 //water (millimeter) required//
#define cappucino_milk 70 //milk (millimeter) required//
#define cappucino_chocolate 0//chocolate (millimeter) required//
#define cappucino_price 4.5 //price for one cup of cappucino//

//ingredients and price for mocha//
#define mocha_beans 8  //grams of coffee required//
#define mocha_water 39 //water (millimeter) required//
#define mocha_milk 160 //milk (millimeter) required//
#define mocha_chocolate 30 //chocolate (millimeter) required//
#define mocha_price 5.5 //price for one cup of espresso//

//maximum threshold capacity for ingredients//
#define bean_threshold 10 //maximum threshold for coffee beans//
#define water_threshold 50 //maximum threshold for water//
#define milk_threshold 20 //maximum threshold for milk//
#define chocolate_threshold 10 //maximum threshold for chocolate//

//admin password for access//
#define admin_password 123456

float total_amount = 0.0;

//
int coffee_beans = 70, water = 120, milk = 170, chocolate = 80; //ingredients available in the machine for coffee//

void alert_if_needed() { 
    if (coffee_beans <= bean_threshold) { //level of coffee beans required is low//
        printf("Alert: Coffee beans low!\n");
    }
    if (water <= water_threshold) { //level of water required is low//
        printf("Alert: Water low!\n");
    }
    if (milk <= milk_threshold) { //level of milk required is low//
        printf("Alert: Milk low!\n");
    }
    if (chocolate <= chocolate_threshold) { //level of chocolate required is low//
        printf("Alert: Chocolate syrup low!\n");
    }
}
void display_coffees() {
    printf("%-12s %-12s\n", "Coffee Type", "Price (AED)"); 
    printf("%-12s %-12.2f\n", "Espresso",espresso_price );
    if (coffee_beans >= espresso_beans && water >= espresso_water) { //ingredients for espresso are available//
        printf("Espresso is available.\n");
    } else { //ingredients required for espresso is not available in machine//
        printf("Espresso Unavailable due to insufficient ingredients.\n");
    }
    
    printf("%-12s %-12.2f\n", "Cappuccino", cappucino_price);
    if (coffee_beans >= cappucino_beans && water >= cappucino_water && milk >= cappucino_milk) { //ingredients for cappucino are available//
        printf("Cappuccino is available.\n");
    } else { //ingredients required for cappucino is not available in machine//
        printf("Cappuccino Unavailable due to insufficient ingredients.\n");
    }
    
    printf("%-12s %-12.2f\n", "Mocha", mocha_price);
    if (coffee_beans >= mocha_beans && water >= mocha_water && milk >= mocha_milk && chocolate >= mocha_chocolate) { //ingredients for mocha are available//
        printf("Mocha is available.\n");
    } else {  //ingredients required for mocha is not available in machine//
        printf("Mocha Unavailable due to insufficient ingredients.\n");
    }
}

void order_coffee() {
    int choice, confirm;
    float payment;
    
    while (1) {
        display_coffees();
        printf("Select coffee type (1: Espresso, 2: Cappuccino, 3: Mocha, 0: Exit): ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                if (coffee_beans < espresso_beans || water < espresso_water) { 
                    printf("Espresso Unavailable.\n");  //unavailable as espresso requires more beans and water than available//
                    continue;
                }
                printf("You selected Espresso, price: %.2f AED\n", espresso_price);
                break;
            case 2:
                if (coffee_beans < cappucino_beans || water < cappucino_water || milk < cappucino_milk) {
                    printf("Cappuccino Unavailable.\n"); //unavailable as cappucino requires more beans,water and milk than available//
                    continue;
                }
                printf("You selected Cappuccino, price: %.2f AED\n", cappucino_price);
                break;
            case 3:
                if (coffee_beans < mocha_beans || water < mocha_water || milk < mocha_milk || chocolate < mocha_chocolate) {
                    printf("Mocha Unavailable.\n"); //unavailable as mocha requires more beans,water, milk and chocolate than available//
                    continue;
                }
                printf("You selected Mocha, price: %.2f AED\n", mocha_price);
                break;
            default:
                printf("Invalid selection.\n");
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
            printf("Insert coin (1 or 0.5 AED): ");
            scanf("%f", &coin);
            if (coin != 1.0 && coin != 0.5) {
                printf("Invalid coin.Please insert a valid one.\n");
                continue;
            }
            payment += coin;
        }

        printf("You paid: %.2f AED\n", payment);
        total_amount += (choice == 1 ? espresso_price : (choice == 2 ? cappucino_price : mocha_price));

        // Update ingredients
        coffee_beans -= (choice == 1 ? espresso_beans : (choice == 2 ? cappucino_beans : mocha_beans));
        water -= (choice == 1 ? espresso_water : (choice == 2 ? cappucino_water : mocha_water));
        milk -= (choice == 1 ? espresso_milk : (choice == 2 ? cappucino_milk : mocha_milk));
        chocolate -= (choice == 1 ? espresso_chocolate : (choice == 2 ? cappucino_chocolate : mocha_chocolate));

        printf("Enjoy your coffee!\n");
        alert_if_needed();
    }
}

void admin_mode() {
    char password[55];
    while (1) {
        printf("Enter admin password: ");
        scanf("%s", password);

       
        if (strcmp(password, admin_password) != 0) {
            printf("Password incorrect. Exiting Admin mode.\n");
            return;
        }

        while (1) {
            printf("1: Display ingredient quantities\n");
            printf("2: Replenish ingredients\n");
            printf("3: Change coffee price\n");
            printf("0: Exit Admin Mode\n");
            
            int choice;
            scanf("%d", &choice);
            if (choice == 0) {
                break;
            }

            switch (choice) {
                case 1:
                    printf("Ingredients:\n");
                    printf("Coffee Beans: %d grams\n", coffee_beans);
                    printf("Water: %d ml\n", water);
                    printf("Milk: %d ml\n", milk);
                    printf("Chocolate Syrup: %d ml\n", chocolate);
                    printf("Total Sales Amount: %.2f AED\n", total_amount);
                    break;
                    
                case 2:
                    coffee_beans = rand() % 100 + 50; // Randomly reset to between 50-149
                    water = rand() % 100 + 50; // Randomly reset to between 50-149
                    milk = rand() % 100 + 50; // Randomly reset to between 50-149
                    chocolate = rand() % 100 + 50; // Randomly reset to between 50-149
                    printf("Ingredients replenished randomly.\n");
                    break;
                    
                case 3: {
                    float new_price;
                    printf("Enter new price for Espresso: ");
                    scanf("%f", &new_price);
                    printf("New price for Espresso is: %.2f AED\n", new_price);
                    break;
                }
                default:
                    printf("Invalid selection.\n");
            }
        }
    }
}

int main() {
    while (1) {
        printf("1: Order a coffee\n");
        printf("2: Admin mode\n");
        printf("3: Exit\n");
        int option;
        scanf("%d", &option);
        switch (option) {
            case 1:
                order_coffee();
                break;
            case 2:
                admin_mode();
                break;
            case 3:
                printf("Exiting the application.\n");
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
}
