#include <iostream>
#include <cstdlib>
using namespace std;

#define ARRAYSIZE 10 // 배열 크기를 정의합니다.

int array1[ARRAYSIZE] = { 3,5,6,1,7,2,9,4,10,8 };
int array2[ARRAYSIZE] = { 3,5,6,1,7,2,9,4,10,8 };

// 배열을 출력하는 함수입니다.
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

// 배열의 범위를 정해서 순서대로 출력하는 함수입니다.
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

// 두 배열 요소의 값을 교환하는 함수입니다.
void swapElements(int* index1, int* index2)
{
	int temp = *index1;
	*index1  = *index2;
	*index2  =  temp;
}

// 배열을 분할하는 함수입니다. 
// 퀵 정렬에서 피벗을 기준으로 왼쪽은 작은 값들, 오른쪽은 큰 값들로 분할합니다.
// 피벗의 최종 위치를 반환합니다.
int partitionArray(int array[], int left, int right, const string& prefix)
{
	int low   = left + 1;    // 피벗 다음 인덱스를 가리킵니다.
	int high  = right;       // 배열의 마지막 요소를 가리킵니다.
	int pivot = array[left]; // 배열의 첫 번째 요소를 피벗으로 설정합니다.

	cout << prefix << "|  현재 배열:  ";
	printArray(array, ARRAYSIZE);
	cout << endl;
	cout << prefix << "|  피벗 " << pivot << "을(를) index "
		<< left << " ~ " << right << "사이로 분할" << endl;
	cout << prefix << "|  분할할배열: ";
	cout << "(" << pivot << ")";                 // 피벗 출력
	printArrayRange(array, low, high);           // 오른쪽 부분 배열 출력
	cout << endl;

	int lastSwapLow = -1, lastSwapHigh = -1;     // 교환된 요소 위치 저장

	// low가 high보다 작거나 같을 때까지 반복합니다.
	while (low <= high)
	{
		while (low <= right && array[high] > pivot)// 피벗보다 큰 값을 찾습니다.
			high -= 1;

		while (low <= high && array[low] <= pivot) // 피벗보다 작은 값을 찾습니다.
			low += 1;

		if (low <= high)                           // low와 high의 값을 교환합니다.
		{
			swapElements(&array[low], &array[high]);

			lastSwapLow  = low;  // 교환된 위치 저장
			lastSwapHigh = high;

			// 교환된 위치에 화살표 추가
			cout << prefix << "|                  ";
			for (int i = left + 1; i <= right; i++) {
				if (i == lastSwapLow || i == lastSwapHigh)
					cout << "↓  ";
				else
					cout << "   ";
			}

			cout << array[low] << " ↔ " << array[high];
			cout << endl;

			cout << prefix <<  "|  교환후배열: ";
			cout << "(" << pivot << ")";                // 피벗 출력
			printArrayRange(array, left + 1, right);    // 오른쪽 부분 배열 출력
			cout << endl;

			

			low += 1;
			high -= 1;
		}
	}
	cout << prefix << "└─ Pivot 교환: " << array[left] << " ↔ " << array[high] << endl;
	swapElements(&array[left], &array[high]);      // 피벗과 high의 값을 교환하여 피벗을 적절한 위치에 놓습니다.

	cout << prefix << "분할된배열: ";
	if (left < high)
		printArrayRange(array, left, high - 1); // 왼쪽 부분 배열 출력
	cout << "(" << pivot << ")";                // 피벗 출력
	if (high < right)
		printArrayRange(array, high + 1, right);    // 오른쪽 부분 배열 출력
	cout << endl << endl;
	
	return high;
}

// 퀵 정렬 함수입니다. 
// 배열을 분할한 후 재귀적으로 왼쪽과 오른쪽 부분 배열을 정렬합니다.
void quickSort(int array[], int left, int right, const string& prefix = "")
{
	if (left < right)
	{
		cout << prefix << (prefix.empty() ? "" : "|  ")
			<< "├─ quickSort 호출 : left=" << left << ", right=" << right << endl;
		int index = partitionArray(array, left, right, prefix + "|  "); // 배열을 분할하고 피벗의 최종 위치를 받습니다.

		cout << prefix << "|  ├─ 왼쪽 부분 정렬 호출: left=" << left << ", right=" << index - 1 << endl;
		quickSort(array, left, index - 1, prefix + "|  |  ");             // 피벗의 왼쪽 부분 배열을 정렬합니다.

		cout << prefix << "│  └─ 오른쪽 부분 정렬 호출: left=" << index + 1 << ", right=" << right << endl;
		quickSort(array, index + 1, right, prefix + "|    ");             // 피벗의 오른쪽 부분 배열을 정렬합니다.
	}
	else if (left == right)
	{
		cout << prefix << "└─ 하나의 요소만 남음: index=" << left << endl;
	}
		
}

// 삽입 정렬 함수입니다. 
// 배열의 각 요소를 이미 정렬된 부분에 삽입하여 정렬을 진행합니다.
void insertSort(int array[])
{
	int temp, sortedIndex;
	// 두 번째 요소부터 마지막 요소까지 순회합니다.
	for (int currentIndex = 1; currentIndex < ARRAYSIZE; currentIndex++)
	{
		temp = array[currentIndex];                       // 현재 정렬할 요소를 임시로 저장합니다.

		cout << "<삽입할 값 " << temp << "을(를) 정렬된 부분 [0-" << currentIndex - 1
			<< "] index에 삽입>" << endl;

		for (sortedIndex = currentIndex - 1; sortedIndex >= 0
			&& array[sortedIndex] > temp; sortedIndex--) // 정렬된 부분을 순회하며 삽입 위치를 찾습니다.
		{
			array[sortedIndex + 1] = array[sortedIndex];  // 요소를 오른쪽으로 이동합니다.

			cout << "요소 " << array[sortedIndex] << "을(를) index "
				<< sortedIndex + 1 << "으로 이동함" << endl;
		}

		array[sortedIndex + 1] = temp;                    // 적절한 위치에 현재 요소를 삽입합니다.
		cout << "값 " << temp << "을(를) index "
			<< sortedIndex + 1 << "에 삽입함"
			<< endl;
		cout << "현재 배열: ";
		printArray(array, ARRAYSIZE);                     // 배열의 각 삽입 단계가 완료 될 때마다 출력합니다.
		cout << endl;
		cout << "----------" << endl;
	}
}

int main()
{
	cout << "배열 크기: " << ARRAYSIZE << endl << endl;

	cout << "----------------퀵정렬------------------" << endl;
	quickSort(array1, 0, ARRAYSIZE - 1);
	cout << "최종 배열: ";
	printArray(array1, ARRAYSIZE);
	cout << endl;
	cout << "----------------------------------------" << endl;

	cout << endl;
	cout << "---------------삽입정렬-----------------" << endl;
	cout << "시작 배열: ";
	printArray(array2, ARRAYSIZE);
	cout << endl;
	insertSort(array2);
	cout << "----------------------------------------" << endl;
}