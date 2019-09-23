#include <iostream>
#include <vector>
#include<string>
#include"ArrayList.h"
using namespace std;

int main(){
  ArrayList<int> a;
  for(int i=1;i<4;i++){
    a.push_back(i);
    cout << a[i-1] << endl;
  }
  a.pop_back();
  cout << a[0] << endl;
  cout << a[1] << endl;
  a.pop_back();
  a.pop_back();
  if(a.isEmpty()){ 
    cout << "The Array is Empty"<< endl;
  }else{
    cout << "The Array is not Empty"<< endl;
  }
  cout << a.size() << endl;
  cout << endl;
  a.push_back(1);
  a.clear();
  for(int i=0; i<20;i++){
    a.insert(i,0);
  }
  for(int i=0; i<a.size();i++){
    cout << a[i] << endl;
  }
  a.remove(0);
  /*for(int i=0;i<a.size();i++){
    cout << a[i] << endl;
  }*/
  for(auto x:a){
    cout << x << endl;
  }
  cout << endl;
  auto i = a.begin();
  cout << *(i++) << endl;
  auto b = a.end();
  b--;
  cout << *(b--)<<endl;
  for(int i=0; i< 2000; ++i){
    a.insert(i,0);
  }  
  for(int i=0; i< 2000; ++i){
    if(a[i] != 1999-i){
       cout << "The Array List does not work." << endl;
       break;
    }
  }
  cout << "Test for ArrayList is over"<< endl;
  ArrayList<string> l;
  string s1{"a"};
  for(int i=0; i<5; ++i){
     l.insert(s1,0);
     s1 += "a";
  }
  for(int i=0; i<5; ++i){
    cout << l[i] << endl;
  } 
  return 0;
}
