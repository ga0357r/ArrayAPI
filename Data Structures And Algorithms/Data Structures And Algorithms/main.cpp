#include<iostream>
#include <chrono>
#include "Array.h"

using namespace std;

void ArrayMenu()
{
	int ch, x, index;
	Array<int> data;

	do
	{
		cout << "\n\nMenu\n";
		cout << "1. Insert\n";
		cout << "2. Delete\n";
		cout << "3. Search\n";
		cout << "4. Sum\n";
		cout << "5. Display\n";
		cout << "6. Exit\n";
		cout << "enter your choice ";
		cin >> ch;

		switch (ch)
		{
		case 1:
			cout << "Enter an element and an index to insert ";
			cin >> x >> index;
			data.Insert(index, x);
			break;
		case 2:
			cout << "Enter an index to delete an element ";
			cin >> index;
			x = data.GetElementAtIndex(index);
			data.Delete(index);
			cout << "Deleted Element is " << x;
			break;
		case 3:
			cout << "Enter an element to search for ";
			cin >> x;
			index = data.LinearSearch(x);
			cout << "Element index is " << index;
			break;
		case 4:
			cout << "Sum of all elements is " << data.SumIterative();
			break;
		case 5:
			data.Display();
		}
	}

	while (ch < 6);
}

void DisplayElements(std::chrono::steady_clock::time_point& start, Array<int>& arr, std::chrono::steady_clock::time_point& end, std::chrono::duration<double>& duration)
{
	std::cout << std::endl << "Display Elements:" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	arr.Display();
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Display Array Elements Execution time: " << duration.count() << " seconds" << std::endl;
}

void BinarySearch(std::chrono::steady_clock::time_point& start, Array<int>& arr, int& elementToFind, std::chrono::steady_clock::time_point& end, std::chrono::duration<double>& duration)
{
	std::cout << std::endl << "Binary Search:" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	int indexOfElement = arr.BinarySearchIterative(elementToFind);
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Binary Search Execution time: " << duration.count() << " seconds" << std::endl;

	if (indexOfElement == -1)
	{
		std::cout << elementToFind << " does not exist in the array" << std::endl;
	}

	else
	{
		std::cout << elementToFind << " exists in the array at index" << indexOfElement << std::endl;
	}
}

void LinearSearch(std::chrono::steady_clock::time_point& start, Array<int>& arr, int& elementToFind, std::chrono::steady_clock::time_point& end, std::chrono::duration<double>& duration)
{
	std::cout << std::endl << "Linear Search:" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	int indexOfElement = arr.LinearSearch(elementToFind);
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Linear Search Execution time: " << duration.count() << " seconds" << std::endl;

	if (indexOfElement == -1)
	{
		std::cout << elementToFind << " does not exist in the array" << std::endl;
	}

	else
	{
		std::cout << elementToFind << " exists in the array at index" << indexOfElement << std::endl;
	}
}

void BubbleSort(std::chrono::steady_clock::time_point& start, Array<int>& arr, std::chrono::steady_clock::time_point& end, std::chrono::duration<double>& duration)
{
	std::cout << std::endl << "Bubble Sort:" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	arr.BubbleSort();
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Bubble Sort Execution time: " << duration.count() << " seconds" << std::endl;
}

void PopulateArrayRandomly(std::chrono::steady_clock::time_point& start, Array<int>& arr, std::chrono::steady_clock::time_point& end, std::chrono::duration<double>& duration)
{
	std::cout << std::endl << "Populate Array Randomly:" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	arr.PopulateArrayRandomly();
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Populating Array Randomly Execution time: " << duration.count() << " seconds" << std::endl;
}

void ChooseElementToFind(int& elementToFind)
{
	cout << "What element do you want to find?" << endl;
	cin >> elementToFind;
}

void ChooseArrayLength(int& arrayLength)
{
	cout << "Any Length higher than 20000 will cause longer times(> 10 seconds) in the Bubble Sort Algorithm" << endl;
	cout << "What is the Array Length?" << endl;
	cin >> arrayLength;
}


int main()
{
	std::chrono::steady_clock::time_point start, end;
	std::chrono::duration<double> duration;
	int arrayLength = 20000;
	int elementToFind;

	ChooseArrayLength(arrayLength);
	ChooseElementToFind(elementToFind);

	std::cout << std::endl << "Create Array:" << std::endl;
	start = std::chrono::high_resolution_clock::now();
	Array<int> arr(arrayLength);
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Array Definition Execution time: " << duration.count() << " seconds" << std::endl;

	PopulateArrayRandomly(start, arr, end, duration);
	BubbleSort(start, arr, end, duration);
	LinearSearch(start, arr, elementToFind, end, duration);
	BinarySearch(start, arr, elementToFind, end, duration);
	//DisplayElements(start, arr, end, duration);

	return 0;
}