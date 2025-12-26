#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

const int NUM_THREADS = 16;
const int SIZE = 1000000;
const int SECTION_SIZE = SIZE / NUM_THREADS;
int* numbers; // Dynamic array for storing numbers
long long total_swaps = 0; // Global swap counter
mutex swap_mutex; // Mutex for protecting swap count

// Bubble Sort function (per thread)
void bubble(int* arr, int size, int thread_id) {
    long long local_swaps = 0; // Track swaps per thread
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                local_swaps++;
            }
        }
    }
    
    // Safely update the global swap count
    swap_mutex.lock();
    total_swaps += local_swaps;
    swap_mutex.unlock();
    cout << "Thread " << thread_id << " swap count: " << local_swaps << endl;
}

// Merging two sorted sections
void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

// Merging all sorted sections iteratively
void mergeSections() {
    int step = SECTION_SIZE;
    while (step < SIZE) {
        for (int i = 0; i < SIZE; i += 2 * step) {
            int left = i;
            int mid = min(i + step - 1, SIZE - 1);
            int right = min(i + 2 * step - 1, SIZE - 1);
            merge(numbers, left, mid, right);
        }
        step *= 2;
    }
}

// Read numbers from file into dynamic array
void readNumbers(const string& filename, int num_count) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open " << filename << endl;
        exit(1);
    }
    numbers = new int[num_count]; // Dynamically allocate memory
    for (int i = 0; i < num_count; i++) {
        file >> numbers[i];
    }
    file.close();
}

// Write sorted numbers to output file
void writeNumbers(const string& filename, int num_count) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error: Could not open " << filename << endl;
        exit(1);
    }
    for (int i = 0; i < num_count; i++) {
        file << numbers[i] << endl;
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " input_file output_file [-test]" << endl;
        return 1;
    }
    string input_file = argv[1];
    string output_file = argv[2];
    int num_count = SIZE;
    // If "-test" is provided, use only 10,000 numbers
    if (argc == 4 && string(argv[3]) == "-test") {
        num_count = 10000;
    }
    readNumbers(input_file, num_count);
    thread threads[NUM_THREADS];
    // Create threads to sort each section
    for (int i = 0; i < NUM_THREADS; i++) {
        int start = i * SECTION_SIZE;
        int size = (i == NUM_THREADS - 1) ? num_count - start : SECTION_SIZE;
        threads[i] = thread(bubble, &numbers[start], size, i);
    }
    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    mergeSections();
    writeNumbers(output_file, num_count);
    cout << "Total Swaps: " << total_swaps << endl;
    delete[] numbers; // Free allocated memory
    return 0;
}
