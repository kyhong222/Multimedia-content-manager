#pragma once

using namespace std;

template<typename T>
struct node
{
	T data;
	node* next = nullptr;
};

template<typename T>
class myLinkedList {
public:
	myLinkedList();

	~myLinkedList();

	void MakeEmpty();

	int GetLength() { return length; }

	int Add(T item);

	int Delete(T item);

	int Replace(T item);

	int Get(T& item);

	void ResetList();

	void GetNextItem(T& item);

private:
	node<T>* head;
	node<T>* current;
	int length;
};

template<typename T>
myLinkedList<T>::myLinkedList() {
	length = 0;
	head = NULL;
	current = NULL;
}

template<typename T>
myLinkedList<T>::~myLinkedList() {
	/*node<T>* temp;

	while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}*/
	/*node<T> *n = this->head, *current = nullptr;
	while (n) {
		current = n;
		n = n->next;
		delete(current);
	}

	head = nullptr;*/
	//MakeEmpty();
}

template<typename T>
void myLinkedList<T>::MakeEmpty() {
	node<T>* temp;

	while (head != nullptr){
		temp = head;
		head = head->next;
		delete temp;
	}
	length = 0;
}

template<typename T>
int myLinkedList<T>::Add(T item) {
	ResetList();
	T dummy;
	
	node<T>* temp = new node<T>;
	temp->data = item;
	temp->next = nullptr;

	if (head == nullptr) {
		head = temp;
		length++;
		return 1;
	}

	while (true) {
		GetNextItem(dummy);
		if (current->data == item) {
			return 0;
		}
		if (current->next == nullptr) {
			current->next = temp;
			length++;
			return 1;
		}
	}
}

template<typename T>
int myLinkedList<T>::Delete(T item) {
	node<T>* temp;
	node<T>* target;
	temp = head;
	
	// head�� �����ߵ� ����ΰ��
	if (temp->data == item) {
		head = temp->next;
		delete temp;
		length--;
		return 1;
	}

	// ����Ʈ ��򰡿� �����ߵɰ� �ִ°��
	for (int i = 0; i < length-1; i++) {
		if (temp->next->data == item) {
			target = temp->next;
			temp->next = target->next;
			delete target;
			length--;
			return 1;
		}
	}

	// ����� ���°��
	return 0;

}

template<typename T>
int myLinkedList<T>::Replace(T item) {
	node<T>* temp = head;
	while (temp != nullptr) {
		// ���� �����Ͱ� item�� ��ġ�ϸ�
		if (temp->data == item) {
			temp->data = item;
			return 1;
		}

		// ���� �����Ͱ� ã�°� �ƴѰ��
		temp = temp->next;
	}

	// ã�� ���Ѱ��
	return 0;
}

template<typename T>
int myLinkedList<T>::Get(T& item) {
	node<T>* temp = head;
	while (temp != nullptr) {
		// ���� �����Ͱ� item�� ��ġ�ϸ�
		if (temp->data == item) {
			item = temp->data;
			return 1;
		}

		// ���� �����Ͱ� ã�°� �ƴѰ��
		temp = temp->next;
	}

	// ã�� ���Ѱ��
	return 0;
}

template<typename T>
void myLinkedList<T>::ResetList() {
	current = nullptr;
}

template<typename T>
void myLinkedList<T>::GetNextItem(T& item) {
	if (current == nullptr) {
		current = head;
	}
	else {
		current = current->next;
	}
	item = current->data;
}