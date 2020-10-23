#pragma once
#include<iostream>
#include<string>

#include"content.h"
#include"mySortedArrayList.h"

using namespace std;

class favorites {
public:
	// constructor
	favorites();

	// destructor
	~favorites();

	// set MasterList
	void SetMasterListPointer(mySortedArrayList<content>* masterList) { this->masterList = masterList; }

	// general functions
	void Print();	// to print favorites rank, contents

	/*
	@brief 즐겨찾기를 세팅하는 함수, application에서 print하기전 실행시킬 예정이다.
	@pre masterList에 컨텐츠가 있어야한다.
	@post content.searchCount에 따라 정렬한뒤, 10개까지 contentList에 담는다.
	*/
	void SetFavorites();


private:
	mySortedArrayList<content>* masterList;
	content contentList[10];
};
