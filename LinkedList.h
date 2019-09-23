#include <iostream>
using namespace std;
template<typename T>
class LinkedList{
  struct Node{
    T data;
    Node* prev;
    Node* next;
  };
  public:
    typedef T value_type;
  class iterator{
    public:
     iterator(Node *l):ptr{l}{}

     iterator();

     iterator(const iterator &i):ptr{i.ptr}{}

     T &operator*(){
       return ptr->data;
     } 
     bool operator==(const iterator &i) const{
       return ptr == i.ptr;
     }
     bool operator!=(const iterator &i) const{
       return ptr != i.ptr;
     }
     iterator &operator=(const iterator &i){
       ptr = i.ptr;
       return *this;
     }
     iterator &operator++(){
       ptr = ptr->next;
       return *this;
     }
     iterator &operator--(){
       ptr = ptr->prev;
       return *this;
     }
     iterator operator++(int){
       iterator i(ptr);
       ptr = ptr->next;
       return i;
     }
     iterator operator--(int){
       iterator i(ptr);
       ptr = ptr->prev;
       return i;
     }     
     friend class const_iterator;
     friend class LinkedList;
    private:
     Node* ptr;
  };
  class const_iterator{
    public:
     const_iterator(Node *l):ptr(l){}

     const_iterator();

     const_iterator(const iterator &i):ptr{i.ptr}{}

     const_iterator(const const_iterator &i):ptr{i.ptr}{}

     T &operator*(){
       return ptr->data;
     }
     bool operator==(const const_iterator &i) const{
       return ptr == i.ptr;
     }
     bool operator!=(const const_iterator &i) const{
       return ptr != i.ptr;
     }
     const_iterator &operator=(const const_iterator &i){
       return const_iterator(i.ptr);
     }
     const_iterator &operator++(){
       ptr = ptr->next;
       return *this;
     }
     const_iterator &operator--(){
       ptr = ptr->prev;
       return *this;
     }
     const_iterator operator++(int){
       const_iterator i(ptr);
       ptr = ptr->next;
       return i;
     }
     const_iterator operator--(int){
       const_iterator i(ptr);
       ptr = ptr->prev;
       return i;
     }
    private:
     Node* ptr;
  };

  //general Methods
  //constructor
  LinkedList():sentinel{ new Node()},sz{0}{
    sentinel->data = T();
    sentinel->prev = sentinel;
    sentinel->next = sentinel;
  }
  
  LinkedList(const LinkedList &al){
    sentinel = new Node();
    sentinel->data = al.sentinel->data;
    sentinel->prev = sentinel;
    sentinel->next = sentinel;
    Node* tmp_al = al.sentinel->next;
    for(int i = 0; i < al.sz; ++i){
      (*this).push_back(tmp_al->data);
      tmp_al = tmp_al -> next;
    }
    sz = al.sz;
  }

  LinkedList &operator=(const LinkedList &al) {
    (*this).clear();
    Node* tmp_al = al.sentinel->next;
    for(int i = 0; i < al.sz; ++i){
      (*this).push_back(tmp_al->data);
      tmp_al = tmp_al -> next;
    }
    sz = al.sz;
    return *this;
  }  

 ~LinkedList(){
    
    Node* deleteNode = sentinel;
    for(int i=0; i < sz+1; i++){
      Node* tmp = deleteNode->next;
      delete deleteNode;
      deleteNode = tmp;
    }
    sentinel = nullptr;
  }

  void push_back(const T&t){
    Node* newNode = new Node{t,sentinel->prev,sentinel};
    sentinel->prev->next = newNode;
    sentinel->prev = newNode;
    sz += 1;
  }

  void pop_back(){
    Node* deleteNode = sentinel->prev;
    deleteNode->prev->next = sentinel;
    sentinel->prev = deleteNode->prev;
    delete deleteNode;
    sz -= 1;
  }

  int size() const{
    return sz;
  }  

  void clear(){ 
    Node* deleteNode = sentinel->next;
    for(int i=0; i < sz; ++i){
       Node* tmp = deleteNode->next;
       delete deleteNode;
       deleteNode = tmp;
    }
    sentinel->prev=sentinel;
    sentinel->next=sentinel;
    sz = 0;
  }

  iterator insert(iterator position,const T &t){
    Node* ptr = position.ptr;
    Node* newNode = new Node{t,ptr->prev,ptr};
    ptr->prev->next = newNode;
    ptr->prev = newNode;
    sz += 1;
    return iterator(newNode);
  }

  const T &operator[](int index) const{
    Node* tmp = sentinel;
    for(int i=0;i<index+1;++i){
      tmp = tmp->next;
    }
    return tmp->data;
  }

  T &operator[](int index){
    Node* tmp = sentinel;
    for(int i=0;i<index+1;++i){
      tmp = tmp->next;
    }
    return tmp->data;    
  }

  iterator erase(iterator position){
    Node* ptr = position.ptr;
    Node* tmp = ptr->next;
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    delete ptr;
    sz -= 1;
    return iterator(tmp);
  }

  iterator begin(){
    return iterator(sentinel->next);
  }

  const_iterator begin() const{
    return const_iterator(sentinel->next);
  }

  iterator end(){
    return iterator(sentinel);
  }

  const_iterator end() const{
    return const_iterator(sentinel);
  }

  const_iterator cbegin() const{
    return const_iterator(sentinel->next);
  }

  const_iterator cend() const{
    return const_iterator(sentinel);
  } 
  
  private:
  Node* sentinel;
  int sz;
};
