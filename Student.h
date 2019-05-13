#pragma once
#include<string>
#include<memory>
#include<iostream>
#include<vector>
#include "Course.h"
#include "courses_manager.h"
#include "students_manager.h"
#include "assignment_manager.h"
#include "system_flow.h"
#include "doctors_manager.h"

using namespace std;


namespace ES{
	class assignment;

	class Student
	{
	public:
		Student();
		Student(const Student &st);
		Student(string a, string b, string c, string d,string e);
		string first_name, last_name, email, id,password;
		vector<shared_ptr<Course>> registered_courses;
		void show_registered_courses();
		void Menu();
		void Register_new_course();
		void unregister_from_course(string _course_code);
		void view_student_course_inf();
	};

}