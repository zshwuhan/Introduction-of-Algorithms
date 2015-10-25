#include <iostream>
#include <ctime>
#include <cassert>
#include <sstream>
using namespace std;

#include "red_black_tree.h"

//��̬��Ա������ʼ��
template<typename TKey, typename TValue>
typename RBTree<TKey, TValue>::RBTreeNode * RBTree<TKey, TValue>::m_pNil = NULL;

template<typename TKey, typename TValue>
RBTree<TKey, TValue>::RBTree() 
{
	if ( !m_pNil ) {
		//Ҷ�����һ������ĺڽ��
		m_pNil = new RBTreeNode();
		m_pNil->Color = BLACK;
	}
	m_pRoot = m_pNil;
}

template<typename TKey, typename TValue>
RBTree<TKey, TValue>::~RBTree()
{
	_RecursiveReleaseNode( m_pRoot );
}

template<typename TKey, typename TValue>
void RBTree<TKey, TValue>::_RecursiveReleaseNode( RBTreeNode *node )
{
	if ( node->isValid() ) {
		_RecursiveReleaseNode( node->Left );
		_RecursiveReleaseNode( node->Right );
		delete node;
	}
}

template<typename TKey, typename TValue>
bool RBTree<TKey, TValue>::Empty()
{
	return !(m_pRoot->isValid());
}

//����
template<typename TKey, typename TValue> 
void RBTree<TKey, TValue>::_LeftRotate( RBTreeNode *x_node )
{
	//assert
	if ( !(x_node->isValid() && x_node->Right->isValid()) )
		throw exception( "��������Ҫ��Է��ڱ����в���������Ҫ���Һ���Ҳ�����ڱ�" );

	RBTreeNode *y_node = x_node->Right;

	//������������ּ���� y �滻 x��ע�⽫ x ��Parent��Left��Right������ y ��
	// 1) x �� y ���� (��)
	x_node->Right = y_node->Left;
	if (y_node->Left != m_pNil)
		y_node->Left->Parent = x_node;
	
	// 2) ����y->Parent (��)
	y_node->Parent = x_node->Parent;
	if (x_node->Parent == m_pNil)
		m_pRoot = y_node;
	else if (x_node->Parent->Left == x_node)
		x_node->Parent->Left = y_node;
	else
		x_node->Parent->Right = y_node;

	// 3) ����y->Left (��)
	y_node->Left = x_node;
	x_node->Parent = y_node;
}

//����
template<typename TKey, typename TValue> 
void RBTree<TKey, TValue>::_RightRotate( RBTreeNode *x_node )
{
	//assert
	if ( !(x_node->isValid() && x_node->Left->isValid()) )
		throw exception( "��������Ҫ��Է��ڱ����в���������Ҫ������Ҳ�����ڱ�" );
	RBTreeNode *y_node = x_node->Left;

	//������������ּ���� y �滻 x��ע�⽫ x ��Parent��Left��Right������ y ��
	// 1) x �� y ���� (��)
	x_node->Left = y_node->Right;
	if (y_node->Right != m_pNil)
		y_node->Right->Parent = x_node;

	// 2) ����y->Parent (��)
	y_node->Parent = x_node->Parent;
	if (x_node->Parent == m_pNil)
		m_pRoot = y_node;
	else if (x_node->Parent->Right == x_node)
		x_node->Parent->Right = y_node;
	else
		x_node->Parent->Left = y_node;

	// 3) ����y->Left (��)
	y_node->Right = x_node;
	x_node->Parent = y_node;
}

//����
template<typename TKey, typename TValue> 
typename RBTree<TKey, TValue>::RBTreeNode* RBTree<TKey, TValue>::Search( TValue const &value )
{
	RBTreeNode *node = m_pRoot;
	while( node != m_pNil && node->Value != value )
		node = ((value < node->Value) ? node->Left:node->Right);
	return node;
}

//����
template<typename TKey, typename TValue> 
bool RBTree<TKey, TValue>::Insert( TKey key, TValue value )
{
	if ( Search(value)->isValid() )
		//value �ظ������ʧ��
		return false;
	else {
		//����ӵĽڵ�Ϊ���㣬left=right=nil
		RBTreeNode *new_node = new RBTreeNode();
		new_node->Key = key;
		new_node->Value = value;
		new_node->Color = RED;
		new_node->Left = new_node->Right = m_pNil;
	
		//����
		_InsertRBTree(new_node);
		//�޸�
		_InsertFixup(new_node);
		return true;
	}
}

