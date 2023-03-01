#include "vector.hpp"

class Test
{
public:
    Test()
    {
        std::cout << "Test()" << std::endl;
    }

    Test(const Test& src)
    {
        std::cout << "Test(const Test&)" << std::endl;
    }

    ~Test()
    {
        std::cout << "~Test()" << std::endl;
    }
};

int main()
{
    std::cout << "test_vector..." << std::endl;

    Vector<Test> vec;

    Test t1;

    vec.PushBack(t1);
    vec.PopBack();

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}