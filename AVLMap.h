#include<utility>
#include<iostream>
#include<algorithm>
#include<cassert>
using namespace std;
template<typename K, typename V>
class AVLMap{
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    struct Node{
        value_type data;
        Node* left;
        Node* right;
        Node* parent;
        int height;
    };
    int sz;
    Node* root;
    void rotateLeft(Node* A){
        Node* B = A -> right;
        assert(B!=nullptr);
        Node* y = B -> left;
        Node* p = A -> parent;
        if(y != nullptr) y->parent = A;
        A -> right = y;
        B -> left = A;
        A -> parent = B;
        B -> parent = p;
        if(p == nullptr) root = B;
        else if(p -> left == A) p -> left = B;
        else p -> right = B;

        updateHeight(A);
    }

    void rotateRight(Node* B){
        Node* A = B -> left;
        assert(A != nullptr);
        Node* y = A -> right;
        Node* p = B -> parent;
        if(y != nullptr) y -> parent = B;
        B -> left = y;
        A -> right = B;
        B -> parent = A;
        A -> parent = p;
        if(p == nullptr) root = A;
        else if(p -> left == B) p->left = A;
        else p -> right = A;
        
        updateHeight(B);
    }

        void updateHeight(Node* n){
        if(n==nullptr) return;
        n -> height = std::max(getHeight(n->left),getHeight(n->right))+1;
        updateHeight(n->parent);
    }

    int getHeight(Node* n){
        if(n == nullptr) return 0;
        return n->height;
    }

    int balanceFactor(Node *n){
        return getHeight(n->left) - getHeight(n->right);
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
        friend class AVLMap<K,V>;
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
          friend class AVLMap<K,V>;
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

      AVLMap(){
        sz = 0;
        root = nullptr;
      }

      ~AVLMap(){
	    clear();
        sz = 0;
      }

      AVLMap(const AVLMap<K,V> &that) {
        root = nullptr;
        sz = 0;
        for(auto i=that.begin();i!=that.end();++i){
            insert(*i);
        }
        sz = that.sz;
      }

      AVLMap &operator=(const AVLMap<K,V> &that){
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
     
      std::pair<iterator,bool> insert(const value_type& val){
        auto ptr = root;
        if(root == nullptr){
            root = new Node{val,nullptr,nullptr,nullptr,1};
            sz += 1;
            return make_pair(iterator(root,false),true);
        }
        while(val.first != (ptr->data).first){
            if(val.first < (ptr->data).first){
                if(ptr->left != nullptr){
                    ptr=ptr->left;
                }else{
                    // insert the node 
                    ptr->left = new Node{val,nullptr,nullptr,ptr,1};
                    sz += 1;
                    Node* ret = ptr->left;
                    balance(ptr);
                    return make_pair(iterator(ret,false),true);
                }
            }else{
                if(ptr->right != nullptr){
                    ptr = ptr->right;
                }else{
                    // insert the node
                    ptr->right = new Node{val,nullptr,nullptr,ptr,1};
                    sz += 1;
                    Node* ret = ptr -> right;
                    balance(ptr);
                    return make_pair(iterator(ret,false),true);
               }
            }
       }
       return make_pair(iterator(ptr,false),false);
    }

    void balance(Node* ptr){
        // updateHeight
        updateHeight(ptr);
        // check balance
        while(ptr!= nullptr){
            auto factor = balanceFactor(ptr);
            if(factor >=2 || factor <= -2){
                if(getHeight(ptr->left)-getHeight(ptr->right)>0){
                    if(getHeight(ptr->left->left)-getHeight(ptr->left->right)>0){
                        //left left
                        rotateRight(ptr);
                        break;
                    }else{ //left right
                            Node* n = ptr;
                            rotateLeft(ptr->left);
                            rotateRight(n);
                            break;
                        }
                }else{ 
                    if(getHeight(ptr->right->left)-getHeight(ptr->right->right)>0){
                            // right left
                            Node* n = ptr ;
                            rotateRight(ptr->right);
                            rotateLeft(n);
                            break;
                   }else{
                             //right right
                            rotateLeft(ptr);
                            break;
                       }
               }
            }
            ptr = ptr->parent;
        }
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

      void clear(){
        clearNode(root);
        root = nullptr;
        sz = 0;
      }

      mapped_type &operator[](const K &key){
        return (*insert(make_pair(key, V())).first).second;
      }

      bool operator==(const AVLMap<K,V>& rhs) const{
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

      bool operator!=(const AVLMap<K,V>& rhs) const{
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
