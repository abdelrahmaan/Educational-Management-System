#include "students_manager.h"
#include "Student.h"

namespace ES{

	students_manager::students_manager() {}
	extern shared_ptr<students_manager> _students_manager(new students_manager());

	void students_manager::add_new_student(Student a){
		shared_ptr<Student> ne(new Student(a));
		_students.push_back(ne);
		return;
	}

}