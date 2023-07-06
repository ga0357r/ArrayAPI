#pragma once
#include <iostream>
#include <algorithm>
#include <cstdarg>
#include <random>

using namespace std;

#pragma region Definition

template<class T>
class Array
{
#pragma region Private Variables
private:
	T* pStorage;
	size_t size;
	const size_t defaultSize = 10;
	size_t length;
#pragma endregion

#pragma region Constructors and Destructors
public:
	Array();
	Array(size_t customSize);
	Array(std::initializer_list<T> values);
	~Array();
#pragma endregion

#pragma region Private Methods
private:
	//methods go here
	void IncreaseArraySize();
	void Swap(T* element1, T* element2);
	void RightShiftArrElement(const size_t elementIndex);
	Array* UnsortedUnion(const Array* firstArray, const Array* secondArray);
	Array* SortedUnion(const Array* firstArray, const Array* secondArray);
	Array* UnsortedIntersection(const Array* firstArray, const Array* secondArray);
	Array* SortedIntersection(const Array* firstArray, const Array* secondArray);
	Array* UnsortedDifference(const Array* firstArray, const Array* secondArray);
	Array* SortedDifference(const Array* firstArray, const Array* secondArray);
#pragma endregion

#pragma region Operators
public:
	bool operator==(const Array& rhs);
	T& operator[](int index);
#pragma endregion

#pragma region Public Methods
public:
	//display contents of an array
	void Display();

	//add element to array
	void Add(const T& element);

	//insert element at index to array
	void Insert(const size_t index, const T& element);

	//delete element at index in array
	void Delete(const size_t index);

	//perform linear search of element in array
	int LinearSearch(const T& keyElement);

	//perform iterative binary search of element in array
	int BinarySearchIterative(const T& keyElement);

	// perform recursive binary search of element in array. it is recommended to use iterative version due to stack size limitation
	int BinarySearchRecursive(const T& keyElement);

	// get element at index
	T GetElementAtIndex(const size_t index);

	//set element at index
	void Set(const size_t index, const T& element);

	//get max element in array
	T Max(bool useSort);

	//get min element in array
	T Min(bool useSort);

	//perform iterative sum of elements in array
	int SumIterative();

	//perform recursive sum of elements in array
	int SumRecursive();

	//get average of all elements in array
	float Average();

	//reverse the array
	void Reverse1();

	//reverse the array
	void Reverse2();

	//perform a left shift on the array
	void LeftShift();

	//perform a right shift on the array
	void RightShift();

	//perform a left shift rotate on the array
	void LeftShiftRotate();

	// perform a right shift rotate on the array
	void RightShiftRotate();

	// perform a sorted insert on the array
	void SortedInsert(const T& element);

	//Is the array sorted
	bool IsSorted() const;

	//sort the array
	void Sort() const;

	//move negative numbers to the left
	void MoveNegativeLeft();

	//merge 2 arrays together
	Array* Merge(const Array* firstArray, const Array* secondArray);

	//perform the union operation on 2 arrays
	Array* Union(const Array* firstArray, const Array* secondArray, const bool useSortedUnion = true);

	//perform the intersection operation on 2 arrays
	Array* Intersection(const Array* firstArray, const Array* secondArray, const bool useSortedIntersection = true);

	//perform the difference operation on 2 arrays
	Array* Difference(const Array* firstArray, const Array* secondArray, const bool useSortedDifference = true);

	//get length
	int GetLength() const;

	void BubbleSort();
	void BubbleSort(Array& arr);

	void PopulateArrayRandomly();
#pragma endregion
};

#pragma endregion

#pragma region Implementation

#pragma region Constructors and Destructors
template<class T>
Array<T>::Array()
{
	size = defaultSize;
	length = 0;
	pStorage = new T[sizeof(T) * size];
}

template<class T>
Array<T>::Array(const size_t customSize)
{
	size = customSize;
	length = 0;
	pStorage = new T[sizeof(T) * size];
}

