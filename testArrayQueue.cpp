#include "ArrayStack.h"
#include "ArrayQueue.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
  ArrayStack<int> a;
  ArrayStack<int> b;
  ArrayQueue<int> c;
  ArrayQueue<int> d;
  cout << a.isEmpty() << endl;
   for(int i= 0; i < 20; ++i){
    a.push(i);
    cout << "After push "<< i << " Stack is "<< a.isEmpty() << endl;
  }
  b = a;
  for(int i= 0; i < 22; ++i){
    cout << b.pop() << endl;
    cout << "After pop " << i << " times Stack is " <<b.isEmpty() << endl;
  }
  cout << c.isEmpty() << endl;
  c.enqueue(100);
  c.enqueue(99);
  cout << c.dequeue(); 
 for(int i= 0; i < 20; ++i){
   c.enqueue(i);
   cout << c.peek() << endl;
   cout << "After enqueue "<< i << " Queue is "<< c.isEmpty() << endl;
 }
 d = c;
 for(int i= 0; i < 21; ++i){
    cout << d.dequeue() << endl;
    cout << "After dequeue " << i << " times Queue is " <<d.isEmpty() << endl;
 }
 ArrayStack<int> e;
 for(int i=0; i< 2000; ++i){
    e.push(i);
 }
 for(int i=0; i< 2000; ++i){
    if(e.pop() != 1999-i){
       cout << "The stack does not work." << endl;
       break;
    }
 }
 cout << "Test for stack is over"<< endl;
 
 ArrayQueue<int> f;
 for(int i=0; i< 2000; ++i){
    f.enqueue(i);
 }
 for(int i=0; i< 2000; ++i){
    if(f.dequeue() != i){
       cout << "The queue does not work." << endl;
       break;
    }
 }
 cout << "Test for queue is over"<< endl;
 
 ArrayStack<string> g;
 ArrayQueue<string> h;
 string s1{"a"};
 string s2{"b"};
 for(int i=0; i<5; ++i){
    g.push(s1);
    s1 += "a";
 } 
 for(int i=0; i<5; ++i){
   cout << g.pop() << endl;
 }
 for(int i=0; i<5; ++i){
    h.enqueue(s2);
    s2 += "b";
 }
 for(int i=0; i<5; ++i){
   cout << h.dequeue() << endl;
 }
  return 0;
}
