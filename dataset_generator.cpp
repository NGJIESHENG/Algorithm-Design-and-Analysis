#include <iostream>
#include <fstream>
#include <string>
#include <random>

using namespace std;

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
    
    // Seed generation based on assignment rules
    string leader_id = "243UC247CT"; // Replace with actual leader ID
    string seed_str = "";
    for (char c : leader_id) {
        if (isdigit(c)) {
            seed_str += c;
        } else if (isalpha(c)) {
            seed_str += to_string((toupper(c) - 'A' + 1) % 10);
        }
    }
    
    unsigned int seed = stoul(seed_str);
    mt19937_64 generator(seed);
    uniform_int_distribution<long long> int_dist(1000000000LL, 9999999999LL);
    uniform_int_distribution<int> char_dist(0, 25);
    
    CustomHashSet used_numbers(num_rows * 2); 
    ofstream file(filename);
    
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
    cout << "Generated " << num_rows << " records in " << filename << endl;
    return 0;
}