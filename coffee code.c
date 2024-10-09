#include <stdio.h>
#include <math.h>
#include <string.h>

/espresso ingredients/
#define e_beans 8; /coffee beans(grams) added/
#define e_water 30; /water(millimeter) added/
#define e_milk 0; /milk(millimeter) added/
#define e_syrup 0; /chocolate syrup added/
#define e_price 3.5; /price for one cup of espresso/

/cappucino ingredients/
#define c_beans 8; /coffee beans (grams) added/
#define c_water 30; /water (millimeter) added/
#define c_milk 70; /milk (millimeter) added/
#define c_syrup 0; /chocolate syrup added/
#define c_price 4.5; /price for one cup of cappucino/

/mocha ingredients/
#define m_beans 8; /coffee beans (grams) added/
#define m_water 30; /*water (millimeter) added */
#define m_milk 70; /milk (millimeter) added/
#define m_syrup 30; /chocolate syrup added/
#define m_price 5.5; /price for one cup of mocha/

#define admin_password 1122

/The low threshold quantity for each ingredient in the machine/
#define low_threshold_beans 20; /maximum low threshold level for coffee beans/
#define low_threshold_water 50; /maximum low threshold level for water/
#define low_threshold_milk 80; /maximum low threshold level for milk/
#define low_threshold_syrup 50; /maximum low threshold level for chocolate syrup/

double total_amount=0.0 

int main()
{
/ingredients stock availability/
int beans=150;
int water= 400;
int milk = 200;
int syrup=100;

/Function to alert the admin if the availalbilty is low/
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
/Function for payment and coins accepted/
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
//function to take coffee orders//
void order_coffee (){
    bool can_serve = false;
    
    do {
        printf("\nAvailable coffee types: \n");
        if (check_ingredients(e_beans,e_water,e_milk,e_syrup));
        printf("1.espresso - 3.5 aed\n");
        can_serve = true;
    } else {
    printf("1. espresso - unavailable. insufficient ingredients. \n");
    }
    if (check_ingredients(c_beans,c_water,c_milk,c_syrup));
     printf("2. Cappucino - 4.5 aed\n");
      can_serve = true;
 } else {
    printf("2. cappucino - unavailable. insufficient ingredients. \n");
    if (check_ingredients(m_beans,m_water,m_milk,m_syrup));
     printf("3. Mocha - 5.5 aed\n");
     can_serve = true;
 } else {
      printf("3. mocha - unavailable. insufficient ingredients. \n");
      
      printf("select your choice between 1 to 3 or press 0 to cancel.\n");
      scanf(%d, &choice){
          switch (choice){
              type 1: 
              printf("you selected espresso - 3.5 aed. confirm? (yes-1, no-0): ");
               scanf(%d, &choice);
               if (choice==1){
                   printf("enjoy your coffee!\n");
               }
          break;
          type 2:
           printf("you selected cappucino - 4.5 aed. confirm? (yes-1, no-0): ");
           scanf(%d, &choice);
            if (choice==2){
                 printf("enjoy your coffee!\n");
            }
              break;
              type 3:
               printf("you selected mocha - 5.5 aed. confirm? (yes-1, no-0): ");
     scanf(%d, &choice);
      if (choice==3){
           printf("enjoy your coffee!\n");
      }
      break;
      
      
      type 0:
      return:
      
      default menu:
      printf("invalid choc=ice, please try again.\n");
}
    }
}