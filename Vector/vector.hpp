#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

namespace DSA
{
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

       template<typename Ty>
       void Construct(T* p, Ty&& val)
       {
           new (p) T(std::forward<Ty>(val));
       }

       void Deconstruct(T* p)
       {
           p->~T();
       }
   };

   template <typename T, typename Alloc, bool kIsTrivial>
   struct Fill;

   template <typename T, typename Alloc>
   struct Fill<T, Alloc, false>
   {
       static void Execute(T* dst, size_t size_of_elements, const T& value, Alloc &allocator)
       {
           for (size_t i = 0; i < size_of_elements; ++i)
               allocator.Construct(dst + i, value);
       }
   };

   template <typename T, typename Alloc>
   struct Fill<T, Alloc, true>
   {
       static void Execute(T* dst, size_t size_of_elements, const T& value, Alloc &allocator)
       {
           std::fill_n(dst, size_of_elements, value);
       }
   };

   template <typename T, typename Alloc, bool kIsTrivial>
   struct Copy;

   template <typename T, typename Alloc>
   struct Copy<T, Alloc, false>
   {
       static void Execute(T* dst, T* src, size_t size_of_elements, Alloc &allocator)
       {
           for (size_t i = 0; i < size_of_elements; ++i)
               allocator.Construct(dst + i, src[i]);
       }
   };

   template <typename T, typename Alloc>
   struct Copy<T, Alloc, true>
   {
       static void Execute(T* dst, T* src, size_t size_of_elements, Alloc &allocator)
       {
           std::memcpy(dst, src, sizeof(T) * size_of_elements);
       }
   };


   template <typename T, typename Alloc, bool kIsTrivial>
   struct Destroy;

   template <typename T, typename Alloc>
   struct Destroy<T, Alloc, false>
   {
       static void Execute(T* src, size_t size_of_elements, Alloc &allocator)
       {
           for (size_t i = 0; i < size_of_elements; ++i)
               allocator.Deconstruct(src + i);

           allocator.Deallocate(src);
       }
   };

   template <typename T, typename Alloc>
   struct Destroy<T, Alloc, true>
   {
       static void Execute(T* src, size_t size_of_elements, Alloc &allocator)
       {
           allocator.Deallocate(src);
       }
   };

   template<typename T, typename Alloc = Allocator<T>>
   class Vector
   {
   public:
       typedef T                value_type;
       typedef T*                iterator;
       typedef const T*        const_iterator;
       typedef std::size_t        size_type;
       typedef T&              reference;
       typedef const T&        const_reference;

       Vector();
       Vector(size_type n, const T& value);

       Vector(const Vector<T>& obj);
       Vector(Vector&& obj);
       ~Vector();

       Vector<T>& operator=(const Vector<T>& obj);
       Vector<T>& operator=(Vector<T>&& obj);
       bool operator==(const Vector<T>& obj);

       reference operator[](size_type index) { return begin_[index]; }
       const_reference operator[](size_type index) const { return begin_[index];}

        template<typename Ty>
        void push_back(Ty&& val)    // 支持左值，也支持右值
         {
             if (!empty())
             {
                 if (size_ == capacity_)
                     expand();
             }
             else
             {
                 capacity_ = 1;
                 begin_ = allocator_.Allocate(capacity_);
             }

             allocator_.Construct(begin_ + size_, std::forward<Ty>(val));
             ++size_;
         }
       
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
   };

   template<typename T, typename Alloc>
   Vector<T, Alloc>::Vector() : size_(0), capacity_(0), begin_(nullptr)
   {}

   template<typename T, typename Alloc>
   Vector<T, Alloc>::Vector(size_type n, const T& value)
   {
       size_ = n;
       capacity_ = n;
       begin_ = allocator_.Allocate(capacity_);

       Fill<T, Alloc, std::is_trivial<T>::value>::Execute(begin_, size_, value, allocator_);
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
           Destroy<T, Alloc, std::is_trivial<T>::value>::Execute(begin_, size_, allocator_);

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

           begin_ = allocator_.Allocate(capacity_);
           Copy<T, Alloc, std::is_trivial<T>::value>::Execute(begin_, src.begin_, size_, allocator_);
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
       capacity_ = size_ * 2;

       T* new_mem = allocator_.Allocate(capacity_);
       Copy<T, Alloc, std::is_trivial<T>::value>::Execute(new_mem, begin_, size_, allocator_);

       Destroy<T, Alloc, std::is_trivial<T>::value>::Execute(begin_, size_, allocator_);
       begin_ = new_mem;
   }
};

#endif