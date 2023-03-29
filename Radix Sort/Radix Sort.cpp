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

vector<int> initVector(vector<int> A, int size) {
	A.clear();
	for (int i = 0; i < size; i++) {
		A.push_back(0);
	}
	return A;
}

//vector<unsigned char> RadixSort(vector<int> A) {
vector<int> RadixSort(vector<int> A) {
	cout << "\nRunning Radix sort...\n";

	cout << "Creating and initializing C vector...\n";
	vector<unsigned int> C; //prefixi
	C.push_back(0); C.push_back(0); //inicializiraj

	vector<int> B;

	for (int k = 0; k < 8; k++) {
		cout << "\nSorting bit "<<k+1<<":\n";

		//nastavi na C[0]=0 in C[1]=0
		C.at(0) = 0;
		C.at(1) = 0;

		cout << "Counting 0s and 1s...\n";
		for (int i = 0; i < A.size(); i++) {
			//cout << ((A.at(i) >> k) & 1) << "\n";
			int(C.at((A.at(i) >> k) & 1)++);
		}
		cout << "0s and 1s successfully counted and saved to C!\n";

		C.at(1) += C.at(0);

		cout << "Initializing vector B...\n";
		B = initVector(B, A.size());

		cout << "Sorting vector B based on values of C...\n";
		for (int i = A.size()-1; i >= 0; i--)
		{
			B.at(int(--C.at(((A.at(i) >> k) & 1)))) = A.at(i);
		}
		cout << "Sorting vector B successful!\n";

		cout << "Saving results of vector B to vector A...\n";
		std::swap(A, B);
	}

	cout << "Radix Sort successfully completed!\n\n";
	return A;
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
		/*
		vector<int> A = { 14,5,2,12 };
		//A = RadixSort(A);
		A = RadixSort(ReadFromFile(argv[1]));
		for (int i = 0; i < A.size(); i++) {
			cout << A.at(i) << " ";
		}
		*/
		
		SaveToFile(RadixSort(ReadFromFile(argv[1])));
	}
	return 0;
}