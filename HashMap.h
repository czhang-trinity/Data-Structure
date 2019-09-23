#include <vector>
#include<type_traits>
using namespace std;
template<typename K, typename V, typename Hash>
class HashMap {
    private:
        Hash hashFunction;
        vector<vector<pair<K,V>>> table;
        int sz;
        int capacity;
    public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;
    class const_iterator;
    class iterator{
        private:
          typename std::remove_reference<decltype(table.begin())>::type mainIter; 
          typename std::remove_reference<decltype(table.begin())>::type mainEnd;
          typename std::remove_reference<decltype(table[0].begin())>::type subIter;
        public:
          friend class const_iterator;
          friend class HashMap;
          iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()){
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
          }

          iterator(const decltype(mainIter) mi, const decltype(mainEnd) me, const decltype(subIter) si):mainIter(mi),mainEnd(me),subIter(si){}

          bool operator==(const iterator &i) const{
            return mainIter == i.mainIter && (mainIter==mainEnd || subIter ==i.subIter);
          }

          bool operator!=(const iterator &i) const{
            return !(*this == i);
          }

          std::pair<K,V> &operator*() {
            return *subIter;
          }

          iterator &operator++(){
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()){
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
          }

          iterator operator++(int){
            iterator tmp(*this);
            ++(*this);
            return tmp;
          }
    };

    class const_iterator{
        typename std::remove_reference<decltype(table.cbegin())>::type mainIter;
        typename std::remove_reference<decltype(table.cbegin())>::type mainEnd;
        typename std::remove_reference<decltype(table[0].cbegin())>::type subIter;
        public:
          friend class HashMap;
          const_iterator(const decltype(table.cbegin()) mi, const decltype(table.cbegin()) me): mainIter(mi), mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd & subIter == mainIter->end()){
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
          }

          const_iterator(const decltype(table.cbegin()) mi,const decltype(table.cbegin()) me,const decltype(table[0].cbegin()) si):
           mainIter(mi),mainEnd(me),subIter(si) {}

          const_iterator(const decltype(table.begin()) mi,const decltype(table.begin()) me,const decltype(table[0].begin()) si):
              mainIter(mi),mainEnd(me),subIter(si) {}
                                                  

          const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter) {
          
          }

          bool operator==(const const_iterator &i) const{
            return mainIter == i.mainIter && (mainIter == mainEnd || subIter==i.subIter); 
          }

          bool operator!=(const const_iterator &i) const{
            return !(*this==i);
          }

          const std::pair<K,V> &operator*() const{
            return *subIter;
          }

          const_iterator &operator++(){
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()){
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
          }

          const_iterator operator++(int){
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
          }
    };

    HashMap(const Hash &hf){
        hashFunction = hf;
        capacity = 100;
        //vector<vector<pair<K,V>>> vec(capacity,vector<pair<K,V>>(1));
        //table = vec;
        table.resize(capacity);
        sz = 0;
    }

    bool empty() const{
        return sz == 0; 
    }

    unsigned int size() const{
        return sz;
    }

    iterator find(const key_type& k){
        int index = hashFunction(k) % table.size();
        for(auto i=table[index].begin();i!=table[index].end();i++){
            if(k == (*i).first){
                return iterator(table.begin()+index,table.end(),i);
            }
        }
        return end();
    } 

    const_iterator find(const key_type& k) const{        
        int index = hashFunction(k) % table.size();
        for(auto i=table[index].begin();i!=table[index].end();i++){
            if(k == (*i).first){
               return const_iterator(table.begin()+index,table.end(),i);
            }
       }
       return cend();
    }

    int count(const key_type& k) const{
        auto i = find(k);
        int index = 0;
        if(i != end()){
            index = 1;
        }
        return index;
    }

    std::pair<iterator,bool> insert(const value_type& val){
        if(sz >= capacity*0.5){
            growTableAndRehash();
        }
        auto i = find(val.first);
        if (i == end()) {
            int index = hashFunction(val.first) % table.size();
            auto subIter = table[index].insert(table[index].begin(),val);
            sz += 1;
            return make_pair(iterator(table.begin()+index,table.end(),subIter),true);
        }else{
            return make_pair(i,false);
        }
    }

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last){
        for(auto i=first;i!=last;i++){
            insert(*i);
        }
    }

    iterator erase(const_iterator position){
        auto index = position.mainIter - table.begin();
        auto i = table[index].erase(position.subIter);
        sz -= 1;
        return iterator(table.begin()+index,table.end(),i);
    }

    int erase(const key_type& k){
        auto i = find(k);
        if(i == end()){
            return 0;
        }else{
            erase(i);
            return 1;
        }
    }

    void clear(){
       //for(auto i = cbegin();i != cend();i++){
        //  if(*i != make_pair(K(),V())){
        //    erase(i);
       //   }
      // }
       table.clear();
       table.resize(capacity);
       //vector<vector<pair<K,V>>> vec(capacity,vector<pair<K,V>>(1));
       //table = vec;
       sz = 0;
    }

    mapped_type &operator[](const K &key){
        auto i = find(key);
        if(i == end()){
            return (*insert(make_pair(key,V())).first).second;
        }else{
            return (*i).second;
        }
    }

    bool operator==(const HashMap<K,V,Hash>& rhs) const{
        //auto ri = rhs.begin();
        if (sz == rhs.sz){
            for(auto i=begin();i != end();++i){
                int is_found = count((*i).first);
                if (is_found == 0){
                    return false;
                }
                //if(*ri != *i){
                //    return false;
                //}
                //ri++;
            }
            return true;
        }else{
            return false;
        }
    }

    bool operator!=(const HashMap<K,V,Hash>& rhs) const{
        return !(*this==rhs);
    }

    iterator begin(){
        return iterator(table.begin(),table.end());
    }

    const_iterator begin() const{
        return const_iterator(table.begin(),table.end());
    }

    iterator end(){
        return iterator(table.end(),table.end());
    }

    const_iterator end() const{
        return const_iterator(table.end(),table.end());
    }

    const_iterator cbegin() const{
        return const_iterator(table.begin(),table.end());
    }

    const_iterator cend() const{
        return const_iterator(table.end(),table.end());
    }
    private:
     void growTableAndRehash(){
        HashMap<K,V,Hash> hashMap((*this).hashFunction);
        hashMap = *(this);
        capacity *= 10;
        //vector<vector<pair<K,V>>> vec(capacity,vector<pair<K,V>>(1));
        //table = vec;
        table.clear();
        table.resize(capacity);
        sz = 0;
        for(auto i=hashMap.begin();i!=hashMap.end();++i){
                insert(*i);
        }
     }
};
