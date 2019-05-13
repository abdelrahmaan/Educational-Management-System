#pragma once
#include<vector>
#include<memory>

using namespace std;


// Is there's a better way to make a vector of all students without definning new class and extern of that class

namespace ES{
	class Student;

	class students_manager
	{
	public:
		students_manager();

		void add_new_student(Student a);

		vector<shared_ptr<Student>> _students;
	};
	extern shared_ptr<students_manager> _students_manager;

}