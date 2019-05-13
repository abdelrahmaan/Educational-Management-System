#include "assignment_manager.h"
#include "assignment.h"


namespace ES{

	assignment_manager::assignment_manager() {}
	assignment_manager::assignment_manager(string a,int b) :assignment_inf(a),max_grade(b)  {	}

	
	void assignment_manager::view_assignment(){
		cout << "Please choose one of the following option:" << '\n';
		int option;
		cout << "\t1 - Show Info" << '\n';
		cout << "\t2 - Show grades Report" << '\n';
		cout << "\t3 - List Solutions" << '\n';
		cout << "\t4 - View Solution" << '\n';
		cout << "\t5 -  Back" << '\n';
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
			cout << assignment_inf << "\n\n\n";
		}
		else if (option == 2){
			grades_report();
		}
		else if (option == 3){
			list_students_solutions();
		}
		else if (option == 4){
			view_student_solution();
		}
		else if (option == 5){
			return;
		}
		else{
			cout << "Invalid Option ... Taking you back to your Menu\n\n\n";
		}
		view_assignment();
		return;
	}

	void assignment_manager::grades_report(){
		cout << "Student Grades:\n";
		for (auto _assignment : assignment_submissions)
			cout << "Student id: " << _assignment->owner << " Grade: " << _assignment->grade << "\n";
		cout << "\n\n\n\n";
	}

	void assignment_manager::list_students_solutions(){
		cout << "Student Solutions:\n";
		for (auto _assignment : assignment_submissions)
			cout << "Student id: " << _assignment->owner << " Solution: " << _assignment->solution << "\n";
		cout << "\n\n\n\n";
	}

	void assignment_manager::view_student_solution(){
		list_students_solutions();
		string _id;
		cout << "Please enter student id: ";
		cin >> _id;
		for (auto _assignment:assignment_submissions)
			if (_assignment->owner == _id){
				int option;
				cout << "Please choose ine of the following options:\n";
				cout << "\t1 - Set-grade\n";
				cout << "\t2 - back";
				cout << "Enter your choice: " << '\n';
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
					cout << "Please enter student grade: ";
					cin >> _assignment->grade;
				}else{
					cout << "Invalid Option, Please try again \n\n\n\n";
					view_student_solution();
				}
				return;
			}
		cout << "Invalid id, Please try again \n\n\n\n";
		view_student_solution();
	}

}