#pragma once
#include "pch.h"
#include <map>

using namespace std;

//������SQLite

struct Subject //�γ�
{
	int32_t num;//���
	CString name;//����
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
	CString addSubject(Subject sub);
	CString delSubject(int32_t num);
	CString addStudent(Student student);
	CString delStudent(int64_t num);
	Student* getStudent(int64_t num);
};
