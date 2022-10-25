
/** @file HuffmanTree.cpp
 @author Anthony Campos
 @date 01/26/2022
 This implementation file implements a HuffmanTree of HuffNodes
	that hold a char and the int count of the specific char */

//---------------------------------------------------------------------------
// HuffmanTree class:  Tree data structure
//   included features:
//   -- allows for construction by char & int, HuffmanTree, 
//			and HuffmanTree & HuffmanTree
//   -- allows for comparison of 2 HuffmanTree, by their roots
//   -- allows for assignment and copy of 2 HuffmanTrees
//   -- provides Huffuman encoder and decoder
//
// Assumptions:
//   -- Non-leaves should store the sum of the weights of the descendant leaves.
//---------------------------------------------------------------------------


// included .h files
#include "HuffmanTree.h"



/** Constructors & Destructor */

/** Default HuffNode Constructor
@pre None
@post HuffNode Object created */

HuffmanTree::HuffNode::HuffNode() 
	:item_('\0'), count_(0), leftChild_(nullptr), rightChild_(nullptr)
{} // End of HuffNode Constructor


/** Defualt Constructor
@pre None
@post Empty HuffmanTree Object created*/
HuffmanTree::HuffmanTree() 
:root_(nullptr)
{} // End of Constuctor

/** Constructor
@pre letter is a valid char, count > 1 & count < 2147483647
@post Empty HuffmanTree Object created
@param char [letter], int [count]*/
HuffmanTree::HuffmanTree(const char& letter, const int& count) 
{
	root_ = new HuffNode;
	root_->item_ = letter;
	root_->count_ = count;

} // End of Constuctor
	

 /** Constructor
@pre neither source HuffmanTrees are empty
@post Empty HuffmanTree Object created and source trees memory captured.
calls combineTrees*/
HuffmanTree::HuffmanTree(HuffmanTree& leftSource, HuffmanTree& rightSource)
:root_(nullptr){


	// safe guard. cannot combine two empty tree, an tree & an empty tree
	if (leftSource.root_ != nullptr && rightSource.root_ != nullptr) {
		
		// clear memory for this tree
		clearTree(root_);

		// determine which tree will be left and right child of new tree
		if (leftSource < rightSource) {

			root_ = combineTrees(leftSource.root_, rightSource.root_);

		}
		else {

			root_ = combineTrees(rightSource.root_, leftSource.root_);

		} // End if

	} // End if

} // End of of Constuctor

/**  combineTrees, combines two trees together by their root
@pre neither root is nullptr
@post a pointer to the new HuffmanTree is returned, and
the memory is captured from the inputted trees
@parm HuffNode[lhsRoot], HuffNode[rhsRoot]
@return pointer to root of new tree*/
HuffmanTree::HuffNode* HuffmanTree::combineTrees(HuffNode*& lhsRoot, HuffNode*& rhsRoot) {

	HuffNode* newTreePtr = nullptr;

	// safe guard. cannot combine two empty tree, an tree & an empty tree  
	if (lhsRoot != nullptr && rhsRoot != nullptr) {

		// capture memory from lhsRoot
		HuffNode* newLeftPtr = lhsRoot;

		// lhsRoot no longer points to tree
		lhsRoot = nullptr;

		// capture memory from rhsRoot
		HuffNode* newRightPtr = rhsRoot;

		// rhsRoot no longer points to tree
		rhsRoot = nullptr;

		// create parent node with sum of weights/count of lhsRoot and rhsRoot
		newTreePtr = new HuffNode;
		newTreePtr->item_ = (newLeftPtr->item_ < newRightPtr->item_) ? newLeftPtr->item_ : newRightPtr->item_;
		newTreePtr->count_ = (newLeftPtr->count_ + newRightPtr->count_);

		// combine trees 
		newTreePtr->leftChild_ = newLeftPtr;
		newTreePtr->rightChild_ = newRightPtr;

	} // end if

	return newTreePtr;

} // End of combineTrees


/** Copy Constructor
@pre None
@post source HuffmanTree deep copied and New HuffmanTree allocated.
Calls the clearTree dellocate memory and  copyTree to copy HuffmanTree
@parm HuffmanTree [sourceTree]*/
HuffmanTree::HuffmanTree(const HuffmanTree& sourceTree) {

	// clear memory for this tree
	clearTree(root_);

	// copy tree
	root_ = copyTree(sourceTree.root_);


} // End of Copy Constuctor

/** copyTree copies the the source tree
@pre none
@post provided tree copied and pointer to the copy returned
@parm HuffNode* [sourceRoot] tree's root to copy
@return a copy of the provided tree*/
HuffmanTree::HuffNode* HuffmanTree::copyTree(const HuffNode* sourceRoot) const {

	HuffNode* newTreePtr = nullptr;
	// copy tree nodes during a preorder traversal

	if (sourceRoot != nullptr) {

		// copy node
		newTreePtr = new HuffNode;
		newTreePtr->item_ = sourceRoot->item_;
		newTreePtr->count_ = sourceRoot->count_;

		newTreePtr->leftChild_ = copyTree(sourceRoot->leftChild_);
		newTreePtr->rightChild_ = copyTree(sourceRoot->rightChild_);

	}

	return newTreePtr;

} // end of copyTree

  
/** Destructor
@pre none
@post destroy HuffmanTree and release memory */
HuffmanTree::~HuffmanTree() {

	clearTree(root_);

} // End of Destructor 

