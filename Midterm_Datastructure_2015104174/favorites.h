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

	// getter
	

	// set MasterList
	void SetMasterListPointer(mySortedArrayList<content>* masterList) { this->masterList = masterList; }

	// general functions
	void Print();	// to print favorites rank, contents
	
	void SetFavorites();
	/*void UpdateFavorites(content data);
	int DeleteOnFavorites(content data)*/;

private:
	mySortedArrayList<content>* masterList;
	content contentList[10];
};
