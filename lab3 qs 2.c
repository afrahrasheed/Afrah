//QUESTION 2 LAB 3//

#include <stdio.h>

void process_transactions(int transactions[], int num_transactions) {
    int balance = 1000; //starting balance //
    int to_be_processed[100]; //number of characters that can be stored in this array//
    int processed_count = 0; //number of transactions taken place//
    
    printf("Initial balance is %d AED\n", balance); //let the user know the starting balance//

    for (int i = 0; i < num_transactions; i++) { 
        int transaction_amount = transactions[i]; 

        if (transaction_amount < 0) { //checking if amount is smaller than 0//
            if (-transaction_amount > balance) { //checking if the given amount can be withdrawn//
                printf("Invalid transaction - Withdrawal of %d AED not processed as it exceeds current balance %d AED.\n", -transaction_amount, balance);
                to_be_processed[processed_count++] = transaction_amount; 
                continue; 
            } else {
                balance += transaction_amount; //checking if the amount transaction can be carried out//
                printf("Withdrawal successful: %d AED. The balance is %d AED.\n", -transaction_amount, balance);
            }
        } else { 
            balance += transaction_amount; //checking if the amount transaction can be carried out//
            printf("Deposited successfully: %d AED. The balance is %d AED.\n", transaction_amount, balance);
        }

        if (balance == 0) { //checking if balance reached 0//
            printf("The balance has reached 0 AED. No more transactions can be done.\n");
            break; 
        }
    }

    printf("\nFinal balance: %d AED\n", balance);
    printf("Transactions that could not be processed:\n");
    if (processed_count > 0) { //seeing if any transaction was not performed//
        for (int i = 0; i < processed_count; i++) {
            printf("%d ", to_be_processed[i]);
        }
    } else {
        printf("None\n"); //if no transaction was declined//
    }
    printf("\n");
}

int main() {
    //giving the values//
    int transactions[] = { 200, -150, -500, -400, -50, -200, 300}; //positive for deposit and negative for withdraw//
    int num_transactions = sizeof(transactions) / sizeof(transactions[0]);


    process_transactions(transactions, num_transactions);

    return 0;
}
