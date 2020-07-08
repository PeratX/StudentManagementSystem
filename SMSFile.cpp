#include "pch.h"
#include "SMSFile.h"

IMPLEMENT_SERIAL(SMSFile, CObject, 0531)

void SMSFile::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << int(subjects.size());
		for (auto s : subjects)
		{
			ar << s.second.num << s.second.name;
		}

		ar << int(students.size());
		for (auto s : students)
		{
			ar << s.second.name << s.second.num << s.second.credit << int(s.second.subjects.size());
			for (auto i : s.second.subjects)
			{
				ar << i.second.sub->num << i.second.mark;
			}
		}
	}
	else
	{
		int count;
		ar >> count;
		for (auto i = 0; i < count; i++)
		{
			Subject sub;
			ar >> sub.num >> sub.name;
			subjects.insert(pair<int32_t, Subject>(sub.num, sub));
		}
		ar >> count;

		for (auto i = 0; i < count; i++)
		{
			Student stu;
			int cnt;
			ar >> stu.name >> stu.num >> stu.credit >> cnt;
			for (auto j = 0; j < cnt; j++)
			{
				int32_t subNum;
				SubjectInfo info;
				ar >> subNum >> info.mark;
				info.sub = &subjects[subNum];
				stu.subjects.insert(pair<int32_t, SubjectInfo>(subNum, info));
			}
			students.insert(pair<int64_t, Student>(stu.num, stu));
		}
	}
}

void SMSFile::Open(CString p)
{
	path = p;
	fileOpened = true;
	Load();
}


void SMSFile::Load()
{
	if (fileOpened)
	{
		CFile file;
		file.Open(path, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}

void SMSFile::Save()
{
	if (fileOpened)
	{
		CFile file;
		file.Open(path, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		Serialize(ar);
		ar.Close();
		file.Close();
	}
}


CString SMSFile::addSubject(Subject sub)
{
	if (subjects.find(sub.num) == subjects.end())
	{
		if (sub.num < 10000 || sub.num > 99999)
		{
			return _T("非法的课程序号");
		}
		subjects[sub.num] = sub;
		Save();
		return _T("课程添加成功！");
	}
	return _T("已有相同课程!");
}

CString SMSFile::delSubject(int32_t num)
{
	for (auto s : students)
	{
		if (s.second.subjects.find(num) != s.second.subjects.end())
		{
			CString msg;
			msg.Format(_T("学号为 %lld 的学生仍然加入了该课程，无法删除课程！"), s.second.num);
			return msg;
		}
	}
	subjects.erase(num);
	Save();
	return _T("课程已删除。");
}

CString SMSFile::addStudent(Student student)
{
	if (students.find(student.num) == students.end())
	{
		if (student.num < 10000000 || student.num > 99999999)
		{
			return _T("非法的学号");
		}
		students[student.num] = student;
		Save();
		return _T("学生已添加");
	}
	return _T("该学号已存在");
}


CString SMSFile::delStudent(int64_t num)
{
	students.erase(num);
	Save();
	return _T("已删除该学生");
}

Student* SMSFile::getStudent(int64_t num)
{
	if (students.find(num) == students.end())
	{
		return nullptr;
	}
	return &students[num];
}
