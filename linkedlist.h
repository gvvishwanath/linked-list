/*
 * G V Vishwanath, 19th May 2019, v1.0
 * Header file containing type declarations and function declarations related to the linked list data structure.
 *
 * The following types are declared in this file:
 * a) Data: the type of the data in a linked list node. Another name for int.
 * b) bool: a Boolean flag (TRUE/FALSE). Another name for int.
 * c) struct listnode (ListNode): a structure representing one list node.
 * d) struct linkedlist (LinkedList): a structure representing a linked list. Wrapper around ListNode;
 *    contains a head pointer, a tail pointer, and information about the length of the list
 *
 * The following functions are declared in this file:
 *
 * Related to printing contents of a linked list
 * a) PrintData: Function to print data (integers)
 * b) PrintList: Function to print the contents of a linked list
 *
 * Related to initialising a linked list
 * c) MakeNode: Function to create a linked list node with given data
 * d) InitialiseList: Function to create an empty linked list
 *
 * Related to adding data (nodes) to a linked list
 * e) AddNode: Function to add a new node after a certain node in a linked list
 * f) AddDataAtEnd: Function to add data at the end of a linked list
 * g) AddDataAtBeginning: Function to add data at the beginning of a linked list
 * h) AddDataFromBeginning: Function to add given data to a linked list at a certain position w.r.t. the head of the list
 * i) AddDataFromEnd: Function to add given data to a linked list at a certain position w.r.t. the tail of the list
 *
 * Related to removing data (nodes) from a linked list
 * j) RemoveNode: Helper function to remove a node from a linked list
 * k) RemoveData: Function to remove all occurrences of given data from the linked list
 * l) RemoveAllNodes: Function to remove (and free) all nodes in a linked list
 *
 * Related to permutation of a linked list
 * m) ReverseList: Function to reverse a linked list
 * n) RotateList: Function to rotate a linked list by a given amount
 * 
 * All of the above functions are defined in "Linked List/linkedlist.c". For more details, see there.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

	#include "basictypes.h"

	// For linked list node data
	typedef int Data;

	// For Boolean flags
	typedef int bool;

	// For one node in linked list
	struct listnode {
		Data data;
		struct listnode *nextNodePtr;
	};
	typedef struct listnode ListNode;

	// Wrapper for linked list node
	struct linkedlist {
		ListNode *headPtr;
		ListNode *tailPtr;
		Length numNodes;
	};
	typedef struct linkedlist LinkedList;

	/*
	 * Function declarations. The functions are defined in "Linked List/linkedlist.c".
	 * For more details, refer to this file.
	 */

	// Related to printing the contents of the linked list
	void PrintData (Data data);
	void PrintList (LinkedList list);

	// Related to initialising linked lists
	ListNode MakeNode (Data data);
	LinkedList InitialiseList (void);

	// Related to adding data (nodes) to a linked list
	void AddNode (LinkedList *listPtr, ListNode *prevNodePtr, ListNode *newNodePtr);
	void AddDataAtEnd (LinkedList *listPtr, Data data);
	void AddDataAtBeginning (LinkedList *listPtr, Data data);
	void AddDataFromBeginning (LinkedList *listPtr, Data data, Index position);
	void AddDataFromEnd (LinkedList *listPtr, Data data, Index position);

	// Related to removing data (nodes) from a linked list
	void RemoveNode (LinkedList *listPtr, ListNode *prevNodePtr, ListNode *currNodePtr);
	void RemoveData (LinkedList *listPtr, Data data);
	void RemoveAllNodes (LinkedList *listPtr);

	// Related to permutation of a linked list
	void ReverseList (LinkedList *listPtr);
	void RotateList (LinkedList *listPtr, Index rotation);

#endif
