#include<iostream>
#include<string>
using namespace std;
class GradeBook
{
private :
		string coursename;
		string instructor;
public:
	GradeBook(string COURSE, string INTER)
	{
		setcoursename(COURSE);
		setinstructor(INTER);
	}
	void setcoursename(string COURSE)
	{
		coursename = COURSE;
	  }
	string getcoursename()
	{
		return coursename;
	}
	void setinstructor(string INTER)
	{
		instructor = INTER;
	}
	string getinstructor()
	{
		return instructor;
	}
	void display()
	{
		cout << "Welcome to the grade book for" << endl;
		cout <<coursename << endl;
		cout <<"This course is presented by: " << instructor;
	}
};
int main()
{
	GradeBook BookA("CS101 Introduction to C++ Programming!", "Sam Smith");
		BookA.display();
		cout <<endl<< "now change the instructor" << endl;
		BookA.setinstructor("JudyJones");
		BookA.display();
		system("pause");

}