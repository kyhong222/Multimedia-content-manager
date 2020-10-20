#pragma once

#include "application.h"

// constructor
application::application() {
	favoriteList.SetMasterListPointer(&masterList);
}

// destructor
application::~application() {}

// general functions
void application::Run() {
	while (true) {
		int command = 0;
		cout << "----------------------------------------" << endl;
		cout << "Select menu" << endl;
		cout << "1. Add content" << endl;
		cout << "2. Delete content" << endl;
		cout << "3. Replace content" << endl;
		cout << "4. Retrive content" << endl;
		cout << "5. Show all content" << endl;
		cout << "6. Show all albums" << endl;
		cout << "7. Read data from file" << endl;
		cout << "8. Write data from file" << endl;
		cout << "9. Search from keyword" << endl;
		cout << "10. Show favorites" << endl;
		cout << "0. exit" << endl;
		cout << "----------------------------------------" << endl;
		cout << "command --> ";
		cin >> command;
		switch (command)
		{
		case 1:
			AddContent();
			break;
		case 2:
			DeleteContent();
			break;
		case 3:
			ReplaceContent();
			break;
		case 4:
			RetriveContent();
			break;
		case 5:
			ShowAllContents();
			break;
		case 6:
			showAlbums();
			break;
		case 7:
			ReadDataFromFile();
			break;
		case 8:
			WriteDataToFile();
			break;
		case 9:
			AdvancedSearch();
			break;
		case 10:
			favoriteList.SetFavorites();
			favoriteList.Print();
			break;
		case 0:
			return;
		default:
			cout << "Invalid command" << endl;
			break;
		}
	}

}

void application::AdvancedSearch() {
	cout << "----------------------------------------" << endl;
	cout << "Type keywords to search(여러개를 검색할때는 스페이스바를 활용하십시오.) : ";
	
	string keywordString;
	cin.ignore();
	getline(cin, keywordString);	

	// split keywords & add on keywordList
	mySortedLinkedList<string> keywordList;
	istringstream ss(keywordString);
	string stringBuffer;

	while (getline(ss, stringBuffer, ' ')) {
		keywordList.Add(stringBuffer);
	}

	mySortedLinkedList<album> targetAlbumList;
	album iterator;

	// find on eventAlbumList
	eventAlbumList.ResetList();
	for (int i = 0; i < eventAlbumList.GetLength(); i++) {
		eventAlbumList.GetNextItem(iterator);
		string temp = iterator.GetName();
		if (keywordList.Get(temp)) {
			targetAlbumList.Add(iterator);
		}
	}

	// find on peopleAlbumList
	peopleAlbumList.ResetList();
	for (int i = 0; i < peopleAlbumList.GetLength(); i++) {
		peopleAlbumList.GetNextItem(iterator);
		string temp = iterator.GetName();
		if (keywordList.Get(temp)) {
			targetAlbumList.Add(iterator);
		}
	}

	// find on placeAlbumList
	placeAlbumList.ResetList();
	for (int i = 0; i < placeAlbumList.GetLength(); i++) {
		placeAlbumList.GetNextItem(iterator);
		string temp = iterator.GetName();
		if (keywordList.Get(temp)) {
			targetAlbumList.Add(iterator);
		}
	}

	// find on typeAlbumList
	typeAlbumList.ResetList();
	for (int i = 0; i < typeAlbumList.GetLength(); i++) {
		typeAlbumList.GetNextItem(iterator);
		string temp = iterator.GetName();
		if (keywordList.Get(temp)) {
			targetAlbumList.Add(iterator);
		}
	}

	// find on createdAtAlbumList
	createdAtAlbumList.ResetList();
	for (int i = 0; i < createdAtAlbumList.GetLength(); i++) {
		createdAtAlbumList.GetNextItem(iterator);
		string temp = iterator.GetName();
		if (keywordList.Get(temp)) {
			targetAlbumList.Add(iterator);
		}
	}

	// make result list
	mySortedLinkedList<string> resultList;
	mySortedLinkedList<string>* tempList;
	
	if (!targetAlbumList.GetLength()) {
		cout << "----------------------------------------" << endl;
		cout << "검색 결과가 없습니다." << endl;
		return;
	}
	targetAlbumList.ResetList();
	
	targetAlbumList.GetNextItem(iterator);
	tempList = iterator.GetContentList();
	
	tempList->ResetList();
	for (int i = 0; i < tempList->GetLength(); i++) {
		string stringIterator;
		tempList->GetNextItem(stringIterator);
		resultList.Add(stringIterator);
	}

	for (int i = 1; i < targetAlbumList.GetLength(); i++) {
		targetAlbumList.GetNextItem(iterator);
		tempList = iterator.GetContentList();

		resultList.ResetList();
		for (int j = 0; j < resultList.GetLength(); j++) {
			string stringIterator;
			resultList.GetNextItem(stringIterator);
			if (!tempList->Get(stringIterator)) {
				resultList.Delete(stringIterator);
			}
		}
	}

	cout << "----------------------------------------" << endl;
	cout << "검색 결과" << endl;

	resultList.ResetList();
	for (int i = 0; i < resultList.GetLength(); i++) {
		string stringIterator;
		content contentIterator;

		resultList.GetNextItem(stringIterator);
		contentIterator.SetFilename(stringIterator);

		masterList.Get(contentIterator);
		contentIterator.Print();
	}
	cout << "----------------------------------------" << endl;
	cout << "총 " << resultList.GetLength() << "건의 검색 결과를 발견했습니다." << endl;
}

