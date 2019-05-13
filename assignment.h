#pragma once
#include "Student.h"
#include "assignment.h"
#include <memory>

using namespace std;

namespace ES{

	class assignment
	{
	public:
		assignment() {}
		int grade;
		string  owner;
		string solution;
		assignment(int a,string b, string c);
	};

}