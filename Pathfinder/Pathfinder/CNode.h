
#ifndef __CNODE_H__
#define __CNODE_H__


#include	<vector>

class CNode
{
public:

	// States that a node can be in
	enum EState
	{
		STATE_NONE			= 0x00000000,
		STATE_OPEN			= 0x00000001,
		STATE_CLOSED,
		STATE_BLOCKED,
		STATE_FORCE_DWORD	= 0x7FFFFFFF
	};

	typedef std::vector< CNode* >	NodeVector;



	// Constructor / Destructor
	explicit CNode	( void );
			~CNode	( void );

	// Node Connections
	NodeVector	m_ConnNodes;
	CNode*		m_pParent;

	// Identifying Variables
	int			m_PosX;
	int			m_PosY;
	int			m_Index;
	EState		m_State;

	// Distance Variables
	float		m_CostToStart;
	float		m_CostToGoal;
	float		m_TotalCost;



};

#endif	// __CNODE_H__
