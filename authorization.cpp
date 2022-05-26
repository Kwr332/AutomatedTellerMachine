#include <iostream>
#include <fstream>
#include <string>
#include "Header.hpp"
#include <conio.h>

//logowanie i rejestracja
bool login(std::string username, std::string password) {
    std::string userN, passW; //logowanie z pliku tekstowego
    std::ifstream read("accounts/data_" + username + ".txt");
    std::getline(read, userN);
    std::getline(read, passW);

    if (username == userN && password == passW) //sprawdzenie zgodznosci nicku i hasla
    {
        return true;
    }
    else return false;
}
void registration() {
    std::string username, password, passCheck;
    
    system("cls");
    std::cout << "\t***ATM***\n\n";
    std::cout << "Enter username you will use: \n";
    std::cin >> username;
    std::cout << "Enter password you will use: \n";
    std::cin >> password;
    std::cout << "Enter your password again: \n";
    std::cin >> passCheck;
    if (password == passCheck)
    {
        std::ofstream account; //zapis danych do specjalnego pliku tekstowego.
        account.open("accounts/data_" + username + ".txt", std::ios::out);
        account << username << std::endl << password << std::endl << 0;
        account.close();
        std::cout << "You have registered successfully!\nPlease deposit money to your account!"; _getch();
    }
    else
    {
        std::cout << "Your passwords don't match, try again! \n";
    }

}