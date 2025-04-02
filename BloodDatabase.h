
#ifndef BLOODDATABASE_H
#define BLOODDATABASE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Donor.h"
#include <curl/curl.h>

using namespace std;

class BloodDatabase {
private:
    const string fileName = "data.txt";
    vector<Donor> donors;
    static void displayProvinces();

public:
    static void clearConsole();
    static void waitForKeyPress();
    static long long getValidatedInput(const string& prompt);
    bool validatePhoneNumber(const std::string& phoneNumber);
    void getDonorDetails();
    void writeDataToFile();
    void searchAndDisplay() const;
    void deleteDonor(const string& donorName);
    void displayAllDonations() const;
    void generateIndicators() const;
};

#endif // BLOODDATABASE_H
