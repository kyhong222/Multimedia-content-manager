#pragma once
#include"album.h"

#include<iostream>

using namespace std;

// constructor
album::album() {
	name = "";
	description = "none";
}

// destructor
album::~album() {}

// to print album's name, description, number of contents
void album::Print() {
	cout << "----------------------------------------" << endl;
	cout << "album name : " << name << endl;
	if (description != "none") {
		cout << "album description : " << description << endl;
	}	
	cout << "album files : " << contentList.GetLength() << endl;
}

// to print contents' detail
void album::PrintContents() {
	cout << "----------------------------------------" << endl;
	string temp;
	contentList.ResetList();
	for (int i = 0; i < contentList.GetLength(); i++) {
		contentList.GetNextItem(temp);
		content tempContent;
		tempContent.SetFilename(temp);
		masterList->Get(tempContent);
		tempContent.Print();
	}
}

void album::SetAlbumFromKB() {
	string inputName, inputDesc;
	cout << "set album name : ";
	cin >> inputName;
	cout << "set album description : ";
	cin >> inputDesc;

	if (inputName != "") {
		name = inputName;
	}
	if (inputDesc != "") {
		description = inputDesc;
	}
}

//void album::SetAlbum(album item) {
//
//}

// operator overloading functions to use data structure
bool album::operator > (const album& data) {
	if (this->name > data.name)	return true;
	return false;
}

bool album::operator == (const album& data) {
	if (this->name == data.name)	return true;
	return false;
}
