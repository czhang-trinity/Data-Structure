#include "Queue.h"
template<typename T>
class ArrayQueue : public Queue<T> {
  public:
    ArrayQueue():elem{new T[10]},size{0},sz{10},begin{0}{}
    
    ArrayQueue(const ArrayQueue& a):elem{new T[size]},size{a.size},sz{a.sz},begin{a.begin}{
      for(int i = 0; i < a.size; ++i){
	  elem[i] = a.elem[i];
	}
    }

    ArrayQueue& operator=(ArrayQueue& a){
      T* p = new T[a.size];
      for(int i=0;i<a.size;++i){
	  p[i] = a.elem[i];
      }
      delete[] elem;
      elem = p;
      begin = a.begin;
      size = a.size;
      sz = a.sz;
      return *this;
    }
 
   ~ArrayQueue(){
     delete[] elem;
   }
   
   ArrayQueue(ArrayQueue&& a):elem{a.elem},size{a.size},sz{a.sz},begin{a.begin}{
     a.elem = nullptr;
     a.size = 0;
     a.sz = 0;
     a.begin = 0;
   }
 
   void enqueue(const T &t){
     if(size == sz){
	    sz *= 2;
        T* p = new T[sz];
        for(int i=0; i<size; ++i){
	        p[i] = elem[(i+begin)%size];
	    }
        delete[] elem;
        elem = p;
        begin = 0;
     }
     elem[(size+begin)% sz] = t;
     size += 1;
   }

   T dequeue(){
     int tmp = begin;
     begin = (begin + 1) % sz;
     size -= 1;
     return elem[tmp];
   } 

   T peek() const{
     return elem[begin];
   }

   bool isEmpty() const{
     return size == 0;
   }  
  private:
    T* elem;
    int size;
    int sz;
    int begin;
};