//�����Ĳ���:���������������һ��
template<typename TKey, typename TValue> 
void RBTree<TKey, TValue>::_InsertRBTree( RBTreeNode *new_node )
{
	RBTreeNode *current_node = m_pNil;
	RBTreeNode *next_node = m_pRoot;

	//�ҵ������
	while ( next_node != m_pNil ) {
		current_node = next_node;
		next_node = ( new_node->Value < next_node->Value )? next_node->Left: next_node->Right;
	}

	new_node->Parent = current_node;
	if ( current_node == m_pNil ) //����
		m_pRoot = new_node;
	else if ( new_node->Value < current_node->Value )
		current_node->Left = new_node; //����������
	else
		current_node->Right = new_node; //����������

	//����new_node-left-right = nil, color = red
	new_node->Left = m_pNil;
	new_node->Right = m_pNil;
	new_node->Color = RED;	//������Ϊ��ɫ
}

//�����޸�
//new_node -> z, uncle_node -> y;
template<typename TKey, typename TValue> 
void RBTree<TKey, TValue>::_InsertFixup( RBTreeNode *new_node )
{
//////////////////////////////////////////////////////////////////////////
//���µ�д��
/*
	while ( new_node->Parent->Color == RED ) {
		RBTreeNode *uncle_node = new RBTreeNode();
		if ( new_node->Parent == new_node->Parent->Parent->Left ) { //new�ĸ����Ϊ�游��������
			uncle_node = new_node->Parent->Right; //uncle������ұ�

			if ( uncle_node->Color == RED ) { //case1: new ������Ϊ��ɫ
				new_node->Color = BLACK;
				uncle_node->Color = BLACK;
				new_node->Parent->Color = RED;
				new_node = new_node->Parent->Parent;
			}

			else if ( uncle_node->Color == BLACK && new_node->Parent->Right )  //case2: new ����Ϊ��ɫ��new��һ���Һ���
				_LeftRotate( new_node->Parent ); 

			new_node->Parent->Color = BLACK;	//case3: new ����Ϊ��ɫ��new������
			new_node->Parent->Parent->Color = RED;
			_RightRotate( new_node->Parent->Parent ); 
		}
		else { //������ԳƵ���ͬ����
			///
		}	
	}
*/
//////////////////////////////////////////////////////////////////////////
//������д��
	while ( new_node->Parent->Color == RED ) {

		//��ʶnew�ĸ�����Ƿ����游��������
		bool parent_is_left_child_flag = ( new_node->Parent == new_node->Parent->Parent->Left );
		RBTreeNode *uncle_node = ( parent_is_left_child_flag ? new_node->Parent->Parent->Right: new_node->Parent->Parent->Left );

		if ( uncle_node->Color == RED ) { //case1: new ������Ϊ��ɫ
			new_node->Parent->Color = BLACK;  //!!!
			uncle_node->Color = BLACK;
			new_node->Parent->Parent->Color = RED; //!!!�������ط�д���ˣ�tmd,�������Ӹ��˴����
			new_node = new_node->Parent->Parent;
		}

		else {
			if ( new_node == ( parent_is_left_child_flag ? new_node->Parent->Right: new_node->Parent->Left ) ) {//case2: new ����Ϊ��ɫ��new��һ���Һ���
				new_node = new_node->Parent;
				parent_is_left_child_flag ? _LeftRotate( new_node ):_RightRotate( new_node );
			}

			new_node->Parent->Color = BLACK;	//case3: new ����Ϊ��ɫ��new������
			new_node->Parent->Parent->Color = RED;
			parent_is_left_child_flag ? _RightRotate( new_node->Parent->Parent ): _LeftRotate( new_node->Parent->Parent );
		}
	}
	m_pRoot->Color = BLACK;
}

//ɾ��
template<typename TKey, typename TValue> 
bool RBTree<TKey, TValue>::Delete( TKey key )
{
	//û���ҵ��ý��
	RBTreeNode *delete_node = Search( key );
	if ( !(delete_node->isValid()) ) //!isValid()
		return false;
	else {
		_Delete( delete_node );
		return true;
	}
}

