#include "system_flow.h"
#include "Student.h"
#include "Course.h"
#include "assignment_manager.h"
#include "assignment.h"

namespace ES{

	system_flow::system_flow()	{}

    extern shared_ptr<system_flow> _system(new system_flow());

	void system_flow::main_Menu(){
		cout << "Please choose one of the following option:" << '\n';
		int option;
		cout << "\t1 - Login" << '\n';
		cout << "\t2 - Sign up" << '\n';
		cout << "\t3 - Shutdown system" << '\n';
		cout << "Enter your choice: " ;
		cin >> option;
		// ignore invalid input such as char instead of int
		while (cin.fail()){
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid Choice, Please try again\n";
			cout << "Enter your choice: ";
			cin >> option;
		}
		if (option == 1){
			Sign_in();
		}
		else if (option == 2){
			Sign_up();
		}
		else if (option == 3){
			return;
		}
		else{
			cout << "Invalid Option ... Taking you back to your Menu\n\n\n";
			main_Menu();
		}
		return;
	}

	void system_flow::Sign_in(){
		cout << "Please enter your id and password\n";
		string _id,_password;
		cout << "Enter your id: ";
		cin >> _id;
		cout << "Enter your Password: ";
		cin >> _password;
		cout << "\n\n\n\n";
		// check user name and password in students
		bool logged_in = 0; // check if user has logged in
		for (auto student : _students_manager->_students)
			if (student->id == _id && student->password == _password){
				student->Menu();
				logged_in = 1;
			}
		// check user name and password in doctors
		if (logged_in == 0){
			for (auto doctor : _doctors_manager->_doctors)
				if (doctor->id == _id && doctor->password == _password){
				doctor->Menu();
				logged_in = 1;
				}
		}
		if (logged_in == 0)
			cout << "Incorrect id/Password, Please try again\n\n\n\n";
		_system->main_Menu();
		return;
	}

	void system_flow::Sign_up(){
		string first_name, last_name, email, id, password;
		cout << "please Enter your first name: ";
		cin >> first_name;
		cout << "please Enter your last name: ";
		cin >> last_name;
		cout << "please Enter your email: ";
		cin >> email;
		cout << "please Enter your id: ";
		cin >> id;
		cout << "please Enter your password: ";
		cin >> password;

		int option;
		cout << "Are you :\n";
		cout << "\t1 - A student\n";
		cout << "\t2 - A doctor\n";
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
		if (option == 1){
			for (auto _student:_students_manager->_students)
				if (_student->id == id){
					cout << "This id is already taken, Please sign up again with different id\n\n\n";
					Sign_up();
					return;
				}
			_students_manager->add_new_student(Student(first_name, last_name, email, id, password));
		}
		else{
			for (auto _doctor : _doctors_manager->_doctors)
				if (_doctor->id == id){
					cout << "This id is already taken, Please sign up again with different id\n\n\n";
					Sign_up();
					return;
				}
			_doctors_manager->add_new_doctor(Doctor(first_name, last_name, email, id, password));
		}
		cout << "You have successfully registered, please  log in now.\n\n\n\n\n";
		main_Menu();
		return;
	}


	void system_flow::load_doctors_courses_assignments(){
		ifstream inputStram("doctors_courses_assignments.txt");
		if (inputStram.fail())
			return;
		// vaibles needed for creating new doctor and ocurse
		string _first_name, _last_name, _email, _id, _pass, _course;
		int numberOfCourses;

		while (inputStram >> _first_name >> _last_name >> _email >> _id >> _pass >> numberOfCourses){
			shared_ptr<Doctor> new_doctor(new Doctor(_first_name,_last_name,_email,_id,_pass));
			// go over all his courses
			while (numberOfCourses--){
				// make a new course by this doctor
				shared_ptr<Course> _course(new Course());
				inputStram >> _course->course_name >> _course->course_code;
				_course->course_doctor = _first_name + " " + _last_name;

				// read assignments of this course
				int numberOfAssignments;
				inputStram >> numberOfAssignments;
				while (numberOfAssignments--){
					// create new assignment
					shared_ptr<assignment_manager> new_assignment(new assignment_manager());
					// read assignment information
					new_assignment->assignment_inf = "";
					string _inf;
					while (inputStram >> _inf){
						if (_inf[0] == '#')
							break;
						new_assignment->assignment_inf += " " + _inf;
					}
					// set assignment max grade
					inputStram >> new_assignment->max_grade;
					// push the assignment to courses assignment list
					_course->course_assignments.push_back(new_assignment);
				}

				// put this course into courses list
				_courses_manager->_courses.push_back(_course);
				// put this course into doctor created course list
				new_doctor->created_courses.push_back(_course);
			}
			_doctors_manager->_doctors.push_back(new_doctor);
		}
		inputStram.close();
		return;
	}

