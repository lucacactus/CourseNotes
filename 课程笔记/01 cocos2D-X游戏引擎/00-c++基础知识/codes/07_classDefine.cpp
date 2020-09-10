#include<iostream>
using namespace std;
class Student{ //以class开头，可以放在.h的头文件中
	int age;//成员变量
	string name;//成员变量
	char sex;//成员变量：男male(m); 女female(f)
	public:
		void setData(int n,string str,char c){//成员函数
			age = n;
			name = str;
			sex = c;
		}
		void display();//声明成员函数
};
void Student::display(){//定义成员函数，可以放在.cpp中
	cout<<"[Student: {name:"<<name<<"; age: "<<age<<"; sex: "<<sex<<" }]"<<endl;
}
int main(){
	Student stu;
	stu.setData(19,"张三",'m');
	stu.display();
	return 0;
}