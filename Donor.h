
#ifndef DONOR_H
#define DONOR_H

#include <string>
#include <iostream>

using namespace std;

class Donor {
private:
    int donorId, district;
    long long number;
    std::string name, address, bloodType;
    static std::string trim(const std::string& str);

public:
    void donorDetails() const;
    static Donor parseLine(const std::string& line);
    
    // Getters
    int getDonorId() const { return donorId; }
    int getDistrict() const { return district; }
    long long getNumber() const { return number; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getBloodType() const { return bloodType; }
    
    // Setters
    void setDonorId(int id) { donorId = id; }
    void setDistrict(int d) { district = d; }
    void setNumber(long long n) { number = n; }
    void setName(const std::string& n) { name = n; }
    void setAddress(const std::string& a) { address = a; }
    void setBloodType(const std::string& bt) { bloodType = bt; }
};

#endif // DONOR_H
