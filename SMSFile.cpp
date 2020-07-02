#include "pch.h"
#include "SMSFile.h"

IMPLEMENT_SERIAL(SMSFile, CObject, 0531)

void SMSFile::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar << int(subjects.size());
		for(auto s : subjects)
		{
			ar << s.second.num << s.second.name;
		}
		
		ar << int(students.size());
		for(auto s : students)
		{
			ar << s.second.name << s.second.num << int(s.second.subjects.size());
			for(auto i : s.second.subjects)
			{
				ar << i.second.sub.num << i.second.mark << i.second.credit;
			}
		}
	} else
	{
		int count;
		ar >> count;
		for(auto i = 0;i < count; i++)
		{
			int32_t num;
			CString name;
			ar >> num >> name;
			subjects[num] = { num, name };
		}
		ar >> count;

		for (auto i = 0; i < count; i++)
		{
			int64_t num;
			CString name;
			int cnt;
			ar >> name >> num >> cnt;
			map<int, SubjectInfo> info;
			for(auto j = 0; j < cnt; j++)
			{
				int32_t subNum;
				int32_t mark;
				double credit;
				ar >> subNum >> mark >> credit;
				info[subNum] = { subjects[subNum], mark, credit };
			}
			students[num] = { num, name ,info };
		}
	}
}

CString SMSFile::addSubject(Subject sub)
{
	if(subjects.find(sub.num) == subjects.end())
	{
		subjects[sub.num] = sub;
		return _T("课程添加成功！");
	}
	return _T("已有相同课程!");
}

CString SMSFile::delSubject(int32_t num)
{
	for(auto s : students)
	{
		if (s.second.subjects.find(num) != s.second.subjects.end())
		{
			CString msg;
			msg.Format(_T("学号为 %lld 的学生仍然加入了该课程，无法删除课程！"), s.second.num);
			return msg;
		}
	}
	return _T("课程已删除。");
}

CString SMSFile::addStudent(Student student)
{
	if(students.find(student.num) == students.end())
	{
		students[student.num] = student;
		return _T("学生已添加");
	}
	return _T("该学号已存在");
}


CString SMSFile::delStudent(int64_t num)
{
	students.erase(num);
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

