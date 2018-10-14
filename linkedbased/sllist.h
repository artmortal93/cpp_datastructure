//
// Created by steafan on 2018/10/13.
//

#ifndef DATASTRUCTURE_SLLIST_H
#define DATASTRUCTURE_SLLIST_H

#include <cstdlib>

template <class T> class sllist{
    T null;///could converted from NULL,small but important trick
protected:
    class Node{
    public:
        T x;
        Node *next;
        Node(T x0){
            x=x0;
            next= NULL;

        }
    };
    Node *head;
    Node *tail;
    int n; //num of node
public:
    sllist(){
        head=tail=NULL;
        n=0;
        null=(T)NULL;
    }
    T push(T x){  //stack operation,add in head
        Node *u=new Node(x);
        u->next=head;
        head=u;
        if(n==0)
            tail=u;
        n++;
        return x;

    }
    T pop(){  //stack operation,remove head
        if(n==0)
            return NULL;
        T x=head->x;
        Node *u=head;
        head=head->next;
        delete u;
        if(--n==0)
            tail=NULL;
        return x;

    }

     T remove(){  //queue operations,FIFO,add on the tail,remove on the head
        if(n==0)
            return NULL;
        T x=head->x;
        Node *u=head;
        head=head->next;
        delete u;
        if(--n==0)
            tail=NULL;
        return x;
    }

    bool add(T x){
        Node *u=new Node(x);
        if(n==0)
            head=u;
        else
            tail->next=u;
        tail=u;
        n++;
        return true;
    }


};

#endif //DATASTRUCTURE_SLLIST_H
