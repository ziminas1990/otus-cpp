#pragma once

#include <functional>
#include <memory>
#include <list>

template<typename T>
class WeakPointersList
{
public:
  void push_back(std::weak_ptr<T> pObject) { m_Pointers.push_back(pObject); }

  void forEach(std::function<void(std::shared_ptr<T>)> action)
  {
    auto I = m_Pointers.begin();
    while (I != m_Pointers.end()) {
      std::shared_ptr<T> pObject = I->lock();
      if (pObject) {
        action(pObject);
        ++I;
      } else {
        I = m_Pointers.erase(I);
      }
    }
  }

private:
  std::list<std::weak_ptr<T>> m_Pointers;
};
