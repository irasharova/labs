#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Constants
int p = 13;
int r = 4096;

long long int HashFunction(string mainPart, int dimension_m, int start)
{
    long long int h = 0;
    for(int i = start, j=0; i <= dimension_m + start; ++i, j++)
    {
        int c = (int)mainPart[i];
        int pow_ = pow(p, j);
        h = (h + c*pow_);
    }
    return h;
}

void RabinKarpAlgorithm(string mainPart, string subPart, vector<int>&result_one)
{
   int dimension_n = mainPart.size();
   int dimension_m = subPart.size();

   long long int hashStr = HashFunction(mainPart, dimension_m-1, 0);
   long long int hashSubStr = HashFunction(subPart, dimension_m-1, 0);
   for(int i = 0; i< dimension_n-dimension_m; ++i)
   {
       if(hashStr == hashSubStr)
       {
           result_one.push_back(i);
       }
       hashStr = HashFunction(mainPart, dimension_m-1, i+1);
   }
   if(result_one.empty()) result_one.push_back(-1);
}

void MaxtrixAlgorithm(string mainMatrix[], string subMatrix[], int dimension_n, int dimension_m, int&i, int&j)
{
    vector<int> result_one;
    vector<int> result_two;
    for(int k = 0; k < dimension_n-dimension_m; ++k)
    {
        RabinKarpAlgorithm(mainMatrix[k], subMatrix[0], result_one);
        if(result_one[0] != -1)
        {
            int s = k+1;
            int l = 1;
            for(l = 1; l < dimension_m; ++l)
            {
                RabinKarpAlgorithm(mainMatrix[s], subMatrix[l], result_two);
                if(result_two[0] == -1 || result_two[0] != result_one[0])
                {
                    break;
                }
                s++;
            }
            if(l == dimension_m)
            {
                i = k;
                j = result_one[0];
                return;
            }
        }
    }
    i = -1;
    j = -1;
}

int main()
{
    string mainPart[4] = {"qhjv", "wiph", "jlmb", "opra"};
    string subPart[2] = {"hj", "ip"};

    int i = -1, j = -1;

    MaxtrixAlgorithm(mainPart, subPart, 4, 2, i, j);
    cout << i << " " << j << endl;

    cin.get();
    return 0;
}
