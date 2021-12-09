#include <iostream>
using namespace std;

struct Obj {

    virtual void init() { cout << "Obj"; }
};

struct Wood : public Obj {
    virtual void init() { cout << "Wood"; }
};


struct Glue : public Obj {
    virtual void init() { cout << "Glue"; }
};

struct Program {

    // Pass by reference the actual object. You want it created it here?
    // Why just create it outside. i.e move your case to the place where you know what i 
    // is. It doesn't have to be created here.
    void foo(Obj& o) {
        o.init();
    }
};



int main()
{
    Program p;
    Obj* ref_p;

    // Move your case here.
    //case
    Wood w;
    ref_p = &w;
    // 
        //Glue g;
        //ref_p = &g;

    p.foo(*ref_p);
}