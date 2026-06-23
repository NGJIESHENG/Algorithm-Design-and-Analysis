// *********************************************************
// Program: heap_sort_step.cpp
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

using namespace std;

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
    outfile << "]\n";
}

void heapifyDown(Record arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

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

void heapSortDemo(Record arr[], int n, string output_file) {
    ofstream outfile(output_file);
    
    outfile << "--- INITIAL UNSORTED ARRAY ---\n";
    printArraySteps(arr, n, outfile);

    // Phase 1: Build the Maxheap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }
    
    outfile << "\n--- ARRAY AFTER BUILDING MAXHEAP ---\n";
    printArraySteps(arr, n, outfile);
    
    outfile << "\n--- EXTRACTION PHASE (SWAPPING MAX TO BACK) ---\n";
    // Phase 2: Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        swapRecords(arr[0], arr[i]); 
        heapifyDown(arr, i, 0);      
        
        outfile << "Step " << (n - i) << " (Size " << i << " remaining): ";
        printArraySteps(arr, n, outfile);
    }
    
    outfile << "\n--- FINAL SORTED ARRAY ---\n";
    printArraySteps(arr, n, outfile);
    outfile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_csv_small_dataset>" << endl;
        return 1;
    }

    string input_file = argv[1];
    ifstream infile(input_file);
    if (!infile.is_open()) {
        cerr << "Error: Cannot open file " << input_file << endl;
        return 1;
    }

    int n = 0;
    string line;
    while (getline(infile, line)) {
        if (!line.empty()) n++;
    }

    infile.clear();
    infile.seekg(0, ios::beg);

    Record* arr = new Record[n];
    int index = 0;

    // Changed to MinHeap
    MinHeap heap;
    heap.buildHeap(records, outfile);
    heap.heapSort(outfile);

    outfile.close();

    cout << "Loaded " << n << " records for Step-By-Step Demo." << endl;
    
    string output_file = "heap_sort_steps_" + to_string(n) + ".txt";
    
    heapSortDemo(arr, n, output_file);
    
    cout << "Step-by-step documentation written to " << output_file << endl;

    delete[] arr;
    return 0;
}