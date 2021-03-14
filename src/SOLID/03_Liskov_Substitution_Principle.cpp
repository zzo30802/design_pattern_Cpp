// 里氏替換原則(LSP)
// 參考: https://ithelp.ithome.com.tw/articles/10212037
// 參考: http://glj8989332.blogspot.com/2018/03/design-pattern-liskov-substitution.html
/*
理念核心:
  子類別必須能夠替換父類別，並且行為正常。

概述:
  -在繼承方面，當子類別替換掉父類別時，其功能不受影響。

  -繼承的特性導致高耦合，子類別對於方法修改(Override, Overload) 必須
  依照父類別行為方向，否則會對整體得繼承系統造成破壞，會產生不可預測的行為
  或不好察覺的Bug。

  -子類別的可替換性，代表不需要修改父類別情況下做擴展，也實現了OCP。
  -如果子類別不能完整時做父類別的方法，或者父類別的某些方法在子類別發生大變化
   則不建議使用繼承關，改用依賴、聚集、組合等關係替代繼承。

*/

#include <boost/lexical_cast.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Rectangle {
 protected:
  int width, height;

 public:
  Rectangle(int width, int height) : width(width), height(height) {}

  int getWidth() const {
    return width;
  }

  virtual void setWidth(int width) {  // virtual : you can override them inside of the square
    Rectangle::width = width;
  }

  int getHeight() const {
    return height;
  }

  virtual void setHeight(int height) {  // virtual
    Rectangle::height = height;
  }

  int area() const { return width * height; }
};

class Square : public Rectangle {
 public:
  Square(int size) : Rectangle(size, size) {}

  void setWidth(int width) override {
    //Rectangle::setWidth(width);
    this->width = this->height = width;
  }

  void setHeight(int height) override {
    //Rectangle::setHeight(height);
    this->width = this->height = height;
  }
};

void process(Rectangle &r) {
  int w = r.getWidth();
  r.setHeight(10);

  std::cout << "expected area = " << (w * 10)
            << ", got" << r.area() << std::endl;
}

struct RectangleFactory {
  static Rectangle create_rectangle(int w, int h);
  static Rectangle create_square(int size);
};

int main() {
  Rectangle r{3, 4};
  process(r);  // expected area = 30, got30

  Square sq{5};
  process(sq);  // expected area = 50, got100

  // RectangleFactory a;
  // a.create_square(5);
  // process(a);
  // Square
  // Square sq2(create_square(5));
  // sq2.create_square(5);
  // process(sq);

  return 0;
}