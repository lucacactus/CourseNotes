#include<iostream>
using namespace std;
class Student{ //��class��ͷ�����Է���.h��ͷ�ļ���
	int age;//��Ա����
	string name;//��Ա����
	char sex;//��Ա��������male(m); Ůfemale(f)
	public:
		void setData(int n,string str,char c){//��Ա����
			age = n;
			name = str;
			sex = c;
		}
		void display();//������Ա����
};
void Student::display(){//�����Ա���������Է���.cpp��
	cout<<"[Student: {name:"<<name<<"; age: "<<age<<"; sex: "<<sex<<" }]"<<endl;
}
int main(){
	Student stu;
	stu.setData(19,"����",'m');
	stu.display();
	return 0;
}