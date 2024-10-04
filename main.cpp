#include <iostream>
#include <cstdlib>
using namespace std;

#define ARRAYSIZE 10 // �迭 ũ�⸦ �����մϴ�.

int array1[ARRAYSIZE] = { 3,5,6,1,7,2,9,4,10,8 };
int array2[ARRAYSIZE] = { 3,5,6,1,7,2,9,4,10,8 };

// �迭�� ����ϴ� �Լ��Դϴ�.
void printArray(int array[], int size)
{
	int arraySize = sizeof(array) / sizeof(*array);
	if(arraySize > 1)
		cout << "[";
	
	for (int index = 0; index < size; index++)
	{
		if (index == size - 1)
			cout << array[index] << "]";

		else
			cout << array[index] << ", ";
	}
	
}

// �迭�� ������ ���ؼ� ������� ����ϴ� �Լ��Դϴ�.
void printArrayRange(int array[], int startIndex, int endIndex)
{
	int arraySize = sizeof(array) / sizeof(*array);
	if (arraySize > 1)
		cout << "[";
	for (int index = startIndex; index < endIndex + 1; index++)
	{
		if (index == endIndex)
			cout << array[index] << "]";
		
		else
			cout << array[index] << ", ";
	}
}

// �� �迭 ����� ���� ��ȯ�ϴ� �Լ��Դϴ�.
void swapElements(int* index1, int* index2)
{
	int temp = *index1;
	*index1  = *index2;
	*index2  =  temp;
}

// �迭�� �����ϴ� �Լ��Դϴ�. 
// �� ���Ŀ��� �ǹ��� �������� ������ ���� ����, �������� ū ����� �����մϴ�.
// �ǹ��� ���� ��ġ�� ��ȯ�մϴ�.
int partitionArray(int array[], int left, int right, const string& prefix)
{
	int low   = left + 1;    // �ǹ� ���� �ε����� ����ŵ�ϴ�.
	int high  = right;       // �迭�� ������ ��Ҹ� ����ŵ�ϴ�.
	int pivot = array[left]; // �迭�� ù ��° ��Ҹ� �ǹ����� �����մϴ�.

	cout << prefix << "|  ���� �迭:  ";
	printArray(array, ARRAYSIZE);
	cout << endl;
	cout << prefix << "|  �ǹ� " << pivot << "��(��) index "
		<< left << " ~ " << right << "���̷� ����" << endl;
	cout << prefix << "|  �����ҹ迭: ";
	cout << "(" << pivot << ")";                 // �ǹ� ���
	printArrayRange(array, low, high);           // ������ �κ� �迭 ���
	cout << endl;

	int lastSwapLow = -1, lastSwapHigh = -1;     // ��ȯ�� ��� ��ġ ����

	// low�� high���� �۰ų� ���� ������ �ݺ��մϴ�.
	while (low <= high)
	{
		while (low <= right && array[high] > pivot)// �ǹ����� ū ���� ã���ϴ�.
			high -= 1;

		while (low <= high && array[low] <= pivot) // �ǹ����� ���� ���� ã���ϴ�.
			low += 1;

		if (low <= high)                           // low�� high�� ���� ��ȯ�մϴ�.
		{
			swapElements(&array[low], &array[high]);

			lastSwapLow  = low;  // ��ȯ�� ��ġ ����
			lastSwapHigh = high;

			// ��ȯ�� ��ġ�� ȭ��ǥ �߰�
			cout << prefix << "|                  ";
			for (int i = left + 1; i <= right; i++) {
				if (i == lastSwapLow || i == lastSwapHigh)
					cout << "��  ";
				else
					cout << "   ";
			}

			cout << array[low] << " �� " << array[high];
			cout << endl;

			cout << prefix <<  "|  ��ȯ�Ĺ迭: ";
			cout << "(" << pivot << ")";                // �ǹ� ���
			printArrayRange(array, left + 1, right);    // ������ �κ� �迭 ���
			cout << endl;

			

			low += 1;
			high -= 1;
		}
	}
	cout << prefix << "���� Pivot ��ȯ: " << array[left] << " �� " << array[high] << endl;
	swapElements(&array[left], &array[high]);      // �ǹ��� high�� ���� ��ȯ�Ͽ� �ǹ��� ������ ��ġ�� �����ϴ�.

	cout << prefix << "���ҵȹ迭: ";
	if (left < high)
		printArrayRange(array, left, high - 1); // ���� �κ� �迭 ���
	cout << "(" << pivot << ")";                // �ǹ� ���
	if (high < right)
		printArrayRange(array, high + 1, right);    // ������ �κ� �迭 ���
	cout << endl << endl;
	
	return high;
}

