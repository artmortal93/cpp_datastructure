//
// Created by steafan on 2018/10/4.
//

#ifndef DATASTRUCTURE_ARRAYSTACK_H
#define DATASTRUCTURE_ARRAYSTACK_H

#include <algorithm>
#include "array.h"
template <class T> class arraystack{
public:

    array<T> a;
    int n; //actually number,a.length>n

    arraystack();
    virtual ~arraystack();
    virtual void resize();
    virtual void clear();
    int size(){
        return n;
    }
    T get(int i){
        return a[i];
    }
    T set(int i,T x){
        T y=a[i];

    }
    virtual void add(int i,T x);
    virtual void add(T x) { add(size(), x); }

    virtual void push(T x){
        add(n,x);
    }


    virtual T pop(){
        return remove(n-1);
    }


    virtual T remove(int i);
};

template <class T> arraystack<T>::arraystack():a(1),n(0) {

}
template<class T> arraystack<T>::~arraystack()=default {
}
template <class T> void arraystack<T>::resize() {
    array<T> b(std::max(2*n,1));
    //std::copy(a[0],a[n],b[0]);
    for(int i=0;i<n;i++)
        b[i]=a[i];
    a=b;
}
template <class T> void arraystack<T>::add(int i, T x) {//charu
    if(n+1>a.length)
        resize();
    for(int j=n;j>i;j--)
        a[j]=a[j-1];
    a[i]=x;
    n++;
}
template <class T> T arraystack<T>::remove(int i) {
     T x=a[i];
     for(int j=i;j<n-1;j++)
         a[j]=a[j+1];
     n--;
     if(a.length>=3*n)
         resize();
     return x;
}

template <class T> void arraystack<T>::clear() {
    n=0;
    array<T> b(1);
    a=b;
}
#endif //DATASTRUCTURE_ARRAYSTACK_H
