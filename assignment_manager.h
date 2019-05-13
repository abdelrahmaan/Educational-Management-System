#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include "system_flow.h"
using namespace std;

namespace ES{
	class assignment;
	class assignment_manager
	{
	public:
		string assignment_inf;
		int max_grade;
		assignment_manager();
		assignment_manager(string a,int b);

		void view_assignment();
		void grades_report();
		void list_students_solutions();
		void view_student_solution();

		vector<shared_ptr<assignment>> assignment_submissions; 
	};

}
