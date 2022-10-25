//--------------------------------------------------------------------
// PRIORITYQUEUE.H
// Declaration and definition of the template PriorityQueue class
// Author: Olson (borrowing from a previous edition of Carrano/Henry)
//--------------------------------------------------------------------
// PriorityQueue class: 
//	Implements a priority queue using a heap with the following methods:
//		insert, deleteMin, findMin, heapify
//  The heap is stored in a vector (see the CSS 502 lecture notes)
//  Assumptions:
//	 Can only store data for which operator< exists
//	 (hence the Comparable type variable)
//--------------------------------------------------------------------

#pragma once
#include <vector>
#include <iostream>

template <typename Comparable>
class PriorityQueue {

public:

	/** Constructors */

	/** Defualt Constructor
	@pre None
	@post PriorityQueue Object created*/
	PriorityQueue() {

		// construct and insert dummy element
		Comparable* c = nullptr;
		items_.push_back(c);

	} // End of Default Constructor 



	/** Constructor
	@pre must be a Comparable that has an overloaded comparison operators
	@post PriorityQueue Object is created with the elements of array.
	Min value is top of heap
	@parm Comparable* [] [array], int [count]*/
	PriorityQueue(Comparable* array[], int count) {


		// construct and insert dummy element
		Comparable* c = nullptr;
		items_.push_back(c);


		for (int i = 0; i < count; ++i) {

			items_.push_back(array[i]);
			array[i] = nullptr;
			++numElements_;

		} // end for

		heapify();

	} // End of Constructor


	/** Copy Constructor
	@pre must be another PriorityQueue object
	@post source PriorityQueue deep copied and New PriorityQueue allocated.
	Calls the clear dellocate memory and  copy to copy PriorityQueue
	@parm PriorityQueue [sourceQueue]*/
	PriorityQueue(const PriorityQueue& sourceQueue) {
		
		// clear memory
		clear();
		// copy PriorityQueue
		copy(sourceQueue);

	} // end of copy constructor


	/** Destructor
	@pre None
	@post destroy PriorityQueue and release memory. Calls the clear dellocate memory*/
	~PriorityQueue() {

		clear();

	} // end of destructor


	/* Overloaded Assigment Operator
	@pre None
	@post left hand PriorityQueue object equals the right hand PriorityQueue object
	Checks for self assignment and calls clear to release memory, calls copy to deep copy 
	@param PriorityQueue [rhsQueue] object to equal
	@return PriorityQueue oject is now equal to right hand PriorityQueu object */
	PriorityQueue& operator=(const PriorityQueue& rhsQueue) {

		if (this == &rhsQueue) {
			return *this;

		} // end if

		// clear memory
		clear();

		// copy PriorityQueue
		copy(rhsQueue);
		return *this;

	} // end of overloaded assignment operator



	//------------------------------------------------------------------------
	// insert - adds a single item to the priority queue
	// Preconditions: the initial heap has sufficient memory allocated
	//		and satisfies the heap order property
	// Postconditions: inserts the item into the queue, such that a new
	//		heap is created containing the union of the elements
	void insert(Comparable* c) {
		
		if (c == NULL) {
			return;
		} //end if

		// Add item in position 0 (dummy position) to prevent percolating up from root 
		if (items_.size() < 1) {
			items_.push_back(c);
		}
		else {
			items_[0] = c;
		} // end if

		// Ensure we have enough space
		numElements_++;
		while ((int)items_.size() <= numElements_) {
			items_.push_back(nullptr);
		} // end of while
			

		// Percolate up
		int position = numElements_;
		while (*c < *items_[position / 2]) {
			items_[position] = items_[position / 2];
			position = position / 2;
		} // end of while
		items_[position] = c;
	}

	//------------------------------------------------------------------------
	// findMin - returns a const pointer to the minimum value in the priority queue
	// Preconditions: items[0] exists if numElements is larger than zero
	// Postconditions: Returns nullptr if the heap is empty, otherwise returns
	//	the item at the root of the heap (presumably the minimum priority).
	const Comparable* findMin() const {
		if (numElements_ <= 0) {
			return nullptr;
		}
		else {
			return items_[1];
		}
	} // end of findMin

	//------------------------------------------------------------------------
	// deleteMin - delete the minimum and return a pointer to it
	// Preconditions: items[0] exists if numElements is larger than zero
	// Postconditions: Returns nullptr if the heap is empty, otherwise returns
	//	the item at the root of the heap (presumably the minimum priority).
	//  That element is deleted from the heap and the heap order property is
	//  restored.
	Comparable* deleteMin() {
		if (numElements_ == 0) {

			return nullptr;
		} // end if

		// Give memory back to user
		Comparable* toReturn = items_[1];
		items_[1] = items_[numElements_];
		numElements_--;

		percolateDown(1);

		return toReturn;
	} // end of deleteMin


	/** clear destroys the PriorityQueue object
	@pre none
	@post all memory for the PriorityQueue object is deallocated */
	void clear() {

		for (int i = numElements_; i > 0; --i) {
			
			delete items_[i];
			items_[i] = nullptr;
			items_.pop_back();

		} // end for

		numElements_ = 0;

	} // end of clear


	//------------------------------------------------------------------------
	// size
	// Preconditions: none
	// Postconditions: returns the size of the queue
	int size() const {

		return numElements_;

	} // end of size

	//------------------------------------------------------------------------
	// isEmpty
	// Preconditions: none
	// Postconditions: returns whether the queue is empty (zero elements)
	int isEmpty() const {
		return numElements_ == 0;
	} // end isEmpty()

private:

	//------------------------------------------------------------------------
	// percolateDown - used to restore the heap order property after deleteMin
	// Preconditions: Both subtrees of the root are heaps
	// Postconditions: Restores the heap order property by shifting the root
	//  down until it reaches an appropriate node
	void percolateDown(int position) {
		
		int child = position * 2;
		
		if (child > numElements_) {
			return;
		} // end if 
		if (child != numElements_ && *items_[child + 1] < *items_[child]) {
			child++;
		} // end if
		if (*items_[child] < *items_[position]) {
			std::swap(items_[child], items_[position]);
			percolateDown(child);
		} // end if

	} // end of percolateDown

	//------------------------------------------------------------------------
	// heapify - modifies any set of data into a heap
	// Preconditions: items has been allocated space for numElements pointers
	// Postconditions: The items stored form a heap
	void heapify() {
		
		for (int i = numElements_ / 2; i > 0; i--){
			percolateDown(i);
		} // end for

	} // end of heapify

	/** copy copies source PriorityQueue
	@pre none
	@post provided source PriorityQueue copied
	@parm PriorityQueue [rhsQueue], sou */
	void copy(const PriorityQueue& rhsQueue) {

		// resize item vector
		items_.resize(rhsQueue.items_.size());


		if (0 < rhsQueue.items_.size()) {
			items_[0] = nullptr;
		}

		for (unsigned int i = 1; i < rhsQueue.items_.size(); ++i) {

			Comparable* newItem = new Comparable;
			*newItem = *rhsQueue.items_[i];
			items_[i] = newItem;


		} // end for

		numElements_ = rhsQueue.numElements_;

	} // end of copy

	// attributes 
	int numElements_ = 0;			// Number of elements in the queue
	std::vector <Comparable*> items_;	// The elements in the priority queue stored in a heap

}; // End of PriorityQueue
