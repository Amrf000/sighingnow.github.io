//file: ����ģ��
#include <iostream>
#include <cstring>
using namespace std;

void swap(int *a, int *b)
{
	int c;
	c = *a, *a = *b, *b = c;
}

void insertSort(int *num, int len) //��������
{
	for(int i = 1; i < len; ++i)
	{
		int tmp = num[i], j = i - 1;
		while(j >= 0 && tmp < num[j])
		{
			num[j+1] = num[j];
			--j;
		}
		num[j+1] = tmp;
	}
}

void bubbleSort(int *num, int len) //ð������
{
	for(int i = 0; i < len; ++i)
	{
		for(int j = 0; j < len - i; ++j)
		{
			if(num[j] > num[j+1])
			{
				swap(num+j, num+j+1);
			}
		}
	}
}

void selectSort(int *num, int len) //ѡ������
{
	for(int i = 0; i < len - 1; ++i)
	{
		for(int j = i + 1; j < len; ++j)
		{
			if(num[i] > num[j])
			{
				swap(num+i, num+j);
			}
		}
	}
}

void shellSort(int *num, int len) //ϣ������
{
	int step = len >> 1;
	while(step >= 1)
	{
		for(int i = step; i < len; ++i)
		{
			int tmp = num[i], j = i - step;
			while(j >= 0 && tmp < num[j])
			{
				num[j+1] = num[j];
				j -= step;
			}
			num[j+step] = tmp;
		}
		step >>= 1;
	}
}

void heapSort(int *num, int len) //������
{
	void heapBuild(int *, int, int);
	for(int i = (len - 1) >> 1; i >= 0; --i)
		heapBuild(num, i, len-1);
	for(int i = 0; i < len - 1; ++i)
	{
		swap(num, num+(len-1-i));
		heapBuild(num, 0, len-2-i);
	}
}
void heapBuild(int *num, int i, int len)
{
	int j = 2 * i + 1;
	while(j <= len)
	{
		if(j < len && num[j] < num[j+1])
			++j;
		if(num[i] >= num[j])
			break;
		swap(num+i, num+j);
		i = j;
		j = 2 * i + 1;
	}
}

void quickSort(int *num, int left, int right)//��������
{
    if(left >= right)
        return;
    srand(time(0)); //use current time as seed for random generator , #include <cstdlib>
    int i = left, j = right;
    int index = rand() % (right-left + 1) + left; // ʹ���������ֹ�������� #include<ctime>
    int key = num[index];
    while(true) {
        while(key < num[j])
            --j;
        while(key > num[i])
            ++i;
        if(i < j)
            swap(num[i], num[j]);
        else
            break;
    }
    swap(num[left], num[j]);
    quickSort(num, left, j);
    quickSort(num, j+1, right);
}

/*���λ���Ȼ������� LsdRadixSort�������Ϊ����Ϊ��MsdRadixSort��
* int *array: ����������,�� index=1 ��ʼ
* int len: ���������鳤��
*/
void lsdRadixSort(int *array, int len)    //�˴���С��������, �ҽ���������
{
	int tmpArray[10][len+1];         //index=0 ������¼�������˴�һ���Է��䣬�Ϸѿռ䣬����ͨ����̬�����Ż�
	int i, j ;
	int maxlen, max;		//max:��������maxlen: ��������λ��
	max = array[0];
	for(i = 1; i < len; ++i)
		max = max > array[i] ? max : array[i];
	maxlen = 1;
	while(max /= 10)
		++maxlen;
	for(i = 1; i <= maxlen; ++i)
	{
		memset(tmpArray, 0, sizeof(tmpArray));
		for(j = 0; j < len; ++j)
		{
			int tmp = *(array+j), k = i - 1;
			while(k--)                  //�õ�array[j]�ĵ� i λ�����ӵ�λ����,����tmp��
				tmp /= 10;
			tmp %= 10;
			tmpArray[tmp][++tmpArray[tmp][0]] = *(array+j);
		}
		int p, q, k = 0;
		for(p = 0; p < 10; ++p)
		{
			for(q = 1; q <= tmpArray[p][0]; ++q)
				array[k++] = tmpArray[p][q];
		}
	}
}

void mergeSort(int *num, int first, int last)//�鲢����
{
	void mergeNum(int *, int, int);
	int mid = (first + last) / 2;
	if(first < mid)
		mergeSort(num, first, mid);
	if(mid + 1 < last)		//ע��˴��� mid + 1
		mergeSort(num, mid, last);	//ע��˴���mid
	mergeNum(num, first, last);
}
void mergeNum(int *num, int first, int last)
{
	int *tmp = new int [last-first+1];
	int mid = (first + last) / 2;
	int indexa = first, indexb = mid, index = 0;
	while(indexa < mid && indexb < last)
	{
		if(num[indexa] < num[indexb])
			tmp[index++] = num[indexa++];
		else
			tmp[index++] = num[indexb++];
	}
	while(indexa < mid)
		tmp[index++] = num[indexa++];
	while(indexb < last)
		tmp[index++] = num[indexb++];
	for(int i = 0; i < index; ++i)
		num[first+i] = tmp[i];
	delete []tmp;
}//�˴���tmp�������ͨ�����ν���Ա����ζ�̬���䣬ʵ���Ż�

void coutSort(){	}//���������ԣ�

int main()
{
	int num[10] = {3, 1, 5, 7, 9, 2, 4, 6, 10, 8};
	mergeSort(num, 0, 10);
	for(int i = 0; i < 10; ++i)
		cout << num[i] << " ";
	return 0;
}
