/**
* @file main.cpp
* @brief El programa principal que se encarga de ejecutar los metodos de BloodDataBase.
*
* @details 
* - Se importan las librerias necesarias para el funcionamiento del programa.
* - Se importan los archivos .h de las clases BloodDataBase y Donor.
* - Se inicializan los objetos "donorName" y "database".
* - Se crea una variable llamada choice para el manejo del menu.
* - Se crea un ciclo while para el funcionamiento del menu haciendo el uso de swith case.
* 
* @bug_fixer [Daniel Andres Micolta Gongora]
* @mail [micolta.daniel@correounivalle.edu.co]
* @date 2025-05-03
* @version 1.1
*
* @comentario: N/N
*/
#include "BloodDatabase.h"
#include "Donor.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main() {
    string donorName;
    BloodDatabase database;
    int choice;

    while (true) {
        BloodDatabase::clearConsole();

        cout <<
             " ░█████╗░██████╗░██╗░░░██╗███████╗  ██████╗░░█████╗░░░░░░██╗░█████╗░\n"
             " ██╔══██╗██╔══██╗██║░░░██║╚════██║  ██╔══██╗██╔══██╗░░░░░██║██╔══██╗\n"
             " ██║░░╚═╝██████╔╝██║░░░██║░░███╔═╝  ██████╔╝██║░░██║░░░░░██║███████║\n"
             " ██║░░██╗██╔══██╗██║░░░██║██╔══╝░░  ██╔══██╗██║░░██║██╗░░██║██╔══██║\n"
             " ╚█████╔╝██║░░██║╚██████╔╝███████╗  ██║░░██║╚█████╔╝╚█████╔╝██║░░██║\n"
             " ░╚════╝░╚═╝░░╚═╝░╚═════╝░╚══════╝  ╚═╝░░╚═╝░╚════╝░░╚════╝░╚═╝░░╚═╝\n";

        cout << "1. Registrar donante\n";
        cout << "2. Buscar donante\n";
        cout << "3. Eliminar donante\n";
        cout << "4. Ver historial de donaciones\n";
        cout << "5. Generar indicadores\n";
        cout << "6. Salir\n";
        cout << "Ingrese su elección: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descartar cualquier entrada extra

        switch (choice) {
        case 1:
            database.getDonorDetails();
            database.writeDataToFile();
            break;
        case 2:
            database.searchAndDisplay();
            break;
        case 3:
            cout << "Ingrese el nombre del donante a eliminar: ";
            getline(cin, donorName);
            database.deleteDonor(donorName);
            BloodDatabase::waitForKeyPress();
            break;
        case 4:
            database.displayAllDonations();
            break;

        case 5:
            database.generateIndicators();
            BloodDatabase::waitForKeyPress();
            break;
        case 6:
            cout << "Gracias por usar el Sistema de la Cruz Roja" << endl;
            return 0;
        default:
            cout << "Opción no válida. Inténtalo de nuevo.\n";
            BloodDatabase::waitForKeyPress();
            break;
        }
    }
}

