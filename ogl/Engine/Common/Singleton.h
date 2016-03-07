//
//  __SINGLETON_HPP__
//
// The MIT License (MIT)

// Copyright (c) <2013> <Jiang Bian jbian@uams.edu>

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// Usage:
//   class Foo : public Singleton<Foo> {
//       friend class Singleton<Foo>;

//   private:

//       Foo(const std::string& hello) : hello_(hello)  {
//           std::cout << hello << std::endl;
//       }

//       Foo() : hello_(nullptr) {
//           std::cout << "Foo()" << std::endl;
//       }

//       const std::string& hello_;
//   };

//   int main(int, const char**) {
//     const std::string hello("hello world");
//     Foo::Instance(hello);
//     Foo::Instance();
//   }

#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <mutex>
#include <functional>
#include <memory>
#include <utility>

using std::call_once;
using std::once_flag;

// This is from boost/utility.hpp
// if you don't mind having dependency on boost, get rid of this, and replace it with boost::noncopyable
namespace noncopyable_  // protection from unintended ADL
{
  class noncopyable
  {
   protected:
      noncopyable() {}
      ~noncopyable() {}
   private:  // emphasize the following members are private
      noncopyable( const noncopyable& );
      const noncopyable& operator=( const noncopyable& );
  };
}

typedef noncopyable_::noncopyable noncopyable;


template <class T>
class Singleton : private noncopyable {
  public:
    template <typename... Args>
    static T& Instance(Args&&... args) {
      
      call_once(
        get_once_flag(),
        [] (Args&&... args) {
          instance_.reset(new T(std::forward<Args>(args)...));
        }, std::forward<Args>(args)...);
      /*
      c++11 standard does specify the following syntax to be valid... but it is not supported by gcc-4.8 yet.
      Final Committee Draft, section 5.1.2.23:
      A capture followed by an ellipsis is a pack expansion (14.5.3). [ Example:
      template<class... Args> void f(Args... args) {
          auto lm = [&, args...] { return g(args...); }; lm();
      }
      — end example ]
      call_once(
        get_once_flag(),
        [&, args...] () {
          instance_.reset(new T(std::forward<Args>(args)...));
        });
      */
      return *instance_.get();
    }

  protected:
    explicit Singleton<T>() {}
    ~Singleton<T>() {}

  private:
    static std::unique_ptr<T> instance_;
    static once_flag& get_once_flag() {
      static once_flag once_;
      return once_;
    }
};

template<class T> std::unique_ptr<T> Singleton<T>::instance_ = nullptr;

#endif