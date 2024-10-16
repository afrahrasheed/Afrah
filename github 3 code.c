#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//define constants for ingredient requirement//
//espresso ingredients//
#define espresso_beans 8; //coffee beans(grams) added//
#define espresso_water 30; //water(millimeter) added//
#define e_milk 0; //milk(millimeter) added//
#define espresso_syrup 0; //chocolate syrup added//

//cappucino ingredients//
#define cappucino_beans 8; //coffee beans (grams) added//
#define cappucino_water 30; //water (millimeter) added//
#define cappucino_milk 70; //milk (millimeter) added//
#define cappucino_syrup 0; //chocolate syrup added//


//mocha ingredients//
#define mocha_beans 8; //coffee beans (grams) added//
#define mocha_water 30; //water (millimeter) added/
#define mocha_milk 70; //milk (millimeter) added//
#define mocha_syrup 30; //chocolate syrup added//

//price for coffee//
float espresso_price 3.5; //price for one cup of espresso//
float cappucino_price 4.5; //price for one cup of cappucino//
float mocha_price 5.5; //price for one cup of mocha//

//define admin password for access//
#define admin_password 1122

//The low threshold quantity for each ingredient in the machine//
#define low_threshold_beans 10; //maximum low threshold level for coffee beans//
#define low_threshold_water 50; //maximum low threshold level for water//
#define low_threshold_milk 90; //maximum low threshold level for milk//
#define low_threshold_syrup 40; //maximum low threshold level for chocolate syrup//

//Ingredients total quantity//
int beans = 120;
int water = 200;
int milk = 150;
int syrup= 100;
float total_amount=0.0;

int main() {
int choice;

while (true){
    printf("\n Coffee maker menu: \n");
    printf("1. Order coffee type \n");
    printf("2. Admin mode for the coffee maker operator \n");
    printf("3. End the application execution \n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) { 
        case 1:
        orderCoffee();
        break;
        case 2:
        adminMode();
        break;
        case 3:
        printf("Ending application. \n");
        return 0;
        default:
        printf("Invalid choice. Please try again! \n");
    }
}
}
void orderCoffee (){
    int coffee_choice;
    bool coffee_available = false;
    
    while (true) {
        printf ("\n Available Coffee types: \n");
        printf("Espresso", espresso_price);
        if (coffee_beans>=espresso_beans && water>= espresso_water){
            printf("Cappucino", cappucino_price);
            coffee_available = true;
        }
        else {
            printf ("Cappucino", "Unavailable due to insuffiecient ingredients");
        }
        if (coffee_beans>=mocha_beans && water>=mocha_water && milk>=mocha_milk && syrup>=mocha_syrup)
        printf("Mocha", mocha_price);
        coffee_available = true;
    }
    else {
        printf("Mocha","Unavailable due to insuffiecient ingredients");
    }
    if (coffee_available) {
        printf("No coffee can be served at the moment. \n");
        return;
    }
    printf("select coffee type (1. Espresso, 2.Cappucino, 3.Mocha, 0.Exit): ");
    scanf("%d", &coffee_choice);
    if (coffee_choice==0){
    return:
    }
    float price = 0.0 
    switch (coffee_choice){
        case 1:
        price = espresso_price
        break;
        case 2:
        if (coffee_beans<espresso_beans&& water<espresso_water && milk<espresso_milk && syrup<espresso_syrup) {
            printf("Espresso not available at the moment due to insufficient ingredients available. \n");
            continue;
        }
        price = cappucino_price
        break;
        case 3:
        if (coffe_beans<cappucino_beans && water<cappucino_water && milk<cappucino_milk && syrup<Cappucino_syrup){
            printf("Cappucino not available at the moment due to insuffiecient ingredients available. \n")
        }
        continue;
        price = mocha_price
        break;
        default;
        return 0
        
        printf("you selected : coffee_price - 3.5AED" %2f\n);
    }
else
printf("you selected : coffee_price - 4 AED" %2f\n);
else 
printf("you selected : coffee_price - 4.5 AED" %2f\n);

//Function to alert the admin if the availalbilty is low//
void alert_operator(){
    if (beans>=low_threshold_beans)
    printf("ALERT: Please refill the beans!\n");
    if (water>=low_threshold_water)
    printf("ALERT: Please refill the water!\n");
    if (milk>=low_threshold_milk)
    printf("ALERT: Please refill the milk!\n");
    if (syrup>=low_threshold_syrup)
    printf("ALERT: Please refill the chocolate syrup!\n");
}
//Function for payment and coins accepted//
void process_payment(double price) {
    printf("Please insert coins, accepted coins are 1 and 0.5 aed\n")
while (inserted>price)
    printf("please insert coins: ");
    scanf(%f, &coin);
    if coin==1 || coin==0.5) {
        inserted +=coin;
        printf("total inserted: %2f\n", inserted);
    }
    else if {
        printf("invalid coin inserted. try again!\n");
    }
}
      type 0:
      return:
      
      default menu:
      printf("invalid choice, please try again.\n");
}
    }
