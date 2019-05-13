#include "courses_manager.h"
#include "Course.h"



namespace ES{

	courses_manager::courses_manager() {}
	extern shared_ptr<courses_manager> _courses_manager(new courses_manager());

}