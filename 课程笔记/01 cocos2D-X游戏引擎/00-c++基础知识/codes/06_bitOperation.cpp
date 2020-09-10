#include<iostream>
using namespace std;
int main(){
	short int a = 0xA;
	short int b = 0xC;
	cout<<"a|b = "<<(a|b)<<endl;
	cout<<"a&b = "<<(a&b)<<endl;
	cout<<"~a = "<<(~a)<<endl;
	cout<<"a<<2 = "<<(a<<2)<<endl;
	cout<<"b<<2 = "<<(b<<2)<<endl;
	cout<<"a>>2 = "<<(a>>2)<<endl;
	cout<<"b>>2 = "<<(b>>2)<<endl;
	return 0;
}