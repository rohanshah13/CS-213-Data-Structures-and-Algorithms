#include<iostream>
#include<vector>

template <class T>
class myvector
{
      std::vector<T> v;
      int size_back; //number of elements after and including origin
      int size_front; //number of elements before and excluding origin
      int origin; //n+1th element of the vector
      // declare variables that are needed. These are private to the class.

      public:
     
      // define the methods     

      void push_front(T x){
            if(size_front==v.size()/2){
                  int n;
                  if(v.size()==0){
                        n=2;
                  }
                  else{
                        n=2*v.size();
                  }
                  std::vector<T> v1(n);
                  origin=v1.size()/2;
                  for(int i=origin-size_front;i<origin+size_back;i++){
                        v1[i]=v[i-origin+v.size()/2];
                  }
                  v1[origin-size_front-1]=x; 
                  v=v1;                                        // copy to a new location, vector size =2*v.size()
                  size_front++;
            }
            else{
                  v[origin-size_front-1]=x;
                  size_front++;
            }
            return;
      }
      void push_back(T x){
            if(size_back==v.size()/2){
                  int n;
                  if(v.size()==0){
                        n=2;
                  }
                  else{
                        n=2*v.size();
                  }
                  std::vector<T> v1(n);
                  origin=v1.size()/2;
                  for(int i=origin-size_front;i<origin+size_back;i++){
                        v1[i]=v[i-origin+v.size()/2];
                  }
                  v1[origin+size_back]=x; 
                  v=v1;                                        // copy to a new location, vector size =2*v.size()
                  size_back++;
            }
            else{
                  v[origin+size_back]=x;
                  size_back++;
            }
            return;
      }
      void pop_front(){
            if(size_front>0){
                  size_front--;
            }
            else if(size_back>0){
                  int n;
                  if(size_back%2==0){
                        n=size_back/2;
                  }
                  else{
                        n=(size_back+1)/2;
                  }
                  for(int i=origin-n;i<size_back+origin-n;i++){
                        v[i]=v[i+n];
                  }
                  size_front=n-1;
                  size_back=size_back-n;

            }
            else{}
      }
      void pop_back(){
            if(size_back>0){
                  size_back--;
            }
            else if(size_front>0){
                  int n;
                  if(size_front%2==0){
                        n=size_front/2;
                  }
                  else{
                        n=(size_front+1)/2;
                  }
                  for(int i=origin+n-1;i>origin+n-1-size_front;i--){
                        v[i]=v[i-n];
                  }
                  size_back=n-1;
                  size_front=size_front-n;
            }
      }
      int size()  const{
            return size_front+size_back;
      }
      T & operator[](int i){
            return v[origin-size_front+i];
      }

      // You may also need to define a constructor for initialization;
      myvector<T>(){
            size_back=0;
            size_front=0;
            origin=0;
      }
};