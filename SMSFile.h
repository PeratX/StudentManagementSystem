#pragma once
#include "pch.h"
#include <map>

using namespace std;

//懒得用SQLite

struct Subject //课程
{
	int32_t num;//序号
	CString name;//名称
};

struct SubjectInfo
{
	Subject sub;
	int32_t mark;
	double credit;
};

struct Student
{
	int64_t num;
	CString name;
	map<int32_t, SubjectInfo> subjects = {};
};

class SMSFile : public CObject
{
	DECLARE_SERIAL(SMSFile)
public:
	virtual void Serialize(CArchive& ar) override;
	map<int64_t, Student> students;
	map<int32_t, Subject> subjects;
	CString addSubject(Subject);
	CString delSubject(int32_t);
	CString addStudent(Student);
	CString delStudent(int64_t);
	Student* getStudent(int64_t);
	CString path;
	bool fileOpened = false;
	void Save();
	void Load();
	void Open(CString);
};

