// *********************************************************
// Program: dataset_generator.cpp
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
#include <random>
#include <chrono> // Added for timing

using namespace std;
using namespace std::chrono; 

// Custom Hash Set to avoid using banned standard libraries
struct HashNode {
    long long id;
    HashNode* next;
};

class CustomHashSet {
    HashNode** table;
    int size;
public:
    CustomHashSet(int s) {
        size = s;
        table = new HashNode*[size]();
    }
    ~CustomHashSet() {
        for(int i = 0; i < size; i++) {
            HashNode* curr = table[i];
            while(curr) {
                HashNode* prev = curr;
                curr = curr->next;
                delete prev;
            }
        }
        delete[] table;
    }
    bool insert(long long id) {
        int index = id % size;
        HashNode* curr = table[index];
        while(curr) {
            if(curr->id == id) return false; // Already exists
            curr = curr->next;
        }
        HashNode* newNode = new HashNode{id, table[index]};
        table[index] = newNode;
        return true;
    }
};

int main(int argc, char* argv[]) {
    int num_rows = 1000;
    if (argc > 1) num_rows = stoi(argv[1]);
    
    string filename = "dataset_" + to_string(num_rows) + ".csv";
    
    // Seed generation
    string leader_id = "243UC247D5"; 
    string seed_str = "";
    for (char c : leader_id) {
        if (isdigit(c)) {
            seed_str += c;
        } else if (isalpha(c)) {
            seed_str += to_string((toupper(c) - 'A' + 1) % 10);
        }
    }
    
    
    auto start_time = high_resolution_clock::now();
    
    unsigned int seed = stoul(seed_str);
    mt19937_64 generator(seed);
    uniform_int_distribution<long long> int_dist(1000000000LL, 9999999999LL);
    uniform_int_distribution<int> char_dist(0, 25);
    
    CustomHashSet used_numbers(num_rows * 2); 
    ofstream file(filename);

    file << "ID,NAME\n";
    
    int generated = 0;
    while (generated < num_rows) {
        long long random_id = int_dist(generator);
        if (used_numbers.insert(random_id)) {
            string random_str = "";
            for (int i = 0; i < 5; i++) {
                random_str += (char)('a' + char_dist(generator));
            }
            file << random_id << "," << random_str << "\n";
            generated++;
        }
    }
    
    file.close();
    
    // Stop the timer
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop_time - start_time);
    
    cout << "Generated " << num_rows << " records in " << filename << endl;
    cout << "Dataset Generation Runtime: " << duration.count() / 1000000.0 << " seconds" << endl;
    
    return 0;
}