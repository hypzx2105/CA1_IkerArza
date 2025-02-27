#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <algorithm>


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


//Stage 3:
///1.Write a function that will accept the vector of structs, iterate through the elements, and display the elements in a neatly formatted fashion.


void displayCars(const vector<Cars> &cars) {
    cout << left << setw(20) << "ID"
         << setw(15) << "Brand"
         << setw(15) << "Model"
         << setw(6)  << "Year"
         << setw(12) << "Price"
         << setw(12) << "Horsepower"
         << setw(12) << "Engine Size" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;


    for (int i = 0; i < cars.size(); i++) {
        cout << left << setw(20) << cars[i].id
             << setw(15) << cars[i].brand
             << setw(15) << cars[i].model
             << setw(6)  << cars[i].year
             << setw(12) << cars[i].price
             << setw(12) << cars[i].horsePower
             << setw(12) << cars[i].engineSize << endl;
    }
}


///  2.Write a function that searches a vector of structs for a specific field value, returning the index if found or -1 otherwise. Display the struct's contents if found, or a 'not found' message.


int searchCarByBrand(const vector<Cars> &cars, const string &brand) {

    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].brand == brand) {
            return i;
        }
    }
    return -1;
}

void displaySearchResult(const vector<Cars> &cars, int index) {
    if (index != -1) {
        cout << "Car Found:\n";
        cout << left << setw(20) << "ID"
             << setw(15) << "Brand"
             << setw(15) << "Model"
             << setw(6)  << "Year"
             << setw(12) << "Price"
             << setw(12) << "Horsepower"
             << setw(12) << "Engine Size" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
        cout << left << setw(20) << cars[index].id
             << setw(15) << cars[index].brand
             << setw(15) << cars[index].model
             << setw(6)  << cars[index].year
             << setw(12) << cars[index].price
             << setw(12) << cars[index].horsePower
             << setw(12) << cars[index].engineSize << endl;
    } else {
        cout << "Car not found." << endl;
    }
}

///3.Write a function that will accept the vector of structs, iterate through the data loaded in stage 2 and accumulate a count of the number of rows that are a match for each of the unique values in a chosen column. For example, if you chose movie data then this function could return the number of movies of each genre (comedy, thriller, drama, etc.). This function should return a map containing all information.


unordered_map<string, int> countByBrand(const vector<Cars> &cars) {
    unordered_map<string, int> brandCount;


    for (size_t i = 0; i < cars.size(); i++) {
        brandCount[cars[i].brand]++;
    }

    return brandCount;
}

void displayBrandCount(const unordered_map<string, int> &brandCount) {
    cout << "\n[Car Count by Brand]\n";
    cout << left << setw(15) << "Brand" << setw(10) << "Count" << endl;
    cout << "-----------------------------\n";


    vector<pair<string, int>> brandVector(brandCount.begin(), brandCount.end());

    for (size_t i = 0; i < brandVector.size(); i++) {
        cout << left << setw(15) << brandVector[i].first
             << setw(10) << brandVector[i].second << endl;
    }
}


///4.Write a function that displays a subset of the data rows based on a user input. For example, this function could show all of the movies of a particular genre entered by the user and passed into the function as an argument.



