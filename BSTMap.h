#include<utility>
#include<iostream>
using namespace std;
template<typename K, typename V>
class BSTMap{
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    struct Node{
        value_type data;
        Node* left;
        Node* right;
        Node* parent;
    };
    int sz;
    Node* root;
    static Node* findNode(Node* node, const key_type& k){
	    if(node==nullptr)return nullptr;
        auto key = (node->data).first;
        if( key == k){
            return node;
        }else if(k < key && node->left != nullptr){
            return findNode(node->left,k);
        }else if(k > key && node->right != nullptr){
            return findNode(node->right,k);
        }else{
            return nullptr;
        }
    }


    void insertNode(value_type val, Node* node){
        if(val.first < (node->data).first){
            if (node -> left == nullptr){
                node -> left = new Node{val,nullptr,nullptr,node};
            }else{
                insertNode(val,node->left);
            }
        }else{
            if(node -> right == nullptr){
                node -> right = new Node{val,nullptr,nullptr,node};
            }else{
                insertNode(val,node->right);
            }
        }
    }

    void preOrderInsert(Node* node){
        insert(node->data);
        if(node->left != nullptr){
            preOrderInsert(node->left);
        }
        if(node->right != nullptr){
            preOrderInsert(node->right);
        }
    }

    static Node* successor(Node* node){
        Node* ptr;
        if(node->right == nullptr){
            ptr = node;
            while(ptr->parent != nullptr && ptr->parent->right == ptr){
                ptr = ptr -> parent;
            }
            return ptr->parent;
        }else{
            ptr = node -> right;
            while(ptr -> left != nullptr){
                ptr = ptr -> left;
            }
            return ptr;
        }
    }

    static Node* predecessor(Node* node){
        Node* ptr;
        if(node->left == nullptr){
           ptr = node;
           while(ptr->parent != nullptr && ptr->parent->left == ptr){
               ptr = ptr -> parent;     
           }
           return ptr -> parent;
        }else{
            ptr = node->left;
            while(ptr->right != nullptr){
                ptr = ptr -> right;
            }
            return ptr;
        }
    }

    Node* findMaxNode(Node* node) const{
        Node* ptr = node;
    	if (ptr==nullptr) return nullptr;
        while(ptr->right != nullptr){
            ptr = ptr->right;
        }
        return ptr;
    }

    Node* findMinNode(Node* node) const{
        Node* ptr = node;
        if(ptr ==nullptr) return nullptr;
        while(ptr->left != nullptr){
            ptr = ptr->left;
        }
        return ptr;
    }
    
    public:
     class const_iterator;
      class iterator{
        private:
            Node* ptr;
            bool isEnd;
        public:
        friend class const_iterator;
        friend class BSTMap<K,V>;
        iterator(Node* node,bool isend){
            ptr = node;
            isEnd = isend;
        }

        iterator(const const_iterator &i){
            ptr = i.ptr;
            isEnd = i.isEnd;
        }

        bool operator==(const iterator &i) const {
            return ptr == i.ptr && isEnd == i.isEnd;        
        }

        bool operator!=(const iterator &i) const {
            return !(*this == i);
        }

        std::pair<K,V> &operator*() {
            return ptr->data;
        }

        iterator &operator++() {
            Node* node = successor(ptr);
            if(node == nullptr){
                isEnd = true;
            }
            else{
                ptr = node;
            }
            return *this;
        }

        iterator &operator--(){
            if(isEnd){
                isEnd = false;
            }else{
                Node* node = predecessor(ptr);
                ptr = node;
            }
            return *this;
        }

        iterator operator++(int){
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
      };

      class const_iterator {
        private:
            Node* ptr;
            bool isEnd;
        public:
          friend class BSTMap<K,V>;
          const_iterator(Node* node,bool isend){
            ptr = node;
            isEnd = isend;
          }

          const_iterator(const iterator &iter){
            ptr = iter.ptr;
            isEnd = iter.isEnd;
          }

          bool operator==(const const_iterator &i) const{
            return ptr == i.ptr && isEnd == i.isEnd;
          }

          bool operator!=(const const_iterator &i) const{
            return !(*this == i);
          } 

          const std::pair<K,V> operator*(){
            return ptr->data;
          }

          const_iterator &operator++(){
            Node* node = successor(ptr);
            if(node == nullptr){
                isEnd = true;
            }
            else{
                ptr = node;
            }
            return *this;
          }

          const_iterator &operator--(){
            if(isEnd){
                isEnd = false;
            }else{
                Node* node = predecessor(ptr);
                ptr = node;       
            }
            return *this;
          }

          const_iterator operator++(int){
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
          }

          const_iterator operator--(int){
            const_iterator tmp(*this);
            --(*this);
            return tmp;
          }
      };

      BSTMap(){
        sz = 0;
        root = nullptr;
      }

      ~BSTMap(){
	    clear();
        sz = 0;
      }

      BSTMap(const BSTMap<K,V> &that) {
        root = nullptr;
        sz = 0;
        for(auto i=that.begin();i!=that.end();++i){
            insert(*i);
        }
        sz = that.sz;
      }

      BSTMap &operator=(const BSTMap<K,V> &that){
        (*this).clear();
        for(auto i=that.begin();i!=that.end();++i){
            insert(*i);
        }
        sz = that.sz;
        return *this;
      }