template<class T>
Array<T>::Array(std::initializer_list<T> values) 
{
	length = values.size();
	size = length;
	pStorage = new T[length];
	std::copy(values.begin(), values.end(), pStorage);
}

template<class T>
Array<T>::~Array()
{
	delete[] pStorage;
}
#pragma endregion

#pragma region Private Methods
template<class T>
void Array<T>::IncreaseArraySize()
{
	T* temp = new T[(size *= 2)];

	for (size_t i = 0; i < length; i++)
	{
		temp[i] = pStorage[i];
	}

	pStorage = temp;
}

template<class T>
void Array<T>::Swap(T* element1, T* element2)
{
	T temp = *element1;
	*element1 = *element2;
	*element2 = temp;
}

template<class T>
void Array<T>::RightShiftArrElement(const size_t elementIndex)
{
	if (elementIndex >= size) IncreaseArraySize();
	pStorage[elementIndex + 1] = pStorage[elementIndex];
}

template<class T>
Array<T>* Array<T>::UnsortedUnion(const Array* firstArray, const Array* secondArray)
{
	size_t firstArrayIndex = 0, secondArrayIndex = 0;
	bool elementExists = false;

	//copy the first array
	while (firstArrayIndex < firstArray->length) Add(firstArray->pStorage[firstArrayIndex++]);
	firstArrayIndex = 0;

	//perform linear search on 2nd array
	for (; secondArrayIndex < secondArray->length; secondArrayIndex++)
	{
		//compare the 2nd array with 1st
		for (; firstArrayIndex < firstArray->length; firstArrayIndex++)
		{
			if (secondArray->pStorage[secondArrayIndex] == firstArray->pStorage[firstArrayIndex])
			{
				elementExists = true;
				break;
			}
		}

		if (!elementExists) Add(secondArray->pStorage[secondArrayIndex]);
		firstArrayIndex = 0;
		elementExists = false;
	}

	return this;
}

template<class T>
Array<T>* Array<T>::SortedUnion(const Array* firstArray, const Array* secondArray)
{
	size_t firstArrayIndex = 0, secondArrayIndex = 0;

	//at least one array will be left out
	while (firstArrayIndex < firstArray->length && secondArrayIndex < secondArray->length)
	{
		if (firstArray->pStorage[firstArrayIndex] < secondArray->pStorage[secondArrayIndex]) Add(firstArray->pStorage[firstArrayIndex++]);
		else if (secondArray->pStorage[secondArrayIndex] < firstArray->pStorage[firstArrayIndex]) Add(secondArray->pStorage[secondArrayIndex++]);
		else
		{
			Add(firstArray->pStorage[firstArrayIndex++]);
			secondArrayIndex++;
		}
	}

	//complete the last uncopied array, it can either be the first or last array left out 
	for (; firstArrayIndex < firstArray->length; firstArrayIndex++)
	{
		//if (pStorage[length - 1] == firstArray->pStorage[firstArrayIndex]) continue;
		Add(firstArray->pStorage[firstArrayIndex]);
	}

	for (; secondArrayIndex < secondArray->length; secondArrayIndex++)
	{
		//if (pStorage[length - 1] != secondArray->pStorage[secondArrayIndex]) continue;
		Add(secondArray->pStorage[secondArrayIndex]);
	}

	return this;
}

template<class T>
Array<T>* Array<T>::UnsortedIntersection(const Array* firstArray, const Array* secondArray)
{
	for (size_t firstArrayIndex = 0; firstArrayIndex < firstArray->length; firstArrayIndex++)
	{
		for (size_t secondArrayIndex = 0; secondArrayIndex < secondArray->length; secondArrayIndex++)
		{
			if (firstArray->pStorage[firstArrayIndex] == secondArray->pStorage[secondArrayIndex])
			{
				Add(firstArray->pStorage[firstArrayIndex]);
				break;
			}
		}
	}

	return this;
}

