#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const int MAX_SIZE = 1000000;

void bubble(int A[], int size) {
    for (int k = 0; k < size - 1; k++) {
        for (int j = 0; j < size - k - 1; j++) {
            if (A[j] > A[j + 1]) {
                swap(A[j], A[j + 1]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " inputfile outputfile" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    int A[MAX_SIZE], size = 0;
    while (inFile >> A[size] && size < MAX_SIZE) {
        size++;
    }
    inFile.close();

    bubble(A, size);

    ofstream outFile(argv[2]);
    if (!outFile) {
        cerr << "Error: Could not open output file." << endl;
        return 1;
    }

    for (int i = 0; i < size; i++) {
        outFile << A[i] << endl;
    }

    outFile.close();
    return 0;
}
