#include <iostream>
using namespace std;

/***********����ʱ������Сֵ************/
int Minimun(int arr[], int n)
{
	int nMin = arr[0];
	for(int i = 1; i < n; i++)
		//min
		if(nMin > arr[i])
			nMin = arr[i];
		//max
// 		if (nMax < arr[i])
// 			nMax = arr[i];
	return nMin;
}

/***********ͨ��3n/2�αȽ�����Сֵ�����ֵ**********/
void MinAndMax(int arr[], int n, int &nMin, int &nMax)
{
	int i;
	//���n������
	if(n % 2 == 1)
	{
		//�����ֵ����Сֵ����Ϊ��һ��Ԫ��
		nMin = arr[1];
		nMax = arr[1];
		i = 2;
	}
	//���n��ż��
	else
	{
		//��ǰ����Ԫ����һ�αȽϣ��Ծ������ֵ����Сֵ�ĳ�ֵ
		nMin = min(arr[1], arr[2]);
		nMax = arr[1] + arr[2] - nMin;
		i = 3;
	}
	//�ɶԵش������µ�Ԫ��
	for(; i < n; i=i+2)
	{
		//��һ������Ԫ�ػ���Ƚ�
		int a = min(arr[i], arr[i+1]);
		int b = arr[i] + arr[i+1] - a;
		//�ѽ�С���뵱ǰ��Сֵ�Ƚ�
		if(a < nMin)
			nMin = a;
		//�ѽϴ����뵱ǰ���ֵ�Ƚ�
		if(b > nMax)
			nMax = b;
	}
}
