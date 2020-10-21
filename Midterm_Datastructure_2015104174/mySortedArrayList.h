#pragma once

#include<iostream>
using namespace std;

template<typename T>
class mySortedArrayList {
public:

	// constructor
	mySortedArrayList();

	// destructor
	~mySortedArrayList();

	void MakeEmpty();

	void ResetList();

	int GetLength() { return length; }

	bool IsFull();

	int Add(T item);

	int Delete(T item);

	int Replace(T item);

	int GetNextItem(T& item);

	int Get(T& item);
	
private:
	int length;
	int maxSize;
	int current;
	T* array;
};

// constructor
template<typename T>
mySortedArrayList<T>::mySortedArrayList() {
	length = 0;
	maxSize = 50;
	current = -1;
	array = new T[maxSize];
}

// destructor
template<typename T>
mySortedArrayList<T>::~mySortedArrayList() {
	//delete[] this->array;
}

template<typename T>
void mySortedArrayList<T>::MakeEmpty() {
	length = 0;
}

template<typename T>
void mySortedArrayList<T>::ResetList() {
	current = -1;
}

template<typename T>
bool mySortedArrayList<T>::IsFull() {
	if (length == maxSize) {
		return true;
	}
	return false;
}

template<typename T>
int mySortedArrayList<T>::Add(T item) {
	if (IsFull()) {
		maxSize += 50;
		T* newArray = new T[maxSize];
		for (int i = 0; i < length; i++) {
			newArray[i] = this->array[i];
		}

		T* temp = this->array;
		array = newArray;
		delete[] temp;
	}

	for (int i = 0; i < length; i++) {
		if (array[i] == item) {
			// �������� �ִ°�� -> ���� �Ұ�
			return 0;
		}
		else if (array[i] < item) {
			// �ڸ�ã��
			continue;
		}
		else {
			// �ڸ��� ã����
			for (int j = length; j > i; j--) {
				// ��ĭ�� ���������� �а�
				array[j] = array[j - 1];
			}
			// �ش��ڸ��� ����
			array[i] = item;
			length++;

			return 1;
		}
	}

	// item�� ���� ū���ϰ��
	array[length] = item;
	length++;

	return 1;
}

template<typename T>
int mySortedArrayList<T>::Delete(T item) {
	for (int i = 0; i < length; i++) {
		if (array[i] == item) {
			// delete it & re-positioning
			length--;
			for (int j = i; j < length; j++) {
				array[j] = array[j + 1];
			}
			return 1;
		}
	}

	// not found
	return 0;
}

template<typename T>
int mySortedArrayList<T>::Replace(T item) {
	for (int i = 0; i < length; i++) {
		if (array[i] == item) {
			array[i] = item;
			return 1;
		}
	}
	return 0;
}

template<typename T>
int mySortedArrayList<T>::GetNextItem(T& item) {
	if (current == length) {
		current = -1;
		return 0;
	}
	current++;
	item = array[current];
	return 1;
}

template<typename T>
int mySortedArrayList<T>::Get(T& item) {

	int start = 0;
	int end = length - 1;
	int mid = 0;
	while (start <= end) {
		mid = (start + end) / 2;
		if (array[mid] == item) {
			item = array[mid];
			return 1;
		}
		else {
			if (array[mid] < item) {
				start = mid + 1;
			}
			else {
				end = mid - 1;
			}
		}
	}
	return 0;

	/*for (int i = 0; i < length; i++) {
		if (array[i] == item) {
			item = array[i];
			return 1;
		}
	}
	return 0;*/
}
