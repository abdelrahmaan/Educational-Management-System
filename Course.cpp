#include "Course.h"
#include "Student.h"
#include "assignment.h"
#include "assignment_manager.h"


namespace ES{

	Course::Course() {}
	Course::Course(string a, string b, string c) :course_name(a), course_code(b), course_doctor(c) {}

	void Course::show_registered_students(){
		cout << "Registered Students ID:";
		for (auto _student : registered_students)
			cout << " " << _student->id;
		cout << "\n\n\n\n";
		return;
	}


	void Course::view_student_course_inf(string cur_student_id){
		cout << "course " << course_name << " - code " << course_code << " - doc " << course_doctor << '\n';
		cout << "course has " << course_assignments.size() << " assignments\n";

		int assignment_number = 0;
		// go over all assignments of this course
		for (auto _assignment : course_assignments){
			bool student_done_this_assignment = 0;
			for (auto _student_assignmnent : _assignment->assignment_submissions)
				if (_student_assignmnent->owner == cur_student_id){
					cout << "Assignment " << ++assignment_number << " Submitted" << " - ";
					// check if he has a grade yet
					if (_student_assignmnent->grade == -1)
						cout << "NA";
					else
						cout << _student_assignmnent->grade;
					cout << " / " << _assignment->max_grade << "\n\n";
					student_done_this_assignment = 1;
				}
			// he havn't submit this assignment yet ( he might want to submit it now )
			if (student_done_this_assignment == false){
				cout << "Do you want to submit this assignment now ?\n";
				cout << "\t1 - submit assignment now\n";
				cout << "\t2 - don't submit now\n";
				int option;
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
					// he want to submit this assignment now
					shared_ptr<assignment> new_assignment(new assignment());
					cout << "Please Enter your Solution (one word): ";  // To-Do make assignment more than 1 word
					cin >> new_assignment->solution;
					new_assignment->grade = -1;
					new_assignment->owner = cur_student_id;
					_assignment->assignment_submissions.push_back(new_assignment);
					cout << "MAX_GRADE :" << _assignment->max_grade << "\n";
					cout << "You've submitted you assignment successfully \n\n\n\n";
				}
			}
		}
		cout << "\n\n\n\n";
		return;
	}


	void Course::list_course_assignment(){
		cout << "This Couse Has " << course_assignments.size() << " assignments\n";
		int assignmentNumber = 0;
		for (auto assignment : course_assignments)
			cout << "Assignment " << ++assignmentNumber << ":" << assignment->assignment_inf <<
			", Grade:" << assignment->max_grade << '\n';
		cout << "\n\n\n";
	}

	void Course::add_assignment(){
		shared_ptr<assignment_manager> new_assignment(new assignment_manager());
		new_assignment->assignment_inf = "";
		cout << "Please enter some inf about the assignment ( end it with # in a sepearte word ):";
		string _inf;
		while (cin >> _inf){
			if (_inf[0] == '#')
				break;
			new_assignment->assignment_inf += " " + _inf;
		}
		cout << "Please enter max grade of the assignment :";
		cin >> new_assignment->max_grade;
		cout << "\n\n\n\n";
		course_assignments.push_back(new_assignment);
		// handle input error To-Do
	}



	void Course::view_doctor_course_inf(){
		cout << "Please choose one of the following option:" << '\n';
		int option;
		cout << "\t1 - List assignment" << '\n';
		cout << "\t2 - add assignment" << '\n';
		cout << "\t3 - View assignment" << '\n';
		cout << "\t4 -  Back" << '\n';
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
		cout << "\n\n\n";
		if (option == 1){
			list_course_assignment();
		}
		else if (option == 2){
			add_assignment();
		}
		else if (option == 3){
			select_assignment();
		}
		else if (option == 4){
			return; // go back to previous window
		}
		else{
			cout << "Invalid Option ... Taking you back to your Menu\n\n\n";
		}
		view_doctor_course_inf();
		return;
	}

	void Course::select_assignment(){
		int numberOfassignment = 0;
		for (auto _assignment : course_assignments){
			cout << "Assignment number " << ++numberOfassignment << '\n';
			cout << "Enter one of the following option: \n";
			cout << "\t1 - view this assignment\n";
			cout << "\t2 - Continue\n";
			cout << "Enter your choice: ";
			int option;
			cin >> option;
			// ignore invalid input such as char instead of int
			while (cin.fail()){
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "Invalid Choice, Please try again\n";
				cout << "Enter your choice: ";
				cin >> option;
			}
			cout << "\n\n";
			if (option == 1)
				_assignment->view_assignment();
			cout << "\n\n";
		}
	}

}