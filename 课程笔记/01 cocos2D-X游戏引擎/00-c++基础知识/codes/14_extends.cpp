#include<iostream>
using namespace std;
class Person{//Person�Ķ���-����
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

//public�̳е����~����PubStudent
class PubStudent:public Person{
	string school;
};

//protected�̳е����~����ProStudent
class ProStudent:protected Person{
	public:
		string school;
		int getAge(){
			return this->age;//�޷�����
		}
};

//˽�м̳е����~����PriStudent
class PriStudent:private Person{
	public:
		string school;
};

int main(){
	//���м̳е��������
	PubStudent* pubstu = new PubStudent();
	pubstu->display();//������������
	delete pubstu;
	
	//protected����ֻ���������з��ʡ�
	//�����̳е�����ָ�����
	ProStudent* prostu = new ProStudent();
	//�������: �����������������main�з��ʡ�
	//prostu->display();
	//prostu->name;
	prostu->getAge();
	string proschool = prostu->school;
	delete prostu;

	//˽�м̳е�����ָ�����
	PriStudent* pristu = new PriStudent();
	//pristu->display();//�������
	//string name = pristu->name;//�������
	string prischool = pristu->school;
	delete pristu;
	
	return 0;
}