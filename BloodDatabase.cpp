/**
* @file BloodDatabase.cpp
* @brief Declaracion de los métodos de la clase BloodDatabase para la gestión de donantes de sangre.
*

* @details 
* - Se importan las librerías necesarias para la manipulación de archivos, entrada/salida y validaciones.
* - Se define la clase BloodDatabase, que maneja el registro, búsqueda, eliminación y visualización de donantes.
* - Se implementa el método displayProvinces() para mostrar los departamentos disponibles.
* - Se incluyen métodos auxiliares como "clearConsole()"" y "waitForKeyPress()"" para mejorar la experiencia del usuario.
* - Se implementa "getValidatedInput()" para garantizar que las entradas numericas sean correctas.
* - Se desarrolla "getDonorDetails()" para registrar nuevos donantes con información validada.
* - Se implementa "writeDataToFile()" para almacenar la información de los donantes en el archivo "data.txt".
* - Se programa "searchAndDisplay()" para buscar y mostrar donantes filtrando por departamento, dirección y tipo de sangre.
* - Se implementa "deleteDonor()" para eliminar un donante específico después de la confirmación del usuario.
* - Se incluye "displayAllDonations()" para mostrar el historial completo de donaciones almacenadas.
*
* @bug_fixer [Daniel Andres Micolta Gongora]
* @mail [micolta.daniel@correounivalle.edu.co]
* @date 2025-13-03
* @version 1.2
* /CAMBIOS/ - Se elimino el uso de "std::" para un codigo visiblemente mas limpio y legible.
*
*           - Se agrego una validacion la funcion "getValidatedInput()" para asegurar que el valor ingresado en el ID de la persona registrada sea un numero entero positivo.
*
*           - Se agrego una prevencion de acceso en el metodo "deleteDonor()" para evitar que el programa continue apesar de que no se haya podido crear el archivo temporal.
*            
*           - Se agrego la libreria <map>, usada para el corrrecto funcionamiento de la funcion generateIndicators()
*
* @comentario: Para crear el metodo displayAllDonations() tuve que usar como apoyo la IA de ChatGPT, ya que despues de varios intentos de
* prueba y error no pude encontrar la manera de hacerlo.
*/

// =================== PUNTO 5: FUNCIONES REUTILIZABLES ===================

// Esta función elimina los espacios al principio y final de un texto.
// Es útil cuando el usuario escribe por error espacios de más.
/*std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";  // Si solo había espacios
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Esta función solicita un número, valida que sea numérico y mayor que 0.
// Se usa para ingresar datos como ID o número de teléfono del donante.
long long getValidatedInput(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        input = trim(input); // Se limpia la entrada del usuario

        try {
            long long value = std::stoll(input); // Convierte texto a número
            if (value <= 0) throw std::invalid_argument("Debe ser positivo");
            return value;
        } catch (...) {
            std::cout << "Entrada inválida. Intente de nuevo." << std::endl;
        }
    }
}*/


#include "BloodDatabase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <map>
#include "Donor.h"
#include <curl/curl.h>

using namespace std;


static string toLowerCase(const string &s) { //FUNCION AUXILIAR PARA CONVERTIR A MINUSCULAS
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void BloodDatabase::displayProvinces() {
    cout << "Elige el departamento:\n";
    cout << "1. Putumayo\n";
    cout << "2. Cauca\n";
    cout << "3. Valle del Cauca\n";
    cout << "4. Amazonas\n";
    cout << "5. Risaralda\n";
    cout << "6. Antioquia\n";
    cout << "7. Norte de Santander\n";
    cout << "8. Chocó\n";
    cout << "9. Arauca\n";
    cout << "10. Guainía\n";
}

void BloodDatabase::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    //   system("clear");
#endif
}

void BloodDatabase::waitForKeyPress() {
    cout << "Presiona cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

long long BloodDatabase::getValidatedInput(const string& prompt) {
    long long value;
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            if (!all_of(input.begin(), input.end(), ::isdigit)) {
                throw invalid_argument("La entrada contiene caracteres no numéricos");
            }
            value = stoll(input);
            if(value < 0)
            {
                throw invalid_argument("Numero de ID invalido, la entrada debe ser positiva");
            }
            break; // si la conversión es exitosa, salir del bucle
        } catch (const invalid_argument& e) {
            cout << "Entrada no válida: " << e.what() << ". Por favor ingrese un número válido." << endl;
        } catch (const out_of_range&) {
            cout << "Entrada fuera de rango. Por favor ingrese un número válido." << endl;
        }
    }
    return value;
}

//CODIGO INTEGRACION API
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

