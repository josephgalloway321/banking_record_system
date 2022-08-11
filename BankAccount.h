// Specification of class

#ifndef PROJECTS_BANKACCOUNT_H
#define PROJECTS_BANKACCOUNT_H

#include <iostream>
#include <vector>

class BankAccount {
private:
    std::string Name;
    //std::string Username;
    //std::string Password;    // Future: Make log in process more secure with username and password
    double Balance;

public:
    /*
 * *************************************************************************************************************
 * The methods below focus on what the users can do once they log in to their respective account
 * *************************************************************************************************************
 */
    void user_menu(std::vector<BankAccount>&);
    void deposit();
    void auto_deposit(double user_deposit);    // Used by upload_accounts function and transfer_to_another_user method to bypass correspondence with user in deposit() method
    void withdraw();
    double get_user_balance() const;
    std::string get_user_name() const;
    bool transfer_to_another_user(std::vector<BankAccount>&);
    static double input_precision_check(double user_input);        // Make sure user_input is to only two decimals

    // Constructor
    BankAccount(std::string name){
        Name = name;
        Balance = 0;
    }
};

/*
 * *************************************************************************************************************
 * The functions below focus on what users can do with their accounts
 * *************************************************************************************************************
 */
void new_bank_account(std::vector<BankAccount>&);    // Creates a new account for a user then stores in vector
void remove_bank_account(std::vector<BankAccount>&);    // Removes a user's account
void show_all_bank_accounts(const std::vector<BankAccount>&);    // Print the information for all bank account users
bool valid_login(const std::vector<BankAccount>&, const std::string&);    // Check if the login entered belongs to an account
void main_menu(std::vector<BankAccount>&);    // Starting menu for users to create, delete, or log in to their accounts
bool save_accounts(std::vector<BankAccount>&, const std::string&);    // Save all accounts to a txt file (End of program)
void upload_accounts(std::vector<BankAccount>&, const std::string&);    // Upload all saved account information to all_bank_accounts vector (Beginning of program)
#endif //PROJECTS_BANKACCOUNT_H
