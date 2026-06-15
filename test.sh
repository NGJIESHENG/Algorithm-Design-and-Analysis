#!/bin/bash
# Test script for all four C++ programs

echo "=========================================="
echo "Algorithm Design & Analysis - Test Suite"
echo "=========================================="
echo ""

# Compile all programs
echo "[1/5] Compiling programs..."
g++ -std=c++17 -O2 -o dataset_generator dataset_generator.cpp
g++ -std=c++17 -O2 -o radix_sort radix_sort.cpp
g++ -std=c++17 -O2 -o heap_sort heap_sort.cpp
g++ -std=c++17 -O2 -o hash_table_search hash_table_search.cpp

if [ $? -eq 0 ]; then
    echo "✓ All programs compiled successfully"
else
    echo "✗ Compilation failed"
    exit 1
fi
echo ""

# Test 1: Generate dataset
echo "[2/5] Generating dataset with 10000 records..."
./dataset_generator 10000 test_dataset.csv
echo ""

# Test 2: Radix Sort
echo "[3/5] Testing Radix Sort..."
time ./radix_sort test_dataset.csv test_radix_sorted.csv
echo ""

# Test 3: Heap Sort
echo "[4/5] Testing Heap Sort..."
time ./heap_sort test_dataset.csv test_heap_sorted.csv
echo ""

# Test 4: Hash Table Search
echo "[5/5] Testing Hash Table Search..."
./hash_table_search test_dataset.csv
echo ""

# Verify results
echo "=========================================="
echo "Results Verification"
echo "=========================================="
echo ""

echo "Original dataset sample (first 3 records):"
head -4 test_dataset.csv | tail -3
echo ""

echo "Radix sorted sample (first 3 records - should be ascending):"
head -4 test_radix_sorted.csv | tail -3
echo ""

echo "Heap sorted sample (first 3 records - should be descending):"
head -4 test_heap_sorted.csv | tail -3
echo ""

echo "=========================================="
echo "Test Complete!"
echo "=========================================="
