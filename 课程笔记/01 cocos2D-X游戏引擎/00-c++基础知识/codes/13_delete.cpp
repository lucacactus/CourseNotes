#include<iostream>
using namespace std;
//1.类声明
class Student{
	private:
		int age;
		string name;
		char sex;
	public:
		Student();//无参构造函数
		Student(int page,string pname,char psex);//含参数的构造函数
		
		/*void setData(int page,string pname,char psex){
			age = page;
			name = pname;
			sex = psex;
		}*/
		void setData(int age,string name,char sex);
		void display();
		~Student();
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
/*Student::Student(int page,string pname,char psex){
	age = page;
	name = pname;
	sex = psex;
};*/
Student::Student(int age,string name,char sex){//新·构造函数
	this->age = age;
	this->name = name;
	this->sex = sex;//使用this指针就能将自己的成员变量和参数变量区分开来
}
void Student::setData(int age,string name,char sex){//新·修改函数
	this->age = age;
	this->name = name;
	this->sex = sex;//同上
}

//定义的析构函数
Student::~Student(){
	cout<<"~Student"<<endl;
}
int main(){
	Student stu1 = Student(19,"张三",'M');//创建实例stu1
	cout<<"stu1:\n\t";
	stu1.display();
	
	Student* stu2 = &stu1;//定义指向stu1的指针
	cout<<"stu2(point to stu1):\n\t";
	stu2->display();
	cout<<"stu2->setData(18,\"张三\",'M');"<<endl;
	stu2->setData(18,"张三",'M');//调用stu2的修改函数
	cout<<"stu2(point to stu1):\n\t";
	stu2->display();
	cout<<"stu1:\n\t";
	stu1.display();//发现stu1也被修改了

	Student* stu3 = new Student(20,"李四",'F');
	cout<<"stu3:\n\t";
	stu3->display();
	delete stu3;
	return 0;
}