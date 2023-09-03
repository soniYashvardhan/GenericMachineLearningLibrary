#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Initialize a vector to store integers
    std::vector<int> integers;
	vector<vector<int>> input_X;
	vector<int> input_Y;

    // Open the CSV file for reading
    std::ifstream file("breast_cancer.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    // Read the file line by line
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        // Split each line by ',' and convert to integers
        while (std::getline(iss, token, ',')) {
            integers.push_back(std::stoi(token));
        }
		input_Y.push_back(integers[integers.size()-1]);
		integers.pop_back();
		input_X.push_back(integers);
		integers.clear();
    }

    // Close the file
    file.close();

    // Now, 'integers' contains all the integers from the CSV file
    for (int i=0;i<input_X.size();++i) {
		for(int num: input_X[i]) {
        	std::cout << num << " ";
		}
		std::cout<<"\t"<<input_Y[i]<<std::endl;
    }
    std::cout << std::endl;

    return 0;
}
