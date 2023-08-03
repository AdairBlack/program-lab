#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

class Widget {
    int propertyX;
};

std::vector<Widget> createVec()
{
    return std::vector<Widget>(5);
}

template<typename T>
void f(const T& param)
{
    using boost::typeindex::type_id_with_cvr;

    std::cout << "T: "
              << type_id_with_cvr<T>().pretty_name()
              << std::endl;

    std::cout << "param: "
              << type_id_with_cvr<decltype(param)>().pretty_name()
              << std::endl; 
}

int main()
{
    using boost::typeindex::type_id_with_cvr;
    const auto vw = createVec();

    std::cout << "decltype(vw): "
              << type_id_with_cvr<decltype(vw)>().pretty_name()
              << std::endl;
    
    std::cout << "decltype(vw[0]): "
              << type_id_with_cvr<decltype(vw[0])>().pretty_name()
              << std::endl;
    
    std::cout << "decltype(&vw[0]): "
              << type_id_with_cvr<decltype(&vw[0])>().pretty_name()
              << std::endl;
    
    f(&vw[0]);

    const int a = 0;
    int const & b = a;
    const int & c = a;
    // int d = 1;
    // int & const e = d;

    std::cout << "decltype(a): "
              << type_id_with_cvr<decltype(a)>().pretty_name()
              << std::endl;
    
    std::cout << "decltype(b): "
                << type_id_with_cvr<decltype(b)>().pretty_name()
                << std::endl;
    
    std::cout << "decltype(c): "
                << type_id_with_cvr<decltype(c)>().pretty_name()
                << std::endl;

    return 0;
}