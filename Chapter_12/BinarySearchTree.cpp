#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

#include "BinarySearchTree.h"

BinarySearchTree::~BinarySearchTree()
{
	_RecursiveReleaseNode(m_pRoot);
}

//@brief ����Ԫ��
//@return �Ƿ����ɹ�
bool BinarySearchTree::Insert(const int new_value)
{
	//�ǵݹ�
	if (Search(new_value))
		return false;

	_Node *pTemp = NULL;
	_Node *pCurrent = m_pRoot;
	while ( pCurrent ) {
		pTemp = pCurrent;
		if ( new_value < pCurrent->m_nValue )
			pCurrent = pCurrent->m_pLeft;
		else
			pCurrent = pCurrent->m_pRight;

	}
	_Node *pInsert = new _Node();
	pInsert->m_nValue = new_value;
	pInsert->m_pParent = pTemp;

	if ( !pTemp ) //����
		m_pRoot = pInsert;
	else if ( new_value < pTemp->m_nValue ) 
		pTemp->m_pLeft = pInsert;
	else
		pTemp->m_pRight = pInsert;
	return true;


// 	//��Ԫ���Ѿ�����
// 	if (Search(new_value))
// 		return false;
// 	
// 	//�����������1���ڵ�
// 	if (!m_pRoot) {
// 		m_pRoot = new _Node();
// 		m_pRoot->m_nValue = new_value;
// 		return true;
// 	}
// 
// 	//�ǵ�һ���ڵ�
// 	_Node *current_node = m_pRoot;
// 	while( current_node ) {
// 		_Node *&next_node_pointer = (new_value < current_node->m_nValue ? current_node->m_pLeft:current_node->m_pRight);
// 		if ( next_node_pointer )
// 			current_node = next_node_pointer;
// 		else {
// 			next_node_pointer = new _Node();
// 			next_node_pointer->m_nValue = new_value;
// 			next_node_pointer->m_pParent = current_node;
// 			break;
// 		}
// 	}
// 	return true;
}

//�ݹ�
BinarySearchTree::_Node * BinarySearchTree::Insert_Recur(_Node *&node, const int new_value)
{
	if ( node == NULL ) {
		_Node *pInsert = new _Node();
		pInsert->m_nValue = new_value;
		node = pInsert;
	}
	else if ( new_value < node->m_nValue )
		node->m_pLeft = Insert_Recur( node->m_pLeft, new_value );
	else
		node->m_pRight = Insert_Recur( node->m_pRight, new_value );
	return node;
}

//@brief ɾ��Ԫ��
//@return �Ƿ�ɾ���ɹ�
bool BinarySearchTree::Delete(const int delete_value)
{
	_Node *delete_node = _Search(m_pRoot, delete_value);
	
	//δ�ҵ��ýڵ�
	if (!delete_node)
		return false;
	else {
		_DeleteNode(delete_node);
		return true;
	}
}

//@brief ����Ԫ��
//@return �Ƿ���ҳɹ�
bool BinarySearchTree::Search(const int search_value) const
{
	return _Search(m_pRoot, search_value) != NULL;
}

//@brief ʹ��dot������ǰ���������
void BinarySearchTree::Display() const
{
	_Display(m_pRoot);
}

//@brief ���ı���
//����
void BinarySearchTree::Inorder_Tree_Walk(_Node *node) const
{
	if (node) {
		Inorder_Tree_Walk(node->m_pLeft);
		cout << node->m_nValue << " ";
		Inorder_Tree_Walk(node->m_pRight);
	}
}

//ǰ��
void BinarySearchTree::Preorder_Tree_Walk(_Node *node) const
{
	if (node) {
		cout << node->m_nValue << " ";
		Preorder_Tree_Walk(node->m_pLeft);
		Preorder_Tree_Walk(node->m_pRight);
	}
}

//����
void BinarySearchTree::Postorder_Tree_Walk(_Node *node) const
{
	if (node) {
		Postorder_Tree_Walk(node->m_pLeft);
		Postorder_Tree_Walk(node->m_pRight);
		cout << node->m_nValue << " ";
	}
}

