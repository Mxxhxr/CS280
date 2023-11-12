#include <iostream>
using namespace std;
#include <stack>

int main() {
    stack<int> intStack;
    for (int i=0; i<10; ++i) {
        intStack.push(i);
        cout << "pushing " << i << " to stack" << endl;
    }

    while (!intStack.empty()) {
        cout << intStack.top() << endl;
        intStack.pop();
    }
}