#pragma once
#include<vector>
#include<memory>
using namespace std;



namespace ES{
	class Course;

	class courses_manager
	{
	public:
		courses_manager();
		vector<shared_ptr<Course>> _courses;

	};
	extern shared_ptr<courses_manager> _courses_manager;
}