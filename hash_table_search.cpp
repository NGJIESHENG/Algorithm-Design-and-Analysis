#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <iomanip>

using namespace std;

struct Record {
    long long id;
    string name;
};

struct SearchResult {
    long long target;
    bool found;
    long long best_case_ns;
    long long worst_case_ns;
    long long average_case_ns;
    int comparisons;
};

class HashTableSearch {
private:
    unordered_map<long long, string> hash_table;
    vector<Record> records; // For linear search comparison
    
public:
    void buildHashTable(const vector<Record>& data) {
        records = data;
        for (const auto& rec : data) {
            hash_table[rec.id] = rec.name;
        }
        cout << "Hash table built with " << hash_table.size() << " records." << endl;
    }
    
    // Best case: element found at first position (linear search)
    long long linearSearchBestCase(long long target) {
        auto start = chrono::high_resolution_clock::now();
        
        for (const auto& rec : records) {
            if (rec.id == target) {
                auto end = chrono::high_resolution_clock::now();
                return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }
    
    // Worst case: element not found or at last position (linear search)
    long long linearSearchWorstCase(long long target) {
        auto start = chrono::high_resolution_clock::now();
        
        for (const auto& rec : records) {
            if (rec.id == target) {
                auto end = chrono::high_resolution_clock::now();
                return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }
    
    // Average case: O(1) for hash table lookup
    long long hashTableSearch(long long target) {
        auto start = chrono::high_resolution_clock::now();
        
        auto it = hash_table.find(target);
        bool found = (it != hash_table.end());
        
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }
    
    // Search and return comprehensive results
    SearchResult search(long long target) {
        SearchResult result;
        result.target = target;
        
        // Hash table search (average case)
        auto start_avg = chrono::high_resolution_clock::now();
        auto it = hash_table.find(target);
        result.found = (it != hash_table.end());
        auto end_avg = chrono::high_resolution_clock::now();
        result.average_case_ns = chrono::duration_cast<chrono::nanoseconds>(end_avg - start_avg).count();
        
        // Best case: first element in records
        if (!records.empty()) {
            auto start_best = chrono::high_resolution_clock::now();
            if (records[0].id == target) {
                auto end_best = chrono::high_resolution_clock::now();
                result.best_case_ns = chrono::duration_cast<chrono::nanoseconds>(end_best - start_best).count();
            } else {
                result.best_case_ns = chrono::duration_cast<chrono::nanoseconds>(start_best - start_best).count() + 1; // Minimal time
            }
        }
        
        // Worst case: linear search through all elements or not found
        auto start_worst = chrono::high_resolution_clock::now();
        bool found_worst = false;
        for (const auto& rec : records) {
            if (rec.id == target) {
                found_worst = true;
                break;
            }
        }
        auto end_worst = chrono::high_resolution_clock::now();
        result.worst_case_ns = chrono::duration_cast<chrono::nanoseconds>(end_worst - start_worst).count();
        
        result.comparisons = result.found ? 1 : (int)records.size();
        
        return result;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_csv> [targets_file]" << endl;
        return 1;
    }
    
    string input_file = argv[1];
    string targets_file = "";
    
    if (argc > 2) {
        targets_file = argv[2];
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
    
    // Build hash table
    HashTableSearch search_engine;
    search_engine.buildHashTable(records);
    
    // Get targets
    vector<long long> targets;
    
    if (!targets_file.empty()) {
        // Read from targets file
        ifstream targets_in(targets_file);
        if (targets_in.is_open()) {
            string target_line;
            while (getline(targets_in, target_line)) {
                try {
                    targets.push_back(stoll(target_line));
                } catch (...) {
                    continue;
                }
            }
            targets_in.close();
        } else {
            cerr << "Warning: Cannot open targets file " << targets_file << endl;
            // Use first few records as targets
            for (size_t i = 0; i < min((size_t)10, records.size()); i++) {
                targets.push_back(records[i].id);
            }
        }
    } else {
        // Use first 10 records as targets
        for (size_t i = 0; i < min((size_t)10, records.size()); i++) {
            targets.push_back(records[i].id);
        }
        // Also test with some non-existent IDs
        targets.push_back(1111111111LL);
        targets.push_back(9999999999LL);
    }
    
    cout << "\n=== SEARCH RESULTS ===" << endl;
    cout << left << setw(15) << "Target ID" 
         << setw(10) << "Found" 
         << setw(20) << "Best Case (ns)"
         << setw(20) << "Avg Case (ns)"
         << setw(20) << "Worst Case (ns)"
         << setw(12) << "Comparisons" << endl;
    cout << string(97, '-') << endl;
    
    long long total_avg = 0;
    int found_count = 0;
    
    for (long long target : targets) {
        SearchResult result = search_engine.search(target);
        total_avg += result.average_case_ns;
        if (result.found) found_count++;
        
        cout << left << setw(15) << result.target
             << setw(10) << (result.found ? "YES" : "NO")
             << setw(20) << result.best_case_ns
             << setw(20) << result.average_case_ns
             << setw(20) << result.worst_case_ns
             << setw(12) << result.comparisons << endl;
    }
    
    cout << "\n=== SUMMARY ===" << endl;
    cout << "Total searches: " << targets.size() << endl;
    cout << "Found: " << found_count << endl;
    cout << "Not found: " << (targets.size() - found_count) << endl;
    cout << "Average search time: " << (total_avg / (long long)targets.size()) << " ns" << endl;
    cout << "Average search time: " << fixed << setprecision(6) 
         << (total_avg / (double)targets.size() / 1000000) << " ms" << endl;
    
    return 0;
}