template<class T>
Array<T>* Array<T>::SortedIntersection(const Array* firstArray, const Array* secondArray)
{
	size_t firstArrayIndex = 0, secondArrayIndex = 0;

	for (; (firstArrayIndex < firstArray->length && secondArrayIndex < secondArray->length);)
	{
		if (firstArray->pStorage[firstArrayIndex] < secondArray->pStorage[secondArrayIndex])
		{
			firstArrayIndex++;
			continue;
		}

		if (secondArray->pStorage[secondArrayIndex] < firstArray->pStorage[firstArrayIndex])
		{
			secondArrayIndex++;
			continue;
		}

		if (firstArray->pStorage[firstArrayIndex] == secondArray->pStorage[secondArrayIndex])
		{
			Add(firstArray->pStorage[firstArrayIndex]);
			firstArrayIndex++;
			secondArrayIndex++;
		}
	}

	return this;
}

template<class T>
Array<T>* Array<T>::UnsortedDifference(const Array* firstArray, const Array* secondArray)
{
	bool isDistinct = false;

	for (size_t firstArrayIndex = 0; firstArrayIndex < firstArray->length; firstArrayIndex++)
	{
		for (size_t secondArrayIndex = 0; secondArrayIndex < secondArray->length; secondArrayIndex++)
		{
			if (firstArray->pStorage[firstArrayIndex] == secondArray->pStorage[secondArrayIndex])
			{
				isDistinct = false;
				break;
			}

			isDistinct = true;
		}

		if (isDistinct) Add(firstArray->pStorage[firstArrayIndex]);
	}

	return this;
}

template<class T>
Array<T>* Array<T>::SortedDifference(const Array* firstArray, const Array* secondArray)
{
	size_t firstArrayIndex = 0, secondArrayIndex = 0;
	for (; (firstArrayIndex < firstArray->length && secondArrayIndex < secondArray->length);)
	{
		if (firstArray->pStorage[firstArrayIndex] == secondArray->pStorage[secondArrayIndex])
		{
			firstArrayIndex++;
			secondArrayIndex++;
			continue;
		}

		if (firstArray->pStorage[firstArrayIndex] < secondArray->pStorage[secondArrayIndex])
		{
			Add(firstArray->pStorage[firstArrayIndex]);
			firstArrayIndex++;
			continue;
		}

		secondArrayIndex++;
	}

	//the first array may have some uncopied elements
	for (; firstArrayIndex < firstArray->length; firstArrayIndex++) { Add(firstArray->pStorage[firstArrayIndex]); }

	return this;
}
#pragma endregion

#pragma region Operators
template<class T>
bool Array<T>::operator==(const Array& rhs)
{
	T lhsValue, rhsValue;

	for (size_t lhsIndex = 0, rhsIndex = 0; lhsIndex < length && rhsIndex < rhs.length; lhsIndex++, rhsIndex++)
	{
		lhsValue = pStorage[lhsIndex];
		rhsValue = rhs.pStorage[rhsIndex];
		if (lhsValue != rhsValue) return false;
	}

	return true;
}

template<class T>
T& Array<T>::operator[](int index)
{
	if (index > length)
	{
		cout << "Array index out of bound, exiting";
		exit(0);
	}

	return pStorage[index];
}
#pragma endregion

#pragma region Public Methods
template<class T>
void Array<T>::Display()
{
	for (size_t i = 0; i < length; i++)
	{
		cout << pStorage[i] << endl;
	}
}

template<class T>
void Array<T>::Add(const T& element)
{
	if (length < size)
	{
		pStorage[length] = element;
		length++;
	}

	else
	{
		IncreaseArraySize();
		pStorage[length] = element;
		length++;
	}
}

template<class T>
void Array<T>::Insert(const size_t index, const T& element)
{
	if (index >= 0 && index <= length)
	{
		for (size_t i = length; i > index; i--)
		{
			pStorage[i] = pStorage[i - 1];
		}

		pStorage[index] = element;
		length++;
	}

	else if (index >= 0 && (index > length || index > size))
	{
		Add(element);
	}
}

