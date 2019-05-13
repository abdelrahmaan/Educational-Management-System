#pragma once
#include<vector>
#include<memory>
using namespace std;


// Is there's a better way to make a vector of all students without definning new class and extern of that class

namespace ES{
	class Doctor;

	class doctors_manager
	{
	public:
		doctors_manager();

		void add_new_doctor(Doctor doc);

		vector<shared_ptr<Doctor>> _doctors;
	};

	extern shared_ptr<doctors_manager> _doctors_manager;
}