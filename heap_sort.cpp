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

// Changed from MaxHeap to MinHeap
class MinHeap {
private:
    vector<Record> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyDown(int i) {
        int smallest = i; // Changed 'largest' to 'smallest'
        int left = leftChild(i);
        int right = rightChild(i);

        // Change: heap[left].id < heap[smallest].id
        if (left < (int)heap.size() && heap[left].id < heap[smallest].id) {
            smallest = left;
        }

        // Change: heap[right].id < heap[smallest].id
        if (right < (int)heap.size() && heap[right].id < heap[smallest].id) {
            smallest = right;
        }

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int i) {
        // Change: heap[i].id < heap[parent(i)].id
        if (i > 0 && heap[i].id < heap[parent(i)].id) {
            swap(heap[i], heap[parent(i)]);
            heapifyUp(parent(i));
        }
    }

    if (largest != i) {
        swapRecords(arr[i], arr[largest]);
        heapifyDown(arr, n, largest);
    }
}

void heapSort(Record arr[], int n) {
    // Phase 1: Build the Maxheap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }
    // Phase 2: Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        swapRecords(arr[0], arr[i]); 
        heapifyDown(arr, i, 0);      
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_csv>" << endl;
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

    // Pass 1: Count exact rows
    int n = 0;
    string line;
    while (getline(infile, line)) {
        if (!line.empty()) n++;
    }

    infile.clear();
    infile.seekg(0, ios::beg);

    // Pass 2: Dynamically allocate the raw array
    Record* arr = new Record[n];
    int index = 0;

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

    auto start = high_resolution_clock::now();
    heapSort(arr, n);
    auto end = high_resolution_clock::now();

    // Changed to MinHeap
    MinHeap heap;
    heap.buildHeap(records);
    vector<Record> sorted_records = heap.heapSort();

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    if (argc > 2) {
        output_file = argv[2];
    } else {
        output_file = "heap_sort_dataset_" + to_string(sorted_records.size()) + ".txt";
    }

    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Cannot open file " << output_file << " for writing." << endl;
        delete[] arr;
        return 1;
    }

    for (int i = 0; i < n; i++) {
        outfile << arr[i].id << "," << arr[i].name << "\n";
    }
    outfile.close();

    cout << "Heap Sort completed in " << elapsed.count() << " seconds." << endl;
    cout << "Sorted data written to " << output_file << endl;

    // Change: Check for Ascending Order
    bool is_sorted = true;
    for (size_t i = 1; i < sorted_records.size(); i++) {
        if (sorted_records[i].id < sorted_records[i-1].id) { 
            is_sorted = false;
            break;
        }
    }

    // Change: Print Ascending verification message
    cout << "Verification: " << (is_sorted ? "PASSED (correctly sorted in ascending order)" : "FAILED (not sorted)") << endl;

    delete[] arr;
    return 0;
}