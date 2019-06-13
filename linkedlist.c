#include <stdio.h>  		// For input/output
#include <stdlib.h> 		// For dynamic memory allocation and de-allocation
#include "../linkedlist.h"	// For type declarations and function declarations related to the linked list data structure

#define DEBUG 0	    // Condition to print statements for debugging. If 0, no need to print. If 1, print.

/*
 * G V Vishwanath, 15th May 2019. v1.0
 * Function to print data (integers)
 * Input: data (Data) (int)
 * Return value: none
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
void PrintData (Data data) {
	printf ("%d", data);
}

/*
 * G V Vishwanath, 15th May 2019, v1.0
 * Function to print the contents of a linked list
 * Input: list (LinkedList)
 * Return value: none
 * Assumptions: list is terminated with a NULL, empty list has headPtr == NULL
 * Time complexity: O(list.numNodes)
 * Space complexity: O(1)
 */
void PrintList (LinkedList list) {
	ListNode *currNodePtr;
	currNodePtr = list.headPtr;
	
	while (currNodePtr != NULL) {
		PrintData (currNodePtr->data);
		printf (" -> ");
		currNodePtr = currNodePtr->nextNodePtr;
	}
	printf ("NULL\n");
}

/*
 * G V Vishwanath, 14th May 2019, v1.0
 * Function to create a linked list node with given data
 * Input: data (Data) (int)
 * Return value: node (ListNode) : linked list node with node->data = data, node->nextNodePtr = NULL
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
ListNode MakeNode (Data data) {
	ListNode node;
	node.data = data;
	node.nextNodePtr = NULL;
	return node;
}

/*
 * G V Vishwanath, 15th May 2019, v1.0
 * Function to create an empty linked list
 * Input: none
 * Return value: list (ListNode) : linked list with list.numNodes = 0, list.headPtr = NULL, list.tailPtr = NULL
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
LinkedList InitialiseList (void) {
	LinkedList list;
	list.numNodes = 0;
	list.headPtr = NULL;
	list.tailPtr = NULL;
	return list;
}

/*
 * G V Vishwanath, 15th May 2019, v1.0
 * Function to add a new node after a certain node in a linked list
 * Takes special action if the list is empty, or the new node is to be inserted at the head, 
 * or the new node is to be inserted after the tail
 * Inputs: listPtr (LinkedList *): pointer to linked list, prevNodePtr (ListNode *): pointer to node before which
 * new node is to be inserted, newNodePtr (ListNode *): new node to be inserted
 * Return value: none
 * Pre-condition: The list has some (or no) nodes
 * Post-condition: newNodePtr is inserted between "the previous node" (might be NULL => new node is inserted at the head) 
 * and "the node originally after it" (might be NULL => new node is inserted at the tail). listPtr->numNodes is incremented by 1.
 * Assumptions: listPtr != NULL
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
void AddNode (LinkedList *listPtr, ListNode *prevNodePtr, ListNode *newNodePtr) {
	if (listPtr == NULL) {
		printf ("Error: Argument 1 of AddNode (LinkedList *listPtr) cannot be NULL\n");
		return;
	}

	// list is empty
	if (listPtr->headPtr == NULL) {
		listPtr->headPtr = newNodePtr;
		listPtr->tailPtr = newNodePtr;
	}

	// new node is to be inserted at the head
	else if (prevNodePtr == NULL) {
		newNodePtr->nextNodePtr = listPtr->headPtr;
		listPtr->headPtr = newNodePtr;
	}

	// new node is to be inserted at the tail
	else if (prevNodePtr->nextNodePtr == NULL) {
		listPtr->tailPtr->nextNodePtr = newNodePtr;
		listPtr->tailPtr = newNodePtr;
	}

	// general case
	else {
		newNodePtr->nextNodePtr = prevNodePtr->nextNodePtr;
		prevNodePtr->nextNodePtr = newNodePtr;
	}

	(listPtr->numNodes)++;
}

/*
 * G V Vishwanath, 14th May 2019, v1.1
 * Function to add data at the end of a linked list
 * Inputs: listPtr (LinkedList *), data (Data) (int)
 * Return value: none
 * Pre-condition: listPtr is a linked list, with some (or no) nodes
 * Post-condition: A node with node.data = data is inserted at the end of the linked list.
 * Assumptions: listPtr != NULL
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
void AddDataAtEnd (LinkedList *listPtr, Data data) {
	ListNode *newNodePtr;

	if (listPtr == NULL) {
		printf ("Error: Argument 1 of AddDataAtEnd (LinkedList *listPtr) cannot be NULL\n");
		return;
	}

	newNodePtr = (ListNode *) malloc (sizeof (ListNode));
	*newNodePtr = MakeNode (data);

	AddNode (listPtr, listPtr->tailPtr, newNodePtr); 
}

/*
 * G V Vishwanath, 14th May 2019, v1.1
 * Function to add data at the beginning of a linked list
 * Inputs: listPtr (LinkedList *), data (Data) (int)
 * Return value: none
 * Pre-condition: listPtr is a linked list, with some (or no) nodes
 * Post-condition: A node with node.data = data is inserted at the beginning of the linked list.
 * Assumptions: listPtr != NULL
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
void AddDataAtBeginning (LinkedList *listPtr, Data data) {
	ListNode *newNodePtr;

	if (listPtr == NULL) {
		printf ("Error: Argument 1 of AddDataAtBeginning (LinkedList *listPtr) cannot be NULL\n");
		return;
	}

	newNodePtr = (ListNode *) malloc (sizeof (ListNode));
	*newNodePtr = MakeNode (data);

	AddNode (listPtr, NULL, newNodePtr); 
}

/*
 * G V Vishwanath, 15th May 2019, v1.1
 * Function to add given data to a linked list at a certain position w.r.t. the head of the list
 * Inputs: listPtr (LinkedList *): pointer to linked list, data (Data) (int), position (Index) (int)
 * position is like an array index: should range from 0 (head) to (listPtr->numNodes) (after tail)
 * Return value: None
 * Pre-condition: list contains some (or no) nodes
 * Post-condition: node containing data is inserted at offset 'position' from the beginning
 * Assumptions: listPtr != NULL, position is in range [0, (listPtr->numNodes)]
 * Time complexity: O(position)
 * Space complexity: O(1)
 */