template<class T>
void Array<T>::Delete(const size_t index)
{
	if (index >= 0 && index < length)
	{
		for (size_t i = index; i < length - 1; i++)
		{
			pStorage[i] = pStorage[i + 1];
		}

		length--;
	}

	else if (index >= 0 && index >= length)
	{
		pStorage[length - 1] = NULL;
	}
}

template<class T>
int Array<T>::LinearSearch(const T& keyElement)
{
	for (size_t i = 0; i < length; i++)
	{
		if (pStorage[i] == keyElement)
		{
			if ((i - 1) >= 0) Swap(&pStorage[i], &pStorage[i - 1]);
			return i;
		}
	}

	return -1;
}

template<class T>
int Array<T>::BinarySearchIterative(const T& keyElement)
{
	if (!IsSorted()) Sort();
	size_t low = 0;
	size_t high = length - 1;

	while (low <= high)
	{
		size_t mid = (low + high) / 2;
		if (keyElement == pStorage[mid]) return mid;
		else if (keyElement < pStorage[mid]) high = mid - 1;
		else low = mid + 1;
	}

	return -1;
}

template<class T>
int Array<T>::BinarySearchRecursive(const T& keyElement)
{
	static bool isSorted = false;
	static size_t low = 0;
	static size_t high = length - 1;

	if (!isSorted)
	{
		Sort();
		isSorted = true;
	}

	if (low <= high)
	{
		size_t mid = (low + high) / 2;
		if (keyElement == pStorage[mid]) return mid;

		else if (keyElement < pStorage[mid])
		{
			high = mid - 1;
			return BinarySearchRecursive(keyElement);
		}

		else
		{
			low = mid + 1;
			return BinarySearchRecursive(keyElement);
		}
	}

	return -1;
}

template<class T>
T Array<T>::GetElementAtIndex(const size_t index)
{
	if (index >= 0 && index < length) return pStorage[index];
	else exit(0);
}

template<class T>
void Array<T>::Set(const size_t index, const T& element)
{
	if (index >= 0 && index < length) pStorage[index] = element;
}

template<class T>
T Array<T>::Max(bool useSort)
{
	if (useSort)
	{
		if (!IsSorted()) Sort();
		return pStorage[length - 1];
	}
	else
	{
		T max = pStorage[0];

		for (size_t i = 1; i < length; i++)
		{
			if (pStorage[i] > max)
			{
				max = pStorage[i];
				return max;
			}
		}
	}
}

template<class T>
T Array<T>::Min(bool useSort)
{
	if (useSort)
	{
		if (!IsSorted()) Sort();
		return pStorage[0];
	}
	else
	{
		T min = pStorage[0];

		for (size_t i = 1; i < length; i++)
		{
			if (pStorage[i] < min)
			{
				min = pStorage[i];
				return min;
			}
		}
	}
}

template<class T>
int Array<T>::SumIterative()
{
	int sum = 0;

	for (size_t i = 0; i < length; i++)
	{
		sum += pStorage[i];
	}

	return sum;
}

template<class T>
int Array<T>::SumRecursive()
{
	static int index = 0;
	static int sum = 0;

	if (index >= length) return sum;

	else
	{
		sum += pStorage[index];
		index++;
		SumRecursive();
	}
}

template<class T>
float Array<T>::Average()
{
	int sum = SumIterative();
	int average = sum / length;
	return average;
}

template<class T>
void Array<T>::Reverse1()
{
	T* auxArray = new T[sizeof(T) * length];

	for (size_t auxIndex = 0, pStorageIndex = length - 1; auxIndex < length; auxIndex++, pStorageIndex--)
	{
		auxArray[auxIndex] = pStorage[pStorageIndex];
	}

	for (size_t index = 0; index < length; index++)
	{
		pStorage[index] = auxArray[index];
	}
}

