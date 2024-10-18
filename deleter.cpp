#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <thread>

using namespace std;

struct B {
    
    B() { b = new int[4]; }
    
    int * b;
    
    ~B() { delete [] b; }
    
    B(const B &) = delete;
    
    void operator= (const B & ) = delete;

};


int main() {
    // unique pointer to array of B objects with custom deleter

    
    unique_ptr<B,function<void(B*) >> pb(new B[2],[](B* element){
         delete [] element; 
         });
    

    


    return 0;
}