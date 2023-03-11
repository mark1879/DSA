#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

/**
*  将内存分配、回收 跟 对象构造、析构分离
*  适用于使用连续内存（数组）当存储空间的容器
*/
template<typename T>
struct Allocator
{
    T* Allocate(size_t size)
    {
        return (T*)malloc(sizeof(T) * size);
    }

    void Deallocate(void *p)
    {
        free(p);
    }

    void Construct(T* p, const T& val)
    {
        new (p) T(val);
    }

    void Deconstruct(T* p)
    {
        p->~T();
    }
};

template<typename T, typename Alloc = Allocator<T>>
class Vector
{
public:
    Vector(int size = 10 )
    {
        // first_ = new T[size];    // 初始化时会调用 size 次 T 的构造函数
        first_ = allocator_.Allocate(size);
        last_ = first_;
        end_ = first_ + size;
    }

    ~Vector()
    {
        // delete first_;
        Destroy();
        first_ = last_ = end_ = nullptr;
    }

    Vector(const Vector<T>& src)
    {
        CopyFromObj(src);
    }

    Vector<T>& operator=(const Vector<T>& src)
    {
        if (this == &src)
            return *this;

        Destroy();
        CopyFromObj(src);

        return *this;
    }

    void PushBack(const T& val)
    {
        if (Full())
            Expand();

        allocator_.Construct(last_, val);
        ++last_;
    }

    void PopBack()
    {
        if (Empty())
            return ;

        --last_;
        allocator_.Deconstruct(last_); 
        
    }

    T Back() const 
    {
        return *(last_ - 1);
    }
     
    bool Full() const { return last_ == end_; }
    bool Empty() const { return first_ == last_; }
    int Size() const { return last_ - first_; }
private:
    void Destroy()
    {
        for (T *p = first_; p != last_; ++p)
        {
            allocator_.Deconstruct(p);
        } 

        allocator_.Deallocate(first_);
    }

    void CopyFromObj(const Vector<T>& src)
    {
        int size = src.end_ - src.first_;
        first_ = allocator_.Allocate(size);

        int data_len = src.last_ - src.first_;
        for (int i = 0; i < data_len; i++)
        {
            allocator_.Construct(first_ + i, src.first_[i]);
        }

        last_ = first_ + data_len;
        end_ = first_ + size;
    }

    void Expand()
    {
        int size = end_ - first_;
        T* new_mem = allocator_.Allocate(size * 2);

        for (int i = 0; i < size; i++)
        {
            allocator_.Construct(new_mem + i, first_[i]);
        }
        
        Destroy();

        first_ = new_mem;
        last_ = first_ + size;
        end_ = first_ + size * 2;
    }


private:
    T *first_;
    T *last_;
    T *end_;
    Alloc allocator_;
};

#endif