//============================================================================
// Name        : Course.cpp
// Author      : Kyle Cortez
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : CPP file for Course Class
//============================================================================

#include "Course.hpp"
#include <iostream>


void Course::SetCourseNumber(std::string courseNumber) {
    this->courseNumber = courseNumber;
}
void Course::SetCourseName(std::string courseName){
    this->courseName = courseName;
}
void Course::SetCoursePrerequisites(std::vector <std::string> coursePrerequisites){
    this->coursePrerequisites = coursePrerequisites;
}
std::string Course::GetCourseNumber(){
    return this->courseNumber;
}
std::string Course::GetCourseName(){
    return this->courseName;
}
std::vector <std::string> Course::GetCoursePrerequisites(){
    return this->coursePrerequisites;
}

void Course::AddCoursePrerequisite(std::string course) {
    coursePrerequisites.push_back(course);
}

Course::Course() {
    this->courseNumber = "";
}

Course::Course(std::string courseNumber, std::string courseName, std::vector<std::string> coursePrerequisites) {
    this->courseNumber = courseNumber;
    this->courseName = courseName;
    this->coursePrerequisites = coursePrerequisites;
}

void Course::PrintCourse(bool printPrerequisites){
    std::cout << courseNumber << ", " << courseName << std::endl;
    if (printPrerequisites){
        Course::PrintCoursePrerequisites();
    }
}

void Course::PrintCoursePrerequisites() {
    if(!coursePrerequisites.empty()){
        std::cout << "Prerequisites: ";
        for (int i = 0; i < coursePrerequisites.size()-1; ++i) {

            std::cout << coursePrerequisites[i] << ", ";
        }
        std::cout << coursePrerequisites[coursePrerequisites.size()-1] << std::endl;
    }
}
