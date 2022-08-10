// Implementation of class

#include <fstream>    // Used to read/write to a txt file
#include <limits>    // Used to handle invalid input std::cin
#include "BankAccount.h"

// TODO: Prevent users from creating an account with a name already used
// TODO: Prevent users from depositing or withdrawing past two decimals

/*
 * *************************************************************************************************************
 * The methods below focus on what the users can do once they log in to their respective account
 * *************************************************************************************************************
 */
void BankAccount::user_menu(std::vector<BankAccount>& all_bank_accounts){
    // Show user a menu to choose an option
    bool return_to_user_menu {true};    // Use for options that need to return the user to the User Menu

    do{
        return_to_user_menu = true;
        int user_choice {};
        std::cout << "\n___User_Menu___" << std::endl;
        std::cout << "Please choose an option" << std::endl;
        std::cout << "1: Deposit\n"
                     "2: Withdraw\n"
                     "3: Check Balance\n"
                     "4: Transfer to Another User\n"
                     "5: Return to Main Menu\n"
                     "Choice: ";
        std::cin >> user_choice;

        // When input is an int, std::cin is 1, true; other types will return 0, false
        if (!std::cin){
            // Input is NOT an int
            std::cin.clear(); //clear bad input flag if user doesn't input an int
            // Remove the bad input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Invalid input. Please enter an integer." << std::endl;
            // Will return to user menu
        }
        else{
            // Input is an int, continue
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (user_choice == 1){
                deposit();
                // Will return to user menu
            }
            else if (user_choice == 2){
                withdraw();
                // Will return to user menu
            }
            else if (user_choice == 3){
                std::cout << "Account: " << Name << std::endl;
                std::cout << "Balance: $" << get_user_balance() << std::endl;
                // Will return to user menu
            }
            else if (user_choice == 4){
                bool transfer_status;
                transfer_status = transfer_to_another_user(all_bank_accounts);
                if (transfer_status){
                    std::cout << "Transfer successful." << std::endl;
                }
                else{
                    std::cout << "Transfer Failed." << std::endl;
                }
                // Will return to user menu
            }
            else if (user_choice == 5){
                std::cout << "Returning to Main Menu" << std::endl;
                std::cout << std::endl;
                return_to_user_menu = false;
                // Will NOT return to user menu
            }
            else{
                std::cout << "Error: Invalid choice. Please enter a valid option." << std::endl;
                // Will return to user menu
            }
        }
    }
    while (return_to_user_menu);
}

void BankAccount::deposit(){
    double user_deposit {};
    std::cout << "How much would you like to deposit? $";
    std::cin >> user_deposit;

    // When input is an int or double, std::cin is 1, true; other types will return 0, false
    if (!std::cin){
        // Input is NOT an int or double
        std::cin.clear(); //clear bad input flag if user doesn't input an int
        // Remove the bad input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input. Please enter an integer or double." << std::endl;
        // Will return to user menu
    }
    else{
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (user_deposit < 0.0){
            // Prevent depositing a negative number
            std::cout << "Error: Negative number entered. Cannot deposit $" << user_deposit << std::endl;
            std::cout << "Please try again." << std::endl;
        }
        else{
            Balance = Balance + user_deposit;
            std::cout << "Successfully deposited $" << user_deposit << std::endl;
        }
    }
}

void BankAccount::auto_deposit(double user_deposit){
    // This method is the same as deposit but does not include correspondence with user
    Balance = Balance + user_deposit;
}

void BankAccount::withdraw(){
    double user_withdraw {};
    std::cout << "How much would you like to withdraw? $";
    std::cin >> user_withdraw;

    // When input is an int or double, std::cin is 1, true; other types will return 0, false
    if (!std::cin){
        // Input is NOT an int or a double
        std::cin.clear(); //clear bad input flag if user doesn't input an int
        // Remove the bad input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input. Please enter an integer or double." << std::endl;
        // Will return to user menu
    }
    else{
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (Balance - user_withdraw < 0.0){
            // Prevent withdrawing more than what is in the account
            std::cout << "Error: Insufficient Funds. Cannot withdraw $" << user_withdraw << std::endl;
            std::cout << "Please try again." << std::endl;
        }
        else if (user_withdraw < 0.0){
            // Prevent withdrawing a negative number
            std::cout << "Error: Negative number entered. Cannot withdraw $" << user_withdraw << std::endl;
            std::cout << "Please try again." << std::endl;
        }
        else{
            Balance = Balance - user_withdraw;
            std::cout << "Withdrawal of $" << user_withdraw << " successful." << std::endl;
        }
    }
}

double BankAccount::get_user_balance() const{
    return Balance;
}

std::string BankAccount::get_user_name() const{
    return Name;
}

