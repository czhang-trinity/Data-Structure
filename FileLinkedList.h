// data prev next
#include<cstdio>
#include<string>
template<typename T>
class FileLinkedList{
    FileLinkedList(const FileLinkedList<T> &that) = delete;
    FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;
    typedef T value_type;
    struct Node{
        T data;
        int prev;
        int next;
    };
    private: 
      FILE* file;
      int sz;
    static int ReadPrev(int node, FILE* file){
        fseek(file,sizeof(T)+node,SEEK_SET);
        int ret;
        fread(&ret,sizeof(int),1,file);
        return ret;
    }

    static int ReadNext(int node, FILE* file){
        fseek(file,sizeof(T)+node+sizeof(int),SEEK_SET);
        int ret;
        fread(&ret,sizeof(int),1,file);
        return ret;
    }
    
    static T ReadData(int node, FILE* file){
        fseek(file,node,SEEK_SET);
        T ret;
        fread(&ret,sizeof(T),1,file);
        return ret;
    }

    void writePrev(int node, FILE* file, int prev){
        fseek(file,node+sizeof(T),SEEK_SET);
        fwrite(&prev,sizeof(int),1,file);
    }
    
    void writeNext(int node, FILE* file, int next){
        fseek(file,node+sizeof(T)+sizeof(int),SEEK_SET);
        fwrite(&next,sizeof(int),1,file);
    }

    void writeData(int node, FILE* file, T data){
        fseek(file,node,SEEK_SET);
        fwrite(&data,sizeof(T),1,file);
    }

    int AllocateNode(FILE* file, int sz){
        fseek(file,sizeof(Node),SEEK_SET);
        int freelist;
        fread(&freelist,sizeof(int),1,file);
        int ret;
        if(freelist != -1){
            ret = freelist;
            freelist = ReadNext(freelist,file);
            //write freeList
            fseek(file,sizeof(Node),SEEK_SET);
            fwrite(&freelist,sizeof(int),1,file);
        }else{
            ret = sizeof(Node) + 2*sizeof(int) + sz * sizeof(Node);
        }
        return ret;
    }

    void DeallocateNode(FILE* file, int node){
        int freelist;
        fseek(file,sizeof(Node),SEEK_SET);
        fread(&freelist,sizeof(int),1,file);
        writeNext(node,file,freelist);
        freelist = node;
        fseek(file,sizeof(Node),SEEK_SET);
        fwrite(&freelist,sizeof(int),1,file);
    }

    void changeSize(int size, FILE* file){
        fseek(file,sizeof(Node)+sizeof(int),SEEK_SET);
        fwrite(&size,sizeof(int),1,file);
    }

    public:
    class const_iterator{
        private:
            FILE* file;
            int index;
        public:
          const_iterator(int i, FILE *f){
            file = f;
            index = i;
          }

          const_iterator(const const_iterator &i){
            file = i.file;
            index = i.index;
          }

          T operator*(){
            return ReadData(index,file);
          }

          bool operator==(const const_iterator &i) const{
            return index == i.index && file == i.file;
          }

          bool operator!=(const const_iterator &i) const{
            return !(index == i.index && file == i.file);
          }

          const_iterator &operator=(const const_iterator &i){
            file = i.file;
            index = i.index;
            return *this;
          }

          const_iterator &operator++(){
            index = ReadNext(index,file);
            return *this;
          }

          const_iterator &operator--(){
            index = ReadPrev(index,file);
            return *this;
          }

          const_iterator operator++(int){
            const_iterator i = *this;
            index = ReadNext(index,file);
            return i;
          }

          const_iterator operator--(int){
            const_iterator i = *this;
            index = ReadPrev(index,file);
            return i;
          }

          friend class FileLinkedList;
    };
    // general method
    FileLinkedList(const std::string &fname){
        FILE* f = fopen(fname.c_str(),"r+");
        if(f == nullptr){
            f = fopen(fname.c_str(),"w+");
            init(f);
            sz = 0;
        }else{
            fseek(f,sizeof(Node)+sizeof(int),SEEK_SET);
            fread(&sz,sizeof(int),1,f);
        }
        file = f;
    }

    void init(FILE* f){
        fseek(f,sizeof(T),SEEK_SET);
        int prev = 0;
        fwrite(&prev,sizeof(int),1,f);
        int next = 0;
        fwrite(&next,sizeof(int),1,f);
        int freelist = -1;
        fwrite(&freelist,sizeof(int),1,f);
        sz = 0;
        fwrite(&sz,sizeof(int),1,f);     
    }

    template<typename I> //The type I will be an iterator
    FileLinkedList(I begin,I end,const std::string &fname){
        file = fopen(fname.c_str(),"w+");
        init(file);
        sz = 0;
        for(auto iter=begin;iter != end; ++iter){
            push_back(*iter);
        }
        changeSize(sz,file);
    }

    ~FileLinkedList(){
        fclose(file);
    }

    void push_back(const T &t){
        insert(end(),t);
    }

    void pop_back(){
        erase(--end());
    }

    int size() const{
        return sz;
    }

    void clear(){
        while(size()>0){
            pop_back();
        }
    }

    const_iterator insert(const_iterator position, const T &t){
        int index = position.index;
        int new_position = AllocateNode(file,sz);
        int prev = ReadPrev(index,file);
        //write new Node
        writeData(new_position,file,t);
        writePrev(new_position,file,prev);
        writeNext(new_position,file,index);
        //fix link list
        writeNext(prev,file,new_position);
        writePrev(index,file,new_position);
        sz += 1;
        changeSize(sz,file);
        return const_iterator(new_position,file);
    }

    T operator[](int index) const{
        auto itr = begin();
        for(int i=0;i<index;++i){
            ++itr;
        }
        return *itr;
    }

    const_iterator erase(const_iterator position){
        int index = position.index;
        int prev = ReadPrev(index,file);
        int next = ReadNext(index,file);
        writeNext(prev,file,next);
        writePrev(next,file,prev);
        DeallocateNode(file,index);
        sz -= 1;
        changeSize(sz,file);
        return const_iterator(next,file);
    }

    void set(const T &value, int index){
        int node = ReadNext(0,file);
        for(int i = 0; i< index; ++i){
            node = ReadNext(node,file);
        }
        writeData(node,file,value);
    }

    void set(const T &value, const_iterator position){
        int index = position.index;
        writeData(index,file,value);
    }

    const_iterator begin(){
        int begin = ReadNext(0,file);
        return const_iterator(begin,file);
    }

    const_iterator begin() const{
        int begin = ReadNext(0,file);
        return const_iterator(begin,file);
    }

    const_iterator end(){
        return const_iterator(0,file);
    }

    const_iterator end() const{
        return const_iterator(0,file);
    }

    const_iterator cbegin() const{
        int begin = ReadNext(0,file);
        return const_iterator(begin,file);
    }

    const_iterator cend() const{
        return const_iterator(0,file);
    }
};
