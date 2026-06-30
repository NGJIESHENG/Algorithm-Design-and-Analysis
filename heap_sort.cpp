// *********************************************************
// Program: heap_sort.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC1L
// Tutorial Class: TT1L
// Trimester: 2610
// Member_1: 243UC247C8 | IVAN CHEAH KA JUN | ivan.cheah.ka@student.mmu.edu.my | 0102187449
// Member_2: 243UC247D5 | NG JIE SHENG | ng.jie.sheng@student.mmu.edu.my | 01110890315
// Member_3: 243UC247BY | PAN HAN CHENG | pan.han.cheng@student.mmu.edu.my | 0166137037
// *********************************************************
// Task Distribution
// Member_1:Hash Table Search 
// Member_2:Dataset Generator, Heap Sort 
// Member_3:Radix Sort
// *********************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Record {
    long long id;
    string name;
};

// Custom swap function to avoid <algorithm> library overhead
void swapRecords(Record& a, Record& b) {
    Record temp = a;
    a = b;
    b = temp;
}

// Maintains the max-heap property
void heapifyDown(Record arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare 10-digit IDs using '>' to build a max-heap 
    // (which ultimately extracts into ascending order)
    if (left < n && arr[left].id > arr[largest].id) {
        largest = left;
    }

    if (right < n && arr[right].id > arr[largest].id) {
        largest = right;
    }

    if (largest != i) {
        swapRecords(arr[i], arr[largest]);
        heapifyDown(arr, n, largest);
    }
}

// Core Heap Sort logic
void heapSort(Record arr[], int n) {
    // Phase 1: Build the Maxheap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }

    // Phase 2: Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move the maximum element to the back of the array
        swapRecords(arr[0], arr[i]);
        // Call heapify on the reduced heap
        heapifyDown(arr, i, 0);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_csv> [output_file]" << endl;
        return 1;
    }

    string input_file = argv[1];
    string output_file = "";

    cout << "Reading data from " << input_file << "..." << endl;

    ifstream infile(input_file);
    if (!infile.is_open()) {
        cerr << "Error: Cannot open file " << input_file << endl;
        return 1;
    }

    // --- PASS 1: Count exact rows ---
    int n = 0;
    string line;
    
    // SKIP THE HEADER LINE
    getline(infile, line); 

    while (getline(infile, line)) {
        if (!line.empty()) n++;
    }
    
    // Reset file pointer back to the beginning for the second pass
    infile.clear();
    infile.seekg(0, ios::beg);

    // --- PASS 2: Dynamically allocate the raw array and load data ---
    Record* arr = new Record[n];
    int index = 0;
    
    // SKIP THE HEADER LINE AGAIN
    getline(infile, line); 

    while (getline(infile, line) && index < n) {
        int delim = line.find(',');
        if (delim != string::npos) {
            arr[index].id = stoll(line.substr(0, delim));
            arr[index].name = line.substr(delim + 1);
            index++;
        }
    }
    
    infile.close();

    cout << "Loaded " << n << " records." << endl;
    cout << "Starting Heap Sort..." << endl;

    // Start Timer
    auto start = high_resolution_clock::now();
    
    // Execute Sort
    heapSort(arr, n);
    
    // End Timer
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;

    if (argc > 2) {
        output_file = argv[2];
    } else {
        // CHANGED: output file extension is now .txt instead of .csv
        output_file = "heap_sorted_dataset_" + to_string(n) + ".txt";
    }

    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Cannot open file " << output_file << " for writing." << endl;
        delete[] arr;
        return 1;
    }

    // Write the header into the sorted file
    outfile << "ID,NAME\n";
    for (int i = 0; i < n; i++) {
        outfile << arr[i].id << "," << arr[i].name << "\n";
    }
    outfile.close();

    cout << "Heap Sort completed in " << elapsed.count() << " seconds." << endl;
    cout << "Sorted data written to " << output_file << endl;

    // Check for Ascending Order
    bool is_sorted = true;
    for (int i = 1; i < n; i++) {
        if (arr[i].id < arr[i-1].id) { 
            is_sorted = false;
            break;
        }
    }

    // Print Ascending verification message
    cout << "Verification: " << (is_sorted ? "PASSED (correctly sorted in ascending order)" : "FAILED (not sorted)") << endl;

    // Free dynamically allocated memory
    delete[] arr;
    
    return 0;
}