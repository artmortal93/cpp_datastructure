//
// Created by steafan on 2018/10/13.
//

#ifndef DATASTRUCTURE_ROOTISHARRAYSTACK_H
#define DATASTRUCTURE_ROOTISHARRAYSTACK_H
//space efficient stack
#include <cmath>
#include "arraystack.h"
using namespace std;

template <class T> class rootisharraystack{
protected:
    int n=0;
    void grow();
    void shrink();
    arraystack<T*> blocks;  //stack element f array ,block b contain b+1 element
    int i2b(int i);
public:
    rootisharraystack()= default;
    ~rootisharraystack()= default;
    int size(){
        return n;
    };
    T get(int i);
    T set(int i, T x);
    virtual void add(int i, T x);
    virtual T remove(int i);
    virtual void clear();
};


template <class T> int rootisharraystack::i2b(int i) {
    double db=(-3.0+std::sqrt(9+8*i))/2.0;
    int b=(int)ceil(db);
    return b;
}
template <class T> T rootisharraystack::get(int i) {
    int b =i2b(i);
    int j= i-b*(b+1)/2;
    return blocks.get(b)[j];

}

template <class T> T rootisharraystack::set(int i, T x) {
    int b =i2b(i);
    int j= i-b*(b+1)/2;
    T y=blocks.get(b)[j];
    blocks.get(b)[j]=x;
    return y;
}

template <class T> void rootisharraystack::grow() {
     blocks.add(blocks.size(),new T[blocks.size()+1]);
}

template <class T> void rootisharraystack::add(int i, T x) {
    int r=blocks.size();
    if(r*(r+1)/2<n+1)
        grow();   //not sufficient capacity(full)
    n++;
    for(int j=n-1;j>i;j--)
        set(j,get(i-1));  //bigger then shift
    set(i,x);
}

template <class T> T rootisharraystack::remove(int i) {
    T x=get(i);
    for(int j=i;j<n-1;j++)
        set(j,get(j+1));
    n--;
    int r=blocks.size();
    if((r-2)*(r-1)/2>=n)   //if more then two empty block,delete
        shrink();
    return x;
}

template <class T> void rootisharraystack::shrink() {
    int r=blocks.size();
    while(r>0 && (r-2)*(r-1)/2>=n){
        delete[] blocks.remove(blocks.size()-1);
        r--;

    }
}
template <class T> void rootisharraystack::clear() {
    while(blocks.size()>0)
        delete[] blocks.remove(blocks.size()-1);
}
#endif //DATASTRUCTURE_ROOTISHARRAYSTACK_H
