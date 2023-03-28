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

vector<int> CountingSort(vector<int> A) {
	cout << "Running Counting sort...\n";
	vector<int> C; //pomozno polje

	cout << "Getting minimum and maximum intervals...\n";
	//pridobi interval min in max stevila v polju
	int min = INT_MAX;
	int max = 0;
	for (int i = 0; i < A.size(); i++)
	{
		if (A.at(i) < min)
			min = A.at(i);
		if (A.at(i) > max)
			max = A.at(i);
	}
	cout << "Intervals counted!\n";

	cout << "Removing negative numbers...\n";
	//odstrani negativna stevila (pristej min vrednost)
	int neg = min * (-1);
	for (int i = 0; i < A.size(); i++)
	{
		A.at(i) += neg;
	}
	cout << "Negative numbers removed!\n";

	cout << "Creating array C...\n";
	int sizeC = max + 1 + neg; //velikost C je najvecja vrednost A+1 (upostevaj nove vrednosti (neg))
	//inicializiraj vseh elementov C na 0
	for (int i = 0; i < sizeC; i++)
	{
		C.push_back(0);
	}
	cout << "C array successfully created!\n";

	cout << "Counting C array variables...\n";
	//stej C
	//za vsako vrednost A[i] povecaj C z C[A[i]]=C[A[i]]+1;
	for (int i = 0; i < A.size(); i++)
	{
		//C.at(A.at(i)) = C.at(i) + 1;
		C.at(A.at(i))++;
	}
	cout << "C array variables counted successfully!\n";
	//do tukaj tudi Roman sort

	cout << "Counting sum of variables in C array...\n";
	//sestevaj vrednosti C (inkrementalno, narascajoce)
	//sestej vrednosti polja C kot C[i]=C[i]+C[i-1] za i>0 (vred v C vecja od 0)
	for (int i = 0; i < C.size(); i++)
	{
		if (C.at(i) > 0)
		{
			if (i != 0)
				C.at(i) += C.at(i - 1);
		}
		else
			C.at(i) = C.at(i - 1);
	}
	cout << "Sum of variables in C array successfully counted!\n";

	cout << "Creating B array...\n";
	//ustvari polje B, velikosti A
	vector<int> B;
	for (int i = 0; i < A.size(); i++)
	{
		B.push_back(0);
	}
	cout << "B array successfully created!\n";

	cout << "Counting variables from B array...\n";
	//za vsako vrednost A[i] (OBRATNI VRSTNI RED) zapisi izhod v B kot B[C[A[i]]-1]=A[i]
	//in dekrementiraj C[A[i]]=C[A[i]]-1
	for (int i = A.size() - 1; i >= 0; i--)
	{
		B.at(C.at(A.at(i)) - 1) = A.at(i);
		C.at(A.at(i))--;
	}
	cout << "B array variables successfully counted!\n";

	//od tu dalje vsebuje tudi Roman sort
	cout << "Converting to previous interval...\n";
	//pretvori v obratni interval
	for (int i = 0; i < B.size(); i++)
	{
		B.at(i) -= neg;
	}
	cout << "B array successfully converted to original interval!\n";

	cout << "Counting Sort successfully completed!\n";
	return B;
}

//vector<unsigned char> RadixSort(vector<int> A) {
void RadixSort(vector<int> A) {

	vector<unsigned char> D; //polje bitov
	for (int k = 0; k < 8; k++) {
		D.clear();
		for (int i = 0; i < A.size(); i++) {
			//cout << ((A.at(i) >> k) & 1) << "\n";
			bool bit = ((A.at(i) >> k) & 1);
			D.push_back(bit);
		}

		vector<int> D_copy(D.begin(), D.end());					//vector<unsigned char> pretovori v vector<int>
		D_copy = CountingSort(D_copy);							//sortiraj D
		vector<unsigned char> D(D_copy.begin(), D_copy.end());	//vector<int> pretvori v vector<unsigned char>
		
		for (int i = 0; i < D.size(); i++)
		{
			//cout << int(D.at(i)) << "\n";
		}
		return;
	}

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
		RadixSort(ReadFromFile(argv[1]));
		cout << "OK";
	}
	return 0;
}