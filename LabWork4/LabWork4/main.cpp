#include <iostream>
#include <vector>

using namespace std;

//Operating time O (n), the algorithm is stable
void StableSort(vector<int> &inputArray)
{
	// Zero Count Calculation
	vector<int> B(inputArray.size());
	int x = -1;

	for (auto &element : inputArray)
		if (element == 0) x++;

	int y = inputArray.size() - 1;
	for (int i = inputArray.size() - 1; i >= 0; --i)
	{
		if (inputArray[i] == 0)
		{
			B[x] = inputArray[i];
			x--;
		}
		else
		{
			B[y] = inputArray[i];
			y--;
		}
	}
	inputArray = B;
}

void FixedMemorySort(vector<int> &inputArray)
{
	int c = 0;
	for (auto &element : inputArray)
		if (element == 0)
		{
			swap(element, inputArray[c]);
			c++;
		}
}

void StableFixedSort(vector<int> &inputArray)
{
	int i = -1;
	for (auto &element : inputArray)
		if (element == 0)
		{
			for (int k = j; (k - i - 1) > 0; k--)
			{
				swap(inputArray[k], inputArray[k - 1]);
			}
			i++;
		}
}
void DisplayVector(vector<int> inputArray) {
	for (auto &element : inputArray)
		cout << element << " ";
}

int main()
{
	// Initialization
	vector<int> firstArray = { 1,0,1,0,1,0,1 };
	secondArray = { 1,1,1,1,1,1,0,0,0,0,0,0,1,1, };
	thirdArray = { 0,0,0,0,1,1,0,0,1,0,1 };
	// Sort Type 1
	cout << "Sort type Stable: ";
	StableSort(inputArray);
	DisplayVector(inputArray);

	// Sort Type 2
	cout << "Sort type Fixed Memory: ";
	FixedMemorySort(secondArray);
	DisplayVector(secondArray);

	// Sort Type 3
	cout << "Sort type Stable Fixed Memory: ";
	StableFixedSort(thirdArray);
	DisplayVector(thirdArray);

	// Wait for input to finish
	cin.get();
	return 0;
}
