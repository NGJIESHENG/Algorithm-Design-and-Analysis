#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Record {
    long long id;
    string name;
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_csv> <target_id>" << endl;
        return 1;
    }

    string input_file = argv[1];
    long long target_id = stoll(argv[2]);

    unordered_map<long long, string> hashtable;
    ifstream infile(input_file);

    if (!infile.is_open()) {
        cerr << "Error: Cannot open file " << input_file << endl;
        return 1;
    }

    int total_rows = 0;
    string line;
    bool header = true;

    while (getline(infile, line)) {
        if (header) {
            header = false;
            continue;
        }

        total_rows++;

        stringstream ss(line);
        string id_str, name;
        if (getline(ss, id_str, ',') && getline(ss, name)) {
            long long id = stoll(id_str);
            hashtable[id] = name;
        }
    }
    infile.close();

    string output_file = "dataset_" + to_string(total_rows) + "_hash_table_search_step_" + to_string(target_id) + ".txt";

    ofstream outfile(output_file);
    if (!outfile.is_open()) {
        cerr << "Error: Cannot open output file" << endl;
        return 1;
    }

    auto it = hashtable.find(target_id);
    if (it != hashtable.end()) {
        outfile << target_id << " = " << target_id << "/" << it->second << endl;
    } else {
        outfile << "-1 != " << target_id << endl;
    }

    outfile.close();

    cout << "Hash table search step written to " << output_file << endl;

    return 0;
}