bool BloodDatabase::validatePhoneNumber(const string& phoneNumber) {
    CURL* curl;
    CURLcode res;
    string readBuffer;
    string url = "https://phone-validator-api.p.rapidapi.com/metadata?phone=" + phoneNumber;

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: beed517a78msha7767f75bf3d8d5p1e04b4jsn6981f02d9338");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: phone-validator-api.p.rapidapi.com");

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        return readBuffer.find("\"valid\":true") != string::npos;
    }
    return false;
}

void BloodDatabase::getDonorDetails() {
    clearConsole();
    cout << "Ingrese los detalles del donante\n";

    Donor newDonor;
    newDonor.setDonorId(getValidatedInput("Id: "));

    cout << "Nombre: ";
    string tempName;
    getline(cin, tempName);
    newDonor.setName(toLowerCase(tempName));

    cout << "Dirección: ";
    string tempAddr;
    getline(cin, tempAddr);
    newDonor.setAddress(toLowerCase(tempAddr));

    displayProvinces();
    newDonor.setDistrict(getValidatedInput("departamento (ingrese el número correspondiente): "));
    cout << "Seleccione el tipo de sangre:\n";
    cout << "1. O-\n";
    cout << "2. O+\n";
    cout << "3. A-\n";
    cout << "4. A+\n";
    cout << "5. B-\n";
    cout << "6. B+\n";
    cout << "7. AB-\n";
    cout << "8. AB+\n";
    cout << "Tipo de sangre(ingrese el tipo): ";
    string tempBloodType;
    getline(cin, tempBloodType);
    newDonor.setBloodType(toLowerCase(tempBloodType));

    string phoneNumber;
    cout << "Número: ";
    getline(cin, phoneNumber);

    bool valido = validatePhoneNumber(phoneNumber);
    if (!valido) {
    cout << "⚠️ Número inválido según la API, pero será guardado de todos modos.\n";
    }
    
    newDonor.setNumber(stoll(phoneNumber));

    donors.push_back(newDonor);
    clearConsole();
    cout << "\n¡Donante registrado exitosamente!\n" << endl;
    waitForKeyPress();
}

void BloodDatabase::writeDataToFile() {
    ofstream outfile(fileName, ios::app);
    /*La siguiente bloque de codigo es para verificar si el vector de los donantes realmente tiene algo antes de
    meter datos al archivo de texto*/
    if(donors.empty())
    {
        cout<<"\nNo hay donantes para registrar."<<endl;
        return;
    }
    if (!outfile) {
        cout << "Error al abrir el archivo para escribir." << endl;
        return;
    }

    Donor newDonor = donors.back();
    outfile << newDonor.getDonorId() << ",    " << newDonor.getName() << ",    " << newDonor.getAddress() << ",    " << newDonor.getDistrict() << ",    " << newDonor.getBloodType() << ",    " << newDonor.getNumber() << endl;

    outfile.close();
}

void BloodDatabase::searchAndDisplay() const {
    clearConsole();
    displayProvinces();
    int provinceName = getValidatedInput("Ingrese el número de la departamento: ");

    cout << "Ingrese la dirección (dejar en blanco para omitir): ";
    string addressFilter;
    getline(cin, addressFilter);
    addressFilter = toLowerCase(addressFilter);

    cout << "Ingrese el tipo de sangre (dejar en blanco para omitir): ";
    string bloodTypeFilter;
    getline(cin, bloodTypeFilter);
    bloodTypeFilter = toLowerCase(bloodTypeFilter);

    ifstream inFile(fileName);

    if (!inFile) {
        cout << "Error al abrir el archivo para leer." << endl;
        return;
    }

    vector<Donor> donors;
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        bool match = d.getDistrict() == provinceName &&
            (addressFilter.empty() || d.getAddress().find(addressFilter) != string::npos) &&
            (bloodTypeFilter.empty() || d.getBloodType() == bloodTypeFilter);

        if (match) {
            donors.push_back(d);
            found = true;
        }
    }

    if (!found) {
        cout << "No se encontraron personas de la departamento " << provinceName;
        if (!addressFilter.empty()) {
            cout << " con dirección que contiene '" << addressFilter << "'";
        }
        if (!bloodTypeFilter.empty()) {
            cout << " y tipo de sangre '" << bloodTypeFilter << "'";
        }
        cout << "." << endl;
    } else {
        cout << "Personas de la departamento " << provinceName;
        if (!addressFilter.empty()) {
            cout << " con dirección que contiene '" << addressFilter << "'";
        }
        if (!bloodTypeFilter.empty()) {
            cout << " y tipo de sangre '" << bloodTypeFilter << "'";
        }
        cout << ":" << endl;
        for (const auto& d : donors) {
            cout << "Nombre: " << d.getName() << endl;
            cout << "Dirección: " << d.getAddress() << endl;
            cout << "departamento: " << d.getDistrict() << endl;
            cout << "Tipo de sangre: " << d.getBloodType() << endl;
            cout << "Número de móvil: " << d.getNumber() << endl;
            cout << endl;
        }
    }

    inFile.close();
    waitForKeyPress();
}

