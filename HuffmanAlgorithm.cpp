/** @file HuffmanAlgorithm.cpp
 @author Anthony Campos
 @date 01/26/2022
 This implementation file implements a HuffmanAlgorithm object made up of a
 std::string codebook and HuffmanTree codeTree per provided count/weight of chars 'a' - 'z' */

//---------------------------------------------------------------------------
// HuffmanAlgorithm class:  Huffman Coding implementation
//   included features:
//   -- allows construction by int array that represents char counts for 'a' - 'z' 
//   -- allows for input text/string to be encoded by the HuffmanTree codeTree
//   -- allows for decipher of a input code per the HuffmanTree codeTree
//
// Assumptions:
//   --  index 0-25 represents 'a' - 'z' .
//	  --  text that only contains 'a' - 'z' will be provided to encode 
//---------------------------------------------------------------------------


// included .h files
#include "HuffmanAlgorithm.h"

/** Overloaded Ostream Method
diplays the HuffmanAlgorithm object to ostream stream
@pre None
@post prints out in the following format:
example:

	+=====+ Huffman Code Table +=====+
		  char: a ||  Code: 1001000
		  char: b ||  Code: 10011
		  char: c ||  Code: 00010
		  char: d ||  Code: 11110
		  char: e ||  Code: 000011
		  char: f ||  Code: 0011
		  char: g ||  Code: 11010
		  char: h ||  Code: 00011
		  char: i ||  Code: 1100
		  char: j ||  Code: 01111
		  char: k ||  Code: 0010
		  char: l ||  Code: 1001001
		  char: m ||  Code: 100101
		  char: n ||  Code: 0101
		  char: o ||  Code: 1011
		  char: p ||  Code: 11011
		  char: q ||  Code: 1110
		  char: r ||  Code: 1010
		  char: s ||  Code: 0110
		  char: t ||  Code: 01110
		  char: u ||  Code: 01001
		  char: v ||  Code: 11111
		  char: w ||  Code: 1000
		  char: x ||  Code: 000010
		  char: y ||  Code: 00000
		  char: z ||  Code: 01000
	+=====+ +================+ +=====+

@param ostream [out] and HuffmanAlgorith [object]
@return ostream object that represents an HuffmanAlgorith*/
std::ostream& operator<<(std::ostream& out, const HuffmanAlgorithm& object) {


	out << "+=====+ Huffman Code Table +=====+\n";
	
	char outputChar = 'a';
	for (int i = 0; i < NUM_LETTERS; ++i) {

		out << "     char: " << outputChar<< " || " << " Code: " << object.codebook_[i] << "\n";

		++outputChar;

	} // end for 

	out << "+=====+ +================+ +=====+\n";

	return out;


} // End of Overloaded Operator




/** Constructor
@pre all indexes must have a integer value
@post HuffmanAlgorithm Object is created, construct the Huffman tree, codeTree_ and computes the code
for each character, computed codes stored in codebook_.
@parm int* [] [count], frequency for each letter from 'a' to 'z'.*/
HuffmanAlgorithm::HuffmanAlgorithm(int(&counts)[NUM_LETTERS]) {

	// Note that counts[0] is the frequency for the letter 'a' 
	// and counts[25] is the frequency for the letter 'z'. 

	HuffmanTree* treeArray[NUM_LETTERS];
	
	char startChar = 'a';

	for (int i = 0; i < NUM_LETTERS; ++i) {

		HuffmanTree* tempTreePtr = new HuffmanTree(startChar, counts[i]);

		treeArray[i] = tempTreePtr;
		++startChar;

	} // End of for

	
	PriorityQueue<HuffmanTree> heap(treeArray, NUM_LETTERS);

	while (heap.size() > 0) {

		HuffmanTree* firstMinPtr = heap.deleteMin();

		HuffmanTree* secondMinPtr = heap.deleteMin();

		HuffmanTree* tempTreePtr = nullptr;

		if (firstMinPtr != nullptr && secondMinPtr != nullptr) {

			tempTreePtr = new HuffmanTree(*firstMinPtr, *secondMinPtr);
			heap.insert(tempTreePtr);

		} // End if 

		if (firstMinPtr != nullptr && secondMinPtr == nullptr) {
			codeTree_ = *firstMinPtr;
		} // End if 
		
		delete firstMinPtr;
		firstMinPtr = nullptr;
		delete secondMinPtr;
		secondMinPtr = nullptr;


	} // end while


	codeTree_.encode(codebook_);

} // End of Constructor 

HuffmanAlgorithm::~HuffmanAlgorithm() {

	codeTree_.~HuffmanTree();

} // End of Destructor 

/** getWord
@pre string greater then 0 in size, only contains lower case letters
@post all lowercase letters of provided string are encoded using the codes stored in the codebook_.
calls decrypt
@parm std::string [in], text to be converted with Huffman Coding
@return string that represents the provided text encoded*/
std::string HuffmanAlgorithm::getWord(std::string in) const{
	
	
	std::string code{};

	for (unsigned int i = 0; i < in.size(); ++i) {

		char c = in[i];
		// only valid char 'a' - 'z'
		if (c >= 'a' && c <= 'z') {

			code += decrypt(c);

		} // end if

	} // End for 

	return code;

} // End getWord

/** decrypt
@pre None
@post code return for char 'a' to 'z'
@parm char [targetChar]
@return string that represents code for the provided char 'a' to 'z'*/
std::string HuffmanAlgorithm::decrypt(const char targetChar) const {

	std::string code{};

	code = codebook_[targetChar - 'a'];

	return code;

} // End of decode

/** decipher
@pre provided code was generated by current HuffmanAlgorithm's codebook
@post text representation of the code is computed.
@parm std::string [in], code to be converted to text with Huffman Coding
@return text representation of provided code*/
std::string HuffmanAlgorithm::decipher(std::string in) const {

	std::string text{};

	text = codeTree_.decode(in);

	return text;


} // End of decode 



