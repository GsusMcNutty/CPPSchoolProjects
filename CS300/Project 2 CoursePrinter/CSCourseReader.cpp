//============================================================================
// Name        : CSCoursesReader.cpp
// Author      : Kyle Cortez
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <string>
#include <algorithm>
#include <fstream>
#include "Course.hpp"

using namespace std;

const int BADSTRINGCODE = -999;

// put string to upper with a range
void ToUpper(string &word, int rangeLower = 0, int rangeUpper = 0){
    try{
        // ranges are default, everything to upper
        if (rangeLower == 0 && rangeUpper == 0){
            for (char &letter: word) {
                word[letter] = toupper(letter);
            }
        }
        // do only within range
        if (rangeLower < rangeUpper){
            for (int i = rangeLower; i < rangeUpper; ++i) {
                word[i] = toupper(word[i]);
            }
        }
        else{
            throw runtime_error("ToUpper() failed");
        }
    }
    catch (const exception& e){
        cout << "Error: Ranges may need to be swapped!\n" << e.what() << endl;
    }
}

// Internal structure for tree node
struct Node {
    Course course;
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
            Node() {
        course = aCourse;
    }
};

class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node *node);
    void deleteNode(Node *node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(const Course& course);
    Course Search(string courseNumber);
    void EmptyTree();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
// recursion function for deleting nodes for destructor
void BinarySearchTree::deleteNode(Node* node){
    if(node){
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
    }
}

// empty out the tree
void BinarySearchTree::EmptyTree(){
    deleteNode(root);
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    deleteNode(root);
}

void BinarySearchTree::Insert(const Course& course) {
    // if root equal to null ptr
    if(root == nullptr){
        // root is equal to new node bid
        root = new Node(course);
    }
        // else
    else{
        // add Node root and bid
        addNode(root,course);
    }
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNumber) {
    // set current node equal to root
    ToUpper(courseNumber, 0, 4);
    Node* currentNode = root;
    // keep looping downwards until bottom reached or matching bidId found
    while(currentNode != nullptr) {
        // if match found, return current bid
        if (currentNode->course.GetCourseNumber() == courseNumber) {
            return currentNode->course;
        }
        // if bid is smaller than current node then traverse left
        if (courseNumber < currentNode->course.GetCourseNumber()) {
            currentNode = currentNode->left;
        }
        // else larger so traverse right
        else {
            currentNode = currentNode->right;

        }
    }
    throw invalid_argument("No course found with " + courseNumber + " as course number!");
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger than add to left
    if (node->course.GetCourseNumber() > course.GetCourseNumber()) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            addNode(node->left, course);
        }
    }
        // else
    else{
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else {
            // recurse down the right node
            addNode(node->right, course);
        }
    }
}

void BinarySearchTree::InOrder() {
    // call inOrder function and pass root
    inOrder(root);
}

void BinarySearchTree::inOrder(Node* node) {
    //if node is not equal to null ptr
    if(node != nullptr){
        //InOrder not left
        inOrder(node->left);
        //output bidID, title, amount, fund
        node->course.PrintCourse(false);
        //InOder right
        inOrder(node->right);
    }
}

/**
 * Simple split string function to
 * find each delimiter instance then
 * push each resulting string to a
 * vector<string> which is returned
 *
 * split string by delimiter credit: https://cppbyexample.com/split_string.html
 *
 * @param s input string
 * @param c delimiter
 * @return vector<string>
 */
vector<string> split(const string& s, char c) {
    vector<string> result;
    size_t begin = 0;
    while (true) {
        size_t end = s.find_first_of(c, begin);
        result.push_back(s.substr(begin, end - begin));

        if (end == std::string::npos) {
            break;
        }

        begin = end + 1;
    }
    return result;
}

// Parses the lines to a Course object, then populate courses
void ParseLines(BinarySearchTree* courses, const vector<string>& lines){
    // DebugLines(lines);
    // vector to hold split string
    vector <string> splitLine;
    // iterate through all lines
    for (const string& line:lines) {
        Course course = *new Course();
        // split line by delimiter then store
        splitLine = split(line, ',');
        // push first and second elements of split as course number and name
        course.SetCourseNumber(splitLine[0]);
        course.SetCourseName(splitLine[1]);
        // has more elements remaining? push to prerequisites
        if(splitLine.size() > 2){
            for (int i = 2; i < splitLine.size(); ++i) {
                course.AddCoursePrerequisite(splitLine[i]);
            }
        }
        // push finalized course to courses
        courses->Insert(course);
        //courses.push_back(course);
    }
}

