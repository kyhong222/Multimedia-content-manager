#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<ctime>

#include"content.h"
#include"favorites.h"
#include"album.h"

#include"mySortedLinkedList.h"
#include"mySortedArrayList.h"

using namespace std;

class application {
public:
	// constructor
	application();
	
	// destructor
	~application();

	// general functions
	void Run();
	
	void AdvancedSearch();

	// crud functions
	int AddContent();
	int DeleteContent();
	int ReplaceContent();
	int RetriveContent();

	void ShowAllContents();

	// album control functions
	void showAlbums();

	// file input/output functions
	int ReadDataFromFile();
	int WriteDataToFile();

	void createDataSet();

private:
	mySortedArrayList<content> masterList;
	favorites favoriteList;
	mySortedLinkedList<album> eventAlbumList;
	mySortedLinkedList<album> peopleAlbumList;
	mySortedLinkedList<album> placeAlbumList;
	mySortedLinkedList<album> typeAlbumList;
	mySortedLinkedList<album> createdAtAlbumList;
};
