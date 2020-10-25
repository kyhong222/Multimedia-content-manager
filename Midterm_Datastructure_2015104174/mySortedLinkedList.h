#pragma once

#include <iostream>
using namespace std;

template<typename T>
struct NodeType {
	T data;
	NodeType* next = NULL;
};

template<typename T>
class mySortedLinkedList {
public:
	// constructor
	mySortedLinkedList(mySortedLinkedList<T> &copyList);

	// copy constructor
	mySortedLinkedList();

	// destructor
	~mySortedLinkedList();

	void MakeEmpty();
	int GetLength() { return length; }

	int Add(T item);
	int Delete(T item);
	int Replace(T item);
	int Get(T& item);

	void ResetList();
	int GetNextItem(T& item);

	mySortedLinkedList<T> operator=(mySortedLinkedList<T>& copyList);

private:
	NodeType<T>* head;
	NodeType<T>* current;
	int length;
};

template<typename T>
mySortedLinkedList<T>::mySortedLinkedList() {
	head = nullptr;
	current = nullptr;
	length = 0;
}

template<typename T>
mySortedLinkedList<T>::mySortedLinkedList(mySortedLinkedList<T>& copyList) {
	this->ResetList();
	T dummy;

	for (int i = 0; i < this->GetLength(); i++) {
		this->GetNextItem(dummy);
		copyList.Add(dummy);
	}
}

template<typename T>
mySortedLinkedList<T>::~mySortedLinkedList() {
	MakeEmpty();
}

template<typename T>
void mySortedLinkedList<T>::MakeEmpty() {
	NodeType<T>* temp;

	for (int i = 0; i < length; i++) {
		temp = head;
		head = head->next;
		temp->next = NULL;
		delete temp;
	}

	length = 0;
}

template<typename T>
int mySortedLinkedList<T>::Add(T item) {
	// reset list
	ResetList();

	NodeType<T> *target = new NodeType<T>;
	NodeType<T> *pre;

	T temp;	// is temp object to use GetNextItem()

	target->data = item;
	target->next = nullptr;

	// if length == 0, then target is head
	if (!length) {
		head = target;
		length++;
		return 1;
	}

	while (true) {
		// set pre-node
		pre = current;

		// get next thing
		GetNextItem(temp);

		// if there is a same item, then do not add.
		if (temp == target->data) {
			//cout << "there is same item." << endl;
			return 0;
		}

		// if current data is bigger then target data
		if (current->data > target->data) {
			// if head is bigger then target data, then add item before head
			if (pre == nullptr) {
				target->next = current;
				head = target;
				break;
			}

			// add item after current
			pre->next = target;
			target->next = current;
			break;
		}

		// if there is no item that bigger then target, add it on tail
		if (current->next == nullptr) {
			current->next = target;
			break;
		}
	}

	// increase length
	length++;
	return 1;
}
template<typename T>
int mySortedLinkedList<T>::Delete(T item) {
	// reset list
	ResetList();

	NodeType<T> *pre;
	T temp;	// it is used to use GetNextItem()

	while (true) {
		// set pre-node
		pre = current;

		// get next item
		GetNextItem(temp);

		// if found
		if (temp == item) {
			// if it is head, then set head as next
			if (pre == nullptr) {
				head = current->next;
			}
			// else, then set pre's next as current's next
			else {
				pre->next = current->next;
			}

			// delete current
			delete current;
			length--;
			return 1;
		}

		// if not found
		if (current == nullptr) {
			//cout << "there is no item like that." << endl;
			return 0;
		}
	}
}
template<typename T>
int mySortedLinkedList<T>::Replace(T item) {
	// reset list
	ResetList();

	T temp;	// it is used to use GetNextItem()

	while (true) {
		// get next item
		GetNextItem(temp);

		// if found
		if (temp == item) {
			// replace it
			current->data = item;
			return 1;
		}

		// if not found
		if (current == nullptr) {
			cout << "there is no item like that." << endl;
			return 0;
		}
	}
}
template<typename T>
int mySortedLinkedList<T>::Get(T& item) {
	// reset list
	ResetList();

	T temp;	// it is used to use GetNextItem()

	for (int i = 0; i < length; i++) {
		// get next item
		GetNextItem(temp);

		// if found
		if (temp == item) {
			// get it
			item = temp;
			return 1;
		}
	}

	// if not found
	if (current == nullptr) {
		//cout << "there is no item like that." << endl;
		return 0;
	}
	return 0;
}

template<typename T>
void mySortedLinkedList<T>::ResetList() {
	current = nullptr;
}

template<typename T>
int mySortedLinkedList<T>::GetNextItem(T& item) {
	if (!length)	return 0;
	if (current == nullptr) {
		current = head;
		item = current->data;
		return 1;
	}
	else {
		if (current->next == nullptr) {
			current = nullptr;
			return 0;
		}
		current = current->next;
		item = current->data;
		return 1;
	}

}

template<typename T>
mySortedLinkedList<T> mySortedLinkedList<T>::operator=(mySortedLinkedList<T>& copyList) {
	copyList.ResetList();
	T dummy;
	for (int i = 0; i < copyList.GetLength(); i++) {
		copyList.GetNextItem(dummy);
		this->Add(dummy);
	}

	this->length = copyList.GetLength();
	return *this;
	
}