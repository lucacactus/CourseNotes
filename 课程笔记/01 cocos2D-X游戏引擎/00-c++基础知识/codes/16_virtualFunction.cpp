#include<iostream>
using namespace std;

class Graphics{
	public:
		virtual void onDraw1(){//���麯�����壬������ִ������ʵ�ֺ�����
			cout<<"����ͼ��"<<endl;
		}
		void onDraw2(){//����ͨ���壬������ִ�и���ʵ�ֺ���
			cout<<"����ͼ��"<<endl;
		}
};

class Ellipse:public Graphics{
	public:
		void onDraw1(){
			cout<<"������Բ��"<<endl;
		}
		void onDraw2(){
			cout<<"������Բ��"<<endl;
		}
};

class Triangle:public Graphics{
	public:
		void onDraw1(){
			cout<<"����������"<<endl;
		}
		void onDraw2(){
			cout<<"����������"<<endl;
		}
};
int main(){
	Graphics *g1,*g2;
	g1 = new Ellipse();
	g2 = new Triangle();
	
	cout<<"���麯�����壺"<<endl;
	g1->onDraw1();
	g2->onDraw1();

	cout<<"����ͨ���壺"<<endl;
	g1->onDraw2();
	g2->onDraw2();
	return 0;
}
	