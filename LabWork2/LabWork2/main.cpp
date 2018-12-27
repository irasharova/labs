#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string.h>

using namespace std;

int Search_Binary(int arr[], int left, int right, int key)
{
	int midd = 0;
	while (1)
	{
		midd = (left + right) / 2;

		if (key < arr[midd])       
			right = midd - 1;      
		else if (key > arr[midd])  
			left = midd + 1;   
		else                      
			return midd;         

		if (left > right)  
			return -1;
	}
}



void CountElementsWithNoPair(vector<int> &screws, vector<int> &screwsWithNoPair) // COUNT ELEMENTS WITH NO PAIR
{
	for (auto &screw : screws)
		if (screw != 0)
		{
			screwsWithNoPair.push_back(screw);
			screw = 0;
		}
}

void CountMatch(vector<int> &screws, vector<int> &bolts, vector<int> &sbPairs) //COUNT MATCHES WITH SCREWS AND BOLTS
{
	// Old
	/*for (auto &screw : screws)
		for (auto &bolt : bolts)
            if(bolt != 0 && screw == bolt)
            {
                sbPairs.push_back(bolt);
				screw = 0;
				bolt = 0;
                break;
            }*/

	for (auto &screw : screws)
	{
		int isContains = Search_Binary(bolts, 0, bolts.size(), screw);
		if (isContains >= 0) {
			sbPairs.push_back(screw);
		}
	}
}

void DisplayVector(vector<int> screws) //DISPLAY VECTOR
{
	for (auto &screw : screws)
        cout << screw << " ";
    cout << endl;
}

bool IsEndOfFile(FILE *f)
{
	fpos_t currentPoint, endPoint;
	fgetpos(f, &currentPoint);
	fseek(f, 0, SEEK_END);
	fgetpos(f, &endPoint);
	fsetpos(f, &currentPoint);
	if (currentPoint == endPoint) return true;
	return false;
}

void ReadInputFile(char fileName[], vector<int> &screws, vector<int> &bolts) //READ INPUT DATA FROM FILE
{
	FILE *f = fopen(fileName, "rt");
	char symbol, str[4];
	int iterator = 0;
	bool toScrewsArray = true;
	while (!IsEndOfFile(f))
	{
		fread(&toScrewsArray, sizeof(char), 1, f);
		if (isdigit(symbol))
		{
			str[iterator] = symbol;
			iterator++;
		}
		else
		{
			str[iterator] = '\0';
			int n = atoi(str);
			iterator = 0;
			if (toScrewsArray)
				screws.push_back(n);
			else
				bolts.push_back(n);
			if (symbol == '\n')
				toScrewsArray = false;
		}
	}
	fclose(f);
}

int main()
{
    setlocale(LC_ALL, "Russian");

	// INITIALIZATION
    vector <int> screws,				//SCREWS
				 bolts,					//BOLTS
				 sbPairs,				//SCRE-BOLT PAIRS
				 screwsWithNoPair,		//SCREWS WITHOUT PAIR
				 boltsWithNoPair;		//BOLTS WITHOUT PAIR

	// READ INPUT DATA
    ReadInputFile("ExampleData1.txt", screws, bolts);

	// Sort before processing
	sort(screws, screws+ screws.size());
	sort(bolts, bolts + bolts.size());
	// PROCESSING DATA FROM FILE
    CountMatch(screws, bolts, sbPairs);
    CountElementsWithNoPair(screws, screwsWithNoPair);
    CountElementsWithNoPair(bolts, boltsWithNoPair);

	// DISPLAY RESULTS
    cout << "PAIRS: ";
    DisplayVector(sbPairs);
    cout << "SCREWS WITH NO PAIRS: ";
    DisplayVector(screwsWithNoPair);
    cout << "BOLTS WITH NO PAIRS: ";
    DisplayVector(boltsWithNoPair);

	// WAIT FOR INPUT TO EXIT
    cin.get();
    return 0;
}
