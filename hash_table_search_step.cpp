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

    string output_file = "dataset_" + to_string(target_id) + "_hash_table_search_step_target.txt";

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
