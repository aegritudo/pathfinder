#include	<cstddef>
#include    <stdlib.h>

#include	"CPathFinder.h"



CPathFinder::CPathFinder( void )
// : m_MasterNodeList.clear()
: m_pStartNode( NULL )
, m_pGoalNode( NULL )
//, m_OpenListBreadthFirst
//, m_OpenList
{


} // CPathFinder



CPathFinder::~CPathFinder( void )
{

	// Delete all content
	for( CNode::NodeVector::iterator it = m_MasterNodeList.begin(); it != m_MasterNodeList.end(); ++it )
	{
		CNode*	pNode	= *it;

		delete pNode;
	}

} // ~CPathFinder


void
CPathFinder::BuildSearchSpace( const unsigned char* pMap, const int StartX, const int StartY, const int TargetX, const int TargetY, const int MapWidth, const int MapHeight)
{
	int	Index	= 0;

	//Make sure node list is empty before building the search space
	if (m_MasterNodeList.empty() == false)
	{
		for (CNode::NodeVector::iterator it = m_MasterNodeList.begin(); it != m_MasterNodeList.end(); ++it)
		{
			CNode*	pNode = *it;

			delete pNode;
		}
	}

	// Create nodes row by row and assign their index and state
	for( int Row = 0; Row < MapHeight; Row++ )
	{
		for (int Column = 0; Column < MapWidth; Column++)
		{
			CNode* pNode = new CNode();
			pNode->m_PosX = Column;
			pNode->m_PosY = Row;
			pNode->m_Index = Index;

			if (pMap[Index] == 1)
			{
				pNode->m_State = CNode::STATE_NONE;
			}

			else
			{
				pNode->m_State = CNode::STATE_BLOCKED;
			}

			Index++;

			//Add to Master List
			m_MasterNodeList.push_back(pNode);
		}
				
	}

	// Find the starting and target node
	m_pStartNode = GetNode(&m_MasterNodeList,StartX, StartY);
	m_pGoalNode = GetNode(&m_MasterNodeList,TargetX, TargetY);

	// Create the node connections
	CalculateConnections();

}	// BuildSearchSpace



void
CPathFinder::CalculateConnections( void )
{
	
	const float	Distance = AcceptableDistanceForAConnectingNode() * AcceptableDistanceForAConnectingNode();

	// Clear out the old connection data in the m_MasterNodeList's Nodes
	for( CNode::NodeVector::iterator it = m_MasterNodeList.begin(); it != m_MasterNodeList.end(); ++it )
	{
		CNode*	pNode	= *it;

		pNode->m_ConnNodes.clear();
	}

	// Checks distance between nodes and if the distance is acceptable creates a connection between the nodes
	// Connections are calculated to allow for easy transion between diagonal and non-diagonal movement
	for( CNode::NodeVector::iterator it1 = m_MasterNodeList.begin(); it1 != m_MasterNodeList.end(); ++it1 )
	{
		CNode*	pNode1	= *it1;

		if( pNode1->m_State != CNode::STATE_BLOCKED )
		{			
			for( CNode::NodeVector::iterator it2 = it1 + 1; it2 != m_MasterNodeList.end(); ++it2 )
			{
				CNode*	pNode2	= *it2;

				if( pNode2->m_State != CNode::STATE_BLOCKED )
				{
					float Diff	= CostFromNodeToNode(pNode1, pNode2);

					if (Diff < Distance)
					{
						pNode1->m_ConnNodes.push_back(pNode2);
						pNode2->m_ConnNodes.push_back(pNode1);
					}
				}
			}
		}
	}

}  // CalculateConnections



CNode*
CPathFinder::GetNode( const CNode::NodeVector* pMasterNodeList, const int PosX, const int PosY)
{
	// Check the list and return the correct node, or NULL if no match is found
	for( CNode::NodeVector::const_iterator it = pMasterNodeList->begin(); it != pMasterNodeList->end(); ++it )
	{
		CNode*	pNode	= *it;

		
		if( PosX == pNode->m_PosX && PosY == pNode->m_PosY)
			return pNode;
	}

	return NULL;

}	// */ // GetNode


