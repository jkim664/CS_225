/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
 #include <iostream>
 
template <class T>
List<T>::~List()
{
	clear();	

    /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
	ListNode* target = tail;
	
	while (target != NULL) {
		tail = tail->prev;
		delete target;
		target = tail;
		length--;
		
		
		
	
	}


	head = NULL;
	tail = NULL;
	target = NULL;







    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
	ListNode* p = head;
	
	if (p != NULL) {
	
		
		head = new ListNode(ndata);
		head->next = p;
		p->prev = head;
		p = NULL;
		length++;
		
	} else {
	
		head = new ListNode(ndata);
		tail = head;
		p = NULL;
		length++;
		
	}




    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
	ListNode* p = tail;
	
	if (p != NULL) {
	
		
		tail = new ListNode(ndata);
		p->next = tail;
		tail->prev = p;
		p = NULL;
		length++;
		
	} else {
	
		tail = new ListNode(ndata);
		head = tail;
		p = NULL;
		length++;
		
	}





    /// @todo Graded in MP3.1
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{	
    //ListNode* h = head;
    //ListNode* t = tail;
    
    reverse(head, tail);
    //head = h;
    //tail = t;
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{	
	
	if (startPoint == NULL || endPoint == NULL) return;
	if (startPoint == endPoint) return;
	
	ListNode* temp = NULL;
	ListNode* S = NULL;
	ListNode* E = NULL;
	ListNode* tempS = startPoint;
	
	if (startPoint->prev != NULL) {
		S = startPoint->prev;
		startPoint->prev = NULL;
		S->next = NULL;
		
	}
	
	if (endPoint->next != NULL) {
		E = endPoint->next;
		endPoint->next = NULL;
		E->prev = NULL;
	}
	
	
	while (startPoint != NULL && startPoint != endPoint->next) {
		
		temp = startPoint->prev;
		startPoint->prev = startPoint->next;
		startPoint->next = temp;
		startPoint = startPoint->prev;
	
	}
	
	startPoint = tempS;
	temp = endPoint;
	endPoint = startPoint;
	startPoint = temp;
	
	if (S != NULL) {
		startPoint->prev = S;
		S->next = startPoint;
	}
	
	if (E != NULL) {
		endPoint->next = E;
		E->prev = endPoint;
	
	}
	
	
	
	return;
	
    /// @todo Graded in MP3.1
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{	
	if (head == NULL || tail == NULL) return;
	
	if (n == 0 || n == 1) return;
	
	if (n > length) {
		reverse(head, tail);
		return;
	
	}
	
	ListNode* S = head;
	ListNode* E = S;
	int count = 1;
	
	while (count < length) {
	
		for (int i = 1; i < n; i++) {
		
			if (E->next != NULL) {
			 	E = E->next;
			 	
			}
			count++;
		}
	
		reverse(S, E);
		
		if (count == n) {
			while (head->prev != NULL) {
				head = head->prev;
			}
		}
		
		
		if (count >= length) {
			while (tail->next != NULL) {
				tail = tail->next;
			}
		
		}
		
		if (E->next != NULL) {
			E = E->next;
			S = E;
			count++;			//YOU NEED TO ADD TO COUNT WHEN YOU CHANGE TO THE NEXT BLOCK YOU DOOFUS
		}
				
	
	}
	
	S = NULL;
	E = NULL;
	
	return;
    /// @todo Graded in MP3.1
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{	
	if (head == NULL || tail == NULL || head == tail || length == 1) return;   //Worked on first attempt, I deserve a cookie.
	
	ListNode* current = head;
	ListNode* tempP = NULL;
	ListNode* tempN = NULL;
	
	while (current->next != tail) {
	
		tempP = current;
		current = current->next;
		tempN = current->next;
		
		tempP->next = NULL;
		current->prev = NULL;
		current->next = NULL;
		tempN->prev = NULL;
		
		tail->next = current;
		current->prev = tail;
		
		tempP->next = tempN;
		tempN->prev = tempP; 
		
		tail = tail->next;
		current = tempN;

	}
	
	return;


    /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
	
	
	for (int i = 1; i < splitPoint; i++) {
		
		if (start->next != NULL) {
		
			start = start->next;
		}
	
	}

	ListNode* newStart = start->next;
	
	newStart->prev = NULL;
	start->next = NULL;
	


   
   	return newStart; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{	
	
	if (first == NULL && second == NULL) return NULL;
	
	if (first == NULL) return second;
	if (second == NULL) return first;

	ListNode* merged = (first->data < second->data) ? first : second;
	ListNode* H = merged;
	
	if (merged == first) first = first->next;
	if (merged == second) second = second->next;
	
	
	while (first != NULL || second != NULL) {
		
		if (first != NULL && second != NULL) {
			if (first->data < second->data) {
				merged->next = first;
				first->prev = merged;
				merged = merged->next;
				first = first->next;
				
				
			}
			else {
			
				merged->next = second;
				second->prev = merged;
				merged = merged->next;	
				second = second->next;
		
			}
		
		
		
		
		}
		else if (first != NULL) {
		
			merged->next = first;
			first->prev = merged;
			merged = merged->next;
			first = first->next;
		
		
		
		}
		else if (second != NULL) {
			
			merged->next = second;
			second->prev = merged;
			merged = merged->next;
			second = second->next;
	
		}

   	}
   	
   	//first = NULL;
   	//second = NULL;
   	//merged = NULL;
   	head = H;
   	return H;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
	
	if (chainLength <= 1) return start;	
		
	
	
	ListNode* left = start;
	
	ListNode* right = split(start, chainLength/2);
		
	left = mergesort(left, chainLength/2);
	
    	right = mergesort(right, chainLength - (chainLength/2));
    
	return merge(left, right); // change me!
}






