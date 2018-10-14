//
// Created by steafan on 2018/10/5.
//

#ifndef DATASTRUCTURE_ARRAYDEQUE_H
#define DATASTRUCTURE_ARRAYDEQUE_H


#include "array.h"
#include "algorithm"
//both end add remove
template <class T> class arraydeque{
protected:
    array<T> a;
    int n,j;//j for start and n for number
     void resize();
public:
    arraydeque();
    virtual ~arraydeque()= default;
    T get(int i);
    T set(int i,T x);
    virtual void add(int i,T x);
    virtual T remove(int i);
    virtual void clear();
    int size();

};



template <class T> arraydeque<T>::arraydeque():a(1) {
    n=0;
    j=0;
}

template <class T> T arraydeque<T>::get(int i) {
    return a[(j+i)%a.length];
}

template <class T> T arraydeque<T>::set(int i, T x) {
    T y=a[(j+i)%a.length];
    a[(j+i)%a.length]=x;
    return y;

}

template<class T> void arraydeque<T>::clear() {
    n=0;
    j=0;
    array<T> b(1);
    a=b;
}

template <class T> void arraydeque<T>::resize() {
    array<T> b(std::max(1,2*n));
    for(int k=0;k<n;k++)
        b[k]=a[(j+k)%a.length];
    a=b;
    j=0;
}

template <class T> void arraydeque<T>::add(int i, T x) { //conceptually i not actual i
    if(n+1>a.length)
        resize();
    if(i<n/2){
        j=(j==0)?a.length-1:j-1;  //overlapping case or normal case
        for(int k=0;k<=i-1;k++)
            a[(j+k)%a.length]=a[(j+k+1)%a.length]; //only shift right hand side
    }
    else{
        for(int k=n;k>i;k--)
            a[(j+k)%a.length]=a[(j+k-1)%a.length];
    }
    a[(j+i)%a.length]=x;
    n++;

}

template <class T> T arraydeque<T>::remove(int i) {
    T x=a[(j+i)%a.length];
    if(i<n/2){
        for(int k=i;k>0;k--)
            a[(j+k)%a.length]=a[(j+k-1)%a.length];
        j=(j+1)%a.length;
    }
    else{
        for(int k=i;k<n-1;k++)
            a[(j+k)%a.length]=a[(j+k+1)%a.length];
    }
    n--;
    if(3*n<a.length)
        resize();
    return x;
}

template <class T> int arraydeque<T>::size() {
    return n;
}
#endif //DATASTRUCTURE_ARRAYDEQUE_H

