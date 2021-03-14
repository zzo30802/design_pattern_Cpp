// 依賴反轉原則 Dependency Inversion Principle (DIP)
// https://medium.com/@f40507777/%E4%BE%9D%E8%B3%B4%E5%8F%8D%E8%BD%89%E5%8E%9F%E5%89%87-dependency-inversion-principle-dip-bc0ba2e3a388
/*
理念核心:
  高層模組不應該依賴於低層模組。兩者皆應該依賴抽象。
  抽象不依賴細節。細節應該依賴抽象。

概述:
  - 如果高層模組依賴低層模組，這意味這低層模組的變動使得
    使用者高層模組會受影響，這樣是不合理的，應該是由高層行為去操作低層實作。
  - 所以必須將依賴反轉，使得高階不再依賴低階，而是中間透過抽象來達到依賴的反轉
*/
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

/**
 * 1 : 範例一
 * 2 : 範例二
**/
#define test_idx 2
#if test_idx == 1

using namespace std;
// #include <boost/lexical_cast.hpp>
// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstractions.
// B. Abstractions should not depend on details.
//    Details should depend on abstractions.

enum class Relationship {
  parent,
  child,
  sibling
};

struct Person {
  string name;
};

struct RelationshipBrowser {
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser  // low-level
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string& name) override {
    vector<Person> result;
    for (auto&& [first, rel, second] : relations) {
      if (first.name == name && rel == Relationship::parent) {
        result.push_back(second);
      }
    }
    return result;
  }
};

struct Research  // high-level
{
  Research(RelationshipBrowser& browser) {
    for (auto& child : browser.find_all_children_of("John")) {
      cout << "John has a child called " << child.name << endl;
    }
  }
  //  Research(const Relationships& relationships)
  //  {
  //    auto& relations = relationships.relations;
  //    for (auto&& [first, rel, second] : relations)
  //    {
  //      if (first.name == "John" && rel == Relationship::parent)
  //      {
  //        cout << "John has a child called " << second.name << endl;
  //      }
  //    }
  //  }
};

int main() {
  Person parent{"John"};
  Person child1{"Chris"};
  Person child2{"Matt"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research _(relationships);

  return 0;
}

main() {
  return 0;
}

#elif test_idx == 2
/*
當Button開關時，Lamp要亮或關的反應
以傳統直覺上的設計，高層的Buttom會直接使用Lamp得實作方法。
Buttom -> Lamp -> turnOn / turnOff
但這樣做明顯違反了DIP，因為如果Lamp修改的話buttom可能也會需要修改。
*/

// class Lamp {
//  public:
//   void TurnOn() {
//     std::cout << "lamp turn on" << std::endl;
//   }
//   void TurnOff() {
//     std::cout << "lamp turn off" << std::endl;
//   }
// };

// class Button : Lamp {
//  public:
//   void poll() {
//     Lamp::TurnOn();
//   }
// };
// int main() {
//   Button a;
//   a.poll();
// }
/*
為了解決上述問題，我們將使用者縮需要的服務介面抽象化，
再讓Lamp根據抽象化ButtonServer所需要的介面去實作。
Lamp -> ButtonServer -> TurnOn/ TurnOff
*/
class ButtonServer {
  virtual void TurnOn() = 0;
  virtual void TurnOff() = 0;
};

class Lamp : ButtonServer {
 public:
  void TurnOn() override {
    std::cout << "lamp turn on..." << std::endl;
  }
  void TurnOff() override {
    std::cout << "lamp turn off..." << std::endl;
  }
};
int main() {
  Lamp a;
  a.TurnOn();
}

#endif