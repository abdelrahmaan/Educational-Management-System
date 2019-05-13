/*
This Project idea/concept are from en.mostafa saad channel .. https://www.youtube.com/user/nobody123497/featured
This just my implementation of it
*/


#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include "system_flow.h"

using namespace std;


int main(){
	ES::system_flow ne;
	ne.load_doctors_courses_assignments();
	ne.load_students();
	ne.show_students_data();
	ne.show_doctors_data();
	ne.main_Menu();
	ne.save_doctors_courses_assignments();
}