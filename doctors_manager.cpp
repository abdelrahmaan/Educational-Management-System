#include "doctors_manager.h"
#include "Doctor.h"

namespace ES{

	doctors_manager::doctors_manager() {}
	extern shared_ptr<doctors_manager> _doctors_manager(new doctors_manager());

	void doctors_manager::add_new_doctor(Doctor doc){
		shared_ptr<Doctor> ne(new Doctor(doc));
		_doctors.push_back(ne);
		return;
	}

}