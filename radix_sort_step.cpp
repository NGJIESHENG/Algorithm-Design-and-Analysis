#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

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

void printRecords(ofstream& out, const vector<Record>& records) {
    out << "[";
    for (size_t i = 0; i < records.size(); i++) {
        out << records[i].id << "/" << records[i].name;
        if (i < records.size() - 1) out << ", ";
    }
    out << "]";
}

void countingSortByDigit(vector<Record>& records, int digit_pos, ofstream& out) {
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

    out << " d=" << (10 - digit_pos) << endl;
}

void radixSort(vector<Record>& records, int start_row, int end_row, ofstream& out) {
    printRecords(out, records);
    out << " original" << endl;

    for (int pos = 0; pos < 10; pos++) {
        countingSortByDigit(records, pos, out);
        printRecords(out, records);
    }
}

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

    string output_file = "dataset_" + to_string(total_rows) + "_radix_sorted_step_"
                         + to_string(start_row) + "_" + to_string(end_row) + ".txt";

    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Cannot open output file" << endl;
        return 1;
    }

    radixSort(records, start_row, end_row, outfile);
    outfile.close();

    cout << "Radix sort steps written to " << output_file << endl;

    return 0;
}
