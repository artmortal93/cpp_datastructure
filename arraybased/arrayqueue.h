//
// Created by steafan on 2018/10/4.
//

#ifndef DATASTRUCTURE_ARRAYQUEUE_H
#define DATASTRUCTURE_ARRAYQUEUE_H

#include "array.h"
#include <algorithm>

template <class T> class arrayqueue{
protected:
    array<T> a;
    int j,n;
    void resize();
public://j for start,n for number of element
    virtual~ arrayqueue();
    arrayqueue();
    virtual bool add(T x);
    int size(){
        return n;
    };
    virtual T remove();


};


template <class T> arrayqueue<T>::arrayqueue() : a(1){
    n=0;
    j=0;
}

template <class T> arrayqueue<T>::~arrayqueue()=default {}

template <class T> bool arrayqueue<T>::add(T x) {

}

template <class T> void arrayqueue<T>::resize() {
    array<T> b(std::max(1,2*n));
    for(int k=0;k<n;k++){
        b[k]=a[(j+k)%a.length];
    }
    a=b;
    j=0;//reset
}

template <class T> bool arrayqueue<T>::add(T x) {
    if((n+1)>a.length)
        resize();
    a[(j+n)%a.length]=x;
    n++;
    return true;
}

template <class T> T arrayqueue<T>::remove() {
    T x=a[j];
    j=(j+1)%a.length;
    n--;
    if(a.length>3n)
        resize();
    return x;
}




#endif //DATASTRUCTURE_ARRAYQUEUE_H
