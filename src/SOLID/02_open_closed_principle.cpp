// 開放封閉原則(OCP)
// 參考 : https://medium.com/@f40507777/%E9%96%8B%E6%94%BE%E5%B0%81%E9%96%89%E5%8E%9F%E5%89%87-open-closed-principle-31d61f9d37a5
/*
理念核心: class可以被擴展，但不能被修改。
  1. 對於擴展是開放的，當需求變更時，模組行為可以新增。
  2. 對於修改是封閉的，當程式進行修改時，不需修改既有的程式碼。

  也就是說在設計已經完整的前提下只能加code，而不能改code

可能遇到的問題:
  1. 別人修改部分的code，我這邊會爆掉: 高耦合、未抽象隔離導致
  2. 要用If else / switch去判斷子類別然後做不同事情
    表示在同一個class中處理不同情況，可能導致相依也會違反單一職責SRP

優點:
  1. 降低耦合性
  2. 增加擴展性
  3. 增加可測試性
  4. 提升維護性

如何做能夠達到 "不改動模組卻可以改變行為"?  Ans: 抽象
  1. 利用繼承(多型)
  2. 利用抽象介面
  3. 依賴倒轉 (Dependency Injection pattern, DIP)
  4. 裝飾者模式
  5. 策略模式

總結:
  OCP在大型或複雜專案上很有效，只要是相同類型，但對處理方式不同就可以使用
*/

#include <boost/lexical_cast.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace boost;

enum class Color { red,
                   green,
                   blue };
enum class Size { small,
                  medium,
                  large };

struct Product {
  string name;
  Color color;
  Size size;
};

// 檢查Product顏色，通過的放入vector
// 這個struct設計的很好，但是如果需求改變就必須更改此function，違反開放封閉原則
struct ProductFilter {
  typedef vector<Product*> Items;
  Items by_color(Items items, Color color) {
    Items result;
    for (auto& i : items)
      if (i->color == color)
        result.push_back(i);
    return result;
  }
  Items by_size(Items items, Size size) {
    Items result;
    for (auto& i : items)
      if (i->size == size)
        result.push_back(i);
    return result;
  }
  Items by_size_and_color(Items items,
                          Size size, Color color) {
    Items result;
    for (auto& i : items)
      if (i->size == size && i->color == color)
        result.push_back(i);
    return result;
  }
};
template <typename T>
struct AndSpecification;
template <typename T>
struct Specification {
  virtual ~Specification() = default;
  virtual bool is_satisfied(T* item) const = 0;  //純虛擬，繼承此struct必須實作此function內容

  // new: breaks OCP if you add it post-hoc
  // AndSpecification<T> operator&&(Specification<T>&& other) {
  //   return AndSpecification<T>(*this, other);
  // }
};

//***********
// new:
template <typename T>
AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second) {
  return {first, second};
}
//***********

template <typename T>
struct Filter {
  virtual vector<T*> filter(vector<T*> items,
                            Specification<T>& spec) = 0;
};
struct BetterFilter : Filter<Product> {
  vector<Product*> filter(vector<Product*> items,
                          Specification<Product>& spec) override {
    vector<Product*> result;
    for (auto& p : items)
      if (spec.is_satisfied(p))
        result.push_back(p);
    return result;
  }
};

// 過濾Product是否為指定color
struct ColorSpecification : Specification<Product> {
  Color color;
  ColorSpecification(Color color) : color(color) {}
  bool is_satisfied(Product* item) const override {  // 改寫args
    return item->color == color;
  }
};

// 過濾Product是否為指定size
struct SizeSpecification : Specification<Product> {
  Size size;
  explicit SizeSpecification(const Size size) : size{size} {}
  bool is_satisfied(Product* item) const override {
    return item->size == size;
  }
};
template <typename T>
struct AndSpecification : Specification<T> {
  const Specification<T>& first;
  const Specification<T>& second;
  AndSpecification(const Specification<T>& first,
                   const Specification<T>& second) : first(first), second(second) {}
  bool is_satisfied(T* item) const override {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

int main() {
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  const vector<Product*> all{&apple, &tree, &house};

  // ProductFilter pf;
  // auto green_things = pf.by_color(items, Color::green);
  // for (auto& item : green_things)
  //   cout << item->name << " is green\n";

  BetterFilter bf;
  ColorSpecification green(Color::green);
  auto green_things = bf.filter(all, green);
  for (auto& item : green_things) {
    cout << item->name << " is green." << std::endl;
  }
  /*
  // Apple is green
  // Tree is green
  */

  SizeSpecification large(Size::large);
  AndSpecification<Product> green_and_large(green, large);
  // for (auto& item : bf.filter(items, green_and_large)) {
  //   cout << item->name << " is green and large." << std::endl;
  // }

  // warning: the following will compile but will NOT work
  // 以下方法會產生Segmentation fault (core dumped)
  // auto spec = ColorSpecification(Color::green) && SizeSpecification(Size::large);
  // for (auto& item : bf.filter(all, spec)) {
  //   cout << item->name << " is green and large." << std::endl;
  // }
  /*
  // Tree is green and large.
  */
  auto spec = green && large;
  for (auto& x : bf.filter(all, spec))
    cout << x->name << " is green and large\n";
  // getchar();
  return 0;
}
// Apple is green
// Tree is green
#endif