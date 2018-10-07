
#include	"CPriorityQueue.h"

#include	<algorithm>




CPriorityQueue::CPriorityQueue( void )
{

}	 // CPriorityQueue



CPriorityQueue::~CPriorityQueue( void )
{

}	// ~CPriorityQueue



CNode*
CPriorityQueue::PopPriorityQueue( void )
{
	// Get the node at the front - it has the lowest total cost
	CNode*	pNode	= m_Heap.front();

	// pop_heap will move the node at the front to the position N and then sort the heap to make positions 1 to N-1 correct
	pop_heap( m_Heap.begin(), m_Heap.end(), CNodeTotalGreater() );

	// pop_back() will actually remove the last element from the heap
	// now the heap is sorted for positions 1 through N 
	m_Heap.pop_back();

	return( pNode );

}	// PopPriorityQueue



void
CPriorityQueue::PushPriorityQueue( CNode* pNode )
{
	// Pushes the node onto the back of the vector ( the heap is now unsorted )
	m_Heap.push_back( pNode );

	// Sorts the new element into the heap
	push_heap( m_Heap.begin(), m_Heap.end(), CNodeTotalGreater() );

}	// PushPriorityQueue



void
CPriorityQueue::UpdateNodeOnPriorityQueue( CNode* pNode )
{
	// Loop through the heap and find the node to be updated
	for( CNode::NodeVector::iterator it = m_Heap.begin(); it != m_Heap.end(); ++it )
	{
		CNode*	pNode	= *it;

		// Comparing the nodes
		if( pNode == pNode )
		{
			// Found node - resort from this position in the heap
			// ( since its total value was changed before this function was called )
			push_heap( m_Heap.begin(), it + 1, CNodeTotalGreater() );

			return;
		}
	}

}	// UpdateNodeOnPriorityQueue



CNode*
CPriorityQueue::ReadPriorityQueue( void )
{
	// Get the node at the front - it has the lowest total cost
	return m_Heap.front();

}	 // ReadPriorityQueue



void
CPriorityQueue::ClearPriorityQueue( void )
{
	// Loop through the heap and delete all content
	for( CNode::NodeVector::iterator it = m_Heap.begin(); it != m_Heap.end(); ++it )
	{
		CNode*	pNode	= *it;

		delete pNode;
	}

	m_Heap.clear();

}	// ClearPriorityQueue



bool
CPriorityQueue::IsPriorityQueueEmpty( void )
{	
	// Check if heap is empty

	return( m_Heap.empty() );

}	// IsPriorityQueueEmpty
