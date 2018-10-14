//
// Created by steafan on 2018/10/4.
//

#ifndef DATASTRUCTURE_FASTARRAYSTCAK_H
#define DATASTRUCTURE_FASTARRAYSTCAK_H

#include "arraystack.h"
#include "algorithm"
template <class T> class fastarraystack:public arraystack<T>{
protected:
    using arraystack<T>::a;
    using arraystack<T>::n;  //important if you want reuse base-class component
    virtual void resize();

public:
    virtual ~fastarraystack();
    fastarraystack();
    virtual void add(int i,T x);
    virtual T remove(int i);
};

template <class T> fastarraystack<T>::fastarraystack() : arraystack<T>()
{}

template <class T> fastarraystack<T>::~fastarraystack()  {

}

template <class T> void fastarraystack::resize() {
    array<T> b(std::max(1, 2*n));
    std::copy(a+0, a+n, b+0);  //beware a+n(end) not exist is the last element,check cpp reference/
    a = b;
}

template <class T> T fastarraystack<T>::remove(int i) {
    T x = a[i];
    std::copy(a+i+1, a+n, a+i);
    n--;
    if (a.length >= 3 * n) resize();
    return x;
}

template <class T> void fastarraystack<T>::add(int i, T x) {
    if (n + 1 > a.length) resize();
    std::copy_backward(a+i, a+n, a+n+1);  //reverse copy,very effcient
    a[i] = x;
    n++;
}



#endif //DATASTRUCTURE_FASTARRAYSTCAK_H
