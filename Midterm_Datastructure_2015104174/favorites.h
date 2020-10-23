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
	@brief ���ã�⸦ �����ϴ� �Լ�, application���� print�ϱ��� �����ų �����̴�.
	@pre masterList�� �������� �־���Ѵ�.
	@post content.searchCount�� ���� �����ѵ�, 10������ contentList�� ��´�.
	*/
	void SetFavorites();


private:
	mySortedArrayList<content>* masterList;
	content contentList[10];
};
