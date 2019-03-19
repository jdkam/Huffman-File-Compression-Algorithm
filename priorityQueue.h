/*
 * PriorityQueue.h
 *
 * Description: Priority Queue
 * Class Invariant: The elements stored in this Priority Queue are always sorted.
 *
 * Credits to: Inspired by Frank M. Carrano and Tim Henry (textbook).
	Author: Jordan Kam
 * Modified: Feb 24, 2019
 *
 */


#pragma once

#include <iostream>
#include "Node.h"
#include "EmptyDataCollectionException.h"

using namespace std;

template <class T>  // We can use T, ElementType or other names as a placeholder
class PriorityQueue {

private:

	Node<T>* head;      // Pointer to first node in the chain
	int elementCount;   // Current count of list items

 /* You can add private methods to this class */

public:

	// Default Constructor
	PriorityQueue();

	// Copy Constructor
	PriorityQueue(const PriorityQueue& rhsPriorityQueue);

	// Destructor
	~PriorityQueue();

	// Description: Returns the number of elements in the Priority Queue.
	// Time Efficiency: O(1)
	int getElementCount() const;

	// Description: Returns "true" is this Priority Queue is empty, otherwise "false".
	// Time Efficiency: O(1)
	bool isEmpty() const;

	// Description: Inserts newElement in sort order.
	//              It returns "true" if successful, otherwise "false".
	// Precondition: This Priority Queue is sorted.
	// Postcondition: Once newElement is inserted, this Priority Queue remains sorted.
	// Time Efficiency: O(n)
	bool enqueue( T& newElement);

	// Description: Removes the element with the "highest" priority.
	//              It returns "true" if successful, otherwise "false".
	// Precondition: This Priority Queue is not empty.
	// Time Efficiency: O(1)
	bool dequeue();

	// Description: Returns the element with the "highest" priority.
	// Precondition: This Priority Queue is not empty.
	// Postcondition: This Priority Queue is unchanged.
	// Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
	// Time Efficiency: O(1)
	T& peek() const throw(EmptyDataCollectionException);

	// To deal with the warning regarding template and friend function: 
   // I used the first "Introvert" solution described in 
   // https://stackoverflow.com/questions/4660123/overloading-friend-operator-for-template-class
   // The idea: only declare a particular instantiation of the << operator as a friend
   // by inlining the operator.  
   friend ostream & operator<< (ostream & os, const PriorityQueue<T>& rhs) {
      Node<T>* current = rhs.head;

      os << "elementCount = " << rhs.elementCount;
      
      // Traverse the list
      while (current != NULL){
         cout << current -> data; // Print data
         current = current -> next; // Go to next Node
      }

      return os;
   } // end of operator <<


}; // end PriorityQueue

// Default Constructor
template <class T>
PriorityQueue<T>::PriorityQueue()
{
	head = NULL;
	elementCount = 0;
}

// Copy Constructor
template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& rhsPriorityQueue)
{
	elementCount = rhsPriorityQueue.elementCount;

	if(head == NULL) //check if empty
	return;

	Node<T>* temp = rhsPriorityQueue.head; //create a new ptr for pqueue
	Node<T>* current = NULL;
	//allocate new mem for copy
	head = new Node<T>; 
	head -> data = temp -> data; //copy over data
	head -> next = NULL; //set next value to null 
	current = head; //point current to head

	//move to next item in list
	temp = temp->next;

	while (temp != NULL) //copy over data
	{
		current -> next = new Node<T>;
		current = current -> next;
		current ->data = temp -> data;
		current -> next = NULL;
		temp = temp -> next;

	}
}

// Destructor
template <class T>
PriorityQueue<T>::~PriorityQueue() {
	Node<T> * curr;
	Node<T> * next;
	curr = head;

	while (curr != NULL)
	{
		next = curr->next;
		delete curr;
		curr = next;
	}
	head = NULL;
}

// Description: Returns the number of elements in the Priority Queue.
// Time Efficiency: O(1)
template <class T>
int PriorityQueue<T>::getElementCount() const {
	return elementCount;
}

// Description: Returns "true" is this Priority Queue is empty, otherwise "false".
// Time Efficiency: O(1)
template <class T>
bool PriorityQueue<T>::isEmpty() const {
	return head == NULL;
}

// Description: Inserts newElement in sort order.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is sorted.
// Postcondition: Once newElement is inserted, this Priority Queue remains sorted.
// Time Efficiency: O(n)
template <class T>
bool PriorityQueue<T>::enqueue( T& newElement) {
	

	if (isEmpty()) //first node created
	{
		head = new Node<T>(newElement, NULL);
		elementCount++;
		return true;
	}
	
	//traverse to find smallest value in list
	Node<T> * curr;
	curr = head;

	if (newElement < head->data) //if element is smaller than the head
	{
		head = new Node<T>(newElement, head);
		elementCount++;
		return true;
	}

	while (curr->next != NULL && curr->next->data < newElement)
	{
		curr = curr->next;
	}

	Node<T> *newNode = new Node<T>(newElement, curr->next);
	curr->next = newNode;
	elementCount++;
	return true;

}

// Description: Removes the element with the "highest" priority.
//              It returns "true" if successful, otherwise "false".
// Precondition: This Priority Queue is not empty.
// Time Efficiency: O(1)
template <class T>
bool PriorityQueue<T>::dequeue() {

	if (isEmpty())
	{
		throw (EmptyDataCollectionException("The queue is empty\n"));	
	
	}

	Node<T>* curr = head;
	head = curr->next;
	delete curr;
	elementCount--;
	return true;
}

// Description: Returns the element with the "highest" priority.
// Precondition: This Priority Queue is not empty.
// Postcondition: This Priority Queue is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
// Time Efficiency: O(1)
template <class T>
T &PriorityQueue<T>::peek() const throw(EmptyDataCollectionException) {

	if (isEmpty())
	{
		throw (EmptyDataCollectionException("The queue is empty\n"));
	}
	return head->data;
}


