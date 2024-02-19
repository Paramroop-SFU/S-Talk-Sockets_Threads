#include "list.h"
#include <stdio.h>
// By Paramroop Parmar
// student number: 301555338
//date: jan31 2024
static List listHead[LIST_MAX_NUM_HEADS];
Node nodes[LIST_MAX_NUM_NODES];
bool made = false; // if list created has been used yet
static int number_of_heads_used = 0;
static int number_of_nodes_used = 0;
Node* top = NULL; // used as a stack for holding all of the unused node poniters



List* head_top;


List* List_create()
{

	if (made == false) // to make sure intialized once
	{

		for (int i = 0; i < LIST_MAX_NUM_HEADS; i++)
		{

			listHead[i].count = 0; // set the bounds and count
			listHead[i].bounds = 2;

			if (i == 0) // add head to free stack
			{
				head_top = &listHead[0];
				listHead[0].next = NULL;
				continue;
			}
			listHead[i].next= head_top;
			head_top = &listHead[i];
		}

		for (int i = 0; i < LIST_MAX_NUM_NODES; i++)
		{

			nodes[i].next= NULL; // set the node to null
			nodes[i].prev = NULL;
			if (i == 0) // add the node to a node free stack
			{
				top = &nodes[0]; // a stack
				nodes[0].next = NULL;

				continue;
			}
			nodes[i].next = top;
			top = &nodes[i];

		}
		made = true; // to make sure it is never happened again
	}

	if (number_of_heads_used == LIST_MAX_NUM_HEADS) // if all heads are used up to return to null
	{
		head_top = NULL;
		return NULL; // null pointer
	}
	else // give a free head from stack and remove it from the stack
	{
		number_of_heads_used++;
		List* temp =  head_top;
		head_top = head_top->next;
		temp->head = NULL;
		temp->tail = NULL;
		temp->current = NULL;
		temp->bounds = LIST_OOB_START;

		return temp;

	}

}

int List_count(List* pList) // number of nodes list
{
	 return pList->count;
}

void* List_curr(List* pList) // return value of current
{
	if (pList->current == NULL || pList->count == 0)
		return NULL;
	else
		return pList->current->value;
}

void* List_prev(List* pList) // move current back a node
{
	if (  pList-> current == NULL && pList->bounds == 1 && pList->count != 0) // edge case if node is empty or if current already behind list
	{
		pList->current = pList->tail;
		pList->bounds = 2;
		return pList->tail;
	}
	if (pList->current == NULL || pList -> current->prev == NULL) // if current is empty or to move it to null if about to got back list
	{
		pList->current = NULL;
		pList->bounds = LIST_OOB_START;
		return NULL;

	}
	else // if no edge case occures
	{
		pList->bounds = 2;
		pList->current = pList->current->prev;
		return pList->current->value;
	}

}
void* List_first(List* pList) // moves the current to head
{
	if (pList->count != 0) // check if no edge case
	{
	pList ->current = pList ->head;
	return pList->head->value;
	}
	pList->current = NULL;
	return NULL;
}

void* List_last(List* pList) // move current to back
{
	if (pList->count != 0) // check if no edge case
	{
	pList ->current = pList ->tail;
	return pList->tail->value;
	}
	pList->current = NULL;
	return NULL;
}


void* List_next(List* pList) // moving forward the current pointer
{
	if (  pList-> current == NULL && pList->bounds == 0 && pList->count != 0) // edge case
	{
		pList->current = pList->head;
		pList->bounds = 2;
		return pList->head;
	}
	if (pList->current == NULL || pList->current->next == NULL) // decond edge case and to be safe
	{

		pList->current = NULL;
		pList->bounds = LIST_OOB_END;
		return NULL;
	}
	else
	{

		pList->bounds = 2;
		pList->current = pList->current->next;
		return pList->current->value;
	}


}
int List_insert_after(List* pList, void* pItem) // make sure to increment number_nodes_used and pop the top of the stack
{


	if (number_of_nodes_used == LIST_MAX_NUM_NODES) // all nodes used up
	{

		return -1;
	}

	top->value = pItem;

	if (pList->count == 0 ) // no node in list
	{

		pList->head = top;
		pList->tail = top;
		pList->current = top;
		pList->head->prev = NULL;
		top = top->next;
		pList->head->next = NULL;

	}
	else if (pList->bounds == 0) // add to the start
	{

		Node* temp = top;
		top = top->next; // pop from the top
		temp->prev = NULL;
		temp->next = pList->head; // node point to head's node
		pList->head = temp; // head point to node

		pList->current  = pList->head;
		temp->next->prev = temp; // make sure the old head node prev point to temp
	}
	else if (pList->bounds == 1 || pList->current == pList->tail  )
	{

		Node* temp = top; // temp node for new node being added

		top=top->next; // pop from the top
		temp->next = NULL;
		temp->prev = pList->tail; // new node points to the tail
		pList->tail->next = temp; // tail node point to new node
		pList->tail = temp;

		pList->current = pList->tail;
	}
	else // add a node after the node
	{
		Node* temp = top; // temp poniter that points to top.head
		top = top->next; // remove top from the stack
		temp->next = pList->current->next; // temp ponit to next to current
		temp->prev = pList->current;// newnode put to current

		pList->current->next = temp; // current point to new node
		temp->next->prev = temp;
		pList->current = temp; // new current
	}
	number_of_nodes_used ++; // update values
	pList->count++;
	pList->bounds = 2;
	return 0;

}

