#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;
using std::swap;

bool IsEndOfFIleCheck(FILE *fileSource)
{
    fpos_t curPos, endPos;
    fgetpos (fileSource,&curPos);
    fseek(fileSource, 0, SEEK_END);
    fgetpos (fileSource,&endPos);
    fsetpos(fileSource, &curPos);
    if(curPos == endPos) return true;
    return false;
}


void Merge(int *dataArray, int p, int q, int r)
{
	
	int n1 = q - p + 2;
	int n2 = r - q + 1;
	int *L = new int[n1];
	int *R = new int[n2];
	CopyArray(dataArray, L, n1, p);
	CopyArray(dataArray, R, n2, q + 1);
	SortArray(dataArray, L, R, p, r);
	delete[]R;
	delete[]L;
}

void MergeSort(int *dataArray, int p, int r)
{
	if (p<r)
	{
		int q = (r + p) / 2;
		MergeSort(dataArray, p, q);
		MergeSort(dataArray, q + 1, r);
		Merge(dataArray, p, q, r);
	}
}

void WriteInFile(bool fileNumber, int n, int dataArray[]) 
{
    FILE *fileSource;
    if(fileNumber) {fileSource = fopen("BinaryFIle1.bin", "a+b");}
    else {fileSource = fopen("BinaryFIle2.bin", "a+b");}
    for(int i = 0; i < n; i++)
    {
        fwrite(&dataArray[i], sizeof(int), 1, fileSource);
    }
    fclose(fileSource);
}


void SequenceFromFile(int* dataArray, char fname[])
{
	FILE *fileSource , *a , *b;
	fileSource = fopen("BinaryFIle1.bin", "wb");
	fclose(fileSource);
	fileSource = fopen("BinaryFIle2.bin", "wb");
	fclose(fileSource);
	fileSource = fopen(fname, "r");
	bool fileNumber = 1;
	while (!feof(fileSource))
	{
		char str[4];
		int i = 0, j = 0;
		while (i < 10 && !feof(fileSource))
		{
			str[j] = fgetc(fileSource);
			if (str[j] == 32)
			{
				str[j] = '\n';
				dataArray[i] = atoi(str);
				i++;
				j = 0;
			}
			else { j++; }
		}
		MergeSort(dataArray, 0, i-1);
		WriteInFile(fileNumber, i, dataArray);
		fileNumber = !fileNumber;
	}
	cout << endl;
	fclose(fileSource);
}

void MergeTwoSequences(int S, FILE *fileSource1, FILE *fileSource2, FILE *currentFile)
{
    int fileSource1Read = 0, fileSource2Read = 0, x=0, y=0;
    while(fileSource1Read !=S && fileSource2Read!=S &&
		!IsEndOfFIleCheck(fileSource1) && 
		!IsEndOfFIleCheck(fileSource2) )
    {
        fread(&y, sizeof(int), 1, fileSource2);
        fread(&x, sizeof(int), 1, fileSource1);
        if(x <= y)
        {
            fwrite(&x, sizeof(int), 1, currentFile);
			fileSource1Read++;
            fseek(fileSource2, -sizeof(int), SEEK_CUR);
        }
        else
        {
            fwrite(&y, sizeof(int), 1, currentFile);
			fileSource2Read++;
            fseek(fileSource1, -sizeof(int), SEEK_CUR);
        }
    }
    if(fileSource1Read != S)
    {
        while(fileSource1Read !=S && !IsEndOfFIleCheck(a))
        {
            fread(&x, sizeof(int), 1, a);
            fwrite(&x, sizeof(int), 1, currentFile);
			fileSource1Read++;
        }
    }
    else if(fileSource2Read !=S)
    {
        while(fileSource2Read !=S && !IsEndOfFIleCheck(b))
        {
            fread(&y, sizeof(int), 1, b);
            fwrite(&y, sizeof(int), 1, currentFile);
			fileSource2Read++;
        }
    }
}

