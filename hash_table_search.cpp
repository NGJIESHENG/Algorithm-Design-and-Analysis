#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <random>

using namespace std;

struct Record {
    long long id;
    string name;
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_csv>" << endl;
        return 1;
    }

    string input_file = argv[1];

    cout << "Reading data from " << input_file << "..." << endl;

    vector<Record> records;
    unordered_map<long long, string> hashtable;
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
            hashtable[rec.id] = rec.name;
        }
    }

    infile.close();

    cout << "Loaded " << records.size() << " records." << endl;
    cout << "Starting hash table search analysis..." << endl;

    long long n = records.size();

    long long best_case_total = 0;
    long long avg_case_total = 0;
    long long worst_case_total = 0;

    auto start_best = chrono::high_resolution_clock::now();
    for (long long i = 0; i < n; i++) {
        auto target = records[i].id;
        if (hashtable.find(target) != hashtable.end()) {
            continue;
        }
    }
    auto end_best = chrono::high_resolution_clock::now();
    best_case_total = chrono::duration_cast<chrono::nanoseconds>(end_best - start_best).count();

    auto start_avg = chrono::high_resolution_clock::now();
    for (long long i = 0; i < n; i++) {
        auto target = records[i].id;
        hashtable.find(target);
    }
    auto end_avg = chrono::high_resolution_clock::now();
    avg_case_total = chrono::duration_cast<chrono::nanoseconds>(end_avg - start_avg).count();

    auto start_worst = chrono::high_resolution_clock::now();
    for (long long i = 0; i < n; i++) {
        bool found = false;
        long long target = 123456789LL;
        for (const auto& rec : records) {
            if (rec.id == target) {
                found = true;
                break;
            }
        }
    }
    auto end_worst = chrono::high_resolution_clock::now();
    worst_case_total = chrono::duration_cast<chrono::nanoseconds>(end_worst - start_worst).count();

    double best_seconds = best_case_total / 1e9;
    double avg_seconds = avg_case_total / 1e9;
    double worst_seconds = worst_case_total / 1e9;

    string output_file = "hash_table_search_dataset_" + to_string(n) + ".txt";

    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Cannot open output file" << endl;
        return 1;
    }

    outfile << fixed << setprecision(9);
    outfile << "Best case time: " << best_seconds << " seconds" << endl;
    outfile << "Average case time: " << avg_seconds << " seconds" << endl;
    outfile << "Worst case time: " << worst_seconds << " seconds" << endl;

    outfile.close();

    cout << "Hash table search analysis completed." << endl;
    cout << "Results written to " << output_file << endl;
    cout << "Best case time: " << best_seconds << " seconds" << endl;
    cout << "Average case time: " << avg_seconds << " seconds" << endl;
    cout << "Worst case time: " << worst_seconds << " seconds" << endl;

    return 0;
}
