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
	Graphics *g1,g2;//�������ָ��ͻ������
	g1 = new Ellipse();//ָ��һ��new����Բ�����
	g2 = Triangle();//��̬����
	cout<<"g1��ָ�룻g2������ʵ��"<<endl;
	
	cout<<"\n���麯�����壺"<<endl;
	g1->onDraw1();//ͨ��ָ�������Բ���onDraw����
	g2.onDraw1();//ͨ��������û����onDraw����

	cout<<"\n����ͨ���壺"<<endl;
	g1->onDraw2();
	g2.onDraw2();
	return 0;
}
	