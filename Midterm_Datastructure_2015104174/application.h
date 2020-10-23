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
	
	/*
	@pre 앨범들이 앨범리스트에 있어야함
	@params 앨범의 이름을 cin으로 받음
	@return	이름을 받은 앨범들의 교집합을 반환
	*/
	void AdvancedSearch();

	// crud functions
	/*
	@brief 컨텐츠 레코드를 생성후 컨텐츠 리스트와 앨범리스트에 삽입
	@post 컨텐츠 리스트에 집어넣은 뒤, 컨텐츠의 멤버변수를 따라 알맞은 앨범리스트에 삽입
	*/
	int AddContent();

	/*
	@pre 컨텐츠가 있어야함
	@params 지울 컨텐츠를 입력받음
	@post 입력받은 컨텐츠를 컨텐츠 리스트와, 속해있던 앨범들에서 지움
	*/
	int DeleteContent();

	/*
	@pre 컨텐츠가 있어야함
	@params 수정할 컨텐츠를 입력받음
	@post 입력받은 컨텐츠를 바탕으로 이름이 일치하는 컨텐츠를 찾아서, 입력받은 컨텐츠로 대체함
	*/
	int ReplaceContent();

	/*
	@pre 컨텐츠가 있어야함
	@params 찾을 컨텐츠 이름을 입력받음
	@post 찾은 컨텐츠를 출력함.
	*/
	int RetriveContent();

	/*
	@pre 컨텐츠가 있어야함
	@post 모든 컨텐츠를 출력함.
	*/
	void ShowAllContents();

	/*
	@pre 앨범이 있어야함
	@post 모든 앨범을 출력함.
	*/
	void showAlbums();

	// file input/output functions
	/*
	@brief 파일로부터 컨텐츠를 받아옴
	@post 파일로부터 컨텐츠를 받아와 앨범과 컨텐츠리스트에 삽입
	*/
	int ReadDataFromFile();

	/*
	@brief 파일로 컨텐츠를 출력함
	@post 컨텐츠리스트로부터 컨텐츠를 파일로 내보내서 저장됨
	*/
	int WriteDataToFile();

	/*
	@brief 개발용 데이터셋 생성 함수
	@post 랜덤변수에 의해 적절한 양의 데이터가 생성됨
	*/
	void createDataSet();

private:
	mySortedArrayList<content> masterList;			// 컨텐츠리스트
	favorites favoriteList;							// 즐겨찾기, 검색순으로 10위까지 담고있음
	mySortedLinkedList<album> eventAlbumList;		// content.event 관련 앨범 리스트
	mySortedLinkedList<album> peopleAlbumList;		// content.people 관련 앨범 리스트
	mySortedLinkedList<album> placeAlbumList;		// content.place 관련 앨범 리스트
	mySortedLinkedList<album> typeAlbumList;		// content.type 관련 앨범 리스트
	mySortedLinkedList<album> createdAtAlbumList;	// content.createdAt 관련 앨범 리스트
};
