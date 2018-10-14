//
// Created by steafan on 2018/10/13.
//

#ifndef DATASTRUCTURE_DUALARRAYDEQUE_H
#define DATASTRUCTURE_DUALARRAYDEQUE_H

#include "arraystack.h"
//array-based conceptual stack
template <class T> class dualarraydeque{
protected:
    arraystack<T> front;
    arraystack<T> back;
    void balance();

public:
    dualarraydeque()= default;
    ~dualarraydeque()= default;
    int size();
    T get(int i);
    T set(int i,T x);
    virtual void add(int i,T x);
    virtual T remove(int i);
    virtual void clear();


};

template <class T> int dualarraydeque<T>::size() {
    return front.size()+back.size();
}

template <class T> void dualarraydeque<T>::clear() {
    front.clear();
    back.clear();
}
//  ]]]]][[[[[[
template <class T> T dualarraydeque<T>::get(int i) {
    if(i<front.size())
        return front.get(front.size()-i-1);
    else
        return back.get(i-front.size());

}

template <class T> T dualarraydeque<T>::set(int i, T x) {
    if(i<front.size())
        return front.set(front.size()-i-1,x);
    else
        return back.set(i-front.size(),x);
}

template <class T> void dualarraydeque<T>::add(int i, T x) {
    if(i<front.size())
        front.add(front.size()-i,x);
    else
        back.add(i-front.size(),x);  //check this out
    balance();
}

template <class T> T dualarraydeque::remove(int i) {
    T x;
    if(i<front.size())
        x=front.remove(front.size()-i-1);
    else{
        x=back.remove(i-front.size());
    }
    balance();
    return x;
}

template <class T> void dualarraydeque<T>::balance() {
    if(3*front.size()<back.size() || 3*back.size()<front.size()){
        int n=front.size()+back.size();
        int nf=n/2;
        array<T> af(std::max(2*nf,1)); //front
        for(int i=0;i<nf;i++)
            af[nf-i-1]=get(i);  //reverse order physically
        int nb=n-nf;
        array<T> ab(std::max(2*nb,1));
        for(int i=0;i<nb;i++)
            ab[i]=get(nf+i);  //correct

    }
}
#endif //DATASTRUCTURE_DUALARRAYDEQUE_H
