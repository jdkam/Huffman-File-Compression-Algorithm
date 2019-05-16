/*
 * Node.h
 *
 * Class Definition: Node of a singly linked list
 *                   in which the data is of "int" data type.
 *                   Designed and implemented as a non-ADT.
 *
 * Created on: Feb 24, 2019
 * Author: Jordan Kam
 */

 // #pragma once is shorthand for the 2 #include guards we've seen before:
 // #ifndef _NODE and #define _NODE
 // and it means: do not include me more than once.
#pragma once

template <class T>
class Node
{
public:
	// Public data members - Why are the data members public?
	T data;     // The data in the node
	Node<T>* next;   // Pointer to next node

	// Constructors
	Node();
	Node(T theData);
	Node(T theData, Node<T>* theNextNode);

}; // end Node

template <class T>
Node<T>::Node()
{
	data = 0;
	next = NULL;
}

template <class T>
Node<T>::Node(T theData)
{
	data = theData;
	next = NULL;
}

template <class T>
Node<T>::Node(T theData, Node<T>* theNextNode)
{
	data = theData;
	next = theNextNode;
}