void displayCarsByBrand(const vector<Cars> &cars, const string &brand) {
    bool found = false;

    cout << "\n[ Cars of Brand: " << brand << "]\n";
    cout << left << setw(20) << "ID"
         << setw(15) << "Brand"
         << setw(15) << "Model"
         << setw(6)  << "Year"
         << setw(12) << "Price"
         << setw(12) << "Horsepower"
         << setw(12) << "Engine Size" << endl;
    cout << "--------------------------------------------------------------------------------------\n";


    for (size_t i = 0; i < cars.size(); i++) {
        if (cars[i].brand == brand) {
            cout << left << setw(20) << cars[i].id
                 << setw(15) << cars[i].brand
                 << setw(15) << cars[i].model
                 << setw(6)  << cars[i].year
                 << setw(12) << cars[i].price
                 << setw(12) << cars[i].horsePower
                 << setw(12) << cars[i].engineSize << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No cars found for the brand: " << brand << endl;
    }
}



///5.Write a function that will find the highest, lowest and average of a discrete numerical field (Integer).  The function should return the average value (as an int) and provide (“return”) a copy of the structs with the highest and lowest values. For example, if you chose movie data then this function could provide the highest rated and lowest rated movie, and also return the average rating of all movies.


struct HorsePowerStats {
    int averageHP;
    Cars highestCar;
    Cars lowestCar;
};


HorsePowerStats findHorsePowerStats(const vector<Cars> &cars) {
    if (cars.empty()) {
        cerr << "Error: No cars in the dataset.\n";
        return {0, Cars(), Cars()};
    }

    int totalHorsepower = 0;
    Cars highestCar = cars[0];
    Cars lowestCar = cars[0];


    for (size_t i = 0; i < cars.size(); i++) {
        totalHorsepower += cars[i].horsePower;

        if (cars[i].horsePower > highestCar.horsePower) {
            highestCar = cars[i];
        }

        if (cars[i].horsePower < lowestCar.horsePower) {
            lowestCar = cars[i];
        }
    }

    int averageHorsepower = totalHorsepower / cars.size();

    return {averageHorsepower, highestCar, lowestCar};
}


void displayHorsePowerStats(const HorsePowerStats &stats) {
    cout << "\n[Horsepower Stats]\n";
    cout << "Average Horsepower: " << stats.averageHP << " HP\n";

    cout << "\n Car with Highest Horsepower:\n";
    cout << left << setw(20) << "ID"
         << setw(15) << "Brand"
         << setw(15) << "Model"
         << setw(6)  << "Year"
         << setw(12) << "Price"
         << setw(12) << "Horsepower"
         << setw(12) << "Engine Size" << endl;
    cout << "--------------------------------------------------------------------------------------\n";
    cout << left << setw(20) << stats.highestCar.id
         << setw(15) << stats.highestCar.brand
         << setw(15) << stats.highestCar.model
         << setw(6)  << stats.highestCar.year
         << setw(12) << stats.highestCar.price
         << setw(12) << stats.highestCar.horsePower
         << setw(12) << stats.highestCar.engineSize << endl;

    cout << "\nCar with Lowest Horsepower:\n";
    cout << left << setw(20) << stats.lowestCar.id
         << setw(15) << stats.lowestCar.brand
         << setw(15) << stats.lowestCar.model
         << setw(6)  << stats.lowestCar.year
         << setw(12) << stats.lowestCar.price
         << setw(12) << stats.lowestCar.horsePower
         << setw(12) << stats.lowestCar.engineSize << endl;
}

///6.Write a function that will search through the data and return a list of all items that match or partially match a given text input. For example, all movies that contain the text “The” in the title. Iterators must be used for this function.


void searchCarsByText(const vector<Cars> &cars, const string &searchText) {
    vector<Cars> matchingCars;


    for (size_t i = 0; i < cars.size(); i++) {

        if (cars[i].brand.find(searchText) != string::npos || cars[i].model.find(searchText) != string::npos) {
            matchingCars.push_back(cars[i]);
        }
    }


    cout << "\n[ Search Results for: \"" << searchText << "\"]\n";
    if (matchingCars.empty()) {
        cout << "No matching cars found.\n";
        return;
    }

    cout << left << setw(20) << "ID"
         << setw(15) << "Brand"
         << setw(15) << "Model"
         << setw(6)  << "Year"
         << setw(12) << "Price"
         << setw(12) << "Horsepower"
         << setw(12) << "Engine Size" << endl;
    cout << "--------------------------------------------------------------------------------------\n";


    for (size_t i = 0; i < matchingCars.size(); i++) {
        cout << left << setw(20) << matchingCars[i].id
             << setw(15) << matchingCars[i].brand
             << setw(15) << matchingCars[i].model
             << setw(6)  << matchingCars[i].year
             << setw(12) << matchingCars[i].price
             << setw(12) << matchingCars[i].horsePower
             << setw(12) << matchingCars[i].engineSize << endl;
    }
}


///7.Write a function that will display all of the data in descending order of a selected floating point field. For example, using the gross takings of a movie in Millions (Floating point number), you could display them in descending order of gross takings.

void sortCarsByEngineSize(vector<Cars> &cars) {
    sort(cars.begin(), cars.end(), [](const Cars &a, const Cars &b) {
        return a.engineSize > b.engineSize;
    });
}


void displaySortedCars(const vector<Cars> &cars) {
    cout << "\n[Cars Sorted by Engine Size (Descending)]\n";
    cout << left << setw(20) << "ID"
         << setw(15) << "Brand"
         << setw(15) << "Model"
         << setw(6)  << "Year"
         << setw(12) << "Price"
         << setw(12) << "Horsepower"
         << setw(12) << "Engine Size" << endl;
    cout << "--------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < cars.size(); i++) {
        cout << left << setw(20) << cars[i].id
             << setw(15) << cars[i].brand
             << setw(15) << cars[i].model
             << setw(6)  << cars[i].year
             << setw(12) << fixed << setprecision(2) << cars[i].price
             << setw(12) << cars[i].horsePower
             << setw(12) << fixed << setprecision(1) << cars[i].engineSize << endl;
    }
}

void menu(vector<Cars> &cars) {
    int choice;
    string input;

    do {
        cout << "\n========== Car Database Menu ==========\n";
        cout << "1. Display all cars\n";
        cout << "2. Search car by brand\n";
        cout << "3. Show count of cars by brand\n";
        cout << "4. Filter cars by brand\n";
        cout << "5. Show cars sorted by engine size\n";
        cout << "6. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayCars(cars);
            break;
            case 2:
                cout << "Enter brand to search: ";
            cin >> input;
            displaySearchResult(cars, searchCarByBrand(cars, input));
            break;
            case 3:
                displayBrandCount(countByBrand(cars));
            break;
            case 4:
                cout << "Enter brand to filter: ";
            cin >> input;
            displayCarsByBrand(cars, input);
            break;
            case 5:
                displaySortedCars(cars);
            break;
            case 6:
                cout << "Exiting program...\n";
            return;
            default:
                cout << "Invalid option! Try again.\n";
        }
    } while (choice != 6);
}




int main() {

    vector<Cars> cars;
    loadData("Cars_c++.csv", cars);
    menu(cars);
    return 0;
}
