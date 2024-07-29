#include<iostream>



template<typename ValueType>

class Vector{
public:
    //初始化空vector
    Vector()=default;

    explicit  Vector(int n ,ValueType value= ValueType ());  //初始化vector并填充

    Vector(std::initializer_list<ValueType> list);

    virtual ~Vector()=default;   //虚析构函数， 用于在对象生命周期结束时释放资源

    void add(const ValueType& value);

    void insert(int index,const ValueType& value);

    Vector<ValueType>& addAll(const Vector<ValueType>& v);

    //return the last element
    ValueType&  back();  

    //return the last element of the vector
    const ValueType& back() const;

    void clear();

    bool contains(const ValueType& value) const;

    int Vector<ValueType>::indexOf(const ValueType& value)const;

private:
    void checkIndex(int index,int min,int max,const char* prefix) const;

    using ContainerType = typename std::conditional<std::is_same<ValueType, bool>::value,
                                                    std::deque<bool>,
                                                    std::vector<ValueType>>::type;
    
    ContainerType _elements;

};

template <typename ValueType>
Vector<ValueType>::Vector(int n,ValueType value){
    if(n<0) error("Cannot create a Vector with a negative number of elements.");
    _elements.assign(n,value);
}

template<typename ValueType>
Vector<ValueType>::Vector(std::initializer_list<ValueType>)
    : _elements(list) {
}

template<typename ValueType>
void Vector<ValueType>::add(const ValueType& value){
    insert(size(),value);
}

template<typename ValueType>
Vector<ValueType>& Vector<ValueType>::addAll(const Vector<ValueType>& v){
    for(const ValueType& value :v){
        add(value);
    }
    return *this;
}

template<typename ValueType>
ValueType& Vector<ValueType>::back() {
    return const_cast<ValueType&>(static_cast<const Vector &>(*this).back());
}

template<typename ValueType>
const ValueType& Vector<ValueType>::back() const{
    if(isEmpty()){
        error("Vector::back: vector is empty");
    }
    return _elements.back();
}

template<typename ValueType>
int Vector<ValueType>::indexOf(const ValueType& value)const{
    auto result=std::find(_elements.begin(),_elements.end(),value)
    if(reslut==_elements.end()) return -1;
    return result-_elements.begin()
}

template<typename ValueType>
void Vector<ValueType>::clear(){
    _elements.clear();
    _version.update();
}

template<typename ValueType>
bool Vector<ValueType>::contains(const ValueType& value)const{
    return indexOf(value)>=0;
}

template<typename ValueType>
void Vector<ValueType>::insert(int index,const ValueType& value){
    checkIndex(index,0,size();"insert");
    _element.insert(_element.begin()+index,value);
    _version.update();
}

template<typename ValueType>
void Vector<ValueType>::checkIndex(int index, int min, int max,const char* prefix)const{
    if(index<min||index>max){
        std::ostringstream out;
        out <<  "Vector::" << prefix << ": index of "<< index
            << "is outside of valid range";
        if(isEmpty()){
            out<<" (empty vector) ";
        }else{
            out<< "[";
            if (min<max){
                out<<min<<".."<<max;
            }else if (min==max){
                out<<min;
            }
            out<<"]";
        }    
        error(out.str());
    }
}