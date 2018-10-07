

#ifndef __CPRIORITYQUEUE_H__
#define __CPRIORITYQUEUE_H__


#include	"CNode.h"

class CPriorityQueue
{
public:

	// Constructor / Destructor
	explicit CPriorityQueue	( void );
			~CPriorityQueue	( void );



	CNode*		PopPriorityQueue			( void );
	void		PushPriorityQueue			( CNode* pNode );
	void		UpdateNodeOnPriorityQueue	( CNode* pNode );
	CNode*		ReadPriorityQueue			( void );
	void		ClearPriorityQueue			( void );
	bool		IsPriorityQueueEmpty		( void );

	// Heap implementation using an STL vector
	// Note; the vector is an STL container, but the
	// operations done on the container cause it to
	// be a priority queue organized as a heap
	CNode::NodeVector	m_Heap;



private:

	class CNodeTotalGreater
	{
	public:

		// This is required for STL to sort the priority queue
		// it is entered as an argument in the STL heap functions
		bool operator() ( const CNode* pFirst, const CNode* pSecond ) const	{ return ( pFirst->m_TotalCost > pSecond->m_TotalCost ); }
	};

};

#endif	// __CPRIORITYQUEUE_H__
