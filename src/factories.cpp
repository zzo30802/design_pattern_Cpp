// 工廠與抽象工廠 (Factory & Abstract Factory Design Pattern)
// 參考: https://medium.com/wenchin-rolls-around/%E8%A8%AD%E8%A8%88%E6%A8%A1%E5%BC%8F-%E5%B7%A5%E5%BB%A0%E8%88%87%E6%8A%BD%E8%B1%A1%E5%B7%A5%E5%BB%A0-factory-abstract-factory-design-pattern-8c28d29cb3ac
// 參考: https://github.com/JakubVojvoda/design-patterns-cpp
/*
工廠方法 (Factory Method) 
抽象工廠方法 (Abstract Factory Method)



*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>
/**
 * 1 : 工廠模式
 * 2 : 抽象工廠模式
**/
#define test_idx 2
#if test_idx == 1

// Product :
// 麵包種類的interface
class IBread {
 public:
  virtual std::string GetBreadName() = 0;

 public:
  std::string name;
};

// Concrete Product :
// Toast
class Toast : public IBread {
 public:
  Toast(std::string name) {
    this->name = name;
    std::cout << name << std::endl;
  }
  std::string GetBreadName() {
    std::string &&temp = "Toast: " + this->name;
    return temp;
  }

 public:
  std::string name;
};

// Concrete Product :
// Cake
// 蛋糕比吐司多了形狀的屬性
class Cake : public IBread {
 public:
  Cake(std::string name) {
    this->name = name;
  }
  std::string GetBreadName() {
    return "Cake: " + this->name;
  }
  std::string GetShape() {
    return "Cake's shape: " + this->shape;
  }

 public:
  std::string name;
  std::string shape;
};

// Creator :
// Factory 的抽象類別 (abstract class) : 設計一個麵包工廠來產出剛剛所定義的麵包
class Bakery {
 public:
  virtual IBread *CreateBread(std::string name) = 0;
};

// Concrete Creator :
// ToastFactory : 負責生產蛋糕
class ToastFactory : public Bakery {
 public:
  IBread *CreateBread(std::string name) override {
    return (new Toast(name));
  }
};

// Concrete Creator :
// CakeFactory
class CakeFactory : public Bakery {
 public:
  IBread *CreateBread(std::string name) override {
    Cake *cake = new Cake(name);
    if (name == "Cheesecake") {
      cake->shape = "square";
    } else {
      cake->shape = "round";
    }
    return cake;
  }
};

int main() {
  std::cout << "-----start make bread-----" << std::endl;
  std::vector<IBread> bread_list;

  ToastFactory *toastFactory = new ToastFactory();
  CakeFactory *cakeFactory = new CakeFactory();

  IBread *bread = toastFactory->CreateBread("Peanut butter toast");
  IBread *bread1 = toastFactory->CreateBread("Chocolate toast");

  IBread *bread2 = cakeFactory->CreateBread("Cheesecake");
  IBread *bread3 = cakeFactory->CreateBread("Strawberry cake");

  // bread_list.emplace_back(bread);
  // bread_list.emplace_back(bread1);
  // bread_list.emplace_back(bread2);
  // bread_list.emplace_back(bread3);
  std::cout << "====Toast====" << std::endl;
  std::cout << bread->GetBreadName() << std::endl;
  std::cout << bread1->GetBreadName() << std::endl;
  std::cout << "====Cake====" << std::endl;
  std::cout << bread2->GetBreadName() << std::endl;
  std::cout << bread3->GetBreadName() << std::endl;
}

#elif test_idx == 2
/*
假設麵包事業生意越來越好，想要開始專業分工，根據不同原料來生產不同麵包(麵粉、奶油、酵母)
，那麼使用 "工廠模式" 就會變得很複雜。

生產吐司用的麵粉工廠（高筋）
生產吐司用的奶油工廠（橄欖油）
生產蛋糕用的麵粉工廠（低筋）
生產蛋糕用的奶油工廠（無鹽奶油）

如果每種麵包的蛋、鹽、糖、酵母粉等等也都要用不同的，那麼工廠方法就會讓系統非常複雜與難以維護。

所以會需要另一個物件來定義麵粉、奶油、酵母、蛋 等等的實作。
*/

// 麵粉、油的interface
class IFlour {
 public:
  virtual std::string GetIngredient() = 0;

 public:
  std::string name;
  int amount;
};

class IOil {
 public:
  virtual std::string GetIngredient() = 0;

 public:
  std::string name;
  int amount;
};

// 實作 麵粉、油
class Flour : public IFlour {
 public:
  std::string GetIngredient() {
    return "Flour name: " + this->name + "\nFlour amount: " + std::to_string(this->amount);
  };
};
class Oil : public IOil {
 public:
  std::string GetIngredient() {
    return "Oil name: " + this->name + "\nOil amount: " + std::to_string(this->amount);
  }
};

// abstract factory
class Bakery {
 public:
  virtual IFlour *CreateFlour(int amount) = 0;
  virtual IOil *CreateOil(int amount) = 0;
};

// factory
// 只要繼承abstract factory就可以開不同的工廠(吐司工廠、蛋糕工廠... ...)
class ToastFactory : public Bakery {
 public:
  IFlour *CreateFlour(int amount) override {
    Flour *flour = new Flour();
    flour->name = "bread flour";
    flour->amount = amount;
    return flour;
  }
  IOil *CreateOil(int amount) override {
    Oil *oil = new Oil();
    oil->name = "olive oil";
    oil->amount = amount;
    return oil;
  }
};

class CakeFactory : public Bakery {
 public:
  IFlour *CreateFlour(int amount) override {
    Flour *flour = new Flour();
    flour->name = "cake flour";
    flour->amount = amount;
    return flour;
  };
  IOil *CreateOil(int amount) override {
    Oil *oil = new Oil();
    oil->name = "butter";
    oil->amount = amount;
    return oil;
  }
};

// Client :
// 使用者只要指定 甚麼樣的工廠、麵粉數量、油數量，就可以針對同一種產品而產生不同原料比例的麵包。
void CreateBread(Bakery &factory, const int &flourAmount, const int &oilAmount) {
  IFlour *flour = factory.CreateFlour(flourAmount);
  IOil *oil = factory.CreateOil(oilAmount);
  std::cout << "-----" << std::endl;
  std::cout << flour->GetIngredient() << std::endl;
  std::cout << oil->GetIngredient() << std::endl;
  std::cout << "-----" << std::endl;
}

// Main
int main() {
  ToastFactory *factory_toast = new ToastFactory();
  CakeFactory *factory_cake = new CakeFactory();

  std::cout << "====Cheesecake====" << std::endl;
  CreateBread(*factory_toast, 300, 100);
  std::cout << "====Strawberry cake====" << std::endl;
  CreateBread(*factory_cake, 400, 150);

  std::cout << "====Chocolate toast====" << std::endl;
  CreateBread(*factory_toast, 200, 50);
  std::cout << "====Peanut butter toast====" << std::endl;
  CreateBread(*factory_toast, 200, 80);
}

#endif