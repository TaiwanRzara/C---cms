#ifndef LIBBUS_H_
#define LIBBUS_H_
#include <bits/stdc++.h>
using namespace std;

int __n, __a, __b, __cnt = 0;
int __ID[1005]; // 請不要在你的主程式中呼叫這些變數，他們只是給你測試用的而已


int init() {
    cout << "please enter a and b \n";
    cin >> __a >> __b;
    __n = 2 * __a + __b;
	cout << "n = " << __n << endl;
    cout << "give n to user? (0/1)\n";
    int type; cin >> type;
    
    cout << "please enter a numbers \n";
    for (int i = 0; i < __a; ++i) {
        cin >> __ID[i];
        __ID[__n - i - 1] = __ID[i];
    }
    cout << "please enter b numbers \n";
    for (int i = 0; i < __b; ++i) {
        cin >> __ID[__a+i];
    }
    if (type) {
        return __n;
    }
    return -1;
}

int query(int step) {
	__cnt++;
	int index = 0;
	if (step >= 0) {
		index = step;
	} else {
		index = __n-1+step;
	}

	if (index >= 0 && index < __n) {
		return __ID[index];
	} else {
		return -1;
	}

}

void report(int a, int b) {
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "count = " << __cnt << endl;
}
#endif
