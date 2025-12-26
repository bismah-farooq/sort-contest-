#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " COUNT MIN MAX" << endl;
        return 1;
    }

    int count = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    if (min > max) {
        cerr << "Error: MIN cannot be greater than MAX." << endl;
        return 1;
    }

    ofstream outFile("numbers.dat");
    if (!outFile) {
        cerr << "Error: Could not open numbers.dat for writing." << endl;
        return 1;
    }

    srand(time(0));
    for (int i = 0; i < count; i++) {
        outFile << (rand() % (max - min + 1)) + min << endl;
    }

    outFile.close();
    return 0;
}
