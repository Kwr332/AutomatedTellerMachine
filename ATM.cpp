#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include "Header.hpp"
#include<stdio.h>

void logInMenu(); //funkcja wypisująca menu przed zalogowaniem
void atmMenu(); //funkcja wypisująca menu po zalogowaniu
double getBalance(std::string username); //Pokazuje obecny balans konta z pliku txt(po zalogowaniu)
void withdrawMoney(std::string username, std::string password, double withdraw); 
void depositMoney(std::string username, std::string password, double deposit);//Pozwala na wyplacanie pieniedzy z pliku
std::string getFileName(std::string username); //funkcja zwracajaca nazwe pliku txt z danymi o koncie
void deleteLine(std::string username); //funkcja usuwajaca ostatnia linie w pliku


int main()
{
    while (true)
    {
        int option;
        logInMenu();
        option = _getch();
        if (option == '1')
        {
            std::string username, password;
            system("cls");
            std::cout << "\t***ATM***\n\n";
            std::cout << "Enter your username:\n";
            std::cin >> username;
            std::cout << "Enter your PIN: \n";
            std::cin >> password;
            if (login(username, password)) //logowanie
            {
                do
                {
                    atmMenu();
                    option = _getch();
                    switch (option) //wybranie opcji
                    {
                    case '1':  //sprawdzenie balansu
                        std::cout << "Your balance: " << getBalance(username); _getch(); break; 
                    case '2': //wyplata pieniedzy
                        double withdraw;
                        std::cout << "Enter the amount you want to withdraw: ";
                        std::cin >> withdraw;
                        if (getBalance(username) >= withdraw)
                        {
                            std::cout << "You have successfully withdrawn: " << withdraw << std::endl;
                            withdrawMoney(username, password, withdraw);
                            std::cout << "Your new balance: " << getBalance(username) << std::endl; _getch(); break;
                        }
                        else std::cout << "You don't have enough money to to that!\n"; _getch(); break;
                    case '3': //wplata pieniedzy
                        double deposit;
                        std::cout << "Enter the amount you want to deposit: ";
                        std::cin >> deposit;
                        depositMoney(username, password, deposit);
                        std::cout << "Your new balance: " << getBalance(username) << std::endl; _getch(); break;
                    }
                } while (option != '4'); //while sprawdzajacy, czy klient nie chce zamknac aplikacji


            }
            else std::cout << "Your username or password are wrong! Try again!"; _getch();
        }
        else if (option == '2') //rejestracja
        {
            registration();
        }
        else if (option == '3') return 0; //while sprawdzajacy, czy klient nie chce zamknac aplikacji
    }
}

void logInMenu() {
    system("cls");
    std::cout << "\n\t***ATM***\n\n";
    std::cout << "*********\n";
    std::cout << "[1]Login\n";
    std::cout << "[2]Register\n";
    std::cout << "[3]Exit\n";
    std::cout << "*********\n";
}
void atmMenu() {
    system("cls");
    std::cout << "\t***ATM***\n\n";
    std::cout << "*********\n";
    std::cout << "[1]Check balance\n";
    std::cout << "[2]Withdraw money\n";
    std::cout << "[3]Deposit money\n";
    std::cout << "[4]log out\n";
    std::cout << "*********\n";
}
double getBalance(std::string username) {
    std::string ignore, stringBalance;
    double balance;

    std::ifstream read(getFileName(username)); //odczytnie balansu z pliku txt.
    std::getline(read, ignore);
    std::getline(read, ignore);
    std::getline(read, stringBalance);
    balance = std::stod(stringBalance); //konwercja z stringa na double
    return balance;
}
void withdrawMoney(std::string username, std::string password, double withdraw) {
    std::ofstream account;
    double balance;
    balance = getBalance(username);
    deleteLine(username); //usuniecie poprzedniego balansu
    account.open(getFileName(username), std::ios::app);
    account << balance - withdraw; //dopisanie nowego balansu
    account.close();
}
void depositMoney(std::string username, std::string password, double deposit){
    std::ofstream account;
    double balance;
    balance = getBalance(username);
    deleteLine(username); //usuniecie poprzedniego balansu
    account.open(getFileName(username), std::ios::app);
    account << balance + deposit; //dopisanie nowego balansu
    account.close();
}
std::string getFileName(std::string username) {
    std::string fileName = "accounts/data_" + username + ".txt";
    return fileName;
}
void deleteLine(std::string username)
{
    std::fstream acc;
    std::fstream temp;

    acc.open((getFileName(username)), std::ios::in); //otworzenie pliku z danymi o koncie i pliku temp
    temp.open("temp.txt", std::ios::out);
    char usernameTemp[64];
    char passwordTemp[64];
    acc.getline(usernameTemp, 64); //przepisanie nazwy uzytkownika i hasla z pliku oryginalnego do temp
    acc.getline(passwordTemp, 64);
    temp << usernameTemp << std::endl << passwordTemp << std::endl;
    temp.close();
    acc.close();

    acc.open(getFileName(username), std::ios::out); //ponowne otwarcie pliku z danymi i temp, tym razem z odwrocnymi wartosciami
    temp.open("temp.txt", std::ios::in);
    temp.getline(usernameTemp, 64);
    temp.getline(passwordTemp, 64);
    acc << usernameTemp << std::endl << passwordTemp << '\n';
    
    temp.close();
    acc.close();
    const char* file[80] = { getFileName(username).c_str() }; //konwersja z string na const char*
    remove(*file); //usuniecie pliku oryginalnego
    rename("temp.txt", *file); //zmiana nazwy pliku temp na plik oryginalny
}