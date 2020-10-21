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
	mySortedArrayList<content> tempList;
	content dummy;
	masterList->ResetList();
	for (int i = 0; i < masterList->GetLength(); i++) {
		masterList->GetNextItem(dummy);
		tempList.Add(dummy);
	}

	for (int i = 0; i < 10; i++) {
		int count = -1;
		tempList.ResetList();
		content maxContent;
		content iterator;
		for (int j = 0; j < tempList.GetLength(); j++) {
			tempList.GetNextItem(iterator);
			if (iterator.GetSearchCount() > count) {
				maxContent = iterator;
				count = iterator.GetSearchCount();
			}
		}
		contentList[i] = maxContent;
		tempList.Delete(maxContent);
	}

}

//void favorites::UpdateFavorites(content data) {
//	for (int i = 0; i < 10; i++) {
//		content temp;
//		temp.SetFilename(contentList[i]);
//		masterList->Get(temp);
//		if (temp.GetSearchCount() < data.GetSearchCount()) {
//			for (int j = 8; j >= i; j--) {
//				contentList[j+1] = contentList[j];
//			}
//			contentList[i] = data.GetFilename();
//			return;
//		}
//	}
//}