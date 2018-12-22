	#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct table
{
    char c;
    int shift;
};





void BuildShiftTable(string str, int shift[])
{
    for(int i = 0; i < 26; ++i)
    {
        shift[i] = str.size();
    }
    for(int i = 0; i <= str.size()-2; ++i)
    {
        shift[str[i] - 97] = str.size() - i -1;
    }
}

int BoyerMooreSearchAlgorithm(const string &where, const string &what)
{
	vector<int> good_shift(what.size() + 1, what.size());

	vector<int> bad_char(256, what.size());
	vector<int> z(what.size(), 0);
	for (int j = 1, maxZidx = 0, maxZ = 0; j < what.size(); ++j) {
		if (j <= maxZ) z[j] = min(maxZ - j + 1, z[j - maxZidx]);
		while (j + z[j] < what.size() && where[what.size() - 1 - z[j]] == where[what.size() - 1 - (j + z[j])]) z[j]++;
		if (j + z[j] - 1 > maxZ) {
			maxZidx = j;
			maxZ = j + z[j] - 1;
		}
	}

	for (int j = what.size() - 1; j > 0; j--) good_shift[what.size() - z[j]] = j;
	for (int j = 1, r = 0; j <= what.size() - 1; j++)
		if (j + z[j] == what.size())
			for (; r <= j; r++)
				if (good_shift[r] == what.size()) good_shift[r] = j;


	for (int j = 0; j < what.size() - 1; j++) bad_char[(int)what[j]] = what.size() - j - 1;

	int i = 0;
	while (i <= what.size() - where.size()) {
		int j = 0;
		for (j = what.size() - 1; j >= 0 && what[j] == where[i + j]; --j);
		if (j < 0) {
			return i;
		}
		else i += max((good_shift[j + 1]), (int)(bad_char[(int)where[i + j]] - what.size() + j + 1));
	}
	return -1;
}

int NaiveSearchAlgorithm(string str, string subStr)
{
	for (int i = 0; i <= (str.size() - subStr.size()); ++i)
	{
		if (str[i] == subStr[0])
		{
			int j = 0;
			for (j = 0; j < subStr.size(); ++j)
			{
				if (str[i + j] != subStr[j]) break;
			}
			if (j == subStr.size()) return i;
		}
	}
	return -1;
}

int KMPAlgorihm (string s, string p)
{
	int i, j, N, M;
	N = s.size();
	M = p.size();

	int d[M];

	d[0] = 0;
	for(i = 1, j = 0; i < M; i++)
	{
		while(j > 0 && p[j] != p[i])
			j = d[j-1];
		if(p[j] == p[i])
			j++;
		d[i] = j;
	}

	for(i = 0, j = 0; i < N; i++)
	{
		while(j > 0 && p[j] != s[i])
			j = d[j - 1];
		if(p[j] == s[i])
            j++;
		if(j == M)
        {
            return i - j + 1;
        }
	}
	return -1;
}


int HorspoolAlgorithm(string str, string subStr)
{
	int Table[26];
	BuildShiftTable(subStr, Table);
	int m = subStr.length();
	int n = str.length();
	int i = subStr.length() - 1;
	while (i <= str.length())
	{
		int k = 0;
		while (k <= subStr.length() && subStr[m - 1 - k] == str[i - k])
		{
			k++;
		}
		if (k == m) return i - m + 1;
		else
		{
			i = i + Table[str[i] - 97];
		}
	}
	return -1;
}

// Constants
int p = 13;
int r = 4096;

long long int HashFunction(string str, int m, int start)
{
    long long int h = 0;
    for(int i = start, j=0; i <= m + start; ++i, j++)
    {
        int c = (int)str[i];
        int pow_ = pow(p, j);
        h = (h + c*pow_);
    }
    return h;
}

void RabinKarpAlgorithm(string str, string subStr, vector<int>&answer)
{
   int n = str.size();
   int m = subStr.size();

   long long int hashStr = Hash(str, m-1, 0);
   long long int hashSubStr = Hash(subStr, m-1, 0);
   for(int i = 0; i< n-m; ++i)
   {
       if(hashStr == hashSubStr)
       {
           answer.push_back(i);
       }
       hashStr = Hash(str, m-1, i+1);
   }
   if(answer.empty()) answer.push_back(-1);
}

void displayStr(vector<int> answer) {
	for (auto &element : answer)
		cout << element << " ";
}

int main()
{
	// Examples
    string str = "sabcabc";
    string subStr = "abc";
    vector<int> answer;

    cout << "Naive             : " << NaiveSearchAlgorithm(str, subStr) << endl;
    cout << "HorspoolAlgorithm : " << HorspoolAlgorithm(str, subStr) << endl;
    cout << "Boyer-Moore       : " << BoyerMooreSearchAlgorithm(str, subStr) << endl;
    cout << "KMP               : " << KMPAlgorihm(str, subStr) << endl;
    cout << "RK                : ";
    RabinKarpAlgorithm(str, subStr, answer);
	displayStr(answer);
    cout << endl;


    cin.get();
    return 0;
}
