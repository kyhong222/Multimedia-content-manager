#pragma once
#include<iostream>
#include<string>

using namespace std;

class content {
public:
	// constructor
	content();

	// destructor
	~content();

	// getter & setters
	string GetFilename() { return filename; }
	string GetDescription() { return description; }
	string GetEvent() { return this->event; }
	string GetPeople() { return people; }
	string GetPlace() { return place; }
	string GetCreatedAt() { return createdAt; }

	int GetType() { return type; }
	int GetSearchCount() { return searchCount; }

	void SetFilename(string filename) { this->filename = filename; }
	
	void SetContentAsParams(string fn, string dsc, string evt, string pp, string pl, string crt, int ty, int sc) {
		filename = fn;
		description = dsc;
		this->event = evt;
		people = pp;
		place = pl;
		createdAt = crt;
		type = ty;
		searchCount = sc;
	}


	// general functions
	void Print();
	void SetContentFromKB();
	void SetContent(content item);
	void IncreaseSearchCount();

	// operator overloading functions to use data structure
	bool operator < (const content& data);
	bool operator == (const content& data);


private:
	string filename;
	string description;
	string event;
	string people;
	string place;
	string createdAt;

	int type;
	int searchCount;
};
