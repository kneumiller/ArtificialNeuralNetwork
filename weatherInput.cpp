
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void readWeatherData(double (&normalizedData)[20][5]) {
	vector <string> fileData; 

	string input;
	ifstream file ("weather.csv");
	

	if (file.is_open()) {
		//Read file in line by line
		while (getline (file, input)){
			istringstream s(input);
			string field;
			//Gather the column titles first loop, then put the rest of the data
			// into a vector to later be sorted
			while (getline(s, field, ',')) {
					fileData.push_back(field);
			}
		}
	}
	
	int row = 0;
	
	//Normalize the data with values between [0-1]
	//Outlook: sunny, overcast, rainy
	//Temp: hot, mild, cool
	//Humidity: high, normal
	//Windy: FALSE, TRUE
	cout << fileData.size() << endl;
	for (int j = 0; j < fileData.size(); j++) {
					cout << j << endl;

		if (fileData[j] == "sunny" || fileData[j] == "hot" || fileData[j] == "high" || fileData[j] == "FALSE" || fileData[j] == "no")
			normalizedData[row][j] = 0.0;
		else if (fileData[j] == "overcast" || fileData[j] == "mild") {
			normalizedData[row][j] = 0.5;
	}
		else if (fileData[j] == "rainy" || fileData[j] == "cool" || fileData[j] == "normal" || fileData[j] == "TRUE" || fileData[j] == "yes")
			normalizedData[row][j] = 1.0;
		row++;
	}
}