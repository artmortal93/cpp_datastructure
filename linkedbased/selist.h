//
// Created by steafan on 2018/10/13.
//

#ifndef DATASTRUCTURE_SELIST_H
#define DATASTRUCTURE_SELIST_H
//a space-efficient list
//block based list like std::vector
//element num for each block b-1 to b+1(max b+1),except for last block
//unrolled linked list
#include "../arraybased/arraydeque.h"

template <class T> class selist{
protected:
    int n;
    int b;
    class BoundDeque:public arraydeque<T>{
        using arraydeque<T>::a;
        using arraydeque<T>::j;
        using arraydeque<T>::n;
    public:
         BoundDeque(int b){
            n=0;
            j=0;
            array<T> z(b+1);
            a=z;
        }
        virtual ~BoundDeque()= default;
        virtual void add(int i,T x){
           arraydeque<T>::add(i,x);
        }
        virtual bool add(T x){
            arraydeque<T>::add(size(),x);
            return true;
        };
         void resize(){
        }
    };

    class Node{
    public:
        BoundDeque d;
        Node *prev,*next;
        Node(int b):d(b){}
    };

    Node dummy;

    class Location{
    public:
        Node *u;
        int j=0;
        Location()= default;
        Location(Node *u,int j){
            this->u=u;
            this->j=j;
        }

    };

    void getLocation(int i,Location&ell){
        if(i<n/2){
            Node *u=dummy.next;
            while(i>=u->d.size()){
                i-=u->d.size();
                u=u->next;
            }
            ell.u=u;
            ell.j=i;
        }else{
            Node *u=&dummy;
            int idx=n;
            while(i<idx){
                u=u->prev;
                idx-=u->d.size();
            }
            ell.u=u;
            ell.j=i-idx;

        }
    }

    Node *addBefore(Node *w) {
        auto *u = new Node(b);
        u->prev = w->prev;
        u->next = w;
        u->next->prev = u;
        u->prev->next = u;
        return u;
    }


    void remove(Node *w) {
        w->prev->next = w->next;
        w->next->prev = w->prev;
        delete w;
    }


public:
    selist(int b):dummy(b){
        this->b=b;
        dummy.next=&dummy;
        dummy.prev=&dummy;
        n=0;

    }

    T get(int i){
        Location l;
        getLocation(i,l);
        return l.u->d.get(l.j);
    }

    T set(int i,T x){
        Location l;
        getLocation(i,l);
        T y=l.u->d.get(l.j);
        l.u->d.set(l.j,x);
        return y;
    }

    virtual void clear(){
        Node *u=dummy.next;
        while(u!=&dummy){
            Node *w=u->next;
            delete u;
            u=w;
        }
        n=0;
    }
    virtual ~selist(){
        clear();
    }

    int size(){
        return n;
    }

    void add(T x){
        Node *last=dummy.prev;
        if(last==&dummy || last->d.size()==b+1){
            last=addBefore(&dummy);
        }
        last->d.add(x);
        n++;
    }
    void gather(Node *u){
        Node *w=u;
        for(int j=0;j<b-1;j++){
             while(w->d.size()<b)
                 w->d.add(w->next->d.remove(0));
             w=w->next;
        }
        remove(w);//discard one block to make other b-1 block have b elements
    }

    void spread(Node *u){
        Node *w=u;  //original node of i
        for(int j=0;j<b;j++)
            w=w->next;
        w=addBefore(w);
        while(w!=u){
            while(w->d.size()<b)
                w->d.add(0,w->prev->d.remove(w->prev->d.size()-1));
            w=w->prev;
        }

    }
    void add(int i,T x){
        if(i==n){
            add(x);
            return;
        }
        Location l;
        getLocation(i,l);
        Node *u=l.u;
        int r=0;

        while(r<b && u!=&dummy && u->d.size()==b+1){
            u=u->next;
            r++;
        }
        //case1,search for b step but dont find any slot,spread 1 element to the last block to make u0 element =b,so have space
        if(r==b){
            spread(l.u);
            u=l.u;
        }

        if(u==&dummy){  //case2,if run out of space,add a new node
            u=addBefore(u);
        }
        while(u!=l.u){  //case1,lucky to have space,shift backward
            u->d.add(0,u->prev->d.remove(u->prev->d.size()-1));
            u=u->prev;
        }
        u->d.add(l.j,x);
        n++;

    }
   //constrain:each block should not contain less than b-1 element
    T remove(int i){//find a block could borrow a element
        Location l;
        getLocation(i,l);
        T y=l.u->d.get(l.j);
        Node *u=l.u;
        int r=0;
        while(r<b && u!=&dummy && u->d.size()==b-1){
           u=u->next;
           r++;
        }
        if(r==b)  //case 2,gather and make origin block to b
            gather(l.u);
        u=l.u;
        u->d.remove(l.j);
        while (u->d.size()<b-1 && u->next!=&dummy){
            //case 3 and case 1,to the end or find a apporiate block toborrow
            u->d.add(u->next->d.remove(0));
            u=u->next;
        }  //shifting
        if(u->d.size()==0)
            remove(u);  //remove node,case3
        n--;
        return y;
    }

};


#endif //DATASTRUCTURE_SELIST_H
