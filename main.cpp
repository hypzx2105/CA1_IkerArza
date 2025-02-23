#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;


struct Cars {
    string id;
    string brand;
    string model;
    int year;
    string price;
    int horsePower;
    float engineSize;
};


Cars parseLine(string line) {
    stringstream ss(line);
    string id, brand, model, year, price, horsePower, engineSize;


    getline(ss, id, ',');
    getline(ss, brand, ',');
    getline(ss, model, ',');
    getline(ss, year, ',');
    getline(ss, price, ',');
    getline(ss, horsePower, ',');
    getline(ss, engineSize, ',');


    Cars car;
    car.id = id;
    car.brand = brand;
    car.model = model;
    car.year = stoi(year);
    car.price = price;
    car.horsePower = stoi(horsePower);
    car.engineSize = stof(engineSize);

    return car;
}


void loadData(const string &filename, vector<Cars> &cars) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        cars.push_back(parseLine(line));
    }

    file.close();
}


void displayCars(const vector<Cars> &cars) {
    cout << left << setw(20) << "ID"
         << setw(15) << "Brand"
         << setw(15) << "Model"
         << setw(6)  << "Year"
         << setw(12) << "Price"
         << setw(12) << "Horsepower"
         << setw(12) << "Engine Size" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;


    for (size_t i = 0; i < cars.size(); i++) {
        cout << left << setw(20) << cars[i].id
             << setw(15) << cars[i].brand
             << setw(15) << cars[i].model
             << setw(6)  << cars[i].year
             << setw(12) << cars[i].price
             << setw(12) << cars[i].horsePower
             << setw(12) << cars[i].engineSize << endl;
    }
}


int main() {
    vector<Cars> cars;

    loadData("Cars_c++.csv", cars);
    displayCars(cars);

    return 0;
}
