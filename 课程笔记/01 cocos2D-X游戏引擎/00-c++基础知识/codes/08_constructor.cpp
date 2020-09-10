#include<iostream>
using namespace std;
class Student{
	int age;
	string name;
	char sex;
	public:
		Student();//无参构造函数
		Student(int page,string pname,char psex);//含参数的构造函数
		
		void setData(int page,string pname,char psex){
			age = page;
			name = pname;
			sex = psex;
		}
		void display();
};
void Student::display(){
	cout<<"[Student: {name:"<<name<<"; age: "<<age<<"; sex: "<<sex<<" }]"<<endl;
}
//定义的无参数构造函数，如果不定义，会有一个默认的无参构造函数，只是啥也没做，函数体为空而己
Student::Student(){
	age = 0;
	name = "null";
	sex = 'M';
};

//定义的有参构造函数，与无参构造函数的关系是重载
Student::Student(int page,string pname,char psex){
	age = page;
	name = pname;
	sex = psex;
};
int main(){
	Student stu1;//调用无参构造函数
	stu1.display();

	Student stu2 = Student();//调用无参构造函数
	cout<<"stu2(before):\n\t ";//stu2修改值前
	stu2.display();
	cout<<"stu2(after): \n\t";//stu修改值后
	stu2.setData(19,"张三",'M');
	stu2.display();

	Student stu3 = Student(20,"李四",'F');//调用含参构造函数
	stu3.display();
	return 0;
}