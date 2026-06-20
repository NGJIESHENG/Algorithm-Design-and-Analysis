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

public:
    void buildHeap(vector<Record>& records) {
        heap = records;
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    vector<Record> heapSort() {
        vector<Record> sorted;

        while (!heap.empty()) {
            sorted.push_back(heap[0]);

            heap[0] = heap[heap.size() - 1];
            heap.pop_back();

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
    string output_file = "";

    cout << "Reading data from " << input_file << "..." << endl;

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
            continue;
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

    auto start = chrono::high_resolution_clock::now();

    // Changed to MinHeap
    MinHeap heap;
    heap.buildHeap(records);
    vector<Record> sorted_records = heap.heapSort();

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    if (argc > 2) {
        output_file = argv[2];
    } else {
        output_file = "heap_sort_dataset_" + to_string(sorted_records.size()) + ".csv";
    }

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

    return 0;
}