//@brief ������ɾ������
void BinarySearchTree::_DeleteNode(_Node *delete_node)
{
	if (delete_node->m_pLeft == NULL) //�����ɾ������������Ϊ��
		_Delete_Transplant(delete_node, delete_node->m_pRight);
	else if (delete_node->m_pRight == NULL) //�����ɾ����������Ϊ��
		_Delete_Transplant(delete_node, delete_node->m_pLeft);
	else {  //��ɾ�����ӵ�������������
		_Node *min_node = _GetMinimum(delete_node->m_pRight); //�õ����
		if (min_node->m_pParent != delete_node) {
			_Delete_Transplant(min_node, min_node->m_pRight);
			min_node->m_pRight = delete_node->m_pRight; //������ָ��ָ��
			min_node->m_pRight->m_pParent = min_node;
		}
		_Delete_Transplant(delete_node, min_node);
		min_node->m_pLeft = delete_node->m_pLeft;
		min_node->m_pLeft->m_pParent = min_node;
	}
}

//��ת�����ĸ�������
//using vnode to replace unode
void BinarySearchTree::_Delete_Transplant(_Node *unode, _Node *vnode)
{
	if (unode->m_pParent == NULL)
		m_pRoot = vnode;
	else if (unode == unode->m_pParent->m_pLeft)
		unode->m_pParent->m_pLeft = vnode;
	else
		unode->m_pParent->m_pRight = vnode;
	if (vnode)
		vnode->m_pParent = unode->m_pParent;
}

//@brief �õ���nodeΪ���ڵ�������е����ؼ��ֽڵ�
BinarySearchTree::_Node * BinarySearchTree::_GetMaximum(_Node *node) const
{
	while(node->m_pRight) {
		node = node->m_pRight;
	}
	return node;
}

//@brief �õ���nodeΪ���ڵ�������е���С�ؼ��ֽڵ�
BinarySearchTree::_Node * BinarySearchTree::_GetMinimum(_Node *node) const
{
	while(node->m_pLeft) {
		node = node->m_pLeft;
	}
	return node;
}

//@brief �õ�һ��ͬʱ�������������Ľڵ�node��ǰ��
BinarySearchTree::_Node * BinarySearchTree::_GetPredecessor(_Node *node) const
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

//@brief �õ�һ��ͬʱ�������������Ľڵ�node�ĺ��
BinarySearchTree::_Node * BinarySearchTree::_GetSuccessor(_Node *node) const
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

//@brief �����Ĳ��Ҳ���
//�ǵݹ����
BinarySearchTree::_Node * BinarySearchTree::_Search(_Node *node, const int search_value) const
{
	//�ݹ�
// 	if (node == NULL || search_value = node->m_nValue)
// 		return node;
// 	if (search_value < node->m_nValue)
// 		return _Search(node->m_pLeft);
// 	else
// 		return _Search(node->m_pRight);

	//�ǵݹ�
	while(node && search_value != node->m_nValue) {
		if (search_value < node->m_nValue)
			node = node->m_pLeft;
		else
			node = node->m_pRight;
	}
	return node;
}

//@brief ��ʾһ�ö���������
void BinarySearchTree::_Display(/*iostream &ss, */_Node *node) const
{
	if ( node )
	{
		cout << node->m_nValue << " ";

		if ( node->m_pLeft )
		{
			_Display( node->m_pLeft );
		}

		if ( node->m_pRight )
		{
			_Display( node->m_pRight );
		}
	}
}

//@brief �ݹ��ͷŽڵ�
void BinarySearchTree::_RecursiveReleaseNode(_Node *node)
{
	if (node) {
		_RecursiveReleaseNode(node->m_pLeft);
		_RecursiveReleaseNode(node->m_pRight);
		delete node;
	}
}


int main()
{
	srand((unsigned)time(NULL));
	BinarySearchTree bst;

	//�����ֵ����һ�ö��������
	for (int i= 0; i < 10; i ++) {
		bst.Insert( rand() % 100 ); 
	}

	bst.Display();
	cout << endl;

	//�������
// 	bst.Inorder();
// 	cout << endl;


	//ɾ�����е�����ֵ���
	for ( int i = 1; i < 100; i += 2 )
	{
		if( bst.Delete( i ) )
		{
			cout << "### Deleted [" << i << "] ###" << endl;
		}
	}
	//��֤ɾ���Ľ�����
// 	bst.Delete(2);
// 	bst.Delete(1);
// 	bst.Display();
// 	cout << endl;


	//����100���ڵ���������ڶ���������У�����ʾ
	cout << endl;
	for ( int i = 0; i < 10; i += 1 )
	{
		if ( bst.Search( i ) )
		{
			cout << "����[" << i << "]Ԫ�أ�\t�ɹ�" << endl;
		}
	}
	
	cout << endl;
	//�������
	bst.Inorder();
	return 0;
}