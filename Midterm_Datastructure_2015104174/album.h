#pragma once
#include<iostream>
#include<string>

#include"content.h"
#include"mySortedLinkedList.h"
#include"mySortedArrayList.h"

using namespace std;

class album {
public:
	// constructor
	album();

	// destructor
	~album();

	// getters
	string GetName() { return name; }
	string GetDescription() { return description; }

	// setters
	void SetName(string name) { this->name = name; }
	void SetMasterListPorinter(mySortedArrayList<content>* masterListPointer) { this->masterList = masterListPointer; }

	// general functions
	mySortedLinkedList<string>* GetContentList() { return &contentList; }

	void Print();	// to print album's name, description, number of contents
	void PrintContents();	// to print contents' detail
	void SetAlbumFromKB();
	//void SetAlbum(album item);

	// operator overloading functions to use data structure
	bool operator > (const album& data);
	bool operator == (const album& data);


private:
	string name;
	string description;

	mySortedLinkedList<string> contentList;
	mySortedArrayList<content>* masterList;
};