//������ɾ��
//���������������ɾ����ֻ������Ҫ��¼��ɾ���ڵ���Һ��ӵ���ɫֵ
//delete_node -> z; min_node -> y; temp_node -> x
template<typename TKey, typename TValue> 
void RBTree<TKey, TValue>::_Delete( RBTreeNode *delete_node )
{
	RBTreeNode *temp_node = delete_node;
	int color = delete_node->Color; //��¼��ɾ�����ԭ������ɫ

	if ( delete_node->Left == m_pNil ) { //����Ϊ��
		temp_node = delete_node->Right;
		_RB_Transplant( delete_node, delete_node->Right );
	}
	else if ( delete_node->Right == m_pNil ) {//�Һ���Ϊ��
		temp_node = delete_node->Left;
		_RB_Transplant( delete_node, delete_node->Left );
	}
	else {
		RBTreeNode *min_node = _Minimum( delete_node->Right ); //delete�ĺ�̽��min_node
		temp_node = min_node->Right;
		color = min_node->Color; //����color

		if ( min_node->Parent == delete_node )
			temp_node->Parent = min_node;

		else {
			_RB_Transplant( min_node, min_node->Right );
			min_node->Right = delete_node->Right;
			min_node->Right->Parent = min_node;
		}
		_RB_Transplant( delete_node, min_node );
		min_node->Left = delete_node->Left;
		min_node->Left->Parent = min_node;
		min_node->Color = delete_node->Color;
	}
	if ( color == BLACK )
		_DeleteFixup( temp_node ); //template_node x
}

//ɾ���޸�
template<typename TKey, typename TValue> 
void RBTree<TKey, TValue>::_DeleteFixup( RBTreeNode *node )
{
	while ( node != m_pRoot && node->Color == BLACK ) {
		//��ʶnode�Ƿ����丸��������
		bool node_is_left_child_flag = ( node == node->Parent->Left );
		//node���ֵܽڵ�
		RBTreeNode *brother = ( node_is_left_child_flag ? node->Parent->Right : node->Parent->Left );
		
		//case1 node���ֵܽ��Ϊ��ɫ��һ����ת�������case2
		if ( brother->Color == RED ) { 
			node->Parent->Color = RED;
			brother->Color = BLACK;
			node_is_left_child_flag ? _LeftRotate( node->Parent ):_RightRotate( node->Parent );
			
			//����brother���
			brother = ( node_is_left_child_flag ? node->Parent->Right : node->Parent->Left );
		}

		//case2 node ���ֵܽ��Ϊ��ɫ����brother�������ӽ���Ϊ��ɫ
		if ( brother->Left->Color == BLACK && brother->Right->Color == BLACK ) { 
			brother->Color = RED;
			node = node->Parent; //node����Ϊ��һ��
		}
		
		//case3 node���ֵܽ��Ϊ��ɫ����brother������Ϊ��ɫ���Һ���Ϊ��ɫ
		else {
			if ( ( node_is_left_child_flag ? brother->Right->Color : brother->Left->Color ) == BLACK ) { 
				brother->Color = RED;
				//ע�����ҵĲ�ͬ
				( node_is_left_child_flag ? brother->Left->Color : brother->Right->Color ) = BLACK;
				node_is_left_child_flag ? _RightRotate( brother ):_LeftRotate( brother );
				brother = ( node_is_left_child_flag ? node->Parent->Right:node->Parent->Left ); //����brother��� -> ���case4
			}
			
			//case4 node�����ֵܽ��Ϊ��ɫ����brother �����Һ���Ϊ��ɫ
			brother->Color = /*node->Parent->Color*/RED; 
			node->Parent->Color = BLACK;
			
			( node_is_left_child_flag ? brother->Right->Color : brother->Left->Color ) = BLACK;
			node_is_left_child_flag ? _LeftRotate( node->Parent ):_RightRotate( node->Parent );
			
			node = m_pRoot; //��󸳸�root
		}
	}
	//���ֻ��Ҫ����xΪ�ڽ��Ϳ��ԣ�_root�ĸı��Ѿ����������Զ�������
	node->Color = BLACK;
}

//RB�滻����
template<typename TKey, typename TValue> 
void RBTree<TKey, TValue>::_RB_Transplant( RBTreeNode *unode, RBTreeNode *vnode )
{
	if ( unode->Parent == m_pNil )
		m_pRoot = vnode;
	else if ( unode->Parent->Left == unode )
		unode->Parent->Left = vnode;
	else
		unode->Parent->Right = vnode;
	vnode->Parent = unode->Parent; //!!!��©��
}