bool BankAccount::transfer_to_another_user(std::vector<BankAccount>& all_bank_accounts){
    std::string transfer_to_name {};
    double transfer_balance {0.0};
    bool transfer_status {false};    // Assume the transfer will fail

    std::cout << "What is the name on the account that you want to transfer to? ";
    getline(std::cin, transfer_to_name);

    // Not needed for string input
    //std::cin.clear();
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Verify name of account to transfer to
    unsigned int vector_size = all_bank_accounts.size();    // Size of vector does not change, so just call the size once
    for (unsigned int i = 0; i < vector_size; i++){    // Loop through vector of bank accounts to find requested name
        if (all_bank_accounts[i].get_user_name() == transfer_to_name){
            // The account exists, so continue transfer process
            std:: cout << "How much would you like to transfer? $";
            std::cin >> transfer_balance;

            // When input is an int or double, std::cin is 1, true; other types will return 0, false
            if (!std::cin){
                // Input is NOT an int or a double
                std::cin.clear(); //clear bad input flag if user doesn't input an int
                // Remove the bad input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Invalid input. Please enter an integer or double." << std::endl;
                return transfer_status;
                // Will return to user menu (Failed)
            }
            else{
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Check to see if user can transfer the requested amount to another user
                if (Balance - transfer_balance < 0.0){
                    std::cout << "Error: Insufficient Funds. Cannot transfer $" << transfer_balance << std::endl;
                    return transfer_status;
                    // Will return to user menu (Failed)
                }
                else{
                    Balance = Balance - transfer_balance;    // Remove money from current user's account
                    std::cout << "Successfully deposited $" << transfer_balance << std::endl;

                    // Deposit transfer balance to other user's account
                    all_bank_accounts[i].auto_deposit(transfer_balance);
                    transfer_status = true;
                    return transfer_status;
                    // Will return to user menu (Success)
                }
            }
        }
    }
    std::cout << "The account for " << transfer_to_name << " does not exist." << std::endl;
    return transfer_status;
    // Will return to user menu (Failed)
}

/*
 * *************************************************************************************************************
 * The functions below focus on what users can do with their accounts
 * *************************************************************************************************************
 */
void new_bank_account(std::vector<BankAccount>& all_bank_accounts){
    std::string input_name;

    std::cout << "We are excited you want to create an account with us!\nPlease begin by entering your name: ";
    getline(std::cin, input_name);

    // Not needed for string input
    //std::cin.clear();
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    BankAccount user(input_name);    // Create the bank account object for this user
    all_bank_accounts.push_back(user);    // Store a copy of the object in the all_bank_accounts vector because the original will be erased at the end of this scope
    std::cout << "Account created for " << input_name << std::endl;
    std::cout << std::endl;
}

void remove_bank_account(std::vector<BankAccount>& all_bank_accounts){
    std::string input_name;

    std::cout << "What is the name on the account that you wish to remove? ";
    getline(std::cin, input_name);

    // Not needed for string input
    //std::cin.clear();
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    unsigned int vector_size = all_bank_accounts.size();    // Size of vector does not change, so just call the size once
    for (unsigned int i = 0; i < vector_size; i++){    // Loop through all accounts in all_bank_accounts vector
        if (all_bank_accounts[i].get_user_name() == input_name){
            all_bank_accounts.erase(all_bank_accounts.begin()+ i);    // Erase user's bank account in vector
            std::cout << input_name << "'s Account Removed." << std::endl;
            std::cout << std::endl;
        }
    }
}

void show_all_bank_accounts(const std::vector<BankAccount>& all_bank_accounts){
    unsigned int vector_size = all_bank_accounts.size();    // Size of vector does not change, so just call the size once

    for (unsigned int i = 0; i < vector_size; i++){
        std::cout << "User: " << all_bank_accounts[i].get_user_name() << std::endl;
        std::cout << "Balance: $" << all_bank_accounts[i].get_user_balance() << std::endl;
        std::cout << std::endl;
    }
}

bool valid_login(const std::vector<BankAccount>& all_bank_accounts, const std::string& user_input){
    unsigned int vector_size = all_bank_accounts.size();    // Size of vector does not change, so just call the size once

    for (unsigned int i = 0; i < vector_size; i++){
        if (all_bank_accounts[i].get_user_name() == user_input){
            return true;
        }
    }
    return false;    // Did not find login in vector of bank accounts
}

