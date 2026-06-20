#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <sstream>

using namespace std;

struct Record {
    long long id;
    string name;
};

long long getDigit(long long num, int pos) {
    for (int i = 0; i < pos; i++) {
        num /= 10;
    }
    return num % 10;
}

void countingSortByDigit(vector<Record>& records, int digit_pos) {
    int n = records.size();
    vector<Record> output(n);
    vector<int> count(10, 0);

    for (int i = 0; i < n; i++) {
        int digit = getDigit(records[i].id, digit_pos);
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = getDigit(records[i].id, digit_pos);
        output[count[digit] - 1] = records[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        records[i] = output[i];
    }
}

void radixSort(vector<Record>& records) {
    for (int pos = 0; pos < 10; pos++) {
        countingSortByDigit(records, pos);
    }
}

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
    cout << "Starting Radix Sort..." << endl;

    auto start = chrono::high_resolution_clock::now();
    radixSort(records);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    if (argc > 2) {
        output_file = argv[2];
    } else {
        output_file = "radix_sorted_dataset_" + to_string(records.size()) + ".txt";
    }

    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Cannot open file " << output_file << " for writing." << endl;
        return 1;
    }

    outfile << "ID,NAME" << endl;
    for (const auto& rec : records) {
        outfile << rec.id << "," << rec.name << endl;
    }
    outfile.close();

    cout << "Radix Sort completed in " << elapsed.count() << " seconds." << endl;
    cout << "Sorted data written to " << output_file << endl;

    bool is_sorted = true;
    for (size_t i = 1; i < records.size(); i++) {
        if (records[i].id < records[i-1].id) {
            is_sorted = false;
            break;
        }
    }

    cout << "Verification: " << (is_sorted ? "PASSED (correctly sorted)" : "FAILED (not sorted)") << endl;

    return 0;
}
