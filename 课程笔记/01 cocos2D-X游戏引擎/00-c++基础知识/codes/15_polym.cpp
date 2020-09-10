#include<iostream>
using namespace std;

void print(int i){
	cout<<"print a integer:"<<i<<endl;
}

void print(float j){
	cout<<"print a float:"<<j<<endl;
}

void print(string str){
	cout<<"print a string:"<<str<<endl;
}

int main(){
	//应该调用第一个print函数，如果第一个print函数不存在，会自动类型转化调用第二个print函数（类型是赋值兼容的）
	print(100);
	print("HELLOWORLD!");
	return 0;
}