#include <iostream>
#include <vector>

#include "PriorityQueue.h"
#include "HuffmanTree.h"
#include "HuffmanAlgorithm.h"

int main(){

	
	
	

	std::vector<int> vec= { 22, 1, 80, 60, 2, 6, 0 };
	int* array[7];


	for (decltype(vec.size()) i = 0; i < vec.size(); i++) {

		int* ptr = new int;

		*ptr = vec[i];
		array[i] = ptr;

		ptr = nullptr;

	} // end for 
	

	PriorityQueue<int> testQ1;

	for (int i = 5; i >= 0; i--) {

		int* num = new int;
		*num = i;
		testQ1.insert(num);
		num = nullptr;
	}
	

	PriorityQueue<int> testQ2(array, 7);

	PriorityQueue<int> testQ3;

	testQ3 = testQ1;

	testQ1.~PriorityQueue();
	
	HuffmanTree T1('a', 2);
	HuffmanTree T2('b', 3);
	HuffmanTree T3('y', 8);
	HuffmanTree T4('x', 2);

	HuffmanTree T5(T1);

	HuffmanTree T6 = T4;

	HuffmanTree T7(T1, T2);

	HuffmanTree T8(T7, T4);
	
	

	/* HuffmanTree Algorithm Testing */
	
	
	// Create random counts
	int counts[NUM_LETTERS];
	for (int i = 0; i < NUM_LETTERS; i++) {
		counts[i] = rand() % 1000;
	}

	// Construct Huffman codes and display table
	HuffmanAlgorithm code(counts);

	std::cout << code << std::endl;

	int counts2[NUM_LETTERS];
	for (int i = 0; i < NUM_LETTERS; i++) {
		counts2[i] = rand() % 10000;
	}
	

	HuffmanAlgorithm code2(counts2);
	std::cout << code2 << std::endl;


	// Simple test of encoding words
	std::cout << "+=====+ Encoding Test +=====+" << std::endl;
	std::cout << "test:  " << code.getWord("test") << std::endl;
	std::cout << "least: " << code.getWord("least") << std::endl;

	std::cout << "Hello to the World: " << code.getWord("Hello to the World") << std::endl;
	std::cout << std::endl;

	std::string testCode = code.getWord("test");
	std::string leastCode = code.getWord("least");
	std::string hellCode = code.getWord("Hello to the World");

	// Simple test of decoding words
	std::cout << "+=====+ decoding Test +=====+" << std::endl;
	std::cout << testCode << ": " << code.decipher(testCode) << std::endl;
	std::cout << leastCode << ": " << code.decipher(leastCode) << std::endl;
	std::cout << hellCode << ": " << code.decipher(hellCode) << std::endl;
	std::cout << std::endl;
	
	return 0;


} // end if