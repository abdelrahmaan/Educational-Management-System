#pragma once
#include<iostream>
#include<string>
#include"students_manager.h"
#include"doctors_manager.h"
#include <vector>
#include <fstream>

using namespace std;



namespace ES{
	class Student;
	class Course;
	class assignment_manager;
	class system_flow
	{
	public:
		system_flow();
		
		// To-Do save data
		void main_Menu();
		void Sign_in();
		void Sign_up();

		// load each class
		void load_doctors_courses_assignments();
		void load_students();
		// save each class
		void save_doctors_courses_assignments();
		void save_students();
		// show data on system
		void show_students_data();
		void show_doctors_data();

	};
	
	extern shared_ptr<system_flow> _system;
}