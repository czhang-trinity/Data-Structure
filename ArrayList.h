#include <stdexcept>
template<typename T>
class ArrayList {
 public:
 class iterator{
  public:
   iterator(T *l):p{l}{}

   iterator();

   iterator(const iterator &i):p{i.p}{} 

   T& operator*(){
     return *p;
   }

   bool operator==(const iterator &i) const {
     return p == i.p;
   }

   bool operator!=(const iterator &i) const {
     return p != i.p;
   }

   iterator &operator=(const iterator&i) {
     p = i.p;
     return *this;
   }

   iterator &operator++() {
     p++;
     return *this;
   }

   iterator &operator--() {
     p--;
     return *this;
   }

   iterator operator++(int) {
     iterator i(p);
     p++;
     return i;
   }

   iterator operator--(int){
     iterator i(p);
     p--;
     return i;
   }
  private:
   T* p;
 };

 class const_iterator{
  public:
   const_iterator(T *l):p{l}{}

   const_iterator();

   const_iterator(const const_iterator &i):p{i.p}{}

   const T &operator*(){
     return *p;
   }

   bool operator==(const const_iterator &i) const {
     return p == i.p;
   }

   bool operator!=(const const_iterator &i) const {
     return p != i.p;
   }
   const_iterator &operator++(){
     p++;
     return *this;
   }

   const_iterator &operator--() {
     p--;
     return *this;
   }

   const_iterator operator++(int) {
     const_iterator i(p);
     p++;
     return i;
   }

   const_iterator operator--(int){
     const_iterator i(p);
     p--;
     return i;
   }
  private:
   T* p;
 };
  ArrayList():elem{new T[10]},sz{0},capacity{10}{}
 
  ArrayList(const ArrayList &that):elem{new T[that.capacity]},sz{that.sz},capacity{that.capacity}{
    for(int i=0; i < sz; ++i){
      elem[i] = that.elem[i];
    }
  }

  ArrayList<T> &operator=(const ArrayList<T> &al){
    T *p = new T[al.capacity];
    for(int i=0; i < al.sz; ++i){
       p[i] = al.elem[i];
    }
    delete[] elem;
    elem = p;
    sz = al.sz;
    capacity = al.capacity;
    return *this;    
  }

  ~ArrayList(){
    delete[] elem; 
  }

  void push_back(const T &t){
    if(sz == capacity){
      capacity *= 2;
      T *p = new T[capacity];
      for(int i = 0; i < sz; i++){
    	p[i] = elem[i];  
      }
      delete[] elem;
      elem = p;
    }
    elem[sz] = t;
    sz += 1;
  }
  void pop_back() {
    sz -= 1;
  }
  
  int size() const{
    return sz;
  }

  void clear(){
    sz = 0;
  }

  void insert(const T &t, int index){
    if(sz == capacity){
      capacity *= 2;
      T *p = new T[capacity];
      for(int i = 0; i < sz; i++){
        p[i] = elem[i];
      }
      delete[] elem;
      elem = p;
    }
    for(int i = sz; i > index; i--){
      elem[i] = elem[i-1];
    }
    elem[index] = t;
    sz += 1;  
  }

  const T &operator[](int index) const{
    if(index >=0 && index < sz){
      return elem[index];
    }else {
      throw std::out_of_range("The index is out of bound");
    }
  }
  
  T &operator[](int index) {
    if(index >= 0 && index < sz){
      return elem[index];
    }else{
      throw std::out_of_range("The index is out of bound");
    }    
  }
  
  void remove(int index){
    for(int i = index; i < sz-1; i++){
      elem[i] = elem[i+1];
    }
    sz -= 1;
  }

  iterator begin(){
      iterator i{elem};
      return i;
  }
  
  const_iterator begin() const{
      const_iterator i{elem};
      return i;
  }
 
  iterator end(){
      iterator i{elem};
      for(int x=0; x< sz; ++x){
         i++;
      }
      return i;
  }
  
  const_iterator end() const {
      const_iterator i{elem};
      for(int x=0; x< sz; ++x){
         i++;
      }
      return i;
  }  
  const_iterator cbegin() const {
      const_iterator i{elem};
      return i;
  }
  
  const_iterator cend() const {
      const_iterator i{elem};
      for(int x=0; x< sz; ++x){
         i++;
      }
      return i;  
  }

  bool isEmpty() const{
    return sz == 0;
  }
 private: 
  T *elem;
  int sz;
  int capacity;
};
