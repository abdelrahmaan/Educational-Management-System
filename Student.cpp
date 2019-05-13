#include "Student.h"
#include <string>
#include "assignment.h"

namespace ES{

	Student::Student()	{}
	Student::Student(string a, string b, string c, string d,string e) :first_name(a), last_name(b), email(c), id(d), password(e) {}
	Student::Student(const Student &st){
		first_name = st.first_name;
		last_name = st.last_name;
		email = st.email;
		id = st.id;
		password = st.password;
	}

	// student main menu
	void Student::Menu(){
		cout << "Please choose one of the following option:" << '\n';
		int option;
		cout << "\t1 - Register in a course" << '\n';
		cout << "\t2 - List My courses" << '\n';
		cout << "\t3 - view course" << '\n';
		cout << "\t4 - log out" << '\n';
		cout << "Enter your choice: ";
		cin >> option;
		// ignore invalid input such as char instead of int
		while (cin.fail()){
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid Choice, Please try again\n";
			cout << "Enter your choice: ";
			cin >> option;
		}
		cout << "\n\n\n";
		if (option == 1){
			Register_new_course();
			Menu();
			return;
		}
		else if (option == 2){
			show_registered_courses();
			Menu();
			return;
		}
		else if (option == 3){
			view_student_course_inf();
			Menu();
			return;
		}
		else if (option == 4){
			return;
		}
		else{
			// invalid option don't handle char instead of int ... this crush ... To-Do
			cout << "Invalid Option ... Taking you back to your Menu\n\n\n";
		}
		return;
	}

	// register in a new course
	void Student::Register_new_course(){
		cout << "Available Courses to register in:\n";
		for (auto new_course : _courses_manager->_courses){
			bool taken = 0;
			for (auto cur_course:registered_courses)
				if (new_course == cur_course){
					// he has registered in this course before
					taken = 1;
					break;
				}
			// he hasn't registered in this course before
			if (!taken) 
				cout << "Course name: " << new_course->course_name << "   Code: " << 
				new_course->course_code << "   Taught by Dr: " << new_course->course_doctor << '\n';
		}
		// Handle if there were no available courses. To-Do

		string choose_course;
		cout << "\n\nplease Enter the course code you want to register on: ";
		cin >> choose_course;
		for (auto new_course : _courses_manager->_courses)
			if (new_course->course_code == choose_course){
				cout << "You have successuflly registered in course " << new_course->course_doctor << " with doc: "
					<< new_course->course_doctor << '\n';

				// add the course to the student registerd courses
				shared_ptr<Course> ne_course(new Course(new_course->course_name,new_course->course_code,new_course->course_doctor));
				registered_courses.push_back(ne_course);

				// add the student to the course registered student
				shared_ptr<Student> ne_student(new Student(first_name,last_name,email,id,password));
				new_course->registered_students.push_back(ne_student);
				cout << "\n\n\n";
				// successfully registered in a new course
				return;
			}
		// unsuccessful registeration
		cout << "Invalid Course Code.. taking you back to your menu\n\n\n";
		Register_new_course();
		return;
	}

	
	void Student::show_registered_courses(){
		// handle if he hasn't reigster in any course yet
		if (registered_courses.size() == 0){
			cout << "you havn't register in any Course yet.\n\n\n\n";
			Menu();
			return;
		}
		cout << "Your Registered Courses:\n";
		for (auto _course : registered_courses)
			cout << "Course " << _course->course_name << " - Code " << _course->course_code << " - Doc " << _course->course_doctor << '\n';
		cout << "\n\n\n\n";
		return;
	}


	void Student::view_student_course_inf(){
		// handle if he hasn't reigster in any course yet
		if (registered_courses.size() == 0){
			cout << "you havn't register in any Course yet.\n\n\n\n";
			Menu();
			return;
		}
		// view all course he's registered in
		show_registered_courses();
		cout << "Select one of your Registered course code( course code not course name ) to view: ";
		string _code;
		cin >> _code;

		// check if course code he entered exist
		bool wrong_code = 1;
		for (auto _course:registered_courses)
			if (_course->course_code == _code){
				int option;
				cout << "Please choose one of the following options: \n";
				cout << "\t1 - Unregister from this Course\n";
				cout << "\t2 - View Course information and assignments\n";
				cout << "Enter your choice here: ";
				cin >> option;
				// ignore invalid input such as char instead of int
				while (cin.fail()){
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					cout << "Invalid Choice, Please try again\n";
					cout << "Enter your choice: ";
					cin >> option;
				}
				cout << "\n\n\n";
				if (option == 1){
					unregister_from_course(_code);
					Menu();
				}
				else if(option == 2){
					for (auto __course : _courses_manager->_courses)
					if(__course->course_code == _code){
						__course->view_student_course_inf(id);
						break;
					}
				}else{
					break; // wrong code
				}
				wrong_code = 0; // course code exist
				break;
			}

		if (wrong_code){
			cout << "You've entered invalid course code, please try again.\n\n\n\n";
			view_student_course_inf();
			return;
		}
		return;
	}


	void Student::unregister_from_course(string _course_code){
		
		for (auto _course : _courses_manager->_courses)
			if(_course_code == _course->course_code ){
				int cur = 0;
				// remove the student from the registered students in the course
				for (auto _student : _course->registered_students){
					if (_student->id == id){
						_course->registered_students.erase(_course->registered_students.begin() + cur);
						break;
					}
					cur++;
				}
				// remove the student assignments ( if he has any )
				for (auto _assignments : _course->course_assignments){
					int cur = 0;
					for (auto _assignment:_assignments->assignment_submissions)
						if (_assignment->owner == id){
							_assignments->assignment_submissions.erase(_assignments->assignment_submissions.begin() + cur);
							break;
						}
				}
			}
		// remove the course from the student courses list
		for (auto _course : registered_courses){
			int cur = 0;
			if (_course->course_code == _course_code){
				registered_courses.erase(registered_courses.begin() + cur);
				break;
			}
			cur++;
		}
		cout << "You have successuflly unregistered from course code: " << _course_code << '\n';
		return;
	}
	
}


