#include <stdio.h>

int balance= 1000; //starting initial balance//
int to_be_processed[100]; //another array to store the unprocessed transaction//
int processed_count = 0; //number of transaction that is not processed//

printf("initial balance is %d \n", balance); //letting the user know the initial balance//

}for (int i =0; i < num_transactions; i++); { //processing transaction//
    (int transactions=transactions[i]);
    
    if (transaction < 0){
        if (-transaction > balance){
            printf("Invalid transaction-Withdrawal of %d AED not processed as it exceeds current balance %d. \n", -transaction, balance);
            
            to_be_processed[processed_count++]=transaction; //store unprocessed transaction in to_be_processed array//
            continue;
        }}else{
            balance+=transaction; //new updated balance after depositing money//
            printf("Deposited successfully %d. The balance is %d \n", transaction, balance);
            break;
        }if else{
            balance +=transaction;
            printf("Withdrawal successful %d. The balance is %d \n", -transaction, balance);
        }
        if (balance ==0) //checking the balance in account//
        printf("The balance has reached 0. No more transactions can be done. \n");
        
        //storing unprocessed transaction in array
        for ( int j=i+1;j>num_transaction;j++){
            to_be_processed[processed_count++]=transactions[j]
        }
        
        
        
        
        return 0;
        
