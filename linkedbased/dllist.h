//
// Created by steafan on 2018/10/13.
//

#ifndef DATASTRUCTURE_DLLIST_H
#define DATASTRUCTURE_DLLIST_H

#include <cstdlib>

//dummy construct a cycle but not a end-to-end structure
//very elegant data structure for dummy node
template <class T> class dllist{
protected:
    struct Node{
        T x;
        Node *prev,*next;

    };
    Node dummy;
    int n;
    Node* getNode(int i);
    Node * addBefore(Node *w,T x);
    void remove(Node *w);
public:
    T get(int i);
    T set(int i ,T x);
    dllist();
    virtual ~dllist();
    int size(){
        return n;
    };
    virtual void add(int i,T x){
        addBefore(getNode(i),x);
    }
    virtual void add(T x){
        add(size(),x);
    }

    T remove(int i){
        if(n==0)
            return NULL;
        Node *w=getNode(i);
        T x=w->x;
        remove(w);
        return x;
    }

    virtual void clear();

};

template <class T> dllist<T>::dllist() {
    dummy.next=&dummy;   //means head
    dummy.prev=&dummy;  //not contain any data,means tail
    n=0;
}


template <class T> Node* dllist<T>::getNode(int i) {
    Node *p;
    if(i<n/2){
        p=dummy.next;//head
        for(int j=0;j<i;j++)
            p=p->next;
    }else{
        p=&dummy;
        for(int j=n;j>i;j--)
            p=p->prev;
    }
    return p;
}

template <class T> T dllist<T>::get(int i) {
    return getNode(i)->x;
}

template <class T> T dllist<T>::set(int i, T x) {
    Node *u=getNode(i);
    T y=u->x;
    u->x=x;
    return y;
}

template <class T> Node* dllist::addBefore(dllist::Node *w, T x) {
    Node* u=new  Node;
    u->x=x;
    u->prev=w->prev;
    u->next=w;
    w->prev=u;
    u->prev->next=u;
    n++;
    return u;
}

template <class T> void dllist::remove(dllist::Node *w) {
    w->prev->next=w->next;
    w->next->prev=w->prev;
    delete w;
    n--;
}

template <class T> dllist::~dllist() {
    clear();

}

template <class T> void dllist::clear() {
    Node*u =dummy.next;
    while(u!=&dummy){
        Node *w=u->next;
        delete u;
        u=w;
    }
    n=0;

}
#endif //DATASTRUCTURE_DLLIST_H
