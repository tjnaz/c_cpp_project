// Question 1
// A text file contains an no more than 100 rows of data in the following
// format. Kandy,Colombo,110 Dehiwela,Ratmalana,5 Dehiwela,Colombo,7.2
// Dehiwela,Wellawatte,1.5
// Wellawatte,Ratmalana,6
// Galle,Kandy,110
// Matara,Dehiwela,150

// NOTE: The above is only a sample for testing.
// It is required to represent this data in a matrix like this (doesn’t need to
// be identical). (where cities are rows and columns and the distance is a cell)

// Q1.1 Explain the data structures you will use to create this matrix. Draw any
// diagrams you will need to support your explanation.

// Q1.2 Write a program to read the data from the text file cities.txt and put
// it into the structure.

// Q1.3 Extend the program to implement the following functions.
// (a) Distance(city1, city2) – returns the distance in kilometres between two
// cities. (b) Shortest(city) – returns the shortest distance from a city. (c)
// Equidistance(city) – outputs two cities with equal distance from city.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct City {
  string name;
  int index;
};

int find_city_index(const vector<City> &cities, const string &city_name) {
  for (const auto &city : cities) {
    if (city.name == city_name) {
      return city.index;
    }
  }
  return -1;
}

int main() {
  ifstream input_file("cities.txt");

  if (!input_file) {
    cerr << "Error opening file 'cities.txt'." << endl; // better than "\n"??
    return -1;
  }

  vector<City> cities;
  vector<vector<int>> distance_matrix;
  string line;

  while (getline(input_file, line)) {
    stringstream ss(line);
    string city1, city2;
    int distance;

    getline(ss, city1, ',');
    getline(ss, city2, ',');
    ss >> distance;
    // cout << city1 << "-" << city2 << ":" << distance << "\n";

    int index1 = find_city_index(cities, city1);
    int index2 = find_city_index(cities, city2);

    if (index1 == -1) {
      index1 = cities.size();
      cities.push_back({city1, index1});
      distance_matrix.push_back(vector<int>(100, 0)); // no more than 100 cities
    }

    if (index2 == -1) {
      index2 = cities.size();
      cities.push_back({city2, index2});
      distance_matrix.push_back(vector<int>(100, 0)); // no more than 100 cities
    }

    distance_matrix[index1][index2] = distance;
    distance_matrix[index1][index2] = distance;
  }

  input_file.close();

  for (int i = 0; i < cities.size(); i++) {
    for (int j = i + 1; j < cities.size(); j++) {
      int dist = distance_matrix[i][j];
      if (dist > 0) {
        cout << cities[i].name << " to " << cities[j].name << ": " << dist
             << endl;
      }
    }
  }

  return 0;
}
