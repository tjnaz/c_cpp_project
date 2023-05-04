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
#include <utility>
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

// find the distance between two cities
int Distance(const vector<City> &cities,
             const vector<vector<int>> &distance_matrix,
             const string &city1_name, const string &city2_name) {
  int city1_index = find_city_index(cities, city1_name);
  int city2_index = find_city_index(cities, city2_name);

  if (city1_index == -1 || city2_index == -1) {
    // Either city1 or city2 was not found in the cities vector
    return -1;
  }

  int distance = distance_matrix[city1_index][city2_index];
  if (distance == 0) {
    // The cities are not connected
    return -1;
  }

  return distance;
}

// Find the shoretest distance to the give city and output the distance with the
// closest city
int Shortest(const vector<City> &cities,
             const vector<vector<int>> &distance_matrix,
             const string &city_name, string &closest_city_name) {
  int city_index = find_city_index(cities, city_name);

  if (city_index == -1) {
    return -1;
  }

  int min_distance = -1;
  int closest_city_index = -1;
  for (int i = 0; i < cities.size(); i++) {
    if (i == city_index) {
      continue;
    }

    int distance = distance_matrix[city_index][i];
    if (distance == 0) {
      continue;
    }

    if (min_distance == -1 || distance < min_distance) {
      min_distance = distance;
      closest_city_index = i;
    }
  }

  if (closest_city_index == -1) {
    return -1;
  }

  closest_city_name = cities[closest_city_index].name;
  return min_distance;
}

// Find two cities with the equal distant to the given city
void Equidistance(const vector<City> &cities,
                  const vector<vector<int>> &distance_matrix,
                  const string &city_name) {
  int city_index = find_city_index(cities, city_name);
  if (city_index == -1) {
    cout << "City nod found!" << endl;
    return;
  }

  vector<pair<string, string>> equidistant_cities;
  for (int i = 0; i < cities.size(); i++) {
    if (i == city_index) {
      continue;
    }

    int distance = distance_matrix[city_index][i];
    if (distance == 0) {
      continue;
    }

    for (int j = i + 1; j < cities.size(); j++) {
      if (j == city_index) {
        continue;
      }

      int second_distance = distance_matrix[city_index][j];
      if (second_distance == 0) {
        continue;
      }

      if (distance == second_distance) {
        equidistant_cities.push_back(make_pair(cities[i].name, cities[j].name));
      }
    }
  }

  if (equidistant_cities.empty()) {
    cout << "No equidistant city found";
  } else {
    cout << "Equidistant cities to " << city_name << " are:" << endl;
    for (auto &pair : equidistant_cities) {
      cout << pair.first << " and " << pair.second << endl;
    }
  }
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

  // for (int i = 0; i < cities.size(); i++) {
  //   for (int j = i + 1; j < cities.size(); j++) {
  //     int dist = distance_matrix[i][j];
  //     if (dist > 0) {
  //       cout << cities[i].name << " to " << cities[j].name << ": " << dist
  //            << endl;
  //     }
  //   }
  // }

  // fixed city names at the start of the program
  // string city1_name = "Colombo";
  // string city2_name = "Galle";

  // take the input of two cities to find the distance between them
  // from the user input
  string city1_name, city2_name;

  cout << "Find the distancee between two cities - ";
  cout << "Enter the name of the City 1: ";
  getline(cin, city1_name);
  cout << "Enter the name of the City 2: ";
  getline(cin, city2_name);

  int distance = Distance(cities, distance_matrix, city1_name, city2_name);
  if (distance == -1) {
    cout << "Error: " << city1_name << " and " << city2_name
         << " are not connected." << endl;
  } else {
    cout << "Distance between " << city1_name << " and " << city2_name << " is "
         << distance << "." << endl;
  }

  // Takee the input for finding the closest city + equidistant cities
  cout << "Find the closest city as well as the two cities with the equal "
          "distance- ";
  string city_name;
  cout << "Enter the name of the city: ";
  getline(cin, city_name);

  string closest_city_name;
  int closestDistance =
      Shortest(cities, distance_matrix, city_name, closest_city_name);

  if (closestDistance == -1) {
    cout << "No such city";
  } else {
    cout << "Closest city to " << city_name << " is " << closest_city_name
         << " with a distance of " << closestDistance << endl;
  }

  // for ease of use the program will find the Equidistance cities for the city
  // entered above NOTE: gonna have to make sure there are two cities with the
  // same distance to  Colombo

  Equidistance(cities, distance_matrix, city_name);

  return 0;
}
