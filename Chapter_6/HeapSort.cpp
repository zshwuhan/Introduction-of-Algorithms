#include <iostream>

using namespace std;


//#include "HeapSort.h"

#define PARENT(x) ((x-1)/2)	//�� x ���ڵ���±�
#define LEFT(x) ((x)*2+1)	//�� x ���ӵ��±�
#define RIGHT(x) ((x)*2+2)	//�� x �Һ��ӵ��±�

void MaxHeapify(int arr[], int heap_size, int index);		//ά�����ѵ�����
void MaxHeapify_Recur(int arr[], int heap_size, int index); //�ݹ�
void BuildMaxHeap(int arr[], int heap_size);					//��һ������������й���һ������
void HeapSort(int arr[], int length);							//������
void Swap(int &a, int &b);

void MaxHeapify(int arr[], int heap_size, int index)
{
	if (index < 0 && index >= heap_size)
		return;
	
	bool isHeapify = true; //��ʶ�����Ƿ�����
	while (isHeapify && index < heap_size) {
		int left = LEFT(index);
		int right = RIGHT(index);
		int largest;

		if (left < heap_size && arr[left] > arr[index]) 
			largest = left;
		else 
			largest = index;

		if (right < heap_size && arr[right] > arr[largest])
			largest = right;

		if (largest != index) {
			Swap(arr[index], arr[largest]);
			index = largest;
		}
		else
			isHeapify = false;
	}
}

void MaxHeapify_Recur(int arr[], int heap_size, int index)
{
	if (index <=0 && index >= heap_size)
		return;

	int left = LEFT(index);
	int right = RIGHT(index);
	int largest;

	if (left < heap_size && arr[left] > arr[index])
		largest = left;
	else 
		largest = index;

	if (right < heap_size && arr[right] > arr[largest])
		largest = right;

	if (largest != index) {
		Swap(arr[index], arr[largest]);
		MaxHeapify_Recur(arr, heap_size, largest);
	}
}

void BuildMaxHeap(int arr[], int heap_size)
{
	if (heap_size == 0)
		return;
	
	for (int i = (heap_size-1)/2; i >= 0; i--)
		MaxHeapify(arr, heap_size, i);
}

void HeapSort(int arr[], int length)
{
	if (length == 0)
		return;

	int heap_size = length;
	BuildMaxHeap(arr, heap_size);
	for (int i = length-1; i >= 1; i --) {
		Swap(arr[0], arr[i]);
		heap_size --;
		MaxHeapify(arr, heap_size, 0);
	}
}

void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

// int main()
// {
// 	int arr[10] = {10,14,16,8,7,9,3,2,4,1};
// 	HeapSort(arr, 10);
// 	for (int i = 0; i < 10; i ++)
// 		cout << arr[i] << " ";
// 	return 0;
// }