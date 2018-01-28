#include <iostream>
#include "LinkedList.h"

template<typename T>
void testConstList (const LinkedList<T>& ls){
    std::cout << "ConstIterator tested" << std::endl;
    typename LinkedList<T>::ConstIterator itr;
    for(itr = ls.cbegin(); itr != ls.cend(); ++itr)
        std::cout << *itr << " ";
    std::cout << std::endl;
}

template<typename T>
LinkedList<T> REVERSE_MOVE_TEST(const LinkedList<T>& other){
    std::cout << "LinkedList<T>::REVERSE and Move assignment tested!" << std::endl;
    LinkedList<T> l = LinkedList<T>::REVERSE(other);
    return l;
}

int main() {

    std::cout << "Constructor with initializer_list tested!" << std::endl;
    LinkedList<int> ls{23, 12, 34, 2343};

    std::cout << "Read only reference type in range based for tested!" << std::endl;
    for (const auto& itr : ls)
        std::cout << itr << " ";
    std::cout << std::endl;

    ls.push_back(120);
    ls.push_back(11);
    ls.push_front(11);
    ls.pop_back();
    ls.pop_front();
    ls.push_front(13);
    ls.push_back(-13);

    LinkedList<int> copied = ls;
    testConstList(copied);

    copied.pop_back();
    copied.pop_front();

    for (const auto& itr : copied)
        std::cout << itr << " ";
    std::cout << std::endl;

    std::cout << "LinkedList<T>::REVERSE and Move assignment tested!" << std::endl;
    copied = LinkedList<int>::REVERSE(copied);

    std::cout << "InputIterator and InputIterator::operator* tested!" << std::endl;
    for (auto& itr : copied){
        if (itr < 0)
            itr = 69;
        std::cout << itr << " ";
    }
    std::cout << '\n';

    copied = REVERSE_MOVE_TEST(ls);

    for (const auto& itr : copied)
        std::cout << itr << " ";
    std::cout << std::endl;


    std::cout << "Hello, World!" << std::endl;
    return 0;
}