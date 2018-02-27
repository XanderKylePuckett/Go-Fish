#pragma once
#include "Card.h"
/*
	A stack is anything that uses FILO (First In, Last Out)
	ordering sequence     // or LIFO

	Examples:	call stack, bullet magazine, PEZ dispenser,
	conventional deck of cards, paper towels


	*/

	// Provides an alias for a datatype
	//typedef Card Item;

	// A FILO data structure implemented using a 
	// singly linked list
template <typename Item>
class Stack
{
private:

	// Without these, you can't have a linked list
	struct Node
	{
		Item m_data;	// What we're storing
		Node* m_next;	// The next Node in the list
	};

	Node* m_top;		// Points to the most recently
	// added node
	int m_currSize;		// Number of nodes in the stack


public:

	// Def ctor
	// Creates an empty stack
	Stack();

	// Dtor
	~Stack();

	int GetCurrSize() const
	{
		return m_currSize;
	}

	// Add an Item to the top of the stack
	// In:	_data		The value to add
	//
	// Return: True, if it was added successfully
	bool Push( const Item& _data );

	// Remove the Item from the top of the stack
	// In:	_data		A "blank" Item
	//
	// Out: _data		The value from the top
	// Return: True, if something was removed
	bool Pop( Item& _data );

	// Empty out the stack for re-use
	void Clear();

	// Look at the top without removing it
	const Item* Peek() const;
};

// Def ctor
// Creates an empty stack
template <typename Item>
Stack<Item>::Stack()
{
	m_top = NULL;
	m_currSize = 0;
}

// Dtor
template <typename Item>
Stack<Item>::~Stack()
{
	Clear();
}

// Add an Item to the top of the stack
// In:	_data		The value to add
//
// Return: True, if it was added successfully
template <typename Item>
bool Stack<Item>::Push( const Item& _data )
{
	// Every time you add something, you have to
	// dynamically allocate a node
	Node* newTop = new Node;

	// Check to see if the memory ran out
	//if (newTop = NULL)
	if ( NULL == newTop )
		return false;

	// Fill in the node
	newTop->m_data = _data;

	// Link it up to the rest of the list
	newTop->m_next = m_top;
	m_top = newTop;

	m_currSize++;
	return true;

}

// Remove the Item from the top of the stack
// In:	_data		A "blank" Item
//
// Out: _data		The value from the top
// Return: True, if something was removed
template <typename Item>
bool Stack<Item>::Pop( Item& _data )
{
	// See if the stack is empty
	if ( !m_top )
		return false;

	// Copy out the value
	_data = m_top->m_data;

	Node* temp = m_top;
	m_top = m_top->m_next;
	delete temp;

	// Success
	--m_currSize;
	return true;
}

// Empty out the stack for re-use
template <typename Item>
void Stack<Item>::Clear()
{
	/*
	while (m_top)
	{
	Node* temp = m_top;
	m_top = m_top->m_next;
	delete temp;
	}
	*/

	for ( Node* temp = m_top; m_top; delete temp )
	{
		temp = m_top;
		m_top = m_top->m_next;
	}

	m_currSize = 0;
}

// Look at the top without removing it
template <typename Item>
const Item* Stack<Item>::Peek() const
{
	return ( m_top ? &m_top->m_data : NULL );
}

// ☻☺ トニー ☺☻ //