	void system_flow::load_students(){
		ifstream inputStram("students.txt");
		if (inputStram.fail())
			return;
		// varibles needed for new student/assignment/courses
		string _first_name, _last_name, _email, _id, _pass, _course;
		int numberOfCourses, _assignment_number, assignment_grade;
		string _course_name, _assignment_solution;
		bool _assignment_solution_done;

		// first read student information
		while (inputStram >> _first_name >> _last_name >> _email >> _id >> _pass >> numberOfCourses){
			// create the student
			shared_ptr<Student> new_student(new Student(_first_name, _last_name, _email, _id, _pass));
			// read all courses he registerd in
			while (numberOfCourses--){
				inputStram >> _course_name >> _assignment_solution_done;

				// find the course in the courses list
				for (auto _course:_courses_manager->_courses)
					if (_course->course_name == _course_name){ // this is his course
						// if he has submitted a solution for the _assignment_number assignment
						if (_assignment_solution_done == 1){
							inputStram >> _assignment_number >> _assignment_solution >> assignment_grade;
							// create his assignment soltuion
							shared_ptr<assignment> new_assignment(new assignment());
							new_assignment->grade = assignment_grade;
							new_assignment->owner = new_student->id;
							new_assignment->solution = _assignment_solution;

							int assignments_counter = 1;
							// go the assignment number _assignment_number and push the assignment into the course assignments
							for (auto _course_assignments_number:_course->course_assignments)
								if (assignments_counter == _assignment_number){
									_course_assignments_number->assignment_submissions.push_back(new_assignment);
								}
						}
						// add course to student courses list
						new_student->registered_courses.push_back(_course);
						// add student to courses students list
						_course->registered_students.push_back(new_student);
						break;
					}
			}
			// add new_student to the students list
			_students_manager->_students.push_back(new_student);
		}
		inputStram.close();
		return;
	}


	void system_flow::show_students_data(){
		cout << "students in the system\n";
		for (auto _student : _students_manager->_students)
			cout << _student->id << " " << _student->password << endl;
	}

	void system_flow::show_doctors_data(){
		cout << "doctors in the system\n";
		for (auto _doctor : _doctors_manager->_doctors)
			cout << _doctor->id << " " << _doctor->password << endl;
	}



	void system_flow::save_doctors_courses_assignments(){
		// this will overwrite all the data from the begin .. To-Do to handle saving the new data only
		ofstream outputStram("doctors_courses_assignments.txt");
		if (outputStram.fail())
			return;
		// go over all doctors
		for (auto _doctor : _doctors_manager->_doctors){
			// print doctor data
			outputStram << _doctor->first_name << " " << _doctor->last_name << " " << _doctor->email << " "
				<< _doctor->id << " " << _doctor->password << '\n';
			outputStram << _doctor->created_courses.size() << '\n';
			for (auto _course : _doctor->created_courses){
				// go over all the course this doctor created
				outputStram << _course->course_name << " " << _course->course_code << " ";
				if (_course->course_assignments.size() > 0){
					outputStram << _course->course_assignments.size() << " ";
					for (auto _course_assignment : _course->course_assignments){
						outputStram << _course_assignment->assignment_inf << " # " << _course_assignment->max_grade << " ";
					}
					outputStram << "\n";
				}else{
					outputStram << 0 << '\n';
				}
			}
			outputStram << "\n";
		}
		outputStram.close();
	}


	void system_flow::save_students(){
		// this will overwrite all the data from the begin .. To-Do to handle saving the new data only
		ofstream outputStram("students.txt");
		if (outputStram.fail())
			return;
		for (auto _student : _students_manager->_students){
			outputStram << _student->first_name << " " << _student->last_name << " " << _student->email << " "
				<< _student->id << " " << _student->password << '\n';
			outputStram << _student->registered_courses.size() << '\n';

		}
		outputStram.close();
	}
}