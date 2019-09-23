#include <iostream> 
using namespace std;

int main(void){
	int a = 1;
	int b = 2;
	int sum = 0;
	while(a<4000000 && b <4000000){
		if(a %2 == 0){
			sum += a;
		}else if( b%2 ==0){
			sum += b;
		}
		a += b;
		b += a; 		
	}
	cout << sum << "\n";
	return 0;
}
