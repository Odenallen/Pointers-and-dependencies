#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <thread>

using namespace std;




struct BhasA;
struct AhasB {
    AhasB(shared_ptr<BhasA> b) : m_b(b)  {
        resource = new int[4];
    };
    
    shared_ptr<BhasA> m_b;
    
    int * resource;
    
    ~AhasB() {delete [] resource;}
    
    AhasB(const AhasB &) = delete;
    
    void operator=(const AhasB &) = delete;
    
    };

struct BhasA {
    BhasA() {resource = new int[4];};
    
    weak_ptr<AhasB> m_a;    // weak pointer pointing at AhasB struct, this is the circular dependency and is assigned.
    
    int * resource;
    
    ~BhasA() {delete [] resource;}
    
    BhasA(const BhasA &) = delete;
    
    void operator=(const BhasA &) = delete;
};

int main(){

    shared_ptr<BhasA> bptr(new BhasA); //shared pointer pointing at BhasA struct
    
    shared_ptr<AhasB> aptr(new AhasB(bptr));
    
    bptr->m_a=aptr;







    return 0;
}