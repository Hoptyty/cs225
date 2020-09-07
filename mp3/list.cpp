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
template <class T>
List<T>::~List()
{
	clear();
}
/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    	ListNode * S;
	while(head!=NULL){
	S=head;
	head=head->next;
	delete S;
	}
	length=0;
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
    	ListNode * S;
	S=new ListNode(ndata);
	
	if(length==0){
	head=S;
	tail=S;
	}else{
	head->prev=S;
	S->next=head;
	head=S;
	S->prev=NULL;
	}
	length++;
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
    	ListNode * S;
	S=new ListNode(ndata);

	if(length==0){
	head=S;
	tail=S;
	}else{
	tail->next =S;
	S->prev=tail;
	tail=S;
	S->next=NULL;
	}
	
	
	length++;
	/// @todo Graded in MP3.1
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
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
   	if(startPoint==NULL||endPoint==NULL||startPoint==endPoint) return;
	ListNode * tempHead;
	ListNode * tempTail;
	tempHead=startPoint->prev;
	tempTail=endPoint->next;
	ListNode * temp;
	temp=startPoint;
	//ListNode * tp;
	//tp=startPoint->next;	
	while(startPoint!=endPoint){
		startPoint->prev=startPoint->next;
		startPoint=startPoint->next;
	}
	startPoint=temp;
	while(startPoint!=endPoint){
		startPoint->prev->next=startPoint;
		startPoint=startPoint->prev;
	}
	
	//startPoint=temp;
	if(tempHead!=NULL){
		tempHead->next=endPoint;
		endPoint->prev=tempHead;
		
	}else {
		endPoint->prev=NULL;
		head=endPoint;
		}
	if(tempTail!=NULL){
		tempTail->prev=temp;
		temp->next=tempTail;
	}else	{
		temp->next=NULL;
		tail=temp;
		}
	
	//startPoint = endPoint;
	endPoint=temp;	
	
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
    	int rest=length;
	ListNode * curr;
	ListNode * tempTail;
	curr=head;
	tempTail=head;
	while(rest>n){
		for(int i=1; i<n;i++)
			tempTail=tempTail->next;
		reverse(curr,tempTail);
		tempTail=tempTail->next;
		curr=tempTail;
		rest=rest-n;
	}
	reverse(curr,tail);
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
    	if(length==0) return;
	ListNode * curr;
	curr=head;

	while(curr->next!=tail&&curr->next!=NULL&&curr!=NULL){
		tail->next=curr->next;
		curr->next->prev=tail;
		curr->next=curr->next->next;
		curr->next->prev=curr;
		curr=curr->next;
		tail->next->next=NULL;
		tail=tail->next;
	}
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
    	//ListNode * tempHead=NULL;
	//if(splitPoint==0) {
	//	if(start->prev!=NULL)
	//		start->prev->next=NULL;
	//	start->prev=NULL;
	//	tempHead=start;
	//	head=start;
	//	return tempHead;
	//}
	//if(start->next==NULL)
	//	return tempHead;
	//return split(start->next,splitPoint-1);
	ListNode * tempHead= start;
	while(splitPoint!=0) {
		if(start->next==NULL)
			return tempHead;
		start=start->next;
		splitPoint--;
	}
	if(start->prev!=NULL)
		start->prev->next=NULL;
	start->prev=NULL;
	return start;



	/// @todo Graded in MP3.2
     // change me!
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
    	ListNode * tempHead;
	if(first->data<second->data) {
		tempHead=first;
		first=first->next;
	}
	else {
		tempHead=second;
		second=second->next;
	}
	ListNode * temp=tempHead;
	while(first!=NULL&&second!=NULL) {
		if(first->data<second->data) {
			temp->next=first;
			first->prev=temp;
			first=first->next;
		} else {
			temp->next=second;
			second->prev=temp;
			second=second->next;
		}
		temp=temp->next;
	}
	if(first==NULL) {
		temp->next=second;
		second->prev=temp;
	} else {
		temp->next=first;
		first->prev=temp;
	}
	return tempHead;
		
			
	/// @todo Graded in MP3.2
     // change me!
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
  	if(chainLength<=1) return start;
	ListNode * mid= split(start, chainLength/2);
	ListNode * temp1=mergesort(start,chainLength/2);
	ListNode * temp2=mergesort(mid,(1+chainLength)/2);
	return merge (temp1,temp2);
	/// @todo Graded in MP3.2
    	 // change me!
}
