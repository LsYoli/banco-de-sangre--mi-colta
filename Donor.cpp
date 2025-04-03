/**
* @file Donor.cpp
* @brief Declaracion de los métodos de la clase Donor para la gestión de datos de donantes de sangre, limpia y organiza los datos antes de ser pasados al archivo txt.
*
* @details 
* - Se importan las librerías necesarias para la manipulación de cadenas y entrada/salida.
* - Se define la clase Donor, encargada de representar a un donante con sus respectivos atributos.
* - Se implementa "donorDetails()" para mostrar la información de un donante en consola.
* - Se desarrolla "parseLine()" para convertir una línea de texto en un objeto Donor.
* - Se implementa "trim()" para eliminar espacios en blanco al inicio y final de una cadena, asegurando datos limpios.
*
* @bug_fixer [Daniel Andres Micolta Gongora]
* @bug_fixer [Luis Santiago Arenas Hincapie]
* @mail [luis.arenas@correounivalle.edu.co]
* @mail [micolta.daniel@correounivalle.edu.co]
* @date 2025-05-03
* @version 1.1
*
* @comentario: N/N
*/

#include "Donor.h"
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

void Donor::donorDetails() const {
    cout << "Nombre del donante: " << name << endl;
    cout << "Distrito del donante: " << district << endl;
    cout << "Tipo de sangre del donante: " << bloodType << endl;
}

Donor Donor::parseLine(const string& line) {
    Donor d;
    stringstream ss(line);
    string token;

    getline(ss, token, ','); d.donorId = stoi(trim(token));
    getline(ss, token, ','); d.name = trim(token);
    getline(ss, token, ','); d.address = trim(token);
    getline(ss, token, ','); d.district = stoi(trim(token));
    getline(ss, token, ','); d.bloodType = trim(token);
    getline(ss, token, ','); d.number = stoll(trim(token));

    return d;
}

string Donor::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
