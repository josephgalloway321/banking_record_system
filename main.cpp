/*
 * Author: Joseph D. Galloway II
 * This program is an interface for Happy Bank. A fictional bank that allows users to create/delete/login to their account, deposit
 * their money, withdraw their money, check their current balance, and transfer money to another user's account.
 * All the account data is read from and saved to a txt file at the start and end of the program.
 */

#include <iostream>
#include <vector>
#include "BankAccount.h"


int main(){
    std::vector<BankAccount> all_bank_accounts;    // Create vector to hold bank account information for each user

    // Below is the path in your computer that the txt file will save to
    // The txt file will read/record the account information for all users when the program begins
    // The txt file will store the account information for all users when the program is ending
    const std::string defaultDirectory = R"(C:\Users\Public\)";    // Feel free to edit path

    // Below is an example of the path I use
    //const std::string defaultDirectory = R"(C:\Users\josep\CLionProjects\projects\banking_record_system\)";

    // Record all data from txt file to all_bank_accounts vector
    upload_accounts(all_bank_accounts, defaultDirectory);

    // Begin main menu
    std::cout << "Welcome to Happy Bank!\n Please choose an option from the Main Menu to get started.\n";
    main_menu(all_bank_accounts);    // Pass in the all_bank_accounts vector for transfer_to_another_user method

    // Save data from all accounts to txt file before closing program
    bool saved_successfully {};
    saved_successfully = save_accounts(all_bank_accounts, defaultDirectory);
    if (saved_successfully){
        std::cout << "Accounts saved successfully." << std::endl;
    }
    else{
        std::cout << "Error: Could not save accounts. Please record data and contact technical support." << std::endl;
        show_all_bank_accounts(all_bank_accounts);
    }
    std::cout << "Ending program." << std::endl;
}


