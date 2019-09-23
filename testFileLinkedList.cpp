#include <iostream>
#include <cassert>
#include "FileLinkedList.h"
using namespace std;
int main(){
    FileLinkedList<int> a("a.txt");
    for(int i=0;i<3;i++){
        a.push_back(i);
    }
    for(int i=0;i<3;++i){
       assert(a[i] == i);
     }
    assert(a.size() == 3);
    a.insert(a.begin(),7);
    a.insert(a.end(),8);
    assert(a[0]==7);
    assert(a[a.size()-1]==8);
    a.erase(a.begin());
    a.erase(--a.end());
    assert(a[0]==0);
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
    for(int i=0;i<2000;++i){
      a.push_back(i);
      assert(a[i] == i);
    }
    for(int i=0;i<1999;++i){
      a.erase(a.begin());
      assert(a[0] == i+1);
    }
    a.clear();
    FileLinkedList<int> b("a.txt");
    b.push_back(1);
    cout << b.size() << endl;
    cout << b[0] << endl;
    
    return 0;
}