void AddDataFromBeginning (LinkedList *listPtr, Data data, Index position) {
	ListNode *prevNodePtr, *currNodePtr, *newNodePtr;
	Index i;

	if (listPtr == NULL) {
		printf ("Error: Argument 1 of AddDataFromBeginning (LinkedList *listPtr) cannot be NULL\n");
		return;
	}

	if (position < 0 || position > (listPtr->numNodes)) {
		printf ("Error:	Argument 3 of AddDataFromBeginning (Index position) is out of bounds\n");
		return;
	}

	newNodePtr = (ListNode *) malloc (sizeof (ListNode));
	*newNodePtr = MakeNode (data);

	prevNodePtr = NULL;
	currNodePtr = listPtr->headPtr;

	for (i = 0; i < position; i++) {
		prevNodePtr = currNodePtr;
		currNodePtr = currNodePtr->nextNodePtr;
	}
	
	AddNode (listPtr, prevNodePtr, newNodePtr);
}

/*
 * G V Vishwanath, 15th May 2019, v1.0
 * Function to add given data to a linked list at a certain position w.r.t. the tail of the list
 * Inputs: listPtr (LinkedList *): pointer to linked list, data (Data) (int), position (Index) (int).
 * Position is like an array index: should range from 0 (tail) to (listPtr->numNodes) (before head)
 * Return value: none
 * Pre-condition: list contains some (or no) nodes
 * Post-condition: node containing data is inserted at offset 'position' from the end
 * Assumptions: listPtr != NULL, position is in range [0, (listPtr->numNodes)]
 * Time complexity: O(positionFromBeginning)
 * Space complexity: O(1)
 */
void AddDataFromEnd (LinkedList *listPtr, Data data, Index position) {
	Index positionFromBeginning = (listPtr->numNodes)-position;

	if (listPtr == NULL) {
		printf ("Error: Argument 1 of AddDataFromEnd (LinkedList *listPtr) cannot be NULL\n");
		return;
	}

	if (position < 0 || position > (listPtr->numNodes)) {
		printf ("Error:	Argument 3 of AddDataFromEnd (Index position) is out of bounds\n");
		return;
	}

	AddDataFromBeginning (listPtr, data, positionFromBeginning);
}

/*
 * G V Vishwanath, 15th May 2019, v1.2
 * Helper function to remove a node from a linked list
 * Inputs: listPtr (LinkedList *): pointer to linked list, prevNodePtr (ListNode *): the node before the node to be deleted,
 * currNodePtr (ListNode *): the node to be deleted
 * Return value: none
 * Pre-condition: list has some (or no) nodes
 * Post-condition: currNode is removed from list, listPtr->numNodes is decremented by 1
 * Assumption: listPtr != NULL
 * Time complexity: O(1)
 * Space complexity: O(1)
 */
void RemoveNode (LinkedList *listPtr, ListNode *prevNodePtr, ListNode *currNodePtr) {
	ListNode *tempNodePtr;

	if (listPtr == NULL) {
		printf ("Error: Argument 1 of RemoveNode (LinkedList *listPtr) cannot be NULL\n");
		return;
	}

	if (prevNodePtr == NULL) {
		tempNodePtr = listPtr->headPtr;
		listPtr->headPtr = listPtr->headPtr->nextNodePtr;
	}
	else {
		tempNodePtr = currNodePtr;
		prevNodePtr->nextNodePtr = currNodePtr->nextNodePtr;

		if (prevNodePtr->nextNodePtr == NULL) {
			listPtr->tailPtr = prevNodePtr;
		}
	}

	free (tempNodePtr);
	(listPtr->numNodes)--;
}