int List_insert_before(List* pList, void* pItem)
{

	if (number_of_nodes_used == LIST_MAX_NUM_NODES) // no more nodes
	{

		return -1;
	}

	top->value = pItem;

	if (pList->count == 0 )
	{

		pList->head = top;
		pList->tail = top;
		pList->current = top;
		pList->head->prev = NULL;
		top = top->next;
		pList->head->next = NULL;
	}
	else if (pList->bounds == 0 || pList->head == pList->current) // add to the start
	{

		Node* temp = top;
		temp->prev = NULL;
		top = top->next; // pop from the top
		temp->next = pList->head;
		pList->head = temp;
		pList->current  = pList->head;
		temp->next->prev = temp;
	}
	else if (pList->bounds == 1)
	{

		Node* temp = top; // temp node for new node being added
		top=top->next; // pop from the top
		temp->prev = pList->tail; // new node points to the tail
		pList->tail->next = temp;
		pList->tail = temp;
		temp->next = NULL;
		pList->current = pList->tail;


	}
	else // need a case if current->prev is NULL
	{
		Node* temp = top; // temp poniter that points to top->head
		top = top->next; // remove top from the stack
		temp->next = pList->current; // newnode point to current
		temp->prev = pList->current->prev; // newnode point to current prev
		pList->current->prev = temp; //current  prev to temp
		temp->prev->next = temp;
		pList->current = temp; // set current to temp
	}
	number_of_nodes_used ++; // update
	pList->count++;
	pList->bounds = 2;
	return 0;

}

int List_append(List* pList, void* pItem) // append item to tail
{

	if (number_of_nodes_used == LIST_MAX_NUM_NODES)
	{

		return -1;
	}

	top->value = pItem;

	if (pList->count == 0 )
	{

		pList->head = top;
		pList->tail = top;
		pList->current = top;
		top = top->next;
		pList->head->prev = NULL;
		pList->head->next = NULL;

	}
	else  // add to the start
	{

	Node* temp = top; // temp node for new node being added
		top=top->next; // pop from the top

		temp->prev = pList->tail; // new node points to the tail
		pList->tail->next = temp;
		pList->tail = temp;
		temp->next = NULL;
		pList->current = pList->tail;
	}


	number_of_nodes_used++; // increment the node
	pList->count++; // increment the count of the head number of nodes
	pList->bounds = 2;
	return 0;
}


int List_prepend(List* pList, void* pItem) // add to head code been said before
{
	if (number_of_nodes_used == LIST_MAX_NUM_NODES)
	{

		return -1;
	}

	top->value = pItem;

	if (pList->count == 0 )
	{

		pList->head = top;
		pList->tail = top;
		pList->current = top;
		top = top->next;

		pList->head->prev = NULL;
		pList->head->next = NULL;
	}
	else
	{

		Node* temp = top;
		top = top->next; // pop from the top
		temp->prev = NULL;
		temp->next = pList->head;
		pList->head = temp;

		pList->current  = pList->head;
		temp->next->prev = temp;
	}
	number_of_nodes_used++; // increment the node
	pList->count++; // increment the count of the head number of nodes
	pList->bounds = 2;
	return 0;
}