// crud functions
int application::AddContent() {
	content newContent;
	newContent.SetContentFromKB();

	// add on masterList
	if (!masterList.Add(newContent)) {
		return 0;
	}

	// add on eventAlbum
	album tempEventAlbum;
	tempEventAlbum.SetName(newContent.GetEvent());
	if (eventAlbumList.Get(tempEventAlbum)) {
		// 있는경우
		tempEventAlbum.GetContentList()->Add(newContent.GetFilename());
		eventAlbumList.Replace(tempEventAlbum);
	}
	else {
		// 앨범이 없는경우
		tempEventAlbum.SetMasterListPorinter(&masterList);
		tempEventAlbum.GetContentList()->Add(newContent.GetFilename());
		eventAlbumList.Add(tempEventAlbum);
	}

	// add on peopleAlbum
	// people need to split
	mySortedLinkedList<string> peopleList;
	istringstream ss(newContent.GetPeople());
	string stringBuffer;

	while (getline(ss, stringBuffer, ' ')) {
		peopleList.Add(stringBuffer);
	}

	peopleList.ResetList();
	for (int i = 0; i < peopleList.GetLength(); i++) {
		string tempPeopleName;
		peopleList.GetNextItem(tempPeopleName);

		// set album name as peopleList's element
		album tempPeopleAlbum;

		tempPeopleAlbum.SetName(tempPeopleName);

		if (peopleAlbumList.Get(tempPeopleAlbum)) {
			// 있는경우
			tempPeopleAlbum.GetContentList()->Add(newContent.GetFilename());
			peopleAlbumList.Replace(tempPeopleAlbum);
		}
		else {
			// 앨범이 없는경우
			tempPeopleAlbum.SetMasterListPorinter(&masterList);
			tempPeopleAlbum.GetContentList()->Add(newContent.GetFilename());
			peopleAlbumList.Add(tempPeopleAlbum);
		}
	}

	// add on placeAlbum
	album tempPlaceAlbum;
	tempPlaceAlbum.SetName(newContent.GetPlace());
	if (placeAlbumList.Get(tempPlaceAlbum)) {
		// 있는경우
		tempPlaceAlbum.GetContentList()->Add(newContent.GetFilename());
		placeAlbumList.Replace(tempPlaceAlbum);
	}
	else {
		// 앨범이 없는경우
		tempPlaceAlbum.SetMasterListPorinter(&masterList);
		tempPlaceAlbum.GetContentList()->Add(newContent.GetFilename());
		placeAlbumList.Add(tempPlaceAlbum);
	}

	// add on typeAlbum
	album tempTypeAlbum;
	string typeName;
	switch (newContent.GetType())
	{
	case 1:
		typeName = "Photo";
		break;
	case 2:
		typeName = "Video";
		break;
	case 3:
		typeName = "Panorama";
		break;
	default:
		typeName = "Unknown";
		break;
	}
	tempTypeAlbum.SetName(typeName);
	if (typeAlbumList.Get(tempTypeAlbum)) {
		// 있는경우
		tempTypeAlbum.GetContentList()->Add(newContent.GetFilename());
		typeAlbumList.Replace(tempTypeAlbum);
	}
	else {
		// 앨범이 없는경우
		tempTypeAlbum.SetMasterListPorinter(&masterList);
		tempTypeAlbum.GetContentList()->Add(newContent.GetFilename());
		typeAlbumList.Add(tempTypeAlbum);
	}

	// add on createdAtAlbum
	album tempCreatedAtAlbum;
	tempCreatedAtAlbum.SetName(newContent.GetCreatedAt());
	if (createdAtAlbumList.Get(tempCreatedAtAlbum)) {
		// 있는경우
		tempCreatedAtAlbum.GetContentList()->Add(newContent.GetFilename());
		createdAtAlbumList.Replace(tempCreatedAtAlbum);
	}
	else {
		// 앨범이 없는경우
		tempCreatedAtAlbum.SetMasterListPorinter(&masterList);
		tempCreatedAtAlbum.GetContentList()->Add(newContent.GetFilename());
		createdAtAlbumList.Add(tempCreatedAtAlbum);
	}
	
	return 1;
}

