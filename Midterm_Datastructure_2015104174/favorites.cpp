#pragma once
#include "favorites.h"

// constructor
favorites::favorites() {

}

// destructor
favorites::~favorites() {

}

// general functions
void favorites::Print() {
	cout << "----------------------------------------" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i+1 << ". " << contentList[i].GetFilename() << endl;
	}
}

void favorites::SetFavorites() {
	// masterList�� ���� �״�� �����ؿ��� tempList�� �����.
	mySortedArrayList<content> tempList;
	content dummy;
	masterList->ResetList();
	for (int i = 0; i < masterList->GetLength(); i++) {
		masterList->GetNextItem(dummy);
		tempList.Add(dummy);
	}

	// ���� searchCount�� ū���� ã��, contentList�� �־��ص�, �ش��������� tempList���� �����Ѵ�.
	// �ش� ������ 10ȸ �ݺ��Ѵ�.
	for (int i = 0; i < 10; i++) {
		int count = -1;
		tempList.ResetList();
		content maxContent;
		content iterator;
		// tempList���� ���� ū�� ã��
		for (int j = 0; j < tempList.GetLength(); j++) {
			tempList.GetNextItem(iterator);
			if (iterator.GetSearchCount() > count) {
				maxContent = iterator;
				count = iterator.GetSearchCount();
			}
		}
		// ���� ū���� �־��ص�
		contentList[i] = maxContent;

		// tempList���� �����Ѵ�.
		tempList.Delete(maxContent);
	}

}