void DisplaySource(FILE *fileSource1, FILE *fileSource2) {
	int n = 0;
	if (IsEndOfFIleCheck(fileSource1))
	{
		while (fread(&n, sizeof(int), 1, fileSource2)) cout << n << " ";
	}
	else
	{
		while (fread(&n, sizeof(int), 1, fileSource1)) cout << n << " ";
	}
}

void PolyPhaseMerge()
{
    int Size = 10, current = 3;
    bool mergeMode = 1;
    FILE *fileSource1 = fopen("BinaryFIle1.bin", "a+b");
    FILE *fileSource2 = fopen("BinaryFIle2.bin", "a+b");
    FILE *currentFile = fopen("BinaryFIle3.bin", "wb");
    FILE *fileSource3 = fopen("BinaryFIle4.bin", "wb");
    fclose(fileSource3);

    int x = 0, y = 0;
    while(!IsEndOfFIleCheck(fileSource1) && !IsEndOfFIleCheck(fileSource2))
    {
        while(!IsEndOfFIleCheck(fileSource1) || !IsEndOfFIleCheck(fileSource2))
        {
            MergeTwoSequences(Size, fileSource1, fileSource2, currentFile);
            fclose(currentFile);
            if(current == 3)
            {
                currentFile = fopen("BinaryFIle4.bin", "a+b");
                current++;
            }
            else if(current == 4)
            {
                currentFile = fopen("BinaryFIle3.bin", "a+b");
                current--;
            }
            else if(current == 1)
            {
                currentFile = fopen("BinaryFIle2.bin", "a+b");
                current++;
            }
            else
            {
                currentFile = fopen("BinaryFIle1.bin", "a+b");
                current--;
            }
        }

        Size *= 2;
        fclose(fileSource1);
        fclose(fileSource2);
        fclose(currentFile);
        if(current == 3 || current == 4) current = 1;
        else if(current == 1 || current == 2) current = 3;
        if(mergeMode)
        {
            FILE *fileSource1 = fopen("BinaryFIle3.bin", "a+b");
            FILE *fileSource2 = fopen("BinaryFIle4.bin", "a+b");
            FILE *fileSource3 = fopen("BinaryFIle1.bin", "wb");
            FILE *currentFile = fopen("BinaryFIle2.bin", "wb");
        }
        else
        {
            FILE *fileSource1 = fopen("BinaryFIle1.bin", "a+b");
            FILE *fileSource2 = fopen("BinaryFIle2.bin", "a+b");
            FILE *fileSource3 = fopen("BinaryFIle4.bin", "wb");
            FILE *currentFile = fopen("BinaryFIle3.bin", "wb");
        }
        mergeMode = !mergeMode;
    }
    fclose(fileSource3);
    fclose(currentFile);
	DisplaySource(fileSource1, fileSource2);
    fclose(fileSource1);
    fclose(fileSource2);
}


void CopyArray(int *dataArray, int *arr, int n, int beg)
{
	int MAX = 10000;

	for (int i = 0; i < n - 1; ++i)
	{
		arr[i] = dataArray[beg + i];
	}
	arr[n - 1] = MAX;
}

void SortArray(int *dataArray, int*L, int*R, int p, int r)
{
	int i = 0, j = 0;
	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			dataArray[k] = L[i];
			i++;
		}
		else
		{
			dataArray[k] = R[j];
			j++;
		}
	}
}

int main()
{
	int dataArray[10];
	SequenceFromFile(dataArray, "Input1.txt");
	cout << "Input1, Result" << endl;
	PolyPhaseMerge();
	cout << endl;
	SequenceFromFile(dataArray, "Input2.txt");
	cout << "Input2, Result" << endl;
	PolyPhaseMerge();
	cout << endl;
	SequenceFromFile(dataArray, "Input3.txt");
	cout << "Input3, Result" << endl;
	PolyPhaseMerge();

	cin.get();
	return 0;
}
