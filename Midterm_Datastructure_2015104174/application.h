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
	@pre �ٹ����� �ٹ�����Ʈ�� �־����
	@params �ٹ��� �̸��� cin���� ����
	@return	�̸��� ���� �ٹ����� �������� ��ȯ
	*/
	void AdvancedSearch();

	// crud functions
	/*
	@brief ������ ���ڵ带 ������ ������ ����Ʈ�� �ٹ�����Ʈ�� ����
	@post ������ ����Ʈ�� ������� ��, �������� ��������� ���� �˸��� �ٹ�����Ʈ�� ����
	*/
	int AddContent();

	/*
	@pre �������� �־����
	@params ���� �������� �Է¹���
	@post �Է¹��� �������� ������ ����Ʈ��, �����ִ� �ٹ��鿡�� ����
	*/
	int DeleteContent();

	/*
	@pre �������� �־����
	@params ������ �������� �Է¹���
	@post �Է¹��� �������� �������� �̸��� ��ġ�ϴ� �������� ã�Ƽ�, �Է¹��� �������� ��ü��
	*/
	int ReplaceContent();

	/*
	@pre �������� �־����
	@params ã�� ������ �̸��� �Է¹���
	@post ã�� �������� �����.
	*/
	int RetriveContent();

	/*
	@pre �������� �־����
	@post ��� �������� �����.
	*/
	void ShowAllContents();

	/*
	@pre �ٹ��� �־����
	@post ��� �ٹ��� �����.
	*/
	void showAlbums();

	// file input/output functions
	/*
	@brief ���Ϸκ��� �������� �޾ƿ�
	@post ���Ϸκ��� �������� �޾ƿ� �ٹ��� ����������Ʈ�� ����
	*/
	int ReadDataFromFile();

	/*
	@brief ���Ϸ� �������� �����
	@post ����������Ʈ�κ��� �������� ���Ϸ� �������� �����
	*/
	int WriteDataToFile();

	/*
	@brief ���߿� �����ͼ� ���� �Լ�
	@post ���������� ���� ������ ���� �����Ͱ� ������
	*/
	void createDataSet();

private:
	mySortedArrayList<content> masterList;			// ����������Ʈ
	favorites favoriteList;							// ���ã��, �˻������� 10������ �������
	mySortedLinkedList<album> eventAlbumList;		// content.event ���� �ٹ� ����Ʈ
	mySortedLinkedList<album> peopleAlbumList;		// content.people ���� �ٹ� ����Ʈ
	mySortedLinkedList<album> placeAlbumList;		// content.place ���� �ٹ� ����Ʈ
	mySortedLinkedList<album> typeAlbumList;		// content.type ���� �ٹ� ����Ʈ
	mySortedLinkedList<album> createdAtAlbumList;	// content.createdAt ���� �ٹ� ����Ʈ
};
