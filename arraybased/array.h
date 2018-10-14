//
// Created by steafan on 2018/10/4.
//

#ifndef DATASTRUCTURE_ARRAY_H
#define DATASTRUCTURE_ARRAY_H


#include <cassert>
#include "algorithm"
template <class T> class array {
public:
    int length;
    T* a;
    explicit array(int len);
    array(int len,T init);

    T&operator[](int i){
        assert(i>0 && i<length);
        return a[i];
    };

    array<T>& operator=(array<T> &b){
        if(a!=NULL)
            delete[] a;
        a=b.a;
        b.a=NULL;
        length=b.length;
        return *this;
    }

    T*operator+(int i){
        return &a[i];
    }

    void swap(int i, int j){
        T x=a[i];
        a[i]=a[j];
        a[j]=x;

    }
    void fill(T x);
    virtual ~array();
    virtual void reverse();
    static void copyOfrange(array<T> &a0,array<T> &a,int i,int j);

};

template <class T> array<T>::array(int len) {
    length=len;
    a=new T[length];
}

template <class T> array<T>::~array() {
    if(a!=NULL)
        delete [] a;
}
template <class T> array<T>::array(int len, T init) {
    length=len;
    a=new T[length];
    for(int i=0;i<length;i++)
        a[i]=init;
}

template<class T>
void array<T>::reverse() {
    for (int i = 0; i < length/2; i++) {
        swap(i, length-i-1);
    }
}

template<class T>
void array<T>::fill(T x) {
    std::fill(a, a+length, x);
}


template <class T> void array<T>::copyOfrange(array<T> &a0, array<T> &a, int i, int j) {
     array<T> b(j-i);//j will be end of empty elements
     std::copy(a.a+i,a.a+j,b.a);  //copy a[i]-a[j] to a0
     a0=b;

}
#endif //DATASTRUCTURE_ARRAY_H
