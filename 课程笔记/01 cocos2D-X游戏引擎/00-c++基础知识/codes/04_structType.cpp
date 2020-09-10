#include<iostream>
using namespace std;
int main(){
	//结构体可以看做轻量级的类，有三种定义方法:
	//方法1
	struct Student{
 	   const char* name;
 	   int age;
	};
	//访问代码如下:
	Student s;
	s.name="Tony";
	s.age=19;

	//方法2
	struct{
	    const char* name;
	    int age;
	}s1;//s1是临时变量，匿名结构体，只可以使用一次
	//访问代码为
	s1.name="Timmy";
	s1.age=20;

	//方法3
	typedef struct Student_{
 	   const char* name;
 	   int age;
	}student;
	//student是Student_的别名
	//访问代码如下：
	student s2;
	s2.name = "Tong";
	s2.age = 21;
	//打印
	cout<<s.name<<endl;
	cout<<s.age<<endl;
	cout<<s1.name<<endl;
	cout<<s1.age<<endl;
	cout<<s2.name<<endl;
	cout<<s2.age<<endl;
	return 0;
}