template<class T>
void Array<T>::Reverse2()
{
	T temp;

	for (size_t firstIndex = 0, lastIndex = length - 1; firstIndex < lastIndex; firstIndex++, lastIndex--)
	{
		temp = pStorage[firstIndex];
		pStorage[firstIndex] = pStorage[lastIndex];
		pStorage[lastIndex] = temp;
	}
}

template<class T>
void Array<T>::LeftShift()
{
	for (size_t index = 1; index < length; index++)
	{
		pStorage[index - 1] = pStorage[index];
	}

	pStorage[length - 1] = NULL;
}

template<class T>
void Array<T>::RightShift()
{
	for (int index = length - 2; index >= 0; index--)
	{
		pStorage[index + 1] = pStorage[index];
	}

	pStorage[0] = NULL;
}

template<class T>
void Array<T>::LeftShiftRotate()
{
	T temp = pStorage[0];
	LeftShift();
	pStorage[length - 1] = temp;
}

template<class T>
void Array<T>::RightShiftRotate()
{
	T temp = pStorage[length - 1];
	RightShift();
	pStorage[0] = temp;
}

template<class T>
void Array<T>::SortedInsert(const T& element)
{
	size_t arrIndex = length - 1;

	while (pStorage[arrIndex] > element)
	{
		RightShiftArrElement(arrIndex);
		arrIndex--;
	}

	pStorage[arrIndex] = element;
}

template<class T>
bool Array<T>::IsSorted() const
{
	for (size_t arrIndex = 0; arrIndex < length - 1; arrIndex++)
	{
		if (pStorage[arrIndex] > pStorage[arrIndex + 1])
		{
			return false;
		}
	}

	return true;
}

template<class T>
void Array<T>::Sort() const
{
	sort(pStorage, pStorage + length);
}

template<class T>
void Array<T>::MoveNegativeLeft()
{
	size_t negativeIndex, positiveIndex;
	negativeIndex = 0;
	positiveIndex = length - 1;

	while (negativeIndex > positiveIndex)
	{
		while (pStorage[negativeIndex] < 0) { negativeIndex++; }
		while (pStorage[negativeIndex] >= 0) { positiveIndex--; }
		if (negativeIndex < positiveIndex) Swap(pStorage[negativeIndex], pStorage[positiveIndex]);
	}
}

template<class T>
Array<T>* Array<T>::Merge(const Array* firstArray, const Array* secondArray)
{
	const bool firstArraySorted = firstArray->IsSorted();
	const bool secondArraySorted = secondArray->IsSorted();

	//both firstArray and Second Array must be sorted for the merge operation to happen
	if (!firstArraySorted || !secondArraySorted)
	{
		cout << "The merge operation only works on sorted arrays. please sort each array before merging";
		if (!firstArraySorted) firstArray->Sort();
		if (!secondArraySorted) secondArray->Sort();
	}

	size_t firstArrayIndex = 0, secondArrayIndex = 0;

	//at least one array will be left out
	while (firstArrayIndex < firstArray->length && secondArrayIndex < secondArray->length)
	{
		if (firstArray->pStorage[firstArrayIndex] < secondArray->pStorage[secondArrayIndex]) Add(firstArray->pStorage[firstArrayIndex++]);
		else if (secondArray->pStorage[secondArrayIndex] < firstArray->pStorage[firstArrayIndex]) Add(secondArray->pStorage[secondArrayIndex++]);
		else
		{
			//if the elements are equal
			Add(firstArray->pStorage[firstArrayIndex++]);
			secondArrayIndex++;
		}
	}

	//complete the last uncopied array, it can either be the first or last array left out 
	for (; firstArrayIndex < firstArray->length; firstArrayIndex++) { Add(firstArray->pStorage[firstArrayIndex]); }
	for (; secondArrayIndex < secondArray->length; secondArrayIndex++) { Add(secondArray->pStorage[secondArrayIndex]); }
	return this;
}

