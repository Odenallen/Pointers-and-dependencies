#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <thread>
using namespace std;







struct A {
int data;
};
void foo(unique_ptr<A> p) {
cout << p->data << endl;
}
void foo2(shared_ptr<A> p) {
cout << p->data << endl;
}

int main() {

    unique_ptr<A> pa(new A {4} );               //unique pointer, pointing at A-struct with data 4
    cout << pa -> data;                         //print data of A-struct
    foo(move(pa)); cout<< endl;                 //move the unique pointer to foo, print data of A-struct

    // Now use a shared ptr
    shared_ptr<A> sa(new A {5});
    cout << sa -> data<<endl;                   //print data of A-struct

    foo2(sa);                                   // no memory leak, because shared pointer is copied
    // foo2(move(sa));                             // no memory leak, because shared pointer is moved
    if (sa == nullptr) {
        cout << "sa is null" << endl;
    }
    // Weak ptr
    weak_ptr<A> wa = sa;
    cout<< "Are we here"<<endl;
    cout << wa.lock()->data;            
    cout<< " \nAre we Done?"<<endl;

}