/*
 * G V Vishwanath, 15th May 2019, v1.4
 * Function to remove given data from the linked list
 * Inputs: listPtr (LinkedList *): pointer to linked list, data (Data) (int)
 * Return value: none
 * Pre-condition: list has some (or no) nodes
 * Post-condition: All occurrences of data in list are removed, if data is present at least once, 
 * size of linked list is reduced by number of nodes removed
 * Assumptions: listPtr != NULL, data is present at least once, all occurrences of data need to be removed
 * Time complexity: O(listPtr->numNodes) [just before function is called]
 * Space complexity: O(1)
 */
void RemoveData (LinkedList *listPtr, Data data) {
	ListNode *prevNodePtr, *currNodePtr, *tempNodePtr;
	Length numNodesFound = 0;

	if (listPtr == NULL) {
		printf ("Error: Argument 1 of RemoveData (LinkedList *listPtr) cannot be NULL\n");
		return;
	}

	prevNodePtr = NULL;
	currNodePtr = listPtr->headPtr;

	while (currNodePtr != NULL) {
		if (currNodePtr->data == data) {
			numNodesFound++;
			tempNodePtr = currNodePtr;
			currNodePtr = currNodePtr->nextNodePtr;
			RemoveNode (listPtr, prevNodePtr, tempNodePtr);
		}

		else {
			prevNodePtr = currNodePtr;
			currNodePtr = currNodePtr->nextNodePtr;
		}
	}

	#if DEBUG
		printf ("RemoveData: ");
		PrintData (data);
		printf (" : ");

		if (numNodesFound == 0) {
			printf ("data not found in list\n");
		}
		else {
			printf ("data found and deleted %d times in list\n", numNodesFound);
		}
	#endif
}

/*
 * G V Vishwanath, 15th May 2019, v1.0
 * Function to remove (and free) all nodes in a linked list
 * Input: listPtr (LinkedList *): pointer to linked list
 * Return value: none
 * Pre-condition: list contains some (or no) nodes
 * Post-condition: list contains zero nodes, listPtr->headPtr = listPtr->tailPtr = NULL, listPtr->numNodes = 0
 * Assumption: listPtr != NULL
 * Time complexity: O(listPtr->numNodes) [just before function is called]
 * Space complexity: O(1)
 */
void RemoveAllNodes (LinkedList *listPtr) {
	ListNode *prevNodePtr = NULL;

	if (listPtr == NULL) {
		printf ("Error: Argument 1 of RemoveAllNodes (LinkedList *listPtr) cannot be NULL\n");
		return;
	}

	while (listPtr->headPtr != NULL) {
		prevNodePtr = listPtr->headPtr;
		listPtr->headPtr = listPtr->headPtr->nextNodePtr;
		free (prevNodePtr);
	}

	listPtr->tailPtr = NULL;
	listPtr->numNodes = 0;

	#if DEBUG
		printf ("RemoveAllNodes: Removed all nodes from list\n");
	#endif
}

/*
 * G V Vishwanath, 16th May 2019, v1.0
 * Function to reverse a linked list
 * Input: listPtr (LinkedList *): pointer to linked list
 * Return value: none
 * Pre-condition: linked list contains some nodes (n_1)->...(n_numNodes)->NULL
 * Post-condition: linked list contains the nodes in order (n_numNodes)->...(n_1)->NULL
 * Assumption: listPtr != NULL
 * Time complexity: O(listPtr->numNodes)
 * Space complexity: O(1)
 */
void ReverseList (LinkedList *listPtr) {
	ListNode *prevNodePtr, *currNodePtr, *nextNodePtr, *originalHeadPtr;

	if (listPtr == NULL) {
		printf ("Error: Argument 1 of ReverseList (LinkedList *listPtr) cannot be NULL\n");
		return;
	}

	originalHeadPtr = listPtr->headPtr;
	prevNodePtr = NULL;
	currNodePtr = listPtr->headPtr;
	nextNodePtr = NULL;

	while (currNodePtr != NULL) {
		nextNodePtr = currNodePtr->nextNodePtr;
		currNodePtr->nextNodePtr = prevNodePtr;
		prevNodePtr = currNodePtr;
		currNodePtr = nextNodePtr;
	}	

	listPtr->headPtr = prevNodePtr;
	listPtr->tailPtr = originalHeadPtr;
}

