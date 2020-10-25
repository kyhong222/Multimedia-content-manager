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
		//cout << "11. create dataSet(only for develop)" << endl;
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
		/*case 11:
			createDataSet();
			break;*/
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
	
	// 키워드를 입력받음
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

	// 관련 앨범을 담을 targetAlbumList 선언
	mySortedLinkedList<album> targetAlbumList;
	album iterator;	// 앨범의 이터레이터(더미 역할)

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
	mySortedLinkedList<string> tempList;
	
	// 일치 앨범이 없는 경우 예외처리
	if (!targetAlbumList.GetLength()) {
		cout << "----------------------------------------" << endl;
		cout << "검색 결과가 없습니다." << endl;
		return;
	}

	// 앨범 리스트에서 순차적으로 돌며 리스트 생성 시작
	targetAlbumList.ResetList();
	
	targetAlbumList.GetNextItem(iterator);
	
	// 첫 연관 앨범을 resultList에 복사하고, 그 다음부터는 교집합을 구한다.
	// tempList에 iterator의 list를 깊은복사
	iterator.GetContentList()->ResetList();
	for (int i = 0; i < iterator.GetContentList()->GetLength(); i++) {
		string dummy;
		iterator.GetContentList()->GetNextItem(dummy);
		tempList.Add(dummy);
	}
	
	// resultList에 tempList 복사.
	tempList.ResetList();
	for (int i = 0; i < tempList.GetLength(); i++) {
		string stringIterator;
		tempList.GetNextItem(stringIterator);
		resultList.Add(stringIterator);
	}

	// 그 다음 앨범부터는 교집합을 구함.
	for (int i = 1; i < targetAlbumList.GetLength(); i++) {
		targetAlbumList.GetNextItem(iterator);
		resultList.MakeEmpty();
		
		// tempList와 iterator.getContentList의 교집합을 resultList에 추가
		int p1 = 0, p2 = 0;
		//mySortedLinkedList<string> temp2List = *(iterator.GetContentList());
		mySortedLinkedList<string> temp2List;
		temp2List = *(iterator.GetContentList());
		int temp1Length = tempList.GetLength();
		int temp2Length = temp2List.GetLength();
		tempList.ResetList();
		temp2List.ResetList();
		string item1, item2;
		tempList.GetNextItem(item1);
		temp2List.GetNextItem(item2);
		while (p1 < temp1Length && p2 < temp2Length) {
			if (item1 < item2) {
				tempList.GetNextItem(item1);
				p1++;
			}
			else if (item1 > item2) {
				temp2List.GetNextItem(item2);
				p2++;
			}
			else {
				resultList.Add(item1);
				tempList.GetNextItem(item1);
				temp2List.GetNextItem(item2);
				p1++;
				p2++;
			}
		}

		// result엘범에 교집합 결과를 다시 담아줌
		resultList.ResetList();
		for (int i = 0; i < resultList.GetLength(); i++) {
			string stringIterator;
			resultList.GetNextItem(stringIterator);
			tempList.Add(stringIterator);
		}
		
		
	}

	// 검색결과 출력부
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

int application::AddContent() {
	content newContent;
	newContent.SetContentFromKB();

	// add on masterList
	if (!masterList.Add(newContent)) {
		return 0;
	}

	insertOnAlbums(newContent);

	/*
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
	*/
	return 1;
}

int application::DeleteContent() {
	// 지울 컨텐츠를 입력받음
	content deleteContent;
	string deleteFilename;
	cout << "Type filename to delete : ";
	cin >> deleteFilename;

	// 지우려는 컨텐츠가 없을시 예외처리
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
			eventAlbumList.Replace(iterator);
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
				peopleAlbumList.Replace(iterator);
				break;
			}
		}
	}

	// delete on placeAlbumList
	placeAlbumList.ResetList();
	for (int i = 0; i < placeAlbumList.GetLength(); i++) {
		placeAlbumList.GetNextItem(iterator);
		if (iterator.GetContentList()->Delete(deleteContent.GetFilename())) {
			placeAlbumList.Replace(iterator);
			break;
		}
	}

	// delete on typeAlbumList;
	typeAlbumList.ResetList();

	for (int i = 0; i < typeAlbumList.GetLength(); i++) {
		typeAlbumList.GetNextItem(iterator);
		if (iterator.GetContentList()->Delete(deleteContent.GetFilename())) {
			typeAlbumList.Replace(iterator);
			break;
		}
	}

	// delete on createdAtAlbumList;
	createdAtAlbumList.ResetList();

	for (int i = 0; i < createdAtAlbumList.GetLength(); i++) {
		createdAtAlbumList.GetNextItem(iterator);
		if (iterator.GetContentList()->Delete(deleteContent.GetFilename())) {
			createdAtAlbumList.Replace(iterator);
			break;
		}
	}

	// delete on masterList	
	cout << endl << deleteContent.GetFilename() << " has deleted." << endl;
	masterList.Delete(deleteContent);
	
	return 1; 
}

