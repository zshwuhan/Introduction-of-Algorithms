#ifndef __RED_BLACK_TREE_
#define __RED_BLACK_TREE_

//ʹ��ģ����
template< typename TKey, typename TValue >
class RBTree 
{
/************************************************************************/
/* ������������                                                               
/************************************************************************/
public:
	//������ɫ-ö��
	enum RBTreeNodeColor {
		RED,	//��ɫ
		BLACK	//��ɫ
	};

	//��������
	struct RBTreeNode {
		TKey				Key;
		TValue				Value;
		RBTreeNodeColor		Color;
		RBTreeNode			*Parent;
		RBTreeNode			*Left;
		RBTreeNode			*Right;
		
		//@brief ������е��ڱ����T.nilʵ�����ǿս�㣬Ϊ��Ч���
		//@return ����ĳ������Ƿ�Ϊ��Ч���
		//@retval = true ��nil���
		//@retval = false nil���
		inline bool isValid() const {
			return ( this != m_pNil );
		}
	};

/************************************************************************/
/* �������������                                                          
/************************************************************************/
public:
	RBTree();	//���캯��
	~RBTree();	//��������

	//@brief ����һ�����
	bool Insert( TKey key, TValue value );

	//@brief ɾ��һ�����
	bool Delete( TKey key );

	//@brief ����һ�����
	RBTreeNode * Search( TValue const &value );

	//@brief �жϺ�����Ƿ�Ϊ��
	bool Empty();

	//@brief ��ʾ��ǰ�����
	void Display() const;

/************************************************************************/
/* �����˽������                                                          
/************************************************************************/
private:
	//@brief �ݹ�ɾ�����н��
	void _RecursiveReleaseNode ( RBTreeNode *node );
	
	//@brief ��ʾ
	void _Display( RBTreeNode *node ) const;
	
	//@brief �����Ĳ��뺯��
	void _InsertRBTree( RBTreeNode *node ); 

	//@brief �Բ���������޸�
	void _InsertFixup( RBTreeNode *node );

	//@brief ����
	void _LeftRotate( RBTreeNode *node );

	//@brief ����
	void _RightRotate( RBTreeNode *node );

	//@brief ������ɾ������
	void _Delete( RBTreeNode *node );

	//@brief ר����������滻����
	void _RB_Transplant( RBTreeNode *unode, RBTreeNode *vnode );
	
	//@brief ��ɾ���������޸�
	void _DeleteFixup( RBTreeNode *node );

	//@brief ���
	RBTreeNode * _Successor( RBTreeNode *node );

	//@brief ǰ��
	RBTreeNode * _Predecessor( RBTreeNode *node );

	//@brief Maximum
	RBTreeNode * _Maximum( RBTreeNode *node );
	
	//@brief Minimum
	RBTreeNode * _Minimum( RBTreeNode *node );


private:
	//����������ݳ�Ա
	RBTreeNode	*m_pRoot;	//�����
	static RBTreeNode	*m_pNil;	//�ڱ��ս��
};
#endif//__RED_BLACK_TREE_