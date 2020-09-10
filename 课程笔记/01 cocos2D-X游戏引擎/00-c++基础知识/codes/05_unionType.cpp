#include<iostream>
using namespace std;

union Student
{
	const char* name;
	int age;
}s1,s2;
int main() {
	s1.name = "Tony";
	s2.age = 18;
	cout << "Name = " << s1.name << endl;
	cout << "Age = " << s2.age << endl;
	return 0;
}