int
CPathFinder::PopulateOutBuffer(int* pOutBuffer, int OutBufferSize)
{
	int	 StepsTaken = 0;
	std::vector< int >	TempBuffer;

	CNode* pNode = m_pGoalNode;

	// As long as path that is found does nbot have more steps than the buffer size
	// Backtrack from goal to start and save the indices to a temporary buffer
	
	while (pNode->m_pParent != NULL && StepsTaken <= OutBufferSize)
	{
		TempBuffer.push_back(pNode->m_Index);
		pNode = pNode->m_pParent;
		StepsTaken++;
	}

	// Check to make sure we didn't exit the previous if-case due to a small buffer
	if (StepsTaken > OutBufferSize)
	{
		//printf("OutBuffer for path is to small");
		
		return -1;
	}

	// List is from goal to start, so we move from front to back on the temp buffer
	// pop.back() makes sure we always have the next item at the back and can easily get it with back()
	for (int i = 0; i < StepsTaken; i++)
	{
		pOutBuffer[i] = TempBuffer.back();
		TempBuffer.pop_back();
		
	}

	// Fill the rest of the buffer with -1 for clarity when viewing buffer
	// Can be omitted to decrease pathfinding time
	for (int i = StepsTaken; i < OutBufferSize; i++)
	{
		pOutBuffer[i] = -1;
	}

	

	return StepsTaken;

}

float
CPathFinder::GetNodeHeuristic( const CNode* pStartNode, const CNode* pGoalNode )
{
	float	TotalDistance, DistanceX, DistanceY;

	// Find estimated cost to goal using the Manhattan method as we have a non-diagonal pathfindning.
	// If using a diagonal movement this must be changed

	DistanceX = pStartNode->m_PosX - pGoalNode->m_PosX;
	DistanceY = pStartNode->m_PosY - pGoalNode->m_PosY;

	TotalDistance = abs(DistanceX + DistanceY);

	return TotalDistance;

}	// GetNodeHeuristic



float
CPathFinder::CostFromNodeToNode( const CNode* pNewNode, const CNode* pBestNode )
{

	// Distance returned as a square to avoid a performance hit with sqrt
	// Remember that numbers that are compared to the return values should also be squared
	float	TotalDistance, DistanceX, DistanceY;

	DistanceX = pNewNode->m_PosX - pBestNode->m_PosX;
	DistanceY = pNewNode->m_PosY - pBestNode->m_PosY;

	TotalDistance = (DistanceX * DistanceX) + (DistanceY * DistanceY);

	return TotalDistance;

}	// CostFromNodeToNode

int
CPathFinder::FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize)
{
	// Build the search space and put the start node on the open list so we can check its connections
	BuildSearchSpace(pMap, nStartX, nStartY, nTargetX, nTargetY, nMapWidth, nMapHeight);
	
	CNode*	pStartNode = m_pStartNode;

	pStartNode->m_CostToStart = 0;
	pStartNode->m_CostToGoal = GetNodeHeuristic(pStartNode, m_pGoalNode);
	pStartNode->m_TotalCost = pStartNode->m_CostToGoal;
	pStartNode->m_pParent = NULL;

	m_OpenList.PushPriorityQueue(pStartNode);

	while (!m_OpenList.IsPriorityQueueEmpty())
	{
		// Get first candidate node to search next and remove it from list
		CNode*	pCandidateNode = m_OpenList.PopPriorityQueue();

		if (pCandidateNode == m_pGoalNode)
		{
			return PopulateOutBuffer(pOutBuffer, nOutBufferSize); // return with success
		}


		// Loop through all connecting nodes of candidate node
		for (CNode::NodeVector::iterator it = pCandidateNode->m_ConnNodes.begin(); it != pCandidateNode->m_ConnNodes.end(); ++it)
		{
			CNode*	pNode = *it;
			float		RealCost = pCandidateNode->m_CostToStart + CostFromNodeToNode(pCandidateNode, pNode);
			// If we already have checked the node...
			if (pNode->m_State == CNode::STATE_OPEN || pNode->m_State == CNode::STATE_CLOSED)
			{
				//... see if this path is shorter than the last time
				if (pNode->m_CostToStart <= RealCost)
				{
					// If it's longer just ignore the node
					continue;
				}

			}

			pNode->m_pParent = pCandidateNode;
			pNode->m_CostToStart = RealCost;
			pNode->m_CostToGoal = GetNodeHeuristic(pNode, m_pGoalNode);
			pNode->m_TotalCost = pNode->m_CostToGoal + pNode->m_CostToStart;

			if (pNode->m_State == CNode::STATE_CLOSED)
			{
				pNode->m_State = CNode::STATE_NONE;
			}

			if (pNode->m_State != CNode::STATE_OPEN)
			{
				// Put on Open-list
				pNode->m_State = CNode::STATE_OPEN;
				m_OpenList.PushPriorityQueue(pNode);


			}

			else
			{
				//Found alternate path to the node so it needs to be updated on the queue
				m_OpenList.UpdateNodeOnPriorityQueue(pNode);
			}

		}

		// Now that we've explored candidate node, put it on the Closed-list.
		pCandidateNode->m_State = CNode::STATE_CLOSED;

	}

	// If we got here, all nodes have been searched without finding the goal
	return -1;

}	// FindPath
