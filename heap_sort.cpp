#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>

using namespace std;

struct Record {
    long long id;
    string name;
};

class MaxHeap {
private:
    vector<Record> heap;
    
    // Get parent index
    int parent(int i) { return (i - 1) / 2; }
    
    // Get left child index
    int leftChild(int i) { return 2 * i + 1; }
    
    // Get right child index
    int rightChild(int i) { return 2 * i + 2; }
    
    // Heapify down to maintain max heap property
    void heapifyDown(int i) {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (left < (int)heap.size() && heap[left].id > heap[largest].id) {
            largest = left;
        }
        
        if (right < (int)heap.size() && heap[right].id > heap[largest].id) {
            largest = right;
        }
        
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }
    
    // Heapify up to maintain max heap property
    void heapifyUp(int i) {
        if (i > 0 && heap[i].id > heap[parent(i)].id) {
            swap(heap[i], heap[parent(i)]);
            heapifyUp(parent(i));
        }
    }
    
public:
    // Build heap from vector
    void buildHeap(vector<Record>& records) {
        heap = records;
        // Start from last non-leaf node and heapify down
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
    // Extract max and return sorted array
    vector<Record> heapSort() {
        vector<Record> sorted;
        
        while (!heap.empty()) {
            // Max element is at root
            sorted.push_back(heap[0]);
            
            // Move last element to root
            heap[0] = heap[heap.size() - 1];
            heap.pop_back();
            
            // Heapify down
            if (!heap.empty()) {
                heapifyDown(0);
            }
        }
        
        return sorted;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_csv> [output_csv]" << endl;
        return 1;
    }
    
    string input_file = argv[1];
    string output_file = "heap_sorted.csv";
    
    if (argc > 2) {
        output_file = argv[2];
    }
    
    cout << "Reading data from " << input_file << "..." << endl;
    
    // Read CSV file
    vector<Record> records;
    ifstream infile(input_file);
    
    if (!infile.is_open()) {
        cerr << "Error: Cannot open file " << input_file << endl;
        return 1;
    }
    
    string line;
    bool header = true;
    
    while (getline(infile, line)) {
        if (header) {
            header = false;
            continue; // Skip header
        }
        
        stringstream ss(line);
        string id_str, name;
        
        if (getline(ss, id_str, ',') && getline(ss, name)) {
            Record rec;
            rec.id = stoll(id_str);
            rec.name = name;
            records.push_back(rec);
        }
    }
    
    infile.close();
    
    cout << "Loaded " << records.size() << " records." << endl;
    cout << "Starting Heap Sort..." << endl;
    
    // Create heap and sort
    auto start = chrono::high_resolution_clock::now();
    
    MaxHeap heap;
    heap.buildHeap(records);
    vector<Record> sorted_records = heap.heapSort();
    
    auto end = chrono::high_resolution_clock::now();
    
    chrono::duration<double> elapsed = end - start;
    
    // Write sorted data to output file
    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Cannot open file " << output_file << " for writing." << endl;
        return 1;
    }
    
    outfile << "ID,NAME" << endl;
    for (const auto& rec : sorted_records) {
        outfile << rec.id << "," << rec.name << endl;
    }
    outfile.close();
    
    cout << "Heap Sort completed in " << elapsed.count() << " seconds." << endl;
    cout << "Sorted data written to " << output_file << endl;
    
    // Verify sorted (note: heap sort produces descending order due to max heap)
    bool is_sorted = true;
    for (size_t i = 1; i < sorted_records.size(); i++) {
        if (sorted_records[i].id > sorted_records[i-1].id) {
            is_sorted = false;
            break;
        }
    }
    
    cout << "Verification: " << (is_sorted ? "PASSED (correctly sorted in descending order)" : "FAILED (not sorted)") << endl;
    
    return 0;
}
