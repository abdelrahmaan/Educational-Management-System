#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<memory>
#include "Doctor.h"

using namespace std;


namespace ES{
	class Student;
	class assignment_manager;

	class Course
	{
	public:
		Course();
		Course(string a, string b, string c);
		string course_name, course_code, course_doctor;
		
		void show_registered_students();
		void view_student_course_inf(string cur_student_id);
		void view_doctor_course_inf();
		void list_course_assignment();
		void add_assignment();
		void select_assignment();

		// To-Do Teaching assistant
		vector<shared_ptr<assignment_manager>> course_assignments;
		vector<shared_ptr<Student>> registered_students;
	};
}