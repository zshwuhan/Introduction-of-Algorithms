#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
using namespace std;

template<typename T>
class UniversalHashTable {
public:
	UniversalHashTable () {
		p = 101;	//һ���㹻�������
		m = 10;		//�۵ĸ���
		_item.resize(m, NULL);

		for (int i = 0; i < m; i ++) {
			_item[i] = new _Node();
			_item[i]->m_pNext = NULL;
		}

		a = rand() % (p - 1) + 1;
		b = rand() % p;
	}
	
	~UniversalHashTable() {
		for (int i = 0; i < m; i ++) {
			_Node *pT = _item[i]->m_pNext;
			while (pT) {
				_Node *p = pT->m_pNext;
				delete pT;
				pT = p;
			}
		}
	}

	//��ɢ�б��в���һ��Ԫ��
	void Insert(T const &new_value) {
		//ʼ�ղ����ڼ����ͷ��ͷ���֮��ĵ�һ��λ��
		_Node *new_item = new _Node();
		new_item->m_nItem = new_value;
		new_item->m_pNext = NULL;

		int hash_value = _HashFunction(new_value);

		new_item->m_pNext = _item[hash_value]->m_pNext;
		_item[hash_value]->m_pNext = new_item;
	}

	//��ɢ�б���ɾ��һ��Ԫ��
	//@return �Ƿ�ɾ���ɹ���������Ԫ��
	bool Delete(T const &delete_value) {
		int hash_value = _HashFunction(delete_value);
		_Node *root = _item[hash_value];

		while (root->m_pNext) {
			if (root->m_pNext->m_nItem == delete_value) {
				_Node *temp = root->m_pNext;
				root->m_pNext = root->m_pNext->m_pNext;
				delete temp;
				temp = NULL;
				return true;
			}
			else
				root = root->m_pNext;
		}
		return false;
	}

	//��ɢ�б�������һ��Ԫ��
	T * Search(T const &search_value) {
		int hash_value = _HashFunction(search_value);
		_Node *root = _item[hash_value]->m_pNext;

		while(root) {
			if (root->m_nItem == search_value) {
				return &(root->m_nItem);
			}
			else
				root = root->m_pNext;
		}
		return NULL;
	}

	//��ɢ�б�������Ԫ����ʾ���������
	void Display(){
		for (int i = 0; i < m; i ++) {
			_Node *item = _item[i]->m_pNext; //����ͷ���
			cout << "��[" << setw( 3 ) << i << setw( 3 ) << "]";
			while(item) {
				cout << " -> " << item->m_nItem;
				item = item->m_pNext;
			}
			cout << endl;
		}
	}

private:
	struct _Node{
		T		m_nItem;
		_Node	*m_pNext;
	};

	//ȫ��ɢ�к���
	//h(a,b,k) = ((a*k+b) mod p) mod m
	int _HashFunction(T key) {
		return static_cast<int>(a * key + b) % p % m;
	}
	
	//����ɢ��
	int _HashFunctionMul(T key) {
		return static_cast<int> key % m;
	}

	//�˷�ɢ��
	//floor��ʾ��ȡ��
	int _HashFunctionDiv(T key) {
		return static_cast<int> floor(m * (a * key % 1))
	}

	int p, m, a, b;
	vector<_Node *> _item; //�õ�������Ϊɢ�в�
};

int main() 
{
	UniversalHashTable<int> table;
	cout << "��UniversalHashtable���������[0,50):" << endl;
	for (int i = 0; i < 50; i ++) {
		table.Insert(i);
	}
	table.Display();

	cout << "��ʼɾ������[0,5):" << endl;
	for (int i = 0; i < 5; i ++) {
		table.Delete(i);
	}
	table.Display();
	for (int i = 0; i < 10; i ++) {
		int *finded = table.Search(i);
		cout << "��ʼ�����ڵ�[ " << i << " ]:";
		if (finded) 
			cout << *finded << endl;
		else
			cout << "δ�ҵ�" << endl;
	} 
	return 0;
}