void ParseFile(const string& fileLocation, BinarySearchTree* courses){
    courses->EmptyTree();
    ifstream file (fileLocation);
    string line;
    // holder of lines
    vector <string> lines;
    // open file else fail
    if(file.is_open()){
        // get each line then push to lines
        while(getline(file, line)){
            lines.push_back(line);
        }
        // close file when done
        file.close();
    }
    // else throw error if file is unable to open
    else{
        throw invalid_argument(" Unable to open: " + fileLocation + ", Check the FIXME for correct path.");
    }

    // now parse the lines to courses
    ParseLines(courses,lines);
}

// print menu function
void PrintMenu(){
    cout << "   1. Load Data Structure." << endl;
    cout << "   2. Print Course List." << endl;
    cout << "   3. Print Course." << endl;
    cout << "   9. Exit" << endl;
    cout << endl;
}

// for checking number input
string CaptureInputInt(int maxInputLength){
    // temp for holding input string
    string _input;
    cin >> _input;
    if (_input.length() > maxInputLength){
        throw length_error(_input + " is too big of an input!");
    }
    // try to convert string to int
    for (char element:_input) {
        if(!isdigit(element)){
            throw invalid_argument(_input + " is not a valid option.");
        }
    }
    cin.clear();
    return _input;
}

// for checking string input
string CaptureInputString(int maxInputLength){
    // temp for holding input string
    string _input;
    cin >> _input;
    if (_input.length() > maxInputLength){
        throw length_error(_input + " is too big of an input!");
    }
    cin.clear();
    return _input;
}

// to encapsulate case 1
void DoCase1(string &fileLocation, BinarySearchTree *courses){
    cout << "Loading: " << fileLocation << endl;
    try{
        ParseFile(fileLocation, courses);
        cout << "Successfully Loaded!" << endl;
    }
        // catch unable to open error
    catch (const exception& e){
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;
}

// to encapsulate case 2
void DoCase2(BinarySearchTree *courses){
    cout << "Here is a sample schedule:\n" << endl;
    courses->InOrder();
    cout << endl;
}

// to encapsulate case 3
void DoCase3(BinarySearchTree *courses, int _maxInputCourseNumberSize){
    try{
        cout << "What course do you want to know about?";
        courses->Search(CaptureInputString(_maxInputCourseNumberSize)).PrintCourse(true);
        cin.clear();
    }
        // catch invalid argument
    catch(const invalid_argument& e){
        cout << "Error: " << e.what() << endl;
        cin.clear();
    }
        // error if input is too long
    catch(const length_error& e){
        cout << "Error: " << e.what() << endl;
        cin.clear();
    }
    cout << endl;
}

int main() {
    cout << "Welcome to the course planner.\n" << std::endl;

    // create variables and opening states

    int input = BADSTRINGCODE;
    int maxInputMenuSize = 4;
    int maxInputCourseNumberSize = 8;

    BinarySearchTree* courses;
    courses = new BinarySearchTree();
    Course course;
    string courseCode;

    // FIXME: If file location is NOT working
    // this is your path if all the other assignments are an indicator
    string fileLocation = "courses.txt";
    // this is my path
    // string fileLocation = "../courses.txt";

    while(input != 9){
        PrintMenu();
        cout << "What would you like to do?";
        //capture menu input as int
        try{
            input = stoi(CaptureInputInt(maxInputMenuSize));
        }
        //error if input is too long
        catch (const length_error& e){
            // set input as BADSTRINGCODE to not repeat error message with default input number
            cout << "Error: " << e.what() << endl;
            input = BADSTRINGCODE;
            cin.clear();
        }
        //error if input has characters
        catch (const invalid_argument& e){
            cout << "Error: " << e.what() << endl;
            // set input as BADSTRINGCODE to not repeat error message with default input number
            input = BADSTRINGCODE;
            cin.clear();
        }

        switch(input){
            // for invalid NUMBER output
            case BADSTRINGCODE:
                cout << endl;
                break;
            // parse file into tree
            case 1:
                DoCase1(fileLocation, courses);
                break;
            // print example course in order
            case 2:
                DoCase2(courses);
                break;
            // search for course
            case 3:
                DoCase3(courses, maxInputCourseNumberSize);
                break;
            // Not sure why we want 4 as escape per example
            // I went ahead and made it so that either 4 or 9 is the exit key :)
            case 4:
                input = 9;
                break;
            case 9:
                break;
            // for capturing invalid int input
            default:
                cout << input << " is not a valid option." << endl;
                cout << endl;
        }
    }

    // Auf Wiedersehen!
    cout << "Thank you for using the course planner!" << endl;
    return 0;
}
