#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <thread>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v = {1, 3, 4, 5, 6, 7, 8, 9};
    vector<int> b = {1, 3, 4, 5, 6, 7, 8, 9};

    // printing v
    cout << "vector v:" << endl;
    for (auto x : v) { cout << x << " ";};
    cout << endl;

    // Printing odd numbers in v
    cout << "Odd numbers in v Part:" << endl;
    for_each(v.cbegin(), v.cend(), [](int element) 
    {if (element%2!=0){
        cout<<element<<" ";
    } 
    });cout<<endl;
    //Write another for_each statement that changes the values in v 
    //by multipliying all odd numbers by 2
    cout << "Multiplying v Part:" << endl;
    for_each(v.cbegin(), v.cend(), [&v](int a) 
    {if (a%2!=0){
        replace(v.begin(), v.end(),a, a*2);

    }
    });
    for (auto x : v) { cout << x << " ";};
    cout << endl;
    cout<< "Adding the size of v to each element in v, where the size of v is: "<< b.size()<< " Part"<< endl;
    for_each(b.cbegin(), b.cend(), [&b](int a) 
    { a+=b.size();
    cout << a<<" ";
    }
    );cout<<endl;
    cout<<"Change data outside scop of lambda Part:"<<endl;
    int outsidedata = 0;
    cout << "Before lambda: " << outsidedata << endl;
    [& outsidedata]() {
        outsidedata=100;
    }();
    cout<<"After lambda "<<outsidedata<<endl;











}