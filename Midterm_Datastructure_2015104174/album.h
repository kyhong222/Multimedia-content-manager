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

	// copy constructor
	album(album& copyAlbum) {

		this->name = copyAlbum.GetName();
		this->description = copyAlbum.GetDescription();
		this->contentList = copyAlbum.contentList;
		this->masterList = copyAlbum.masterList;


		/*copyAlbum.SetName(this->name);
		copyAlbum.SetDescription(this->description);
		copyAlbum.contentList = this->contentList;
		copyAlbum.SetMasterListPorinter(this->masterList);*/
	}

	// destructor
	~album();

	// getters
	string GetName() { return name; }
	string GetDescription() { return description; }
	mySortedLinkedList<string>* GetContentList() { return &contentList; }

	// setters
	void SetName(string name) { this->name = name; }
	void SetDescription(string desc) { this->description = desc; }
	void SetMasterListPorinter(mySortedArrayList<content>* masterListPointer) { this->masterList = masterListPointer; }
	void SetAlbumFromKB();

	// general functions
	void Print();	// to print album's name, description, number of contents
	void PrintContents();	// to print contents' detail

	// operator overloading functions to use data structure
	bool operator > (const album& data);
	bool operator == (const album& data);

	album operator=(album& copyAlbum);

private:
	string name;
	string description;

	mySortedLinkedList<string> contentList;
	mySortedArrayList<content>* masterList;
};
