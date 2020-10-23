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
	// masterList의 값을 그대로 복사해오는 tempList를 만든다.
	mySortedArrayList<content> tempList;
	content dummy;
	masterList->ResetList();
	for (int i = 0; i < masterList->GetLength(); i++) {
		masterList->GetNextItem(dummy);
		tempList.Add(dummy);
	}

	// 제일 searchCount가 큰값을 찾고, contentList에 넣어준뒤, 해당컨텐츠를 tempList에서 삭제한다.
	// 해당 로직을 10회 반복한다.
	for (int i = 0; i < 10; i++) {
		int count = -1;
		tempList.ResetList();
		content maxContent;
		content iterator;
		// tempList에서 제일 큰것 찾기
		for (int j = 0; j < tempList.GetLength(); j++) {
			tempList.GetNextItem(iterator);
			if (iterator.GetSearchCount() > count) {
				maxContent = iterator;
				count = iterator.GetSearchCount();
			}
		}
		// 제일 큰값을 넣어준뒤
		contentList[i] = maxContent;

		// tempList에서 삭제한다.
		tempList.Delete(maxContent);
	}

}