/*
 * G V Vishwanath, 16th May 2019, v1.0
 * Function to rotate a linked list by a given amount
 * Inputs: listPtr (LinkedList *): pointer to linked list, rotation (Index) (int): amount by which to rotate
 * rotation > 0 => right rotation, rotation < 0 => left rotation
 * Return value: none
 * Pre-condition: say list is (n_0) -> ... (n_(numNodes-1))->NULL and rotation is -r, r > 0
 * Post-condition: new list is  (n_r) -> ... (n_(numNodes-1))->(n_0)->...(n_(r-1)) 
 *
 * [For +r: (n_(numNodes-1-r))->(n_(numNodes-r))->... (n_(numNodes-1))->(n_0)->...(n_(numNodes-2-r))->NULL]
 *
 * Assumptions: listPtr != NULL, -numNodes+1 <= rotation <= numNodes-1
 * Time complexity: O(index) [ = min ( |rotation| , listPtr->numNodes - |rotation| )]
 */
void RotateList (LinkedList *listPtr, Index rotation) {
	ListNode *prevNodePtr, *currNodePtr;
	Index index, i;

	if (listPtr == NULL) {
		printf ("Error: Argument 1 of RotateList (LinkedList *listPtr) cannot be NULL\n");
		return;
	}
	if (rotation <= -(listPtr->numNodes) || rotation >= (listPtr->numNodes)) {
		printf ("Error: Argument 2 of RotateList (Index rotation) describes rotation that is not supported\n");
		return;
	}

	if (rotation == 0) {
		return;
	}
	else if (rotation < 0) {
		index = -rotation;
	}
	else {
		index = (listPtr->numNodes)-rotation;
	}

	prevNodePtr = NULL;
	currNodePtr = listPtr->headPtr;

	for (i = 0; i < index; i++) {
		prevNodePtr = currNodePtr;
		currNodePtr = currNodePtr->nextNodePtr;
	}
	
	listPtr->tailPtr->nextNodePtr = listPtr->headPtr;
	prevNodePtr->nextNodePtr = NULL;
	listPtr->headPtr = currNodePtr;
	listPtr->tailPtr = prevNodePtr;
}

/*
 * G V Vishwanath, 15th May 2019, v1.0
 * Driver program to test the functions in this file
 */
/*int main () {
	LinkedList list;

	list = InitialiseList ();
	PrintList (list);

	AddDataAtBeginning (&list, 1);
	PrintList (list);
	
	AddDataAtBeginning (&list, 2);
	PrintList (list);

	AddDataAtEnd (&list, 3);
	PrintList (list);

	AddDataAtEnd (&list, 4);
	PrintList (list);

	AddDataAtEnd (&list, 5);
	PrintList (list);

	RemoveData (&list, 3);
	PrintList (list);

	RemoveData (&list, 2);
	PrintList (list);

	RemoveData (&list, 5);
	PrintList (list);

	RemoveAllNodes (&list);
	PrintList (list);

	AddDataAtBeginning (&list, 2);
	PrintList (list);

	AddDataAtBeginning (&list, 3);
	PrintList (list);

	AddDataAtBeginning (&list, 2);
	PrintList (list);

	AddDataAtEnd (&list, 2);
	PrintList (list);

	RemoveData (&list, 2);
	PrintList (list);

	AddDataAtBeginning (&list, 2);
	PrintList (list);

	RemoveData (&list, 3);
	PrintList (list);

	RemoveAllNodes (&list);
	PrintList (list);

	list = InitialiseList ();
	PrintList (list);

	AddDataFromBeginning (&list, 2, 0);
	PrintList (list);

	AddDataFromBeginning (&list, 3, 1);
	PrintList (list);

	RemoveData (&list, 3);
	PrintList (list);

	AddDataFromBeginning (&list, 3, 0);
	PrintList (list);

	AddDataFromEnd (&list, 4, 0);
	PrintList (list);

	AddDataFromEnd (&list, 5, 3);
	PrintList (list);

	AddDataFromBeginning (&list, 6, 2);
	PrintList (list);

	AddDataFromEnd (&list, 7, 2);
	PrintList (list);

	RemoveAllNodes (&list);
	PrintList (list);

	ReverseList (&list);
	PrintList (list);

	AddDataAtBeginning (&list, 1);
	AddDataAtBeginning (&list, 2);
	AddDataAtBeginning (&list, 3);
	PrintList (list);

	ReverseList (&list);
	PrintList (list);

	AddDataAtEnd (&list, 4);
	AddDataAtEnd (&list, 5);
	PrintList (list);

	RotateList (&list, 1);
	PrintList (list);

	RotateList (&list, -1);
	PrintList (list);

	RotateList (&list, 0);
	PrintList (list);

	RotateList (&list, 2);
	PrintList (list);

	RotateList (&list, -3);
	PrintList (list);

	RotateList (&list, 5);
	
	RemoveAllNodes (&list);

	return 0;
}*/