// �� ���� �Լ��Դϴ�. 
// �迭�� ������ �� ��������� ���ʰ� ������ �κ� �迭�� �����մϴ�.
void quickSort(int array[], int left, int right, const string& prefix = "")
{
	if (left < right)
	{
		cout << prefix << (prefix.empty() ? "" : "|  ")
			<< "���� quickSort ȣ�� : left=" << left << ", right=" << right << endl;
		int index = partitionArray(array, left, right, prefix + "|  "); // �迭�� �����ϰ� �ǹ��� ���� ��ġ�� �޽��ϴ�.

		cout << prefix << "|  ���� ���� �κ� ���� ȣ��: left=" << left << ", right=" << index - 1 << endl;
		quickSort(array, left, index - 1, prefix + "|  |  ");             // �ǹ��� ���� �κ� �迭�� �����մϴ�.

		cout << prefix << "��  ���� ������ �κ� ���� ȣ��: left=" << index + 1 << ", right=" << right << endl;
		quickSort(array, index + 1, right, prefix + "|    ");             // �ǹ��� ������ �κ� �迭�� �����մϴ�.
	}
	else if (left == right)
	{
		cout << prefix << "���� �ϳ��� ��Ҹ� ����: index=" << left << endl;
	}
		
}

// ���� ���� �Լ��Դϴ�. 
// �迭�� �� ��Ҹ� �̹� ���ĵ� �κп� �����Ͽ� ������ �����մϴ�.
void insertSort(int array[])
{
	int temp, sortedIndex;
	// �� ��° ��Һ��� ������ ��ұ��� ��ȸ�մϴ�.
	for (int currentIndex = 1; currentIndex < ARRAYSIZE; currentIndex++)
	{
		temp = array[currentIndex];                       // ���� ������ ��Ҹ� �ӽ÷� �����մϴ�.

		cout << "<������ �� " << temp << "��(��) ���ĵ� �κ� [0-" << currentIndex - 1
			<< "] index�� ����>" << endl;

		for (sortedIndex = currentIndex - 1; sortedIndex >= 0
			&& array[sortedIndex] > temp; sortedIndex--) // ���ĵ� �κ��� ��ȸ�ϸ� ���� ��ġ�� ã���ϴ�.
		{
			array[sortedIndex + 1] = array[sortedIndex];  // ��Ҹ� ���������� �̵��մϴ�.

			cout << "��� " << array[sortedIndex] << "��(��) index "
				<< sortedIndex + 1 << "���� �̵���" << endl;
		}

		array[sortedIndex + 1] = temp;                    // ������ ��ġ�� ���� ��Ҹ� �����մϴ�.
		cout << "�� " << temp << "��(��) index "
			<< sortedIndex + 1 << "�� ������"
			<< endl;
		cout << "���� �迭: ";
		printArray(array, ARRAYSIZE);                     // �迭�� �� ���� �ܰ谡 �Ϸ� �� ������ ����մϴ�.
		cout << endl;
		cout << "----------" << endl;
	}
}

int main()
{
	cout << "�迭 ũ��: " << ARRAYSIZE << endl << endl;

	cout << "----------------������------------------" << endl;
	quickSort(array1, 0, ARRAYSIZE - 1);
	cout << "���� �迭: ";
	printArray(array1, ARRAYSIZE);
	cout << endl;
	cout << "----------------------------------------" << endl;

	cout << endl;
	cout << "---------------��������-----------------" << endl;
	cout << "���� �迭: ";
	printArray(array2, ARRAYSIZE);
	cout << endl;
	insertSort(array2);
	cout << "----------------------------------------" << endl;
}