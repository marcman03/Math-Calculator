#include <iostream>
using namespace std;

int mcd(int n1, int n2)
{
	if (n1 == 0) {
		return n2;
	}
	else if (n2 == 0){
		return n1;
	}
	else {
		return mcd(n2%n1, n1);
	}
}

int mcm(int n1, int n2)
{
	int max = std::max(n1,n2);
	int min = std::min(n1,n2);
	int aux = (max/mcd(max,min))*min;
	return aux;
}

int main()
{
	int n1 = 42334;
	int n2 = 1677;
	int n3 = 53899;
	int n4 = -13398;
	int aux = mcm(n1,n2);
	//if (aux < 0) {
	//	aux = aux*-1;
	//}
	int n5 = n3 * aux/n1;
	int n6 = n4 * aux/n2;
	cout << (n5 < n6) << endl;
	
}
