#include<iostream>
using namespace std;
//1.������
class Student{
	private:
		int age;
		string name;
		char sex;
	public:
		Student();//�޲ι��캯��
		Student(int page,string pname,char psex);//�������Ĺ��캯��
		
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
//������޲������캯������������壬����һ��Ĭ�ϵ��޲ι��캯����ֻ��ɶҲû����������Ϊ�ն���
Student::Student(){
	age = 0;
	name = "null";
	sex = 'M';
};

//������вι��캯�������޲ι��캯���Ĺ�ϵ������
/*Student::Student(int page,string pname,char psex){
	age = page;
	name = pname;
	sex = psex;
};*/
Student::Student(int age,string name,char sex){//�¡����캯��
	this->age = age;
	this->name = name;
	this->sex = sex;//ʹ��thisָ����ܽ��Լ��ĳ�Ա�����Ͳ����������ֿ���
}
void Student::setData(int age,string name,char sex){//�¡��޸ĺ���
	this->age = age;
	this->name = name;
	this->sex = sex;//ͬ��
}

//�������������
Student::~Student(){
	cout<<"~Student"<<endl;
}
int main(){
	Student stu1 = Student(19,"����",'M');//����ʵ��stu1
	cout<<"stu1:\n\t";
	stu1.display();
	
	Student* stu2 = &stu1;//����ָ��stu1��ָ��
	cout<<"stu2(point to stu1):\n\t";
	stu2->display();
	cout<<"stu2->setData(18,\"����\",'M');"<<endl;
	stu2->setData(18,"����",'M');//����stu2���޸ĺ���
	cout<<"stu2(point to stu1):\n\t";
	stu2->display();
	cout<<"stu1:\n\t";
	stu1.display();//����stu1Ҳ���޸���

	Student* stu3 = new Student(20,"����",'F');
	cout<<"stu3:\n\t";
	stu3->display();
	delete stu3;
	return 0;
}