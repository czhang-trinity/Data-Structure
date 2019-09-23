#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "LinkedList.h"
using namespace std;

int main(){
  LinkedList<int> a;
  //test push back
  for(int i=1;i<4;++i){
    a.push_back(i);
  }
  for(int i=0;i<3;++i){
    assert(a[0] == 1);
  }
  LinkedList<int> f(a);
  for(int i=0;i<3;++i){
    assert(f[i] == i+1);
  }
  assert(a.size() == 3);
  LinkedList<int> b;
  b = a;
  for(int i = 1; i < 4; ++i){
    assert(b[i-1] = i);
    assert(a[i-1] = i);
  }
  a.insert(a.begin(),7);
  a.insert(a.end(),8);
  assert(a[0]==7);
  assert(a[a.size()-1]==8);
  a.erase(a.begin());
  a.erase(--a.end());
  assert(a[0]==1);
  assert(a[a.size()-2]==2);
  a.clear();
  assert(a.size()==0);
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);
  a.pop_back();
  assert(a.size() == 2);
  a.insert(++a.begin(),10);
  assert(a[1] == 10);
  assert(a[2] == 2);
  a.erase(++a.begin());
  assert(a[1] == 2);
  a.clear();
  for(int i=0;i<10;++i){
    a.push_back(i);
  }
  b = a;
 // for(auto x:b){
 //   cout << x << endl;
 // }
  a.clear();
  for(int i=0;i<2000;++i){
    a.push_back(i);
    assert(a[i] == i);
  }
  b = a;
  for(int i=0;i<1999;++i){
    b.erase(b.begin());
    assert(b[0] == i+1);
  }
  LinkedList<string> c;
  for(int i=0;i<5;++i){
    c.push_back("a");
  }
  for(int i=0;i<5;++i){
    assert(c[i]=="a");
  }
  return 0;
}
