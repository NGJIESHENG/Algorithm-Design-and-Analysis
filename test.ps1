# Test script for all four C++ programs (Windows PowerShell)

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "Algorithm Design & Analysis - Test Suite" -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ""

# Compile all programs
Write-Host "[1/5] Compiling programs..." -ForegroundColor Yellow

$compile_output = @()
$compile_output += (g++ -std=c++17 -O2 -o dataset_generator dataset_generator.cpp 2>&1)
$compile_output += (g++ -std=c++17 -O2 -o radix_sort radix_sort.cpp 2>&1)
$compile_output += (g++ -std=c++17 -O2 -o heap_sort heap_sort.cpp 2>&1)
$compile_output += (g++ -std=c++17 -O2 -o hash_table_search hash_table_search.cpp 2>&1)

if ($compile_output -join "" -eq "") {
    Write-Host "✓ All programs compiled successfully" -ForegroundColor Green
}
else {
    Write-Host "✗ Compilation output:" -ForegroundColor Red
    $compile_output
}
Write-Host ""

# Test 1: Generate dataset
Write-Host "[2/5] Generating dataset with 5000 records..." -ForegroundColor Yellow
.\dataset_generator.exe 5000 test_dataset.csv
Write-Host ""

# Test 2: Radix Sort
Write-Host "[3/5] Testing Radix Sort..." -ForegroundColor Yellow
$start = Get-Date
.\radix_sort.exe test_dataset.csv test_radix_sorted.csv
$elapsed = ((Get-Date) - $start).TotalSeconds
Write-Host "PowerShell elapsed time: $elapsed seconds" -ForegroundColor Cyan
Write-Host ""

# Test 3: Heap Sort
Write-Host "[4/5] Testing Heap Sort..." -ForegroundColor Yellow
$start = Get-Date
.\heap_sort.exe test_dataset.csv test_heap_sorted.csv
$elapsed = ((Get-Date) - $start).TotalSeconds
Write-Host "PowerShell elapsed time: $elapsed seconds" -ForegroundColor Cyan
Write-Host ""

# Test 4: Hash Table Search
Write-Host "[5/5] Testing Hash Table Search..." -ForegroundColor Yellow
.\hash_table_search.exe test_dataset.csv
Write-Host ""

# Verify results
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "Results Verification" -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ""

Write-Host "Original dataset sample (first 3 records):" -ForegroundColor Cyan
$original = Get-Content test_dataset.csv | Select-Object -First 4 | Select-Object -Last 3
$original | ForEach-Object { Write-Host $_ }
Write-Host ""

Write-Host "Radix sorted sample (first 3 records - should be ascending):" -ForegroundColor Cyan
$radix = Get-Content test_radix_sorted.csv | Select-Object -First 4 | Select-Object -Last 3
$radix | ForEach-Object { Write-Host $_ }
Write-Host ""

Write-Host "Heap sorted sample (first 3 records - should be descending):" -ForegroundColor Cyan
$heap = Get-Content test_heap_sorted.csv | Select-Object -First 4 | Select-Object -Last 3
$heap | ForEach-Object { Write-Host $_ }
Write-Host ""

Write-Host "==========================================" -ForegroundColor Green
Write-Host "✓ All Tests Complete!" -ForegroundColor Green
Write-Host "==========================================" -ForegroundColor Green

# Clean up test files (comment out if you want to keep them)
# Remove-Item test_*.csv -ErrorAction SilentlyContinue
# Write-Host "Test files cleaned up"
