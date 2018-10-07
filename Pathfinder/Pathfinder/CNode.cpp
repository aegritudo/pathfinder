#include	<cstddef>

#include	"CNode.h"



CNode::CNode( void )
: m_pParent( NULL )
, m_PosX( 0 )
, m_PosY( 0 )
, m_CostToStart( 0.0f )
, m_CostToGoal( 0.0f )
, m_TotalCost( 0.0f )
, m_State( STATE_NONE )
{

}	// */ // CNode



CNode::~CNode( void )
{

}	// */ // ~CNode