//��ʾ
template<typename TKey, typename TValue> 
void RBTree<TKey, TValue>::Display() const
{
	_Display( m_pRoot );
	std::cout << std::endl;
}

template<typename TKey, typename TValue> 
void RBTree<TKey, TValue>::_Display( RBTreeNode *node ) const
{
// 	if ( node->isValid() ) {
// 		cout << node->Value << " ";
// 		if (node->Left->isValid())
// 			_Display(node->Left);
// 		if (node->Right->isValid())
// 			_Display(node->Right);
// 	}
	if ( node->Parent == m_pNil ) 
		cout << "root: " << node->Value << "( " << node->Color << " )" << endl;
	else if ( node->Parent->Left == node )
		cout << "left: " << node->Value << "( " << node->Color << " )" << " " << "parent: " << node->Parent->Value << "( " << node->Parent->Color << " )" << endl;
	else cout << "right: " << node->Value << "( " << node->Color << " )" << " " << "parent: " << node->Parent->Value << "( " << node->Parent->Color << " )" << endl;
	if ( node->Left->isValid() )
		_Display(node->Left);
	if ( node->Right->isValid() )
		_Display(node->Right);
}

//@brief ���
template<typename TKey, typename TValue> 
typename RBTree<TKey, TValue>::RBTreeNode * RBTree<TKey, TValue>::_Successor( RBTreeNode *node )
{
	if(node->m_pRight)
		return _GetMaximum(node);

	_Node *pTemp = node->m_pParent;
	while (pTemp && node == pTemp->m_pRight ) {
		node = pTemp;
		pTemp = pTemp->m_pParent;
	}
	return pTemp;
}

//@brief ǰ��
template<typename TKey, typename TValue> 
typename RBTree<TKey, TValue>::RBTreeNode * RBTree<TKey, TValue>::_Predecessor( RBTreeNode *node )
{
	if (node->m_pLeft)
		return _GetMinimum(node);

	_Node *pTemp = node->m_pParent;
	while (pTemp && node == pTemp->m_pLeft) {
		node = pTemp;
		pTemp = pTemp->m_pParent;
	}
	return pTemp;
}

//@brief Maximum
template<typename TKey, typename TValue> 
typename RBTree<TKey, TValue>::RBTreeNode * RBTree<TKey, TValue>::_Maximum( RBTreeNode *node )
{
	while( node->Right != m_pNil ) {
		node = node->Right;
	}
	return node;
}

//@brief Minimum
template<typename TKey, typename TValue> 
typename RBTree<TKey, TValue>::RBTreeNode * RBTree<TKey, TValue>::_Minimum( RBTreeNode *node )
{
	while( node->Left != m_pNil ) {
		node = node->Left;
	}
	return node;
}

int main()
{
	srand((unsigned)time(NULL));
	RBTree<int, int> rbt;
	int ninsert[] = {12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};
	//int ninsert[] = {3,7,12,10,14,15,16,17,21,19,20,23,26,41,30,28,38,35,39,47};
	int n = sizeof(ninsert)/sizeof(ninsert[0]);

	//�����ֵ����һ�ö��������
	for ( int i = 0; i < n; ++i )
	{
		//int v = rand() % 100;
		rbt.Insert( ninsert[i], ninsert[i] );
		//rbt.Insert( i, i );
	}
	rbt.Display();
	
// 	for ( int i = 0; i < n; i ++)
// 		rbt.Delete( ninsert[i] );

// 	ɾ�����е�С����
	for ( int i = 1; i < n; ++i )
	{
		if ( i % 2 == 1 /*&& i < 50*/ )
		{
			if ( rbt.Delete( i ) )
			{
				cout << "Deleted [" << i << "]" << endl;
			}
		}
	}
	rbt.Display();
// 		//ɾ�����еĴ�ż��
// 		for ( int i = 0; i < 100; ++i )
// 		{
// 			if ( i % 2 == 0 && i > 50 )
// 			{
// 				if ( rbt.Delete( i ) )
// 				{
// 					cout << "Deleted [" << i << "]" << endl;
// 				}
// 			}
// 		}
// 		rbt.Display();

	return 0;
}