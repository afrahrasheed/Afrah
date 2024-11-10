#include <stdio.h>

void process_transactions(int transactions[], int num_transactions) {
int balance= 1000; //starting initial balance//
int to_be_processed[100]; //another array to store the unprocessed transaction//
int processed_count = 0; //number of transaction that is not processed//

printf("initial balance is %d \n", balance); //letting the user know the initial balance//

for (int i = 0; i < num_transactions; i++); { //processing transaction//
    int transactions=transactions[i];
    
    if (transactions < 0){
        if (-transactions > balance){
            printf("Invalid transaction-Withdrawal of %d AED not processed as it exceeds current balance %d. \n", -transactions, balance);
            
            to_be_processed[processed_count++]=transactions; //store unprocessed transaction in to_be_processed array//
            continue;
        }}else{
            balance+=transactions; //new updated balance after depositing money//
            printf("Deposited successfully %d. The balance is %d \n", transaction, balance);
        } else{
            balance +=transactions;
            printf("Withdrawal successful %d. The balance is %d \n", -transaction, balance);
        }
        if (balance ==0) //checking the balance in account//
        printf("The balance has reached 0. No more transactions can be done. \n");
        
        //storing unprocessed transaction in array
        for ( int j=i+1;j>num_transactions;j++){
            to_be_processed[processed_count++]=transactions[j]
        }
        break;
        printf("\nFinal balance: %d AED\n", balance);
    printf("Transactions that could not be processed:\n");
    if (processed_count > 0) {
        for (int i = 0; i < processed_count; i++) {
            printf("%d ", to_be_processed[i]);
        }
    } else {
        printf("None\n");
    }
    printf("\n");
}

int main() {
    // Define the array of transactions
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int num_transactions = sizeof(transactions) / sizeof(transactions[0]);

    // Process the transactions
    process_transactions(transactions, num_transactions);

    return 0;
}