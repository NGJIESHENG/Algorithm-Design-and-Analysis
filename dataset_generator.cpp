#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    // Get number of rows from command line, default to 1000
    int num_rows = 1000;
    string filename = "dataset.csv";
    
    if (argc > 1) {
        num_rows = stoi(argv[1]);
    }
    if (argc > 2) {
        filename = argv[2];
    }
    
    // Create seed from "243UC247D5"
    // Convert to numeric seed by hashing or using as-is
    unsigned long seed = 0;
    string seed_str = "243UC247D5";
    for (char c : seed_str) {
        seed = seed * 31 + (unsigned char)c;
    }
    
    cout << "Generating " << num_rows << " random records to " << filename << endl;
    cout << "Using seed: " << seed << endl;
    
    mt19937 generator(seed);
    uniform_int_distribution<long long> int_dist(1000000000LL, 9999999999LL); // 10-digit numbers
    uniform_int_distribution<int> char_dist(0, 25); // a-z
    
    set<long long> used_numbers; // Track unique numbers
    
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << " for writing." << endl;
        return 1;
    }
    
    // Write header
    file << "ID,NAME" << endl;
    
    int generated = 0;
    int attempts = 0;
    int max_attempts = num_rows * 100; // Prevent infinite loop
    
    while (generated < num_rows && attempts < max_attempts) {
        long long random_id = int_dist(generator);
        
        // Check uniqueness
        if (used_numbers.find(random_id) != used_numbers.end()) {
            attempts++;
            continue;
        }
        
        used_numbers.insert(random_id);
        
        // Generate 5-letter lowercase string
        string random_str = "";
        for (int i = 0; i < 5; i++) {
            random_str += (char)('a' + char_dist(generator));
        }
        
        // Write to CSV
        file << random_id << "," << random_str << endl;
        generated++;
        attempts++;
        
        if (generated % 10000 == 0) {
            cout << "Generated " << generated << " records..." << endl;
        }
    }
    
    file.close();
    
    if (generated < num_rows) {
        cerr << "Warning: Only generated " << generated << " unique records out of " << num_rows << endl;
    } else {
        cout << "Successfully generated " << num_rows << " records." << endl;
    }
    
    return 0;
}
