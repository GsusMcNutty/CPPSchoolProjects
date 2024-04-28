//============================================================================
// Name        : Course.hpp
// Author      : Kyle Cortez
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : HPP file for Course Class
//============================================================================

#ifndef MODULE7_COURSE_HPP
#define MODULE7_COURSE_HPP

#include <string>
#include <vector>


class Course {
private:
    std::string courseNumber;
    std::string courseName;
    std::vector <std::string> coursePrerequisites;

public:
    Course();
    Course(std::string courseNumber, std::string courseName, std::vector <std::string> coursePrerequisites);

    void SetCourseNumber(std::string courseNumber);
    void SetCourseName(std::string courseName);
    void SetCoursePrerequisites(std::vector<std::string> coursePrerequisites);
    void AddCoursePrerequisite(std::string course);
    std::string GetCourseNumber();
    std::string GetCourseName();
    std::vector <std::string> GetCoursePrerequisites();
    void PrintCourse(bool printPrerequisites);
    void PrintCoursePrerequisites();

};

#endif //MODULE7_COURSE_HPP
