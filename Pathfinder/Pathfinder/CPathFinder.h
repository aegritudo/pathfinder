

#ifndef __CPATHFINDER_H__
#define __CPATHFINDER_H__


#include	"CPriorityQueue.h"

class CNode;

class CPathFinder
{
public:

	// Constructor / Destructor
	explicit CPathFinder	( void );
			~CPathFinder	( void );



	// Functions to setup search
	void				BuildSearchSpace		( const unsigned char* pMap,const int StartX, const int StartY, const int TargetX, const int TargetY, const int MapWidth, const int MapHeight );
	void				CalculateConnections	(void);
	
	// Function to output the final path
	int				    PopulateOutBuffer(int* pOutBuffer, int OutBufferSize);
	
	// Functions to get relevant nodes
	CNode*				GetNode									( const CNode::NodeVector* pMasterNodeList, const int PosX, const int PosY );
	CNode*				GetStartNode							( void ) const	{ return m_pStartNode; }
	CNode*				GetGoalNode								( void ) const	{ return m_pGoalNode; }
	CNode::NodeVector*	GetMasterNodeList						( void ) const	{ return ( CNode::NodeVector* )&m_MasterNodeList; }


	// Function called to start search
	int						FindPath								(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
																	 const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
																	 int* pOutBuffer, const int nOutBufferSize);



	float					AcceptableDistanceForAConnectingNode	( void )		{ return 1.1f; }




private:


	// Heuristic and distance functions
	float	GetNodeHeuristic	( const CNode* pStartNode, const CNode* pGoalNode );
	float   CostFromNodeToNode	( const CNode* pNewNode, const CNode* pBestNode );



	// List containing all nodes and list for open nodes
	CNode::NodeVector	m_MasterNodeList;
	CPriorityQueue		m_OpenList;

	// Important nodes
	CNode*			m_pStartNode;
	CNode*			m_pGoalNode;

	


};

#endif	// __CPATHFINDER_H__
