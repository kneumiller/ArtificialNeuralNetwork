#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void readClassData(double normalizedData[20][5]) {
	vector <string> fileData; 

	string input;
	ifstream file ("class.csv");
	

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
	for (int j = 0; j < fileData.size(); j++) {
		if (fileData[j] == "weekday" || fileData[j] == "spring" || fileData[j] == "none" || fileData[j] == "on time")
			normalizedData[row][j] = 0.0;
		else if (fileData[j] == "saturday" || fileData[j] == "winter")
			normalizedData[row][j] = 0.25;
		else if (fileData[j] == "holiday" || fileData[j] == "summer" || fileData[j] == "slight" || fileData[j] == "late")
			normalizedData[row][j] = 0.5;
		else if (fileData[j] == "sunday" || fileData[j] == "autumn" || fileData[j] == "heavy" || fileData[j] == "very late")
			normalizedData[row][j] = 1.0;
		row++;
	}
}