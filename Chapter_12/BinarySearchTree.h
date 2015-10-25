#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_

class BinarySearchTree 
{
private:
	struct _Node {
		int		m_nValue;
		_Node	*m_pParent;
		_Node	*m_pLeft;
		_Node	*m_pRight;
	};

public:
	BinarySearchTree(_Node *pRoot = NULL):m_pRoot(pRoot){}

	~BinarySearchTree();

	//@brief ����Ԫ��
	//@return �Ƿ����ɹ�
	bool Insert(const int new_value);

	//�ݹ�
	_Node * Insert_Recur(_Node *&node, const int new_value);

	//@brief ɾ��Ԫ��
	//@return �Ƿ�ɾ���ɹ�
	bool Delete(const int delete_value);

	//@brief ����Ԫ��
	//@return �Ƿ���ҳɹ�
	bool Search(const int search_value) const;

	//@brief ʹ��dot������ǰ���������
	void Display() const;
	
	//@brief ���ı���
	void Inorder() const {Inorder_Tree_Walk(m_pRoot);}
	void Preorder() const {Preorder_Tree_Walk(m_pRoot);}
	void Postorder() const {Postorder_Tree_Walk(m_pRoot);}
	

private:
	//@brief ������ɾ������
	void _DeleteNode(_Node *delete_node);
	void _Delete_Transplant(_Node *unode, _Node *vnode);

	//@brief �õ���nodeΪ���ڵ�������е����ؼ��ֽڵ�
	_Node * _GetMaximum(_Node *node) const;

	//@brief �õ���nodeΪ���ڵ�������е���С�ؼ��ֽڵ�
	_Node * _GetMinimum(_Node *node) const;

	//@brief �õ�һ��ͬʱ�������������Ľڵ�node��ǰ��
	_Node * _GetPredecessor(_Node *node) const;

	//@brief �õ�һ��ͬʱ�������������Ľڵ�node�ĺ��
	_Node * _GetSuccessor(_Node *node) const;

	//@brief �����Ĳ��Ҳ���
	//�ǵݹ����
	_Node * _Search(_Node *node, const int search_value) const;

	//@brief ��ʾһ�ö���������
	void _Display(/*iostream &ss, */_Node *node) const;

	//@brief �ݹ��ͷŽڵ�
	void _RecursiveReleaseNode(_Node *node);

	void ShowGraphvizViaDot(const string &dot) const;

	//@brief ���ı���
	void Inorder_Tree_Walk(_Node *node) const;
	void Preorder_Tree_Walk(_Node *node) const;
	void Postorder_Tree_Walk(_Node *node) const;

private:
	_Node	*m_pRoot;
};

#endif//_BINARY_SEARCH_TREE_