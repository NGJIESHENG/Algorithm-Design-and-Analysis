CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGETS = dataset_generator radix_sort heap_sort hash_table_search

all: $(TARGETS)

dataset_generator: dataset_generator.cpp
	$(CXX) $(CXXFLAGS) -o dataset_generator dataset_generator.cpp

radix_sort: radix_sort.cpp
	$(CXX) $(CXXFLAGS) -o radix_sort radix_sort.cpp

heap_sort: heap_sort.cpp
	$(CXX) $(CXXFLAGS) -o heap_sort heap_sort.cpp

hash_table_search: hash_table_search.cpp
	$(CXX) $(CXXFLAGS) -o hash_table_search hash_table_search.cpp

clean:
	del /Q $(TARGETS) *.csv 2>nul || true

.PHONY: all clean
