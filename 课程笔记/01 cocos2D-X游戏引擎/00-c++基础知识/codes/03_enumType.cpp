#include<iostream>
using namespace std;
int main(){
	//枚举类型定义的一般形式为： enum  枚举类型名  { 枚举成员列表 };
	enum enumA{A1,A2,A3};//类型名也可放在后面，如：enum {A1,A2,A3}enumA;或者使用typedef来更名
	
	//枚举变量的方式
	enum enumA a1,a2,a3;//直接创建变量
	enum enumB{B1,B2,B3,B4} b1,b2,b3,b4;//在定义类型是创建变量
	
	//赋值和使用
	a1 = A3;
	a2 = A2;
	a3 = A1;
	cout<<a1<<endl;
	cout<<a2<<endl;
	cout<<a3<<endl;
	return 0;
}