#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <initializer_list>

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
    typedef T				value_type;
	typedef T*				iterator;
	typedef const T*		const_iterator;
    typedef std::size_t		size_type;
    typedef T&              reference;
    typedef const T&        const_reference;

    Vector();
    Vector(const std::initializer_list<T>& list);

    Vector(const Vector<T>& obj);
    Vector(Vector&& obj);
    ~Vector();

    Vector<T>& operator=(const Vector<T>& obj);
    Vector<T>& operator=(Vector<T>&& obj);
    bool operator==(const Vector<T>& obj);

    reference operator[](size_type index) { return begin_[index]; }
    const_reference operator[](size_type index) const { return begin_[index];}

    void push_back(const T& val);
    void pop_back();

    iterator begin() { return begin_; }
	const_iterator cbegin() const { return begin_; }

	iterator end() { return begin_ + size_; }
	const_iterator cend() const { return begin_ + size_; }

    reference front() { return begin_[0]; }
    const_reference front() const { return begin_[0]; }

    reference back() { return begin_[size_ - 1]; }
    const_reference back() const { return begin_[size_ - 1]; }
 
    bool empty() const { return size_ == 0; }
    size_type size() const { return size_; }
    size_type capacity() const { return capacity_; }

private:
    void destroy_self();
    void copy_from_obj(const Vector<T>& src);
    void move_from_obj(Vector<T>& src);
    void expand();

private:
    iterator begin_;
    Alloc allocator_;
    size_type size_;
    size_type capacity_;

    const size_type kEndSpace = 1;
};

template<typename T, typename Alloc>
Vector<T, Alloc>::Vector() : size_(0), capacity_(0), begin_(nullptr)
{}

template<typename T, typename Alloc>
Vector<T, Alloc>::Vector(const std::initializer_list<T>& list)
    : size_(0), capacity_(0), begin_(nullptr)
{
    for (const auto& it : list)
        push_back(it);
}

template<typename T, typename Alloc>
Vector<T, Alloc>::Vector(const Vector<T>& obj)
{
    copy_from_obj(obj);
}

template<typename T, typename Alloc>
Vector<T, Alloc>::Vector(Vector&& obj)
{
    move_from_obj(obj);
}

template<typename T, typename Alloc>
Vector<T, Alloc>::~Vector()
{
    destroy_self();
}

template<typename T, typename Alloc>
bool Vector<T, Alloc>::operator==(const Vector<T>& obj)
{
    if (size_ != obj.size())
        return false;

    for (size_type i = 0; i < size_; i++)
    {
        if (begin_[i] != obj.begin_[i])
            return false;
    }

    return true;
}

template<typename T, typename Alloc>
Vector<T>& Vector<T, Alloc>::operator=(const Vector<T>& obj)
{
    if (this != &obj)
    {
        destroy_self();
        copy_from_obj(obj);
    }

    return *this;
}

template<typename T, typename Alloc>
Vector<T>& Vector<T, Alloc>::operator=(Vector<T>&& obj)
{ 
    if (this != &obj)
    {
        destroy_self();
        move_from_obj();
    }
        
    return *this;    
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::push_back(const T& val)
{
    if (size_ == capacity_)
        expand();

    allocator_.Construct(begin_ + size_, val);
    ++size_;
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::pop_back()
{
    if (empty())
        return ;

    --size_;
    allocator_.Deconstruct(begin_ + size_); 
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::destroy_self()
{
    if (begin_ != nullptr)
    {
        for (size_t i = 0; i < size_; i++)
        {
            allocator_.Deconstruct(begin_ + i);
        }

        allocator_.Deallocate(begin_);
    }

    begin_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}

template<>
void Vector<int, Allocator<int>>::destroy_self()
{
    if (begin_ != nullptr)
        free(begin_);

    begin_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::copy_from_obj(const Vector<T>& src)
{
    if (begin_ != nullptr)
        throw "Memory must be freed first!";

    if (src.capacity_ > 0)
    {
        size_ = src.size_;
        capacity_ = src.capacity_;

        begin_ = allocator_.Allocate(capacity_ + kEndSpace);
        for (size_t i = 0; i < size_; i++)
        {
            allocator_.Construct(begin_ + i, src.begin_[i]);
        }
    }
}

template<>
void Vector<int, Allocator<int>>::copy_from_obj(const Vector<int>& src)
{
    if (begin_ != nullptr)
        throw "Memory must be freed first!";

    if (src.capacity_ > 0)
    {
        size_ = src.size_;
        capacity_ = src.capacity_;

        begin_ = (int *)malloc(sizeof(int) * (capacity_ + kEndSpace));
        std::memcpy(begin_, src.begin_, sizeof(int) * size_);
    }
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::move_from_obj(Vector<T>& src)
{
    size_ = src.size_;
    capacity_ = src.capacity_;
    begin_ = src.begin_;

    src.size_ = 0;
    src.capacity_ = 0;
    src.begin_ = nullptr;
}

template<typename T, typename Alloc>
void Vector<T, Alloc>::expand()
{
    if (size_ == 0)
        capacity_ = 1;
    else
        capacity_ = size_ * 2;

    T* new_mem = allocator_.Allocate(capacity_ + kEndSpace);

    for (size_type i = 0; i < size_; i++)
    {
        allocator_.Construct(new_mem + i, begin_[i]);
        allocator_.Deconstruct(begin_ + i);
    }

    allocator_.Deallocate(begin_);
    begin_ = new_mem;
}

template<>
void Vector<int, Allocator<int>>::expand()
{
    if (size_ == 0)
        capacity_ = 1;
    else
        capacity_ = size_ * 2;

    int* new_mem = (int *)malloc(sizeof(int) * (capacity_ + kEndSpace));
    std::memcpy(new_mem, begin_, sizeof(int) * size_);

    free(begin_);
    begin_ = new_mem;
}

#endif