void BloodDatabase::deleteDonor(const string& donorName) {

    string lowerDonorName = toLowerCase(donorName);
    ifstream inFile(fileName);
    ofstream tempFile("temp.txt");

    if (!inFile) {
        cerr << "Error al abrir el archivo " << fileName << endl;
        return;
    }

    if (!tempFile) {
        cerr << "Error al crear el archivo temporal" << endl;
        inFile.close();//Sale de la funcion en caso de que no se pueda crear el archivo temp.
        return;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        if (d.getName() == donorName) {
            found = true;
            cout << "Nombre: " << d.getName() << endl;
            cout << "Dirección: " << d.getAddress() << endl;
            cout << "Tipo de sangre: " << d.getBloodType() << endl;
            cout << "Número de móvil: " << d.getNumber() << endl;
            cout << endl;
            cout << "¿Está seguro de que desea eliminar al donante? [s/n]: ";
            char sureChoice;
            cin >> sureChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // descartar cualquier entrada extra

            if (sureChoice == 's' || sureChoice == 'S') {
                continue;
            }
        }

        tempFile << d.getDonorId() << ",    " << d.getName() << ",    " << d.getAddress() << ",    " << d.getDistrict() << ",    " << d.getBloodType() << ",    " << d.getNumber() << endl;
    }

    inFile.close();
    tempFile.close();

    if (remove(fileName.c_str()) != 0) {
        cerr << "Error al eliminar el archivo original" << endl;
        return;
    }

    if (rename("temp.txt", fileName.c_str()) != 0) {
        cerr << "Error al renombrar el archivo temporal" << endl;
        return;
    }

    if (!found) {
        cout << "No se encontró ningún donante con el nombre " << donorName << endl;
    }
}

void BloodDatabase::displayAllDonations() const {
    clearConsole();
    ifstream inFile(fileName);

    if (!inFile) {
        cout << "Error al abrir el archivo para leer." << endl;
        waitForKeyPress();
        return;
    }

    string line;
    bool hasRecords = false;

    cout << "=== HISTORIAL DE DONACIONES ===\n\n";

    while (getline(inFile, line)) {
        hasRecords = true;
        Donor d = Donor::parseLine(line);

        cout << "ID: " << d.getDonorId() << endl;
        cout << "Nombre: " << d.getName()<< endl;
        cout << "Dirección: " << d.getAddress() << endl;
        cout << "Departamento: " << d.getDistrict() << endl;
        cout << "Tipo de sangre: " << d.getBloodType() << endl;
        cout << "Número de móvil: " << d.getNumber() << endl;
        cout << "----------------------------------------\n";
    }

    if (!hasRecords) {
        cout << "No hay registros de donaciones en el sistema.\n";
    }

    inFile.close();
    waitForKeyPress();
}

void BloodDatabase::generateIndicators() const {
    ifstream inFile(fileName);
    if (!inFile) {
        cout << "Error al abrir el archivo para leer los indicadores." << endl;
        return;
    }
    map<string, int> bloodCount;
    string line;
    int totalRecords = 0;
    while (getline(inFile, line)) {
        try {
            Donor d = Donor::parseLine(line);
            if (!d.getBloodType().empty()) {
                bloodCount[d.getBloodType()]++;
                totalRecords++;
            }
        } catch (exception& e) {
            cout << "Error al procesar la línea: " << line << " (" << e.what() << ")" << endl;
        }
    }
    inFile.close();
    if (totalRecords == 0) {
        cout << "No hay registros para calcular indicadores." << endl;
        return;
    }
    cout << "Total de registros procesados: " << totalRecords << "\n";
    string mostCommonBlood;
    int maxCount = 0;
    for (const auto& pair : bloodCount) {
        double percentage = (pair.second * 100.0) / totalRecords;
        cout << "Tipo de sangre " << pair.first << ": " << pair.second 
             << " personas (" << percentage << "%)" << endl;
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostCommonBlood = pair.first;
        }
    }
    cout << "El tipo de sangre que predomina es: " << mostCommonBlood << "\n";
}


//CODIGO INTEGRACION DE API