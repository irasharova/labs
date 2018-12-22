#include <iostream>
#include <vector>

using namespace std;

int d;

int Parent(int i) //Parent i-node
{
    return (i-1)/d;
}

int Child(int parent, int k) //k-child
{
    return parent*d + k;
}

void Balancing(vector<int> &Piramid, int i) //tree balancing
{
    int max = i;
    for(int j = 1; j <= d; ++j)
    {
        int child = Child(i, j);
        if(child < Piramid.size() && Piramid[child] > Piramid[max])
        {
            max = child;
        }
    }
    if(max != i)
    {
        swap(Piramid[i], Piramid[max]);
        Balancing(Piramid, max);
    }
}

void Increase_Key(vector<int> &Piramid, int i, int key) //Increase Key to equal
{
    if(key < Piramid[i])
    {
        cout << "Key is less then current" << endl;
        return;
    }
    Piramid[i] = key;
    while(i > 0 && Piramid[Parent(i)] < Piramid[i])
    {
        swap(Piramid[i], Piramid[Parent(i)]);
        i = Parent(i);
    }
}

void Insert(vector<int> &Piramid, int key) //Insert Element to Piramid
{
    Piramid.push_back(-1000);
    Increase_Key(Piramid, Piramid.size()-1, key);

}

void DisplayVector(vector<int> Piramid) {
	for (auto &pira : Piramid)
		cout << pira << " ";
}

int main()
{
    d = 3;
    vector<int> Piramid = { 72, 160, 82, 144, 56,20, 30, 80, 74, 22, 21, 32, 126, 13 };
    Balancing(Piramid, 0);
	DisplayVector(Piramid);
    cout << endl;
    Increase_Key(Piramid, 6, 42);
	DisplayVector(Piramid);
    cout << endl;
    Insert(Piramid, 31);
	DisplayVector(Piramid);
    cin.get();
    return 0;
}
