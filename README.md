# Algorithm Design & Analysis - Four C++ Programs

This project contains four C++ programs demonstrating fundamental algorithms: dataset generation, radix sort, heap sort, and hash table search.

## Programs Overview

### 1. Dataset Generator (`dataset_generator.cpp`)

**Purpose:** Generates large CSV files with randomized data for testing sorting and search algorithms.

**Features:**
- Creates records with unique 10-digit integers (1,000,000,000 - 9,999,999,999)
- Generates 5-letter lowercase strings
- Uses seed `243UC247D5` converted to numeric value for reproducible randomness
- Ensures all IDs are unique using a set
- Outputs progress every 10,000 records

**Compilation:**
```bash
g++ -std=c++17 -O2 -o dataset_generator dataset_generator.cpp
```

**Usage:**
```bash
./dataset_generator <num_records> [output_file]
```

**Example:**
```bash
./dataset_generator 1000 dataset.csv
```

**Output Format:**
```csv
ID,NAME
1843241620,nuxrn
2424211641,qhfrk
3278275433,hzuhk
```

---

### 2. Radix Sort (`radix_sort.cpp`)

**Purpose:** Implements radix sort algorithm to sort CSV files by the integer ID in ascending order.

**Algorithm Details:**
- **Time Complexity:** O(d * n) where d = number of digits (10), n = number of records
- **Space Complexity:** O(n)
- **Sorting Method:** Processes digits from rightmost (least significant) to leftmost (most significant)
- Uses counting sort as the stable sub-algorithm for each digit position
- Non-comparative sorting algorithm

**Compilation:**
```bash
g++ -std=c++17 -O2 -o radix_sort radix_sort.cpp
```

**Usage:**
```bash
./radix_sort <input_csv> [output_csv]
```

**Example:**
```bash
./radix_sort dataset.csv radix_sorted.csv
```

**Output:**
- Sorted CSV file in ascending ID order
- Console output showing:
  - Time taken to sort
  - Verification that data is correctly sorted

**Performance:**
- 1000 records: ~0.0003 seconds
- Scalable to millions of records

---

### 3. Heap Sort (`heap_sort.cpp`)

**Purpose:** Implements heap sort using a max heap to sort CSV files by integer ID in descending order.

**Algorithm Details:**
- **Time Complexity:** O(n log n) in all cases
- **Space Complexity:** O(n)
- **Sorting Method:** Uses max heap structure
  1. Build max heap from input array
  2. Repeatedly extract maximum element (root)
  3. Heapify down after extraction
- Results in descending order (opposite of radix sort)
- Excellent for in-place sorting

**Compilation:**
```bash
g++ -std=c++17 -O2 -o heap_sort heap_sort.cpp
```

**Usage:**
```bash
./heap_sort <input_csv> [output_csv]
```

**Example:**
```bash
./heap_sort dataset.csv heap_sorted.csv
```

**Output:**
- Sorted CSV file in descending ID order
- Console output showing:
  - Time taken to sort
  - Verification that data is correctly sorted

**Performance:**
- 1000 records: ~0.0002 seconds
- Consistent O(n log n) performance

---

### 4. Hash Table Search (`hash_table_search.cpp`)

**Purpose:** Implements fast searching using hash tables with detailed time tracking for best, average, and worst-case scenarios.

**Features:**
- Builds hash table (unordered_map) for O(1) average lookup
- Tracks three search time scenarios:
  - **Best Case:** Item found at first position (linear search)
  - **Average Case:** Hash table O(1) lookup (typical case)
  - **Worst Case:** Item not found or linear search through all items
- Reports number of comparisons for each search
- Summary statistics including average search time

**Compilation:**
```bash
g++ -std=c++17 -O2 -o hash_table_search hash_table_search.cpp
```

**Usage:**
```bash
./hash_table_search <input_csv> [targets_file]
```

**Example:**
```bash
./hash_table_search dataset.csv                          # Use first 10 records as targets
./hash_table_search dataset.csv targets.txt              # Use custom targets file
```

**Targets File Format:**
One target ID per line:
```
1843241620
2424211641
1111111111
```

**Output Example:**
```
=== SEARCH RESULTS ===
Target ID      Found     Best Case (ns)      Avg Case (ns)       Worst Case (ns)     Comparisons 
-------------------------------------------------------------------------------------------------
1843241620     YES       100                 500                 0                   1
1111111111     NO        1                   400                 0                   1000

=== SUMMARY ===
Total searches: 12
Found: 10
Not found: 2
Average search time: 375 ns
Average search time: 0.000375 ms
```

**Time Complexity:**
- Average case: O(1)
- Worst case: O(n) (very rare, hash collision chains)
- Building table: O(n)

---

## Compilation & Testing

### Compile All Programs:
```bash
g++ -std=c++17 -O2 -o dataset_generator dataset_generator.cpp
g++ -std=c++17 -O2 -o radix_sort radix_sort.cpp
g++ -std=c++17 -O2 -o heap_sort heap_sort.cpp
g++ -std=c++17 -O2 -o hash_table_search hash_table_search.cpp
```

### Or use Makefile:
```bash
make          # Compile all
make clean    # Remove binaries and CSV files
```

### Complete Testing Workflow:
```bash
# Generate dataset with 1000 records
./dataset_generator 1000 dataset.csv

# Sort with Radix Sort (ascending)
./radix_sort dataset.csv radix_sorted.csv

# Sort with Heap Sort (descending)
./heap_sort dataset.csv heap_sorted.csv

# Search for specific records
./hash_table_search dataset.csv
```

---

## Algorithm Comparison

| Metric | Radix Sort | Heap Sort | Hash Table |
|--------|-----------|-----------|-----------|
| Best Case | O(n) | O(n log n) | O(n) |
| Average Case | O(n) | O(n log n) | O(1) |
| Worst Case | O(n) | O(n log n) | O(n) |
| Space | O(n) | O(n) | O(n) |
| Sorting Order | Ascending | Descending | N/A |
| Stable | Yes | No | N/A |
| In-Place | No | Yes | No |
| Use Case | Integer keys | General sorting | Fast lookup |

---

## Data Structure & Format

All programs use the following CSV format:

```csv
ID,NAME
1843241620,nuxrn
2424211641,qhfrk
...
```

Where:
- **ID:** Unique 10-digit integer (1,000,000,000 - 9,999,999,999)
- **NAME:** 5-letter lowercase string (a-z)

---

## Random Seed

The dataset generator uses the string `243UC247D5` as the random seed. This is converted to a numeric value (2344223815) through character-by-character hashing:
```
seed = 0
for each character c in "243UC247D5":
    seed = seed * 31 + (unsigned char)c
```

This ensures reproducible datasets.

---

## Performance Notes

- All programs use `-O2` optimization flag
- Tested with 1000+ records on standard hardware
- Radix sort is fastest for integer sorting (linear time)
- Heap sort provides consistent O(n log n) performance
- Hash table search provides instant average-case lookup

---

## Author Notes

These implementations demonstrate:
- **Radix Sort:** Non-comparative sorting with excellent performance for fixed-size integers
- **Heap Sort:** Classic comparison-based sort with guaranteed O(n log n) performance
- **Hash Table:** Fast lookup structure with average O(1) performance
- **Dataset Generation:** Handling unique constraint generation and large file I/O

All programs include:
- Input validation and error handling
- Performance timing measurements
- Verification of correct results
- Clear console output reporting