void main_menu(std::vector<BankAccount>& all_bank_accounts){
    // Begin Main Menu
    // Log in, Create a new account, delete an account, or exit bank
    bool return_to_main_menu {true};
    int user_choice {};

    do{
        std::cout << "___Main_Menu___" << std::endl;
        std::cout << "1: Log In\n"
                     "2: Create A New Account\n"
                     "3: Delete an Account\n"
                     "4: Quit\n"
                     "Choice: ";
        std::cin >> user_choice;

        // When input is an int, std::cin is 1, true; other types will return 0, false
        if (!std::cin){
            // Input is NOT an int
            std::cin.clear(); //clear bad input flag if user doesn't input an int
            // Remove the bad input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Invalid input. Please enter an integer." << std::endl;
            // Will return to user menu
        }
        else{
            //std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (user_choice == 1){
                // If the bank account vector is empty, then return to main menu
                if (all_bank_accounts.empty()){
                    std::cout << "Error: There are currently no bank accounts. Please create an account.\n" << std::endl;
                    // Will return to main menu
                }
                else{
                    // Log in using login
                    std::string user_input {};
                    bool is_login_valid {false};    // Assume login is incorrect for security

                    std::cout << "Please enter the name associated with your account: ";
                    getline(std::cin, user_input);

                    // Not needed for string input
                    //std::cin.clear();
                    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // Check if name is in the system
                    is_login_valid = valid_login(all_bank_accounts, user_input);
                    if (is_login_valid){
                        // Move into user menu for this specific user
                        std::cout << "Log in Successful." << std::endl;

                        unsigned int vector_size = all_bank_accounts.size();    // Size of vector does not change, so just call the size once
                        for (unsigned int i = 0; i < vector_size; i++){
                            if (all_bank_accounts[i].get_user_name() == user_input){    // Find the account that matches the login
                                all_bank_accounts[i].user_menu(all_bank_accounts);    // Go to user menu
                                // Will return to main menu after exiting user menu
                            }
                        }
                    }
                    else{
                        std::cout << "Error: Invalid login. There is no account with that name." << std::endl;
                        std::cout << std::endl;
                        // Will return to main menu
                    }
                }
            }
            else if (user_choice == 2){
                // Create new bank account
                new_bank_account(all_bank_accounts);    // Pass in vector of all bank accounts to store new bank account object
                // Will return to main menu
            }
            else if (user_choice == 3){
                // If the bank account vector is empty, then return to main menu
                if (all_bank_accounts.empty()){
                    std::cout << "Error: There are currently no bank accounts. Please create an account.\n" << std::endl;
                }
                else{
                    // Delete a bank account
                    remove_bank_account(all_bank_accounts);    // Pass in vector of all bank accounts to remove user's bank account object
                    // Will return to main menu
                }
            }
            else if (user_choice == 4){
                // Quit the program
                std::cout << "Have a nice day!" << std::endl;
                return_to_main_menu = false;
            }
                /*
                else if (user_choice == 5){
                    // Display all the accounts
                    // ONLY USED FOR DEBUGGING
                    show_all_bank_accounts(all_bank_accounts);
                }
                 */
            else{
                std::cout << "Error: Invalid choice. Please try again." << std::endl;
            }
        }
        std::cout << std::endl;
    }
    while(return_to_main_menu);
}

bool save_accounts(std::vector<BankAccount>& all_bank_accounts, const std::string& defaultDirectory){
    // Variable name of txt file; used to write all bank account information at the end of the program
    std::fstream loginFile;

    std::string line;    // Variable to hold line that the program is currently on
    // Overwrite txt file with updated information from all accounts in all_bank_accounts vector
    loginFile.open(defaultDirectory + "login_file.txt", std::ios::out | std::ios::trunc);
    unsigned int vector_size = all_bank_accounts.size();    // Size of vector does not change, so just call the size once
    if (loginFile.is_open()){
        for (unsigned int i = 0; i < vector_size; i++){
            // Write user information to login_file.txt
            loginFile << all_bank_accounts[i].get_user_name() << std::endl;
            loginFile << all_bank_accounts[i].get_user_balance() << std::endl;
        }
        loginFile.close();
        return true;
    }
    else{
        std::cout << "Error: Login file could not be opened." << std::endl;
        return false;
    }
}

void upload_accounts(std::vector<BankAccount>& all_bank_accounts, const std::string& defaultDirectory){
    // Variable name of txt file; used to read then store all bank account information to all_bank_accounts vector
    // at the beginning of the program
    std::fstream loginFile;

    std::string line_name;    // Variable to hold line that the program is currently on
    std::string line_balance;
    loginFile.open(defaultDirectory + "login_file.txt", std::ios::in);    // Read txt file and record all data to all_bank_accounts vector
    if (loginFile.is_open()){
        while(getline(loginFile, line_name)) {    // Loop through txt file until there is a blank line
            BankAccount user(line_name);    // Create an object with the name on this line

            getline(loginFile, line_balance);    // Get the balance for this account (Line after the user's name)
            user.BankAccount::auto_deposit(std::stod(line_balance));    // Update the balance for this account
            all_bank_accounts.emplace_back(user);    // Copy object to vector because the current object will be deleted after exiting the scope
        }
        loginFile.close();
    }
    else{
        // std::cout << "Log in file does not exist." << std::endl;
        // No worries if there is no login_file.txt at the beginning of the program.
        // Program will create file and save all account information at the end of the program.
    }
}