#include <cstdio>
#include <string>
using namespace std;

template<typename T>
class FileArrayList {
  private:
    FILE* file;
    int sz;
    FileArrayList(const FileArrayList<T> &that) = delete;
    FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;
    static T read(FILE* file,int index) {
      fseek(file,sizeof(int)+index*sizeof(T),SEEK_SET);
      T tmp;
      fread(&tmp,sizeof(T),1,file);
      return tmp;
    }
    void write(int index, T data){
        fseek(file,sizeof(int)+index*sizeof(T),SEEK_SET);
        fwrite(&data,sizeof(T),1,file);
    }

    void changeSize(int size, FILE* f){
        fseek(f,0,SEEK_SET);
        fwrite(&size,sizeof(int),1,f);
    }
  public:
    typedef T value_type;
    class const_iterator{
      private:
        FILE* pFile;
        int index;
      public:
        const_iterator(int i, FILE *f){      
          pFile = f;
          index = i;
        }

        const_iterator(const const_iterator &i){
          pFile = i.pFile;
          index = i.index;
        }

        T operator*(){
          return read(pFile,index);
        }

        bool operator==(const const_iterator &i) const {
          return pFile == i.pFile && index == i.index;
        }

        bool operator!=(const const_iterator &i) const {
          return pFile != i.pFile || index != i.index;
        }

        const_iterator &operator=(const const_iterator &i){
          pFile = i.pFile;
          index = i.index;
          return *this;
        }

        const_iterator &operator++(){
          ++index;
          return *this;
        }

        const_iterator &operator--(){
          --index;
          return *this;
        }

        const_iterator operator++(int){
          const_iterator i = *this;
          ++index;
          return i;
        }

        const_iterator operator--(int){
          const_iterator i = *this;
          --index;
          return i;
        }

        friend class FileArrayList;
    };

    //General Methods
    FileArrayList(const std::string &fname){
      FILE* f = fopen(fname.c_str(),"r+");
      if(f == nullptr){
        f = fopen(fname.c_str(),"w+");
        sz = 0;
        changeSize(sz,f);
      }else{
            fseek(f,0,SEEK_SET);
            fread(&sz,sizeof(int),1,f);
      }
      file = f;
    }

    template<typename I> // The type I will be an iterator
    FileArrayList(I begin,I end,const std::string &fname){
        FILE* f = fopen(fname.c_str(),"r+");
        if(f == nullptr){
          f = fopen(fname.c_str(),"w+");
        }
        file = f;
        sz = 0;
        for(auto iter=begin;iter != end; iter++){
            write(sz,*iter);
            sz += 1;
        }
        changeSize(sz,file);
    }

    ~FileArrayList(){
      fclose(file);
      sz = 0;
    }

    void push_back(const T &t){
      const_iterator i = (*this).end();
      insert(i,t);
    }

    void pop_back(){
      const_iterator i = (*this).end();
      erase(--i);
    }

    int size() const{
      return sz;
    }

    void clear(){
      sz = 0;
      changeSize(0,file);
    }

    const_iterator insert(const_iterator position,const T &t){
      int index = position.index;
      for(int i=sz; i > index; i--){
        auto temp = read(file,i-1);
        write(i,temp);
      }
      write(index,t);
      sz += 1;
      changeSize(sz,file);
      return position;
    }

    T operator[](int index) const {
      const_iterator i(index,file);
      return *i;
    }

    const_iterator erase(const_iterator position){
       int index = position.index;
       for(int i=index; i< sz-1;i++){
           T tmp = read(file,i+1);
           write(i,tmp);
       }
       sz -= 1;
       changeSize(sz,file);
       return position;
    }

    void set(const T &value, int index){
      const_iterator i(index,file);
      erase(i);
      insert(i,value);
    }

    const_iterator begin(){
      return const_iterator(0,file);
    }

    const_iterator begin() const{
      return const_iterator(0,file);
    }

    const_iterator end(){
      return const_iterator(sz,file);
    }

    const_iterator end() const{
      return const_iterator(sz,file);
    }

    const_iterator cbegin() const{
      return const_iterator(0,file);
    }

    const_iterator cend() const{
      return const_iterator(sz,file);
    }
};
