#include<iostream>
using namespace std;

class Account{
	private:
		double amount;
		string owner;
	public:
		static double interestRate;//静态变量定义
		Account(double pamount,string powner){
			amount = pamount;
			owner = powner;
		}
		
		static double getInterestRate(){//静态函数定义
			return interestRate;
		}
};

double Account::interestRate = 0.589;
int main(){
	Account account1 = Account(1000,"张三");
	cout<<"Account::interestRate = "<<Account::interestRate<<endl;//通过类::静态变量访问
	cout<<"Account::getInterestRate() = "<<Account::getInterestRate()<<endl;//通过类::静态函数访问
	cout<<"account1.getInterestRate() = "<<account1.getInterestRate()<<endl;//通过对象.静态函数访问
	cout<<"account1.interestRate = "<<account1.interestRate<<endl;//通过对象.静态变量访问
	
	return 0;
}
	