/** clearTree destroys the tree object
@pre none
@post all memory for the SearchTree object is deallocated
@parm HuffNode* [subTreePtr] pointer to the root of the tree*/
void HuffmanTree::clearTree(HuffNode*& subTreePtr) {

	if (subTreePtr != nullptr) {

		clearTree(subTreePtr->leftChild_);
		clearTree(subTreePtr->rightChild_);

		// release memory
		delete subTreePtr;
		subTreePtr = nullptr;

	} // end if

} // End of clearTree

/* Overloaded Assigment Operator
@pre None
@post left hand HuffmanTree object equals the right hand HuffmanTree object
Checks for self assignment and calls clearTree to release memory, calls copyTree to deep copy
@param HuffmanTree [rhsTree] object to equal
@return HuffmanTree oject is now equal to right hand HuffmanTree object */
HuffmanTree& HuffmanTree::operator=(const HuffmanTree& rhsTree) {

	// check for self assignment
	if (this == &rhsTree) {

		return *this;

	} // end if 

	// clear memory
	clearTree(root_);

	// copy tree
	root_ = copyTree(rhsTree.root_);

	return *this;

} // End of Overloaded Assignment Operator

/** Overloaded operator<
@pre None
@post Node
@param HuffmanTree [rhsTree]
@return if rhsTree root_ count value is greater then left hand side tree, otherwise false.
If TIE tree storing the earliest character is less then, */
bool HuffmanTree::operator<(const HuffmanTree& rhsTree) const {


	bool lessThen = false;

	if (root_ != nullptr && rhsTree.root_ != nullptr) {

		if (root_->count_ == rhsTree.root_->count_) {

			lessThen = root_->item_ < rhsTree.root_->item_;

		}
		else {
			
			lessThen = root_->count_ < rhsTree.root_->count_;

		} // End if

	} // End if

	return lessThen;

} // End of Overloaded < Operator

/* encode updates parm codebook to contain char codes generate by the encoder
@pre Huffman tree has already been completed/filled
@post codebook updated to contain 26 codes for 26 chars
calls encoder to decode Hufftree to generate codes
@param std::string array [codebook] passed by reference*/
void HuffmanTree::encode(std::string(&codebook)[NUM_LETTERS]) const {


	std::vector<std::string> codes{};

	std::string code{};

	encoder(root_, codebook, code);

} // End of encode

/* encoder helps the encode method update codebook parm to contain char codes
generated by traversing the tree
@pre Huffman tree has already been completed/filled/Not Empty
@post codebook updated to contain 26 codes for 26 chars
@param HuffNode [subTreePtrstd],  std::string array [codebook] & std::string [code] passed by reference*/
void HuffmanTree::encoder(const HuffNode* subTreePtr, std::string(&codebook)[NUM_LETTERS], std::string& code) const {


	if (subTreePtr != nullptr) {

		// vist node first


		if (subTreePtr->leftChild_ != nullptr) {

			code.push_back('0');
			encoder(subTreePtr->leftChild_, codebook, code);
		} // End if


		if (subTreePtr->rightChild_ != nullptr) {

			//arr[top] = 1;
			code.push_back('1');
			encoder(subTreePtr->rightChild_, codebook, code);

		} // End if

		// is a leaf 
		if (subTreePtr->leftChild_ == nullptr && subTreePtr->rightChild_ == nullptr) {

			int index = subTreePtr->item_ - 'a';
			codebook[index] = code;

		} // End if

		if (!code.empty()) {
			code.pop_back();
		} // end if


	} // End if 


} // End of encoder

/* decode returns text per the provided code
@pre code provided must be valid code for the current HuffmanTree
@post a string that represents text per the provided code
calls decoder to decode Hufftree to generate text
@param std::string [code]
@return a string that represents the coded message*/
std::string HuffmanTree::decode(const std::string code) const {


	std::string text{};

	unsigned int index = 0;

	decoder(root_, code, index, text);

	return text;

} // End of decode

/* decoder helps the decode method decipher the provided code into text
generated by traversing the tree
@pre Huffman tree has already been completed/filled/Not Empty
@post text variable updated to reflected deciphered code
@param HuffNode [subTreePtrstd], std::string [code] & std::string [text] passed by reference, unsigned int [index]*/
void HuffmanTree::decoder(const HuffNode* subTreePtr, const std::string& code, unsigned int index, std::string& text) const {

	
	// leaf 
	if (subTreePtr != nullptr && subTreePtr->leftChild_ == nullptr && subTreePtr->rightChild_ == nullptr) {

		text += subTreePtr->item_;
		//subTreePtr = root_;
		decoder(root_, code, index, text);

	} // end if
	
	if (subTreePtr != nullptr && index < code.size()) {

		if (code[index] == '0') {

			decoder(subTreePtr->leftChild_, code, index + 1, text);
		}
		// else == '1'
		else {

			decoder(subTreePtr->rightChild_, code, index + 1, text);
		} // end if 



	} // End if

	 
} // End of decoder