void* List_remove(List* pList) // remove current
{
	if (pList->bounds == 0 || pList->bounds == 1 || pList->count == 0) // edge cases
	{

		return NULL;
	}
	number_of_nodes_used--;
	 if (pList->count == 1) // if only one node
	{

		Node*temp = pList->current; // add a temp node to the node about to be removed

		pList->head = NULL;
		pList->tail = NULL;
		pList->current = NULL;
		pList->count = 0;
		pList->bounds = 1;
		temp->next = top; // adding the unused node to stack
		top = temp;
		temp->prev = NULL;

		return temp->value;

	}
	else if (pList->current == pList->head) // if at head
	{

		Node*temp = pList->head; // remove the top
		temp->next->prev = NULL; // the pointer after head does not point to old node
		pList->current = temp->next; // change the current pointer
		pList->head = temp->next;
		temp->next = top;
		top = temp;

		pList->count--;

		temp->prev = NULL;
		return temp->value;
	}
	else if (pList ->tail == pList->current) // if at tail
	{

		Node*temp = pList->current;

		pList->count--;
		pList->tail = pList->tail->prev; //tail points to node before current
		pList->tail->next = NULL;
		pList->bounds = 1; // set beyond list
		pList->current = NULL;

		temp->prev = NULL;
		temp->next = top;
		top = temp;
		return temp->value;
	}
	else // i checked no edge cases hopefully
	{

		pList->current->next->prev = pList->current->prev; // making the pointer next to current prev point to node before current
		pList->current->prev->next = pList->current->next;
		pList->count--;
		Node*temp = pList->current; // remove the top
		pList->current = temp->next;
		temp->next = top;
		top = temp;

		temp->prev = NULL;
		return temp->value;

	}

}


void* List_trim(List* pList) // removes tail and set the prev node of old tail as the new one
{
	if (pList->bounds == 0 || pList->bounds == 1 || pList->count == 0)
	{

		return NULL;
	}
	number_of_nodes_used--;
	 if (pList->count == 1)
	{

		Node*temp = pList->current; // add a temp node to the node about to be removed
		temp->next = top; // adding the unused node to stack
		top = temp;
		pList->head = NULL;
		pList->tail = NULL;
		pList->current = NULL;
		pList->count = 0;
		pList->bounds = 0;

		temp->prev = NULL;
		return temp->value;

	}
	else
	{

		Node*temp = pList->tail;
		pList->count--;
		pList->tail = pList->tail->prev;
		pList->tail->next = NULL;
		pList->bounds = 2;
		pList->current = pList->tail;
		temp->next = top;
		top = temp;
		temp->prev = NULL;
		return temp->value;
	}
}

void List_concat(List* pList1, List* pList2) // combine the node
{
	number_of_heads_used--;
	if (pList1->count == 0 && pList2->count == 0)
	{


	}
	else if (pList2->count == 0)
	{

	}
	else if (pList1->count == 0)
	{
		pList1->head = pList2->head;
		pList1->tail = pList2->tail;
		pList2->next = head_top;
		pList1->count += pList2->count;
	}
	else
	{
	pList1->count += pList2->count;
	pList1->tail->next = pList2->head; // tail connects to head
	pList2->head->prev = pList1->tail; // head connects to tail
	pList1->tail = pList2->tail;
	}
	if (number_of_heads_used == LIST_MAX_NUM_HEADS)
	{
		head_top = pList2;
		pList2->current = NULL;
		pList2->head = NULL;
		pList2->tail = NULL;
		pList2->count = 0;
		return;
	}


	pList2->next = head_top;
		head_top = pList2;
		pList2->current = NULL;
		pList2->head = NULL;
		pList2->tail = NULL;
		pList2->count = 0;
}


void List_free(List* pList, FREE_FN pItemFreeFn) // freeing the node and returning head back to stack
{
	if (pList == NULL)
		return;
	while (pList->head != NULL)
	{

			void* temp = List_trim(pList);
			(*pItemFreeFn)(temp);

	}

	if (number_of_heads_used == LIST_MAX_NUM_HEADS) // edge case if stack of head empty
	{

		head_top = pList;
		number_of_heads_used--;
		pList->current = NULL;
		pList->head = NULL;
		pList->tail = NULL;
		pList->count = 0;
		return;
	}
	pList->next = head_top;
		head_top = pList;
	number_of_heads_used--;
}


void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg) // checks if the item matchs if so then return the pointer to it
{
	Node* temp;
	if (pList == NULL || pList->count == 0)
		return NULL;
	if (pList->current == NULL && pList->bounds == 1)
		return NULL;
	if (pList->current == NULL && pList->bounds == 0)
	{
		temp = pList->head;
	}
	else{
		temp = pList->current;
	}

	while (temp != NULL)
	{

		if ((*pComparator)(temp->value,pComparisonArg) == true)
		{
			pList->current = temp;
			return temp;
		}

		temp = temp->next;
	}
	pList->current = NULL;
	pList->bounds = 1;
	return NULL;

}
