#include<iostream>
using namespace std;
int main(){
	//�ṹ����Կ������������࣬�����ֶ��巽��:
	//����1
	struct Student{
 	   const char* name;
 	   int age;
	};
	//���ʴ�������:
	Student s;
	s.name="Tony";
	s.age=19;

	//����2
	struct{
	    const char* name;
	    int age;
	}s1;//s1����ʱ�����������ṹ�壬ֻ����ʹ��һ��
	//���ʴ���Ϊ
	s1.name="Timmy";
	s1.age=20;

	//����3
	typedef struct Student_{
 	   const char* name;
 	   int age;
	}student;
	//student��Student_�ı���
	//���ʴ������£�
	student s2;
	s2.name = "Tong";
	s2.age = 21;
	//��ӡ
	cout<<s.name<<endl;
	cout<<s.age<<endl;
	cout<<s1.name<<endl;
	cout<<s1.age<<endl;
	cout<<s2.name<<endl;
	cout<<s2.age<<endl;
	return 0;
}