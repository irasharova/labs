#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//Rabin-Karp algorithm
void HashBasedAlgorithm(string str, string subStr, vector<int>&answer)
{
	int firstStringLength = str.size();
	int secondSubStringLength = subStr.size();
	int p = 13;
	int r = 4096;

	long long int hashStr = CalculateStringHash(str, secondSubStringLength - 1, 0);
	long long int hashSubStr = CalculateStringHash(subStr, secondSubStringLength - 1, 0);
	for (int i = 0; i< firstStringLength - secondSubStringLength; ++i)
	{
		if (hashStr == hashSubStr)
		{
			answer.push_back(i);
		}
		hashStr = CalculateStringHash(str, secondSubStringLength - 1, i + 1);
	}
	if (answer.empty()) answer.push_back(-1);
}

//hash function
long long int CalculateStringHash(string str, int secondSubStringLength, int start)
{
    int p = 13;
    int r = 4096;
    long long int h = 0;
    for(int i = start, j=0; i <= secondSubStringLength + start; ++i, j++)
    {
        int c = (int)str[i];
        int pow_ = pow(p, j);
        h = (h + c*pow_);
    }
    return h;
}

//checks whether string oneStr is cyclic move of string secondSubStr
bool CheckCyclicMove(string oneStr, string secondSubStr)
{
    if(oneStr.size() != secondSubStr.size()) return false;
    string doubleStr = secondSubStr + secondSubStr;
    vector<int> answer;
    HashBasedAlgorithm(doubleStr, oneStr, answer);
    if(answer[0] == -1) return false;
    return true;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    string oneStr = "abc";
    string secondSubStr = "cab";
    if(CheckCyclicMove(oneStr, secondSubStr))
    {
        cout << "String " << oneStr << " is a cyclic string shift " << secondSubStr;
    }
    else
    {
        cout << "String " << oneStr << " not a cyclic row shift " << secondSubStr;
    }
    cout << endl << endl << endl;


    oneStr = "abcdefg";
    secondSubStr = "cab";
    if(CheckCyclicMove(oneStr, secondSubStr))
    {
        cout << "String " << oneStr << " is a cyclic row shift " << secondSubStr;
    }
    else
    {
        cout << "String " << oneStr << " not a cyclic row shift " << secondSubStr;
    }
    cout << endl << endl << endl;

    oneStr = "efg";
    secondSubStr = "cab";
    if(CheckCyclicMove(oneStr, secondSubStr))
    {
        cout << "String " << oneStr << " is a cyclic row shift " << secondSubStr;
    }
    else
    {
        cout << "String " << oneStr << " not a cyclic row shift " << secondSubStr;
    }
    cin.get();
    return 0;
}
