#include "Stack.h"
template<typename T>
class ArrayStack : public Stack<T> {
  public:
    ArrayStack():elem{new T[10]},size{0},sz{10}{} 

    ArrayStack(const ArrayStack& a):elem{new T[size]},size{a.size},sz{a.sz}{
      for(int i=0;i<a.size;++i){
	    elem[i] = a.elem[i];
      }
    }

    ArrayStack& operator=(const ArrayStack& a){
      T* p = new T[a.size];
      for(int i=0;i<a.size;++i){
	    p[i] = a.elem[i]; 
      }
      delete[] elem;
      elem = p;
      size = a.size;
      sz = a.sz;
      return *this;
   }

    ArrayStack(ArrayStack&& a):elem{a.elem},sz{a.sz},size{a.size}{
      a.elem = nullptr;
      a.sz = 0;
      a.size = 0;
    }    
    ~ArrayStack(){
      delete[] elem;
    }
    
    void push(const T &t){
      if(size == sz){
        sz *= 2;
	    T* p = new T[size*2];
        for(int i = 0; i < size; ++i){
	        p[i] = elem[i];
	    }
        delete[] elem;
        elem = p;
      }
      elem[size] = t;
      size += 1;
    }

    T pop(){
      size -= 1;
      return elem[size];
    }

    T peek() const {
      return elem[size-1];
    }

    bool isEmpty() const{
     return size == 0;
    }
  private:
    T* elem;
    int size;
    int sz;
};
