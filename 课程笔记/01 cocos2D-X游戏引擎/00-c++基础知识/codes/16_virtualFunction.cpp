#include<iostream>
using namespace std;

class Graphics{
	public:
		virtual void onDraw1(){//按虚函数定义，则子类执行子类实现函数；
			cout<<"绘制图形"<<endl;
		}
		void onDraw2(){//按普通定义，则子类执行父类实现函数
			cout<<"绘制图形"<<endl;
		}
};

class Ellipse:public Graphics{
	public:
		void onDraw1(){
			cout<<"绘制椭圆形"<<endl;
		}
		void onDraw2(){
			cout<<"绘制椭圆形"<<endl;
		}
};

class Triangle:public Graphics{
	public:
		void onDraw1(){
			cout<<"绘制三角形"<<endl;
		}
		void onDraw2(){
			cout<<"绘制三角形"<<endl;
		}
};
int main(){
	Graphics *g1,*g2;
	g1 = new Ellipse();
	g2 = new Triangle();
	
	cout<<"按虚函数定义："<<endl;
	g1->onDraw1();
	g2->onDraw1();

	cout<<"按普通定义："<<endl;
	g1->onDraw2();
	g2->onDraw2();
	return 0;
}
	