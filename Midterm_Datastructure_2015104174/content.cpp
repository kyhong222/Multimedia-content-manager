#pragma once
#include"content.h"

// constructor
content::content() {
	filename = "";
	description = "none";
	event = "";
	people = "none";
	place = "";
	createdAt = "";

	type = 0;
	searchCount = 0;
}

// destructor
content::~content() {}

// general functions
void content::Print() {
	cout << "----------------------------------------" << endl;
	cout << "name : " << filename << endl;
	if(description != "none") cout << "description : " << description << endl;
	cout << "event : " << this->event << endl;
	if (people != "none") cout << "people : " << people << endl;
	cout << "place : " << place << endl;
	cout << "createdAt : " << createdAt << endl;
	cout << "type : ";
	switch (type){
		case 1:
			cout << "Photo" << endl;
			break;
		case 2:
			cout << "Video" << endl;
			break;
		case 3:
			cout << "Panorama" << endl;
			break;
		default:
			cout << "Unknown" << endl;
			break;
	}

	searchCount++;
}
void content::SetContentFromKB() {
	string inputName, inputDescription, inputEvent, inputPeople, inputPlace, inputCreatedAt;
	int inputType;

	cout << "Input filename : ";
	cin >> inputName;

	cout << "Input description : ";
	//cin >> inputDescription;
	cin.ignore();
	getline(cin, inputDescription);
	if (inputDescription == "") inputDescription = "none";

	cout << "Input event : ";
	cin >> inputEvent;

	cout << "Input people(여러사람을 입력할때, 스페이스바를 이용하십시오) : ";
	cin.ignore();
	getline(cin, inputPeople);
	if (inputPeople == "") inputPeople = "none";

	cout << "Input place : ";
	cin >> inputPlace;

	cout << "Input created at(ex: 20200101) : ";
	cin >> inputCreatedAt;

	cout << "Input type(1.Photo 2.Video 3.panorama) : ";
	cin >> inputType;

	filename = inputName;
	description = inputDescription;
	this->event = inputEvent;
	people = inputPeople;
	place = inputPlace;
	createdAt = inputCreatedAt;
	type = inputType;

	this->Print();
}

void content::SetContent(content item) {
	filename = item.filename;
	description = item.description;
	event = item.event;
	people = item.people;
	place = item.place;
	createdAt = item.createdAt;
	type = item.type;
	searchCount = item.searchCount;
}
void content::IncreaseSearchCount() {
	searchCount++;
}

// operator overloading functions to use data structure
bool content::operator < (const content& data) {
	if (this->filename < data.filename)	return true;
	return false;
}
bool content::operator == (const content& data) {
	if (this->filename == data.filename) return true;
	return false;
}

