#include <iostream>
#include "cstack.h"
#include "revstack.h"

using namespace std;

int main()
{
    Stack       s;
    RevStack    r;

    cout << "\t\tClearing stack" << endl;
    s.clear();

    cout << "\t\ts.height() = " << s.height() << endl;
    cout << "\t\ts.pop()    = " << s.pop() << endl;
    cout << "\t\tpushing 1,2,3" << endl;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "\t\ts.height() = " << s.height() << endl;
    cout << "\t\ts.top()    = " << s.top() << endl;

    cout << "\t\ts.pop()    = " << s.pop() << endl;
    cout << "\t\ts.pop()    = " << s.pop() << endl;
    cout << "\t\ts.pop()    = " << s.pop() << endl;
    cout << "\t\ts.height() = " << s.height() << endl;
    cout << "\t\tpushing 1,2,3" << endl;
    r.push(1);
    r.push(2);
    r.push(3);
    cout << "\t\treversing" << endl;
    r.reverse();
    cout << "\t\tr.pop()    = " << r.pop() << endl;
    cout << "\t\tr.pop()    = " << r.pop() << endl;
    cout << "\t\tr.pop()    = " << r.pop() << endl;

    return 0;
}