int application::DeleteContent() {
	content deleteContent;
	string deleteFilename;
	cout << "Type filename to delete : ";
	cin >> deleteFilename;

	deleteContent.SetFilename(deleteFilename);
	if (!masterList.Get(deleteContent)) {
		cout << "There is no item to delete" << endl;
		return 0;
	}

	album iterator;

	// delete on eventAlbumList
	eventAlbumList.ResetList();
	for (int i = 0; i < eventAlbumList.GetLength(); i++) {
		eventAlbumList.GetNextItem(iterator);
		if (iterator.GetContentList()->Delete(deleteContent.GetFilename())) {
			break;
		}
	}

	// delete on peopleAlbumList;
	// people list split
	mySortedLinkedList<string> peopleList;
	istringstream ss(deleteContent.GetPeople());
	string stringBuffer;

	while (getline(ss, stringBuffer, ' ')) {
		peopleList.Add(stringBuffer);
	}

	// find from peopleAlbumList
	peopleList.ResetList();
	for (int i = 0; i < peopleList.GetLength(); i++) {
		// get people name from peopleList
		string peopleIterator;
		peopleList.GetNextItem(peopleIterator);
	
		// find album and delete content
		peopleAlbumList.ResetList();
		for (int j = 0; j < peopleAlbumList.GetLength(); j++) {
			peopleAlbumList.GetNextItem(iterator);
			if (iterator.GetContentList()->Delete(deleteContent.GetFilename())) {
				break;
			}
		}
	}

	// delete on placeAlbumList
	placeAlbumList.ResetList();
	for (int i = 0; i < placeAlbumList.GetLength(); i++) {
		placeAlbumList.GetNextItem(iterator);
		if (iterator.GetContentList()->Delete(deleteContent.GetFilename())) {
			break;
		}
	}

	// delete on typeAlbumList;
	typeAlbumList.ResetList();

	for (int i = 0; i < typeAlbumList.GetLength(); i++) {
		typeAlbumList.GetNextItem(iterator);
		if (iterator.GetContentList()->Delete(deleteContent.GetFilename())) {
			break;
		}
	}

	// TODO : favorite reset

	// delete on masterList	
	masterList.Delete(deleteContent);

	return 1; 
}

