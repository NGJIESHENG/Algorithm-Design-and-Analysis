#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Record {
    long long id;
    string name;
};

class MaxHeap {
private:
    vector<Record> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

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

public:
    void buildHeap(vector<Record>& records, ofstream& out) {
        heap = records;

        printRecords(out, heap);
        out << " initial" << endl;

        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    void heapSort(ofstream& out) {
        int counter = heap.size();
        while (!heap.empty()) {
            swap(heap[0], heap[heap.size() - 1]);
            heap.pop_back();
            counter--;

            if (!heap.empty()) {
                heapifyDown(0);
            }

            printRecords(out, heap);
            out << " i = " << counter << endl;
        }
    }

    void printRecords(ofstream& out, const vector<Record>& records) {
        out << "[";
        for (size_t i = 0; i < records.size(); i++) {
            out << records[i].id << "/" << records[i].name;
            if (i < records.size() - 1) out << ", ";
        }
        out << "]";
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_csv> [start_row] [end_row]" << endl;
        return 1;
    }

    string input_file = argv[1];
    int start_row = 0, end_row = -1;

    if (argc > 2) start_row = stoi(argv[2]);
    if (argc > 3) end_row = stoi(argv[3]);

    ifstream infile(input_file);
    if (!infile.is_open()) {
        cerr << "Error: Cannot open file " << input_file << endl;
        return 1;
    }

    int total_rows = 0;
    string line;
    bool header = true;
    vector<Record> records;

    while (getline(infile, line)) {
        if (header) {
            header = false;
            continue;
        }

        total_rows++;

        if (total_rows - 1 >= start_row && (end_row < 0 || total_rows - 1 <= end_row)) {
            stringstream ss(line);
            string id_str, name;
            if (getline(ss, id_str, ',') && getline(ss, name)) {
                Record rec;
                rec.id = stoll(id_str);
                rec.name = name;
                records.push_back(rec);
            }
        }
    }
    infile.close();

    string output_file = "dataset_" + to_string(total_rows) + "_heap_sorted_step_"
                         + to_string(start_row) + "_" + to_string(end_row) + ".txt";

    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Cannot open output file" << endl;
        return 1;
    }

    MaxHeap heap;
    heap.buildHeap(records, outfile);
    heap.heapSort(outfile);

    outfile.close();

    cout << "Heap sort steps written to " << output_file << endl;

    return 0;
}
