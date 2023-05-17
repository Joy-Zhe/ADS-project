#include "timeSpan.h"



int main() {
    int n, num, type;
    int m;
    cout << "choose the test type(0 for sequence, 1 for random, 2 for diy):";
    cin >> type;
    Test test;
    if(type == 0) {
        cout << endl << "choose the number scale of the data set(<30000):";
        cin >> n;
        test.sequenceTest(n);
    }
    else if(type == 1) {
        cout << endl << "choose the number scale of the data set(<30000):";
        cin >> n;
        cout << endl << "choose the number of insertions(<scale):";
        cin >> m;
        test.randomTest(n, m);
    }
    else {
        cout << endl << "choose the number scale of the data set:"
            << endl << "input n insertion numbers('+' represents insertion, '-' represents deletion):";
        cin >> n;
        test.diyTest(n);
    }
    return 0;
}