#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>

using namespace std;

const int MatrixDimension = 4; //matrix size

void createMatrix(int genericMatrix[][MatrixDimension])
{
    int seed = rand()%2 + 1254;
    srand(seed);
    for(int i = 0; i < MatrixDimension; ++i)
    {
        for(int j = 0; j < MatrixDimension; ++j)
        {
            firstMatrix[i][j] = rand()%10 + 89;
        }
    }
}

void StrassenAlgo(int order, int firstMatrix[][MatrixDimension], int secondMatrix[][MatrixDimension], int thirdMatrix[][MatrixDimension])
{


	int A11[MatrixDimension][MatrixDimension], A12[MatrixDimension][MatrixDimension], A21[MatrixDimension][MatrixDimension], A22[MatrixDimension][MatrixDimension];
	int B11[MatrixDimension][MatrixDimension], B12[MatrixDimension][MatrixDimension], B21[MatrixDimension][MatrixDimension], B22[MatrixDimension][MatrixDimension];
	int C11[MatrixDimension][MatrixDimension], C12[MatrixDimension][MatrixDimension], C21[MatrixDimension][MatrixDimension], C22[MatrixDimension][MatrixDimension];
	int M1[MatrixDimension][MatrixDimension], M2[MatrixDimension][MatrixDimension], M3[MatrixDimension][MatrixDimension], M4[MatrixDimension][MatrixDimension], M5[MatrixDimension][MatrixDimension], M6[MatrixDimension][MatrixDimension], M7[MatrixDimension][MatrixDimension];
	int AA[MatrixDimension][MatrixDimension], BB[MatrixDimension][MatrixDimension];

	if (order == 2) {  //2-order
		multiplyMatrix(firstMatrix, secondMatrix, thirdMatrix);
	}
	else {
		for (int i = 0; i < order / 2; i++) {
			for (int j = 0; j < order / 2; j++) {
				A11[i][j] = firstMatrix[i][j];
				A12[i][j] = firstMatrix[i][j + order / 2];
				A21[i][j] = firstMatrix[i + order / 2][j];
				A22[i][j] = firstMatrix[i + order / 2][j + order / 2];

				B11[i][j] = secondMatrix[i][j];
				B12[i][j] = secondMatrix[i][j + order / 2];
				B21[i][j] = secondMatrix[i + order / 2][j];
				B22[i][j] = secondMatrix[i + order / 2][j + order / 2];
			}
		}

		addMatrix(order / 2, A11, A22, AA);
		addMatrix(order / 2, B11, B22, BB);
		StrassenAlgo(order / 2, AA, BB, M1);


		addMatrix(order / 2, A21, A22, AA);
		StrassenAlgo(order / 2, AA, B11, M2);


		subMatrix(order / 2, B12, B22, BB);
		StrassenAlgo(order / 2, A11, BB, M3);


		subMatrix(order / 2, B21, B11, BB);
		StrassenAlgo(order / 2, A22, BB, M4);


		addMatrix(order / 2, A11, A12, AA);
		StrassenAlgo(order / 2, AA, B22, M5);


		subMatrix(order / 2, A21, A11, AA);
		addMatrix(order / 2, B11, B12, BB);
		StrassenAlgo(order / 2, AA, BB, M6);


		subMatrix(order / 2, A12, A22, AA);
		addMatrix(order / 2, B21, B22, BB);
		StrassenAlgo(order / 2, AA, BB, M7);


		addMatrix(order / 2, M1, M4, AA);
		subMatrix(order / 2, M7, M5, BB);
		addMatrix(order / 2, AA, BB, C11);


		addMatrix(order / 2, M3, M5, C12);


		addMatrix(order / 2, M2, M4, C21);


		subMatrix(order / 2, M1, M2, AA);
		addMatrix(order / 2, M3, M6, BB);

		addMatrix(order / 2, AA, BB, C22);


		for (int i = 0; i < order / 2; i++) {
			for (int j = 0; j < order / 2; j++) {
				thirdMatrix[i][j] = C11[i][j];
				thirdMatrix[i][j + order / 2] = C12[i][j];
				thirdMatrix[i + order / 2][j] = C21[i][j];
				thirdMatrix[i + order / 2][j + order / 2] = C22[i][j];
			}
		}
	}


}


#pragma region helpers


void displayMatrix(int order, int thirdMatrix[][MatrixDimension]) {
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			cout << thirdMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void multiplyMatrix(int firstMatrix[][MatrixDimension], int secondMatrix[][MatrixDimension], int thirdMatrix[][MatrixDimension])
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			thirdMatrix[i][j] = 0;
			for (int t = 0; t < 2; t++) {
				thirdMatrix[i][j] = thirdMatrix[i][j] + firstMatrix[i][t] * secondMatrix[t][j];
			}
		}
	}
}

void addMatrix(int order, int firstMatrix[][MatrixDimension], int secondMatrix[][MatrixDimension], int thirdMatrix[][MatrixDimension]) {
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			thirdMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
		}
	}
}

void subMatrix(int order, int firstMatrix[][MatrixDimension], int secondMatrix[][MatrixDimension], int thirdMatrix[][MatrixDimension]) {
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			thirdMatrix[i][j] = secondMatrix[i][j] - firstMatrix[i][j];
		}
	}
}
#pragma endregion

int main() {

	long elapsed_time;

	// initialization
	int firstMatrix[MatrixDimension][MatrixDimension];
	int secondMatrix[MatrixDimension][MatrixDimension];
	int thirdMatrix[MatrixDimension][MatrixDimension];

	createMatrix(firstMatrix);
	createMatrix(secondMatrix);

	// calculate elapsed time
	auto stopwatch_start = chrono::high_resolution_clock::now();
	multiplyMatrix(firstMatrix, secondMatrix, thirdMatrix);
	auto stopwatch_finish = chrono::high_resolution_clock::now();

	elapsed_time = chrono::duration_cast<chrono::milliseconds>(
		stopwatch_finish - stopwatch_start)
		.count();

	// calculate elapsed time
    stopwatch_start = chrono::high_resolution_clock::now();
	StrassenAlgo(MatrixDimension, firstMatrix, secondMatrix, thirdMatrix);
    stopwatch_finish = chrono::high_resolution_clock::now();

	elapsed_time = chrono::duration_cast<chrono::milliseconds>(
		stopwatch_finish - stopwatch_start)
		.count();

	displayMatrix(MatrixDimension, thirdMatrix);

	cin.get();
	return 0;
}