int application::ReplaceContent() { 
	// 대체할 컨텐츠를 입력받음
	cout << "----------------------------------------" << endl;
	cout << "Type to change file name & properties" << endl;
	content replaceContent;
	replaceContent.SetContentFromKB();
	
	// 대체할 원본 컨텐츠 없을때 예외처리 및 replace 수행
	if (!masterList.Replace(replaceContent)) {
		cout << "There is no item to replace" << endl;
		return 0;
	}
	return 1;
}

int application::RetriveContent() { 
	// 검색할 컨텐츠 입력받기
	cout << "----------------------------------------" << endl;
	cout << "Type to retrive content : ";
	string temp;
	cin >> temp;
	content retriveContent;
	retriveContent.SetFilename(temp);

	// 있으면 출력, 없으면 예외처리
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
		newContent.Print();

		insertOnAlbums(newContent);


		//// add on eventAlbum
		//album tempEventAlbum;
		//tempEventAlbum.SetName(newContent.GetEvent());
		//if (eventAlbumList.Get(tempEventAlbum)) {
		//	// 있는경우
		//	tempEventAlbum.GetContentList()->Add(newContent.GetFilename());
		//	eventAlbumList.Replace(tempEventAlbum);
		//}
		//else {
		//	// 앨범이 없는경우
		//	tempEventAlbum.SetMasterListPorinter(&masterList);
		//	tempEventAlbum.GetContentList()->Add(newContent.GetFilename());
		//	eventAlbumList.Add(tempEventAlbum);
		//}

		//// add on peopleAlbum
		//// people need to split
		//mySortedLinkedList<string> peopleList;
		//istringstream ss(newContent.GetPeople());

		//while (getline(ss, stringBuffer, ' ')) {
		//	peopleList.Add(stringBuffer);
		//}

		//peopleList.ResetList();
		//for (int i = 0; i < peopleList.GetLength(); i++) {
		//	// set album name as peopleList's element
		//	album tempPeopleAlbum;
		//	string tempPeopleName;
		//	peopleList.GetNextItem(tempPeopleName);
		//	tempPeopleAlbum.SetName(tempPeopleName);

		//	if (peopleAlbumList.Get(tempPeopleAlbum)) {
		//		// 있는경우
		//		tempPeopleAlbum.GetContentList()->Add(newContent.GetFilename());
		//		peopleAlbumList.Replace(tempPeopleAlbum);
		//	}
		//	else {
		//		// 앨범이 없는경우
		//		tempPeopleAlbum.SetMasterListPorinter(&masterList);
		//		tempPeopleAlbum.GetContentList()->Add(newContent.GetFilename());
		//		peopleAlbumList.Add(tempPeopleAlbum);
		//	}
		//}

		//// add on placeAlbum
		//album tempPlaceAlbum;
		//tempPlaceAlbum.SetName(newContent.GetPlace());
		//if (placeAlbumList.Get(tempPlaceAlbum)) {
		//	// 있는경우
		//	tempPlaceAlbum.GetContentList()->Add(newContent.GetFilename());
		//	placeAlbumList.Replace(tempPlaceAlbum);
		//}
		//else {
		//	// 앨범이 없는경우
		//	tempPlaceAlbum.SetMasterListPorinter(&masterList);
		//	tempPlaceAlbum.GetContentList()->Add(newContent.GetFilename());
		//	placeAlbumList.Add(tempPlaceAlbum);
		//}

		//// add on typeAlbum
		//album tempTypeAlbum;
		//string typeName;
		//switch (newContent.GetType())
		//{
		//case 1:
		//	typeName = "Photo";
		//	break;
		//case 2:
		//	typeName = "Video";
		//	break;
		//case 3:
		//	typeName = "Panorama";
		//	break;
		//default:
		//	typeName = "Unknown";
		//	break;
		//}
		//tempTypeAlbum.SetName(typeName);
		//if (typeAlbumList.Get(tempTypeAlbum)) {
		//	// 있는경우
		//	tempTypeAlbum.GetContentList()->Add(newContent.GetFilename());
		//	typeAlbumList.Replace(tempTypeAlbum);
		//}
		//else {
		//	// 앨범이 없는경우
		//	tempTypeAlbum.SetMasterListPorinter(&masterList);
		//	tempTypeAlbum.GetContentList()->Add(newContent.GetFilename());
		//	typeAlbumList.Add(tempTypeAlbum);
		//}

		//// add on createdAtAlbum
		//album tempCreatedAtAlbum;
		//tempCreatedAtAlbum.SetName(newContent.GetCreatedAt());
		//if (createdAtAlbumList.Get(tempCreatedAtAlbum)) {
		//	// 있는경우
		//	tempCreatedAtAlbum.GetContentList()->Add(newContent.GetFilename());
		//	createdAtAlbumList.Replace(tempCreatedAtAlbum);
		//}
		//else {
		//	// 앨범이 없는경우
		//	tempCreatedAtAlbum.SetMasterListPorinter(&masterList);
		//	tempCreatedAtAlbum.GetContentList()->Add(newContent.GetFilename());
		//	createdAtAlbumList.Add(tempCreatedAtAlbum);
		//}

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

int application::insertOnAlbums(content newContent) {

	album albumIt;
	bool found = false;

	// event
	eventAlbumList.ResetList();
	for (int i = 0; i < eventAlbumList.GetLength(); i++) {
		eventAlbumList.GetNextItem(albumIt);
		if (albumIt.GetName() == newContent.GetEvent()) {
			albumIt.GetContentList()->Add(newContent.GetFilename());
			eventAlbumList.Replace(albumIt);
			found = true;
			break;
		}
	}
	if (!found) {
		albumIt.SetName(newContent.GetEvent());
		albumIt.SetDescription("none");
		albumIt.SetMasterListPorinter(&masterList);
		albumIt.GetContentList()->MakeEmpty();
		albumIt.GetContentList()->Add(newContent.GetFilename());
		eventAlbumList.Add(albumIt);
	}

	// reset flag
	found = false;	

	// people
	// people string split
	mySortedLinkedList<string> peopleList;
	istringstream ss(newContent.GetPeople());
	string stringBuffer;
	while (getline(ss, stringBuffer, ' ')) {
		peopleList.Add(stringBuffer);
	}

	peopleList.ResetList();
	string peopleDummy;
	for (int i = 0; i < peopleList.GetLength(); i++) {
		peopleList.GetNextItem(peopleDummy);
		peopleAlbumList.ResetList();
		
		for (int j = 0; j < peopleAlbumList.GetLength(); j++) {
			peopleAlbumList.GetNextItem(albumIt);
			if (albumIt.GetName() == peopleDummy) {
				albumIt.GetContentList()->Add(newContent.GetFilename());
				found = true;
				break;
			}
		}
		if (!found) {
			albumIt.SetName(peopleDummy);
			albumIt.SetDescription("none");
			albumIt.SetMasterListPorinter(&masterList);
			albumIt.GetContentList()->MakeEmpty();
			albumIt.GetContentList()->Add(newContent.GetFilename());
			peopleAlbumList.Add(albumIt);
		}

		// reset flag
		found = false;
	}
	
	

	//// add on peopleAlbum
		//// people need to split
		//mySortedLinkedList<string> peopleList;
		//istringstream ss(newContent.GetPeople());

		//while (getline(ss, stringBuffer, ' ')) {
		//	peopleList.Add(stringBuffer);
		//}

		//peopleList.ResetList();
		//for (int i = 0; i < peopleList.GetLength(); i++) {
		//	// set album name as peopleList's element
		//	album tempPeopleAlbum;
		//	string tempPeopleName;
		//	peopleList.GetNextItem(tempPeopleName);
		//	tempPeopleAlbum.SetName(tempPeopleName);

		//	if (peopleAlbumList.Get(tempPeopleAlbum)) {
		//		// 있는경우
		//		tempPeopleAlbum.GetContentList()->Add(newContent.GetFilename());
		//		peopleAlbumList.Replace(tempPeopleAlbum);
		//	}
		//	else {
		//		// 앨범이 없는경우
		//		tempPeopleAlbum.SetMasterListPorinter(&masterList);
		//		tempPeopleAlbum.GetContentList()->Add(newContent.GetFilename());
		//		peopleAlbumList.Add(tempPeopleAlbum);
		//	}
		//}

	// place

	// type

	// createdAt

	return 1;
}

void application::createDataSet() {
	/*
		content
			filename => img001, 002, 003 ...
			description => all is none
			event => izone's appearence
			people	=> izone member
			place	=> KBS, MBC, SBS, MNET
			createdAt => izone's appearence

			type => 70% photo 20% video 10% panorama
			searchCount	=> 0~9999
	*/

	//srand(time(NULL));

	string schedule[29] = {
		"0220 FIESTA MNET",
		"0221 FIESTA KBS",
		"0222 FIESTA MBC",
		"0223 FIESTA SBS",
		"0225 FIESTA SBS",
		"0226 FIESTA MBC",
		"0227 FIESTA MNET",
		"0301 FIESTA SBS",
		"0303 FIESTA SBS",
		"0304 FIESTA MBC",
		"0305 FIESTA MNET",
		"0307 FIESTA MBC",
		"0308 FIESTA SBS",
		"0618 환상동화 MNET",
		"0619 환상동화 KBS",
		"0620 환상동화 MBC",
		"0621 환상동화 SBS",
		"0623 환상동화 SBS",
		"0624 환상동화 MBC",
		"0625 환상동화 MNET",
		"0626 환상동화 KBS",
		"0627 환상동화 MBC",
		"0628 환상동화 SBS",
		"0630 환상동화 SBS",
		"0701 환상동화 MBC",
		"0702 환상동화 SBS",
		"0703 환상동화 KBS",
		"0704 환상동화 MBC",
		"0705 환상동화 MNET"
	};
	string members[12] = {
		"권은비",
		"사쿠라",
		"강혜원",
		"최예나",
		"이채연",
		"김채원",
		"김민주",
		"나코",
		"히토미",
		"조유리",
		"안유진",
		"장원영"
	};

	int pictures[29];
	for (int i = 0; i < 29; i++) {
		pictures[i] = rand() % 30 + 1;
	}

	int peoplenumbers[5] = { 1,2,3,6,12 };


	int makePicture = 0;
	for (int i = 0; i < 29; i++) {
		makePicture += pictures[i];
	}
	
	int eventCounter = 0;
	int pictureCounter = 0;

	//makePicture = 50;

	for (int i = 0; i < makePicture; i++) {
		content newContent;
		
		// filename
		string filename;
		if (i == 1000) {
			filename = "1000";
		}
		else if (i >= 99) {
			// 0100~0999
			filename = "0" + to_string(i + 1);
		}
		else if (i >= 9) {
			filename = "00" + to_string(i + 1);
		}
		else {
			filename = "000" + to_string(i+1);
		}

		filename = "img" + filename;

		// description
		string description = "none";

		// split schedule
		pictureCounter++;
		if (pictureCounter > pictures[eventCounter]) {
			eventCounter++;
			pictureCounter = 0;
		}
	
		string splitSchedule[3];
		istringstream sstream(schedule[eventCounter]);
		string stringBuffer;

		for (int j = 0; j < 3; j++) {
			getline(sstream, stringBuffer, ' ');
			splitSchedule[j] = stringBuffer;
		}
		
		// event
		string eventName = splitSchedule[1];

		// peoples
		int numOfPeople = peoplenumbers[rand() % 5];
		int* memIdx = new int[numOfPeople];
		for (int j = 0; j < numOfPeople; j++) {
			memIdx[j] = rand() % 12;
			for (int k = 0; k < j; k++) {
				if (memIdx[j] == memIdx[k]) {
					j--;
					break;
				}
			}
		}

		mySortedLinkedList<string> sortPeople;
		for (int j = 0; j < numOfPeople; j++) {
			sortPeople.Add(members[memIdx[j]]);
		}


		string people, peopleDummy;
		sortPeople.ResetList();

		sortPeople.GetNextItem(peopleDummy);
		people = peopleDummy;
		for (int j = 1; j < numOfPeople; j++) {
			people += " ";
			sortPeople.GetNextItem(peopleDummy);
			people += peopleDummy;
		}

		// place
		string place = splitSchedule[2];

		// createdAt
		string createdAt = "2020" + splitSchedule[0];
		
		//type
		int typeP = rand() % 100;
		int type;
		if (typeP < 70) {
			type = 1;
		}
		else if (typeP < 90) {
			type = 2;
		}
		else {
			type = 3;
		}

		// searchCount;
		int searchCount = rand() % 10000;

		newContent.SetContentAsParams(filename, description, eventName, people, place, createdAt, type, searchCount);

		// add on masterList
		if (!masterList.Add(newContent)) {
			continue;
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
	}

}
