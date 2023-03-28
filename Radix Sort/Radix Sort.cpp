// Radix Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> ReadFromFile(char* file) {
	vector<int> A; //main polje
	int stevilo; //stevilo iz datoteke
	//cout << "File: " << file << "\n";
	ifstream input(file);
	if (!input.is_open()) //datoteko mozno odpreti
	{
		cout << "ERROR: Cannot open file!\n";
		return vector<int>();
	}
	cout << "Reading file...\n";
	//beri iz datoteke
	while (!input.eof())
	{
		input >> stevilo;
		if (!input) //prazen
			break;
		A.push_back(stevilo);
	}
	cout << "File read successfully!\n";
	return A;
}

void SaveToFile(vector<int> B) {
	const char* file = "out.txt"; //ime izhodne datoteke
	ofstream output(file);
	if (!output.is_open()) //datoteko mozno odpreti
	{
		cout << "ERROR: Cannot open file!\n";
		return;
	}
	cout << "Saving to file...\n";
	//zapisi v datoteko
	for (int i = 0; i < B.size(); i++)
	{
		output << B.at(i) << ' '; //zapisi v datoteko (razdeli z presledki)
	}
	output.close();
	cout << "File saved successfully!\n";
}

int main(int argc, char* argv[])
{
	//argv[1]=pot vhodne datoteke
	//vnos command-line argumentov v: 
	//	Solution Explorer -> desni-klik na Radix Sort -> Properties -> Debugging -> Command Arguments

	if (argc <= 1) {
		cout << "Invalid number of input arguments! Requires at least one!\n";
	}
	else {
		vector<int> A = ReadFromFile(argv[1]);
		cout << "OK";
	}
	return 0;
}