int application::ReplaceContent() { 
	cout << "----------------------------------------" << endl;
	cout << "Type to change file name & properties" << endl;
	content replaceContent;
	replaceContent.SetContentFromKB();
	
	if (!masterList.Replace(replaceContent)) {
		cout << "There is no item to replace" << endl;
		return 0;
	}
	return 1;
}

int application::RetriveContent() { 
	cout << "----------------------------------------" << endl;
	cout << "Type to retrive content : ";
	string temp;
	cin >> temp;
	content retriveContent;
	retriveContent.SetFilename(temp);

	if (!masterList.Get(retriveContent)) {
		cout << "There is no item to retrive" << endl;
		return 0;
	}
	retriveContent.Print();
	return 1;
}

void application::ShowAllContents() {
	cout << "----------------------------------------" << endl;
	content iterator;
	masterList.ResetList();
	for (int i = 0; i < masterList.GetLength(); i++) {
		masterList.GetNextItem(iterator);
		iterator.Print();
	}
}

// album control functions
void application::showAlbums() {
	cout << "----------------------------------------" << endl;
	album iterator;
	
	eventAlbumList.ResetList();
	for (int i = 0; i < eventAlbumList.GetLength(); i++) {
		eventAlbumList.GetNextItem(iterator);
		iterator.Print();
	}

	peopleAlbumList.ResetList();
	for (int i = 0; i < peopleAlbumList.GetLength(); i++) {
		peopleAlbumList.GetNextItem(iterator);
		iterator.Print();
	}

	placeAlbumList.ResetList();
	for (int i = 0; i < placeAlbumList.GetLength(); i++) {
		placeAlbumList.GetNextItem(iterator);
		iterator.Print();
	}

	typeAlbumList.ResetList();
	for (int i = 0; i < typeAlbumList.GetLength(); i++) {
		typeAlbumList.GetNextItem(iterator);
		iterator.Print();
	}

	createdAtAlbumList.ResetList();
	for (int i = 0; i < createdAtAlbumList.GetLength(); i++) {
		createdAtAlbumList.GetNextItem(iterator);
		iterator.Print();
	}
}

