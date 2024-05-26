#include <iostream>
#include <memory> // smart pointers
#include <utility> // std::move

/**
 * 1. std::unique_ptr
 * 2. Returning a std::unique_ptr from a function by value
 * 3. Passing a std::unique_ptr to a function
 * 4. std::shared_ptr
 * 5. std::unique_ptr can be downgraded to std::shared_ptr
 * 6. std::weak_ptr
*/

// this class is used to test the smart pointers
class Resource {
  public:
    Resource() {
      std::cout << "Resource acquired\n";
    }
    ~Resource() {
      std::cout << "Resource destroyed\n";
    }

    void sayHello() const {
      std::cout << "Hello\n";
    }
};

// =================================================================
// 1. std::unique_ptr
// =================================================================
// std::unique_ptr is designed for the move semantics, so the copy constructor and copy assignment operator are deleted.
void test() {
  std::unique_ptr<Resource> res {new Resource()};
  std::unique_ptr<Resource> res2; // start as nullptr
  // res2 = res;  // error: copy constructor and copy assignment operator are deleted
  res2 = std::move(res);  // convert res to rvalue so that it can trigger the move assignment operator

  // Before accessing the resource managed by the unique_ptr, we should check if the underlying resource is valid, because the unique_ptr can be nullptr or the resource has been moved to another unique_ptr.
  // unique_ptr has overloaded the operator* and operator->, they are returning T& and T* respectively.
  if (res) { res->sayHello(); }
  if (res2) { res2->sayHello(); }

  // It is recommended to use std::make_unique to create a unique_ptr, because it is more efficient and safe.
  std::unique_ptr<Resource> res3 = std::make_unique<Resource>();
  auto res4 = std::make_unique<Resource>();
}

// =================================================================
// 2. Returning a std::unique_ptr from a function by value
// =================================================================
// it is safe to return a std::unique_ptr from a function by value
std::unique_ptr<Resource> createResource() {
  return std::make_unique<Resource>();
}
// In C++14 or earlier, the move semantics will be employed to transfer the ownership of the resource from the local unique_ptr to the caller's unique_ptr.
// In C++17 or newer, the return value optimization (RVO) will be applied to avoid the move operation, so the resource will be constructed directly in the caller's unique_ptr. It is also called copy elision.

// =================================================================
// 3. Passing a std::unique_ptr to a function
// =================================================================
// If you want the called function to take the ownership of the resource, you should pass the unique_ptr by value.
void takeOwnership(std::unique_ptr<Resource> res) {
  res->sayHello();
}
void test2() {
  auto res = std::make_unique<Resource>();
  takeOwnership(std::move(res));
  // res->sayHello(); // error: res has been moved
}
// If the called function just wants to access the resource without taking the ownership, you should pass the unique_ptr by reference.
void accessResource(const std::unique_ptr<Resource>& res) {
  res->sayHello();
}
void test3() {
  auto res = std::make_unique<Resource>();
  accessResource(res);
  res->sayHello(); // res is still valid
}
// Or pass in the underlying raw pointer.
void accessResource2(const Resource* res) {
  res->sayHello();
}
void test4() {
  auto res = std::make_unique<Resource>();
  accessResource2(res.get());
  res->sayHello(); // res is still valid
}

// =================================================================
// 4. std::shared_ptr
// =================================================================
// std::shared_ptr is designed for shared ownership, so it has a reference counter to track how many shared_ptr are pointing to the same resource.
void test5() {
  std::shared_ptr<Resource> res {new Resource()};
  std::shared_ptr<Resource> res2 {res}; // shared ownership

  // Use std::make_shared to create a shared_ptr
  auto res3 = std::make_shared<Resource>();
  auto res4 = res3; // shared ownership
}

// =================================================================
// 5. std::unique_ptr can be downgraded to std::shared_ptr
// =================================================================
// std::shared_ptr has a constructor that takes a std::unique_ptr rvalue as the argument,
// the content of the std::unique_ptr will be moved to the std::shared_ptr, and the std::unique_ptr will be nullptr.
void test6() {
  std::unique_ptr<Resource> res {new Resource()};
  std::shared_ptr<Resource> res2 {std::move(res)};
  // res->sayHello(); // error: res is nullptr
  res2->sayHello();
}

// =================================================================
// 6. std::weak_ptr
// =================================================================
// std::weak_ptr is used to break the circular reference between shared_ptr, it doesn't increase the reference counter.
void test7() {
  std::shared_ptr<Resource> res {new Resource()};
  std::weak_ptr<Resource> weakRes {res};
  // weakRes->sayHello(); // error: weak_ptr doesn't have operator->

  // To access the resource managed by the weak_ptr, we should convert it to a shared_ptr first.
  if (auto sharedRes = weakRes.lock()) {
    sharedRes->sayHello();
  }
}