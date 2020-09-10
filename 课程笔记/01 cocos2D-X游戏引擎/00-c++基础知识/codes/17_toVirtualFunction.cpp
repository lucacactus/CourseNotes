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
	Graphics *g1,g2;//定义基类指针和基类对象；
	g1 = new Ellipse();//指向一个new的椭圆类对象
	g2 = Triangle();//静态对象
	cout<<"g1：指针；g2：对象实例"<<endl;
	
	cout<<"\n按虚函数定义："<<endl;
	g1->onDraw1();//通过指针调用椭圆类的onDraw函数
	g2.onDraw1();//通过对象调用基类的onDraw函数

	cout<<"\n按普通定义："<<endl;
	g1->onDraw2();
	g2.onDraw2();
	return 0;
}
	