template<class T>
Array<T>* Array<T>::Union(const Array* firstArray, const Array* secondArray, const bool useSortedUnion)
{
	const bool firstArraySorted = firstArray->IsSorted();
	const bool secondArraySorted = secondArray->IsSorted();

	if (useSortedUnion)
	{
		if (!firstArraySorted || !secondArraySorted)
		{
			if (!firstArraySorted) firstArray->Sort();
			if (!secondArraySorted) secondArray->Sort();
		}

		SortedUnion(firstArray, secondArray);
		return this;
	}


	UnsortedUnion(firstArray, secondArray);
	return this;
}

template<class T>
Array<T>* Array<T>::Intersection(const Array* firstArray, const Array* secondArray, const bool useSortedIntersection)
{
	const bool firstArraySorted = firstArray->IsSorted();
	const bool secondArraySorted = secondArray->IsSorted();

	if (useSortedIntersection)
	{
		if (!firstArraySorted || !secondArraySorted)
		{
			if (!firstArraySorted) firstArray->Sort();
			if (!secondArraySorted) secondArray->Sort();
		}

		SortedIntersection(firstArray, secondArray);
		return this;
	}

	UnsortedIntersection(firstArray, secondArray);
	return this;
}

template<class T>
Array<T>* Array<T>::Difference(const Array* firstArray, const Array* secondArray, const bool useSortedDifference)
{
	const bool firstArraySorted = firstArray->IsSorted();
	const bool secondArraySorted = secondArray->IsSorted();

	if (useSortedDifference)
	{
		if (!firstArraySorted || !secondArraySorted)
		{
			if (!firstArraySorted) firstArray->Sort();
			if (!secondArraySorted) secondArray->Sort();
		}

		SortedDifference(firstArray, secondArray);
		return this;
	}

	UnsortedDifference(firstArray, secondArray);
	return this;
}

template<class T>
int Array<T>::GetLength() const
{
	return length;
}

template<class T>
void Array<T>::BubbleSort(Array<T>& arr)
{
	if (!arr.pStorage) return;

	const int maxPasses = arr.GetLength() - 1;
	bool flag = false;

	//passes
	for (int outerIndex = 0; outerIndex < maxPasses; outerIndex++)
	{
		//comparisons
		for (int innerIndex = 0; innerIndex < maxPasses - outerIndex; innerIndex++)
		{
			//swaps
			if (arr.GetElementAtIndex(innerIndex) > arr.GetElementAtIndex(innerIndex + 1))
			{
				Swap(&arr[innerIndex], &arr[innerIndex + 1]);
				flag = true;
			}
		}

		if (!flag)
		{
			return;
		}
	}
}

template<class T>
void Array<T>::BubbleSort()
{
	if (!pStorage) return;

	const int maxPasses = GetLength() - 1;
	bool flag = false;

	//passes
	for (int outerIndex = 0; outerIndex < maxPasses; outerIndex++)
	{
		//comparisons
		for (int innerIndex = 0; innerIndex < maxPasses - outerIndex; innerIndex++)
		{
			//swaps
			if (GetElementAtIndex(innerIndex) > GetElementAtIndex(innerIndex + 1))
			{
				Swap(&pStorage[innerIndex], &pStorage[innerIndex + 1]);

				flag = true;
			}
		}

		if (!flag)
		{
			return;
		}
	}
}

template<class T>
void Array<T>::PopulateArrayRandomly()
{
	//create random device
	std::random_device rd;

	//init mersenne_twister random gen engine
	std::mt19937 gen(rd());

	//create a distribution of random generation
	std::uniform_int_distribution<int> distribution(1, 1000);

	//generate the random number
	int randomNumber = distribution(gen);

	for (int i = 0; i < size; i++)
	{
		randomNumber = distribution(gen);
		pStorage[i] = randomNumber;
	}

	length = size;
}

#pragma endregion

#pragma endregion
