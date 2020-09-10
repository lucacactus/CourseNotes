#include<iostream>
using namespace std;
class Person{//Person的定义-父类
	private:
		int id;
	protected:
		int age;
	public:
		string name;
		void display(){
			this->name = "Joy";
			this->id = 1;
			this->age = 18;
			cout<<"age:"<<age<<endl;
			cout<<"id:"<<id<<endl;
			cout<<"name:"<<name<<endl;
		}
};

//public继承的情况~类名PubStudent
class PubStudent:public Person{
	string school;
};

//protected继承的情况~类名ProStudent
class ProStudent:protected Person{
	public:
		string school;
		int getAge(){
			return this->age;//无法访问
		}
};

//私有继承的情况~类名PriStudent
class PriStudent:private Person{
	public:
		string school;
};

int main(){
	//公有继承的子类对象：
	PubStudent* pubstu = new PubStudent();
	pubstu->display();//各变量均可用
	delete pubstu;
	
	//protected变量只能在子类中访问。
	//保护继承的子类指针对象
	ProStudent* prostu = new ProStudent();
	//编译错误: 以下两句变量不能在main中访问。
	//prostu->display();
	//prostu->name;
	prostu->getAge();
	string proschool = prostu->school;
	delete prostu;

	//私有继承的子类指针对象
	PriStudent* pristu = new PriStudent();
	//pristu->display();//编译错误
	//string name = pristu->name;//编译错误
	string prischool = pristu->school;
	delete pristu;
	
	return 0;
}