#include<iostream>
using namespace std;
int main(){
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int len = sizeof(a)/sizeof(a[0]);
	cout<<"len = "<<len<<endl;
	for(int i=0;i<len;i++){
		cout<<"a["<<i<<"] = "<<a[i]<<";"<<endl;
	}
	return 0;
}