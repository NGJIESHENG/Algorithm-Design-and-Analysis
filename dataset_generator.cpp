#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    long long num_rows = 1000;
    string filename = "";
    
    if (argc > 1) {
        num_rows = stoll(argv[1]);
    }
    if (argc > 2) {
        filename = argv[2];
    } else {
        filename = "dataset_" + to_string(num_rows) + ".csv";
    }
    
    unsigned long seed = 0;
    string seed_str = "243UC247D5";
    for (char c : seed_str) {
        seed = seed * 31 + (unsigned char)c;
    }
    
    cout << "Generating " << num_rows << " random records to " << filename << endl;
    cout << "Using seed: " << seed << endl;
    
    mt19937 generator(seed);
    uniform_int_distribution<long long> int_dist(1000000000LL, 9999999999LL); 
    uniform_int_distribution<int> char_dist(0, 25); 
    
    set<long long> used_numbers; 
    
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << " for writing." << endl;
        return 1;
    }
    
    file << "ID,NAME" << endl;
    
    long long generated = 0;
    long long attempts = 0;
    long long max_attempts = num_rows * 100; 
    
    while (generated < num_rows && attempts < max_attempts) {
        long long random_id = int_dist(generator);
        
        if (used_numbers.find(random_id) != used_numbers.end()) {
            attempts++;
            continue;
        }
        
        used_numbers.insert(random_id);
        
        string random_str = "";
        for (int i = 0; i < 5; i++) {
            random_str += (char)('a' + char_dist(generator));
        }
        
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