#include "expressio.hpp"
#include <iostream>
using namespace std:

int main()
{
	token t(1);
	token t2(1);
	expressio e(t);
	expressio e2(t2);
	bool igual = (e == e2);
	cout << igual << endl;
}