// file input/output functions
int application::ReadDataFromFile() { 
	string input;
	ifstream in("masterList.txt");

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if (!in)	return 0;

	string inputSplit[8];

	while (getline(in, input))
	{
		content newContent;
		istringstream sstream(input);
		string stringBuffer;
		for (int i = 0; i < 8; i++) {
			getline(sstream, stringBuffer, ',');
			inputSplit[i] = stringBuffer;
		}
		
		newContent.SetContentAsParams(
			inputSplit[0],
			inputSplit[1],
			inputSplit[2],
			inputSplit[3],
			inputSplit[4],
			inputSplit[5],
			stoi(inputSplit[6]),
			stoi(inputSplit[7])
		);

		// add on masterList
		if (!masterList.Add(newContent)) {
			return 0;
		}

		// add on eventAlbum
		album tempEventAlbum;
		tempEventAlbum.SetName(newContent.GetEvent());
		if (eventAlbumList.Get(tempEventAlbum)) {
			// 있는경우
			tempEventAlbum.GetContentList()->Add(newContent.GetFilename());
			eventAlbumList.Replace(tempEventAlbum);
		}
		else {
			// 앨범이 없는경우
			tempEventAlbum.SetMasterListPorinter(&masterList);
			tempEventAlbum.GetContentList()->Add(newContent.GetFilename());
			eventAlbumList.Add(tempEventAlbum);
		}

		// add on peopleAlbum
		// people need to split
		mySortedLinkedList<string> peopleList;
		istringstream ss(newContent.GetPeople());

		while (getline(ss, stringBuffer, ' ')) {
			peopleList.Add(stringBuffer);
		}

		peopleList.ResetList();
		for (int i = 0; i < peopleList.GetLength(); i++) {
			// set album name as peopleList's element
			album tempPeopleAlbum;
			string tempPeopleName;
			peopleList.GetNextItem(tempPeopleName);
			tempPeopleAlbum.SetName(tempPeopleName);

			if (peopleAlbumList.Get(tempPeopleAlbum)) {
				// 있는경우
				tempPeopleAlbum.GetContentList()->Add(newContent.GetFilename());
				peopleAlbumList.Replace(tempPeopleAlbum);
			}
			else {
				// 앨범이 없는경우
				tempPeopleAlbum.SetMasterListPorinter(&masterList);
				tempPeopleAlbum.GetContentList()->Add(newContent.GetFilename());
				peopleAlbumList.Add(tempPeopleAlbum);
			}
		}

		// add on placeAlbum
		album tempPlaceAlbum;
		tempPlaceAlbum.SetName(newContent.GetPlace());
		if (placeAlbumList.Get(tempPlaceAlbum)) {
			// 있는경우
			tempPlaceAlbum.GetContentList()->Add(newContent.GetFilename());
			placeAlbumList.Replace(tempPlaceAlbum);
		}
		else {
			// 앨범이 없는경우
			tempPlaceAlbum.SetMasterListPorinter(&masterList);
			tempPlaceAlbum.GetContentList()->Add(newContent.GetFilename());
			placeAlbumList.Add(tempPlaceAlbum);
		}

		// add on typeAlbum
		album tempTypeAlbum;
		string typeName;
		switch (newContent.GetType())
		{
		case 1:
			typeName = "Photo";
			break;
		case 2:
			typeName = "Video";
			break;
		case 3:
			typeName = "Panorama";
			break;
		default:
			typeName = "Unknown";
			break;
		}
		tempTypeAlbum.SetName(typeName);
		if (typeAlbumList.Get(tempTypeAlbum)) {
			// 있는경우
			tempTypeAlbum.GetContentList()->Add(newContent.GetFilename());
			typeAlbumList.Replace(tempTypeAlbum);
		}
		else {
			// 앨범이 없는경우
			tempTypeAlbum.SetMasterListPorinter(&masterList);
			tempTypeAlbum.GetContentList()->Add(newContent.GetFilename());
			typeAlbumList.Add(tempTypeAlbum);
		}

		// add on createdAtAlbum
		album tempCreatedAtAlbum;
		tempCreatedAtAlbum.SetName(newContent.GetCreatedAt());
		if (createdAtAlbumList.Get(tempCreatedAtAlbum)) {
			// 있는경우
			tempCreatedAtAlbum.GetContentList()->Add(newContent.GetFilename());
			createdAtAlbumList.Replace(tempCreatedAtAlbum);
		}
		else {
			// 앨범이 없는경우
			tempCreatedAtAlbum.SetMasterListPorinter(&masterList);
			tempCreatedAtAlbum.GetContentList()->Add(newContent.GetFilename());
			createdAtAlbumList.Add(tempCreatedAtAlbum);
		}

	}
	in.close();
	return 1;
}
int application::WriteDataToFile() {
	string output;
	ofstream out("masterList.txt");
	if (!out) {
		cout << "cannot open file" << endl;
		return 0;
	}
	content iterator;
	masterList.ResetList();
	for (int i = 0; i < masterList.GetLength(); i++) {
		masterList.GetNextItem(iterator);
		output = iterator.GetFilename() + ","
			+ iterator.GetDescription() + ","
			+ iterator.GetEvent() + ","
			+ iterator.GetPeople() + ","
			+ iterator.GetPlace() + ","
			+ iterator.GetCreatedAt() + ","
			+ to_string(iterator.GetType()) + ","
			+ to_string(iterator.GetSearchCount());

		out << output << endl;
	}

	out.close();
	return 1;
}