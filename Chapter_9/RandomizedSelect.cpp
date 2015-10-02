#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

//��������֮��������
int Random(int m, int n)
{
	srand((unsigned)time(NULL));
	int nRet = m + rand()%(n - m + 1);
	return nRet;
}

void Swap(int &m , int &n)
{
	int t = m;
	m = n;
	n = t;
}

//�ҵ��ʺϵķ����е�
int RandomPatition(int arr[], int p, int r)
{
	int nRand = Random(p, r);
	Swap(arr[r], arr[nRand]);

	int nTemp = arr[r];

	//���������ڱ�i,j�����������
	int i = p - 1;
	int j = p;
	while (j < r) {
		if (arr[j] <= nTemp) {
			Swap(arr[i+1], arr[j]);
			i ++;
		}
		j ++;
	}
	Swap(arr[i+1], arr[r]);
	return i+1;
}

//Ѱ��arr[p,r]�������kС����
int RandomizedSelectMin(int arr[], int nLeft, int nRight, int nMin)
{
	assert(nLeft <= nRight);
	assert(nMin <= (nRight-nLeft+1)); //nMin start from 1,arr[] start from 0;

	if (nLeft == nRight)
		return arr[nLeft];
	
	int nMid = RandomPatition(arr, nLeft, nRight);
	
	int k = nMid - nLeft + 1;
	if (k == nMin)
		return arr[nMid];

	else if (k > nMin)
		return RandomizedSelectMin(arr, nLeft, nMid-1, nMin);
	else
		return RandomizedSelectMin(arr, nMid+1, nRight, nMin-k);
}

//�ǵݹ鷽��
int RandomizedSelect_NRecur(int arr[], int nLeft, int nRight, int nMin)
{
	assert(nLeft <= nRight);
	assert(nMin <= (nRight-nLeft+1)); //nMin start from 1,arr[] start from 0;
	
	int nMid, k;
	while(true) {
		if (nLeft == nRight)
			return arr[nLeft];

		nMid = RandomPatition(arr, nLeft, nRight);

		k = nMid - nLeft + 1;
		if (k == nMin)
			return arr[nMid];
		else if (k > nMin)
			nRight = nMid - 1;
		else {
			nLeft = nMid + 1;
			nMin = nMin - k;
		}
	}
}

int main()
{
	int arr[] = {5,7,2,6,3};
	cout << RandomizedSelect_NRecur(arr, 0, 4, 1);
	//cout << Random(0,0) << endl;
	return 0;
}