      bool empty() const {
        return size() == 0;
      }

      unsigned size() const{
        return sz; 
      }
      

       iterator find(const key_type& k){
        auto node = findNode(root,k);
        if (node == nullptr){
            return end();
        }else{
            return iterator(node,false);
        }
      }

      const_iterator find(const key_type& k) const{
       auto node = findNode(root,k);
       if(node == nullptr){
            return cend();
       }else{
            return const_iterator(node,false);
       }
      }

      unsigned int count(const key_type& k) const{
        if(find(k) != cend()){
            return 1;
        }else{
            return 0;
        }
      }
      
     // std::pair<iterator,bool> insert(const value_type& val){
     //   if(sz == 0){
     //       root = new Node{val,nullptr,nullptr,nullptr};
     //       sz += 1;
     //       return make_pair(iterator(root,false),true);
     //   }else{
     //       auto i = find(val.first);
     //       if(i != end()){
     //           return make_pair(i,false);
      //      }else{
     //           insertNode(val,root);
     //           sz += 1;
     //           return make_pair(find(val.first),true);
     //       }
     //   }
     // }
     
     
      std::pair<iterator,bool> insert(const value_type& val){
        auto ptr = root;
        if(root == nullptr){
            root = new Node{val,nullptr,nullptr,nullptr};
            sz += 1;
            return make_pair(iterator(root,false),true);
        }
        while(val.first != (ptr->data).first){
            if(val.first < (ptr->data).first){
                if(ptr->left != nullptr){
                    ptr=ptr->left;
                }else{
                    ptr->left = new Node{val,nullptr,nullptr,ptr};
                    sz += 1;
                    return make_pair(iterator(ptr->left,false),true);
                }
            }else{
                if(ptr->right != nullptr){
                    ptr = ptr->right;
                }else{
                    ptr->right = new Node{val,nullptr,nullptr,ptr};
                    sz += 1;
                    return make_pair(iterator(ptr->right,false),true);
                }
            }
        }
        return make_pair(iterator(ptr,false),false);
      }

      template<class InputIterator>
      void insert(InputIterator first, InputIterator last){
        for(auto iter=first;iter!=last;++iter){
            insert(*iter);
        }
      }

       iterator erase(const_iterator position){
        auto node = position.ptr;
        auto successor_node = successor(node);
        if(node->left == nullptr && node->right == nullptr){
            auto ptr = node->parent;
            if(ptr==nullptr) {
    		    delete root;
	    	    root=nullptr;
	        }
	        else if(ptr -> left == node){
                ptr->left = nullptr;
                delete node;
            }else{
                ptr->right = nullptr;
                delete node;
            }
            sz -= 1;
            return iterator(successor_node,false);
        }else if(node->right == nullptr && node->left != nullptr){
            auto parent = node->parent;
	        if(parent==nullptr) root=node->left;
            else if(parent->left == node) parent->left = node->left;
            else parent->right = node ->left;
            node->left->parent = parent; 
            delete node;
            sz -= 1;   
            return iterator(successor_node,false);
        }else if(node->left == nullptr &&node->right != nullptr){
            auto parent = node->parent;
	        if (parent==nullptr) root=node->right;
            else if(parent->left==node) parent->left = node->right;
            else parent->right = node->right;
            node->right->parent = parent;
            delete node;
            sz -= 1;
            return iterator(successor_node,false);
        }else{
            auto ptr = findMinNode(node->right);
            node->data = ptr->data;
            erase(const_iterator(ptr,false));
            return iterator(node,false);
        }
      }

     unsigned int erase(const key_type& k){
        const_iterator it = find(k);
        if(it != cend()){
            erase(it);
            return 1;
        }else{
            return 0;
        }
      }

      void clearNode(Node* node){
        if(node->left == nullptr && node->right == nullptr){
            delete node;
        }else if(node->left == nullptr){
            clearNode(node->right);
            delete node;
        }else if(node->right == nullptr){
            clearNode(node->left);
            delete node;
        }else{
            clearNode(node->left);
            clearNode(node->right);
            delete node;
        }
      }

      void clear(){
       //for(auto i=begin();i!=end();++i){
        //    erase(i);
        //}
        clearNode(root);
        root = nullptr;
        sz = 0;
      }

      mapped_type &operator[](const K &key){
        return (*insert(make_pair(key, V())).first).second;
      }

      bool operator==(const BSTMap<K,V>& rhs) const{
        if(sz == rhs.sz){
            for(auto i=rhs.begin();i!=rhs.end();i++){
                if( count((*i).first) == 0){
                    return false;
                }
            }
            return true;
        }else{
            return false;
        }
      }

      bool operator!=(const BSTMap<K,V>& rhs) const{
        return !(*this==rhs);
      }

      iterator begin(){
         return const_iterator(findMinNode(root),false);
      }

      const_iterator begin() const{
         return const_iterator(findMinNode(root),false);
      }

      iterator end(){
        return iterator(findMaxNode(root),true);
      }

      const_iterator end() const{
        return const_iterator(findMaxNode(root),true);
      }

      const_iterator cbegin() const{
        return const_iterator(findMinNode(root),false);
      }

      const_iterator cend() const{
        return const_iterator(findMaxNode(root),true);
      }
    
};
