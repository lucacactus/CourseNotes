#include<iostream>
using namespace std;
class Student{
	int age;
	string name;
	char sex;
	public:
		Student();//�޲ι��캯��
		Student(int page,string pname,char psex);//�������Ĺ��캯��
		
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
//������޲������캯������������壬����һ��Ĭ�ϵ��޲ι��캯����ֻ��ɶҲû����������Ϊ�ն���
Student::Student(){
	age = 0;
	name = "null";
	sex = 'M';
};

//������вι��캯�������޲ι��캯���Ĺ�ϵ������
Student::Student(int page,string pname,char psex){
	age = page;
	name = pname;
	sex = psex;
};
int main(){
	Student stu1;//�����޲ι��캯��
	stu1.display();

	Student stu2 = Student();//�����޲ι��캯��
	cout<<"stu2(before):\n\t ";//stu2�޸�ֵǰ
	stu2.display();
	cout<<"stu2(after): \n\t";//stu�޸�ֵ��
	stu2.setData(19,"����",'M');
	stu2.display();

	Student stu3 = Student(20,"����",'F');//���ú��ι��캯��
	stu3.display();
	return 0;
}