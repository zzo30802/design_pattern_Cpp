// 建造者模式 (Builder Design Pattern)
// 參考: https://medium.com/wenchin-rolls-around/%E8%A8%AD%E8%A8%88%E6%A8%A1%E5%BC%8F-%E5%BB%BA%E9%80%A0%E8%80%85%E6%A8%A1%E5%BC%8F-builder-design-pattern-7c8eac7c9a7

/*
概念:
  - 建造者 (Builder) 模式將物件的「建構」與「表示」分離，隱藏並封裝建構過程的細節。
    讓我們可以將物件本身拆解成不同的元件，一步一步建造每一部分，最後產生出我
    們想要的複雜物件。
  - 是creational design pattern。主要目的是讓你可以一步步的建構複雜的物件。
    這種設計模式允許你使用一樣的程式結構而產生出不同類型或表示的程式。

優點:
  當一個class宣告了相當多的變數，但是卻需要有各種不同組合(甚至有些參數是可選的)，就可以使用builder模式，
  可以避免很長的建構子或是過多的引數導致混亂。

For Example:
  像是下列的實作
  new House(2, 4, 3, true, true, true, false, false, false);
  new House(2, 4, 3, true, true, true, false, null, null);
  透過builder模式，可以變成
  HouseBuilder.SetDoorNum(2);            
  HouseBuilder.SetWindowNum(4);            
  HouseBuilder.SetRoomNum(3);        
  HouseBuilder.SetHasGarden(true);
  HouseBuilder.SetHasPool(true);       
  ...    
  HouseBuilder.GetHouse();
  或是
  new HouseBuilder().SetDoorNum(2)
                    .SetWindowNum(4)
                    .SetRoomNum(3)
                    .SetHasGarden(true)
                    .SetHasPool(true)  
                    ...
                    .Build();
*/

#include <iostream>
#include <memory>
#include <string>
#include <vector>
/*
以下範例:
假設要開一間水上活動工作室
假設今天你擁有 SUP、獨木舟、浮潛、衝浪……的器材和專業，打算開一個水上活動工作室，設計不同的活動來銷售。
*/

/**
 * 1 : SUP 行程價格、困難度、時間……都相同，僅地點有差異
 * 2 : 將1做更動，使得所有參數都可以客製化
**/
#define test_idx 2

#if test_idx == 1
// ------方法一------
// 透過Client、Director、Builder 和 Product 形成的建造者模式

// Product
class Product {
 public:
  void AddDetail(std::string detail) {
    product_detail.emplace_back(detail);
  }
  std::vector<std::string> GetDetail() {
    return this->product_detail;
  }
  void PrintDetail() {
    for (const auto str : this->product_detail) {
      std::cout << str << std::endl;
    }
  }

 private:
  std::vector<std::string> product_detail;
};

// Builder 的介面(規範所有)
class IterfaceBuilder {
 public:
  virtual void Reset() = 0;
  virtual void SetDestination(std::string destination) = 0;
  virtual void SetPrice() = 0;
  virtual void SetDifficulty() = 0;
  virtual void SetDurationHours() = 0;
  virtual void SetMaxParticipants() = 0;
  virtual void SetDescription() = 0;
  virtual void SetSalesContext() = 0;
  virtual Product GetProduct() = 0;
};

// 實作Builder的class
class ConcreteBuilder : public IterfaceBuilder {
 public:
  ConcreteBuilder() {
    Reset();
  }
  ~ConcreteBuilder() {
    delete product;
  }
  void Reset() {
    product = new Product();
    // if (!product) {
    //   product = std::make_shared<Product>();
    // } else {
    //   product.reset();
    // }
  }
  void SetDestination(std::string destrination) {
    product->AddDetail("地點: " + destrination);
  }
  void SetPrice() {
    product->AddDetail("每人價格: NTD " + std::to_string(price));
  }
  void SetDifficulty() {
    product->AddDetail("困難度: " + std::to_string(difficulty) + "/5");
  }
  void SetDurationHours() {
    product->AddDetail("時間: " + std::to_string(durationHours));
  }
  void SetMaxParticipants() {
    product->AddDetail("每團人數限制: " + std::to_string(maxParticipants));
  }
  void SetDescription() {
    product->AddDetail("SUP 活動敘述: " + description);
  }
  void SetSalesContext() {
    product->AddDetail(note);
  }
  Product GetProduct() {
    return *product;
  }

 private:
  // std::shared_ptr<Product> product;
  Product *product;
  int price = 3000;
  int difficulty = 3;
  int durationHours = 5;
  int maxParticipants = 10;
  std::string description = "立式槳板運動";
  std::string note = "7/1-8/31 SUP 行程 85 折";
};

// Director : Director可以選擇呼叫不同的ConcreteBuilder來實作
class Director {
 public:
  Product CreateProduct(IterfaceBuilder *builder_obj, std::string destination) {
    builder_obj->SetSalesContext();
    builder_obj->SetDestination(destination);
    builder_obj->SetPrice();
    builder_obj->SetDifficulty();
    builder_obj->SetDurationHours();
    builder_obj->SetMaxParticipants();
    builder_obj->SetDescription();
    return builder_obj->GetProduct();
  }
};

// Client : 利用Director打造行程
class Client {
  static void PrintProductDetail(Product *product) {
    product->PrintDetail();
  }
};

int main() {
  Director *director;
  Product product;

  std::cout << "----------方案一----------" << std::endl;
  std::cout << "SUP 象鼻岩行程" << std::endl;
  product = director->CreateProduct(new ConcreteBuilder(), "深澳象鼻岩");
  product.PrintDetail();

  std::cout << "----------方案二----------" << std::endl;
  std::cout << "SUP 龜山島行程" << std::endl;
  product = director->CreateProduct(new ConcreteBuilder(), "龜山島牛奶湖");
  product.PrintDetail();

  std::cout << "----------方案三----------" << std::endl;
  std::cout << "獨木舟 東澳行程" << std::endl;
  product = director->CreateProduct(new ConcreteBuilder(), "東澳海蝕洞");
  product.PrintDetail();
}

#elif test_idx == 2
// 方式二：透過靜態內部類方式實現建造者模式

// Product
class Product {
 public:
  std::vector<std::string> GetDetail() {
    return this->product_detail;
  }
  void SetDestination(std::string destrination) {
    this->destination = destrination;
    this->product_detail.emplace_back("地點: " + destrination);
  }
  void SetPrice(int price) {
    this->price = price;
    this->product_detail.emplace_back("每人價格: NTD " + std::to_string(price));
  }
  void SetDifficulty(int difficulty) {
    this->difficulty = difficulty;
    this->product_detail.emplace_back("困難度: " + std::to_string(difficulty) + "/5");
  }
  void SetDurationHours(int durationHours) {
    this->durationHours = durationHours;
    this->product_detail.emplace_back("時間: " + std::to_string(durationHours));
  }
  void SetMaxParticipants(int maxParticipants) {
    this->maxParticipants = maxParticipants;
    this->product_detail.emplace_back("每團人數限制: " + std::to_string(maxParticipants));
  }
  void SetDescription(std::string description) {
    this->description = description;
    this->product_detail.emplace_back("SUP 活動敘述: " + description);
  }
  void SetSalesContext(std::string salesContext) {
    this->salesContext = salesContext;
    this->product_detail.emplace_back(salesContext);
  }
  void PrintDetail() {
    for (const auto str : this->product_detail) {
      std::cout << str << std::endl;
    }
  }

 private:
  std::string destination;
  int price;
  int difficulty;
  int durationHours;
  int maxParticipants;
  std::string description;
  std::string salesContext;
  std::vector<std::string> product_detail;
};

// Builder 的介面(規範所有)
// class IterfaceBuilder {
//  public:
//   // virtual void Reset() = 0;
//   virtual IterfaceBuilder SetDestination(std::string destination) = 0;
//   virtual IterfaceBuilder SetPrice(int price) = 0;
//   virtual IterfaceBuilder SetDifficulty(int difficulty) = 0;
//   virtual IterfaceBuilder SetDurationHours(int durationHours) = 0;
//   virtual IterfaceBuilder SetMaxParticipants(int maxParticipants) = 0;
//   virtual IterfaceBuilder SetDescription() = 0;
//   virtual IterfaceBuilder SetSalesContext() = 0;
//   // virtual Product GetProduct() = 0;
//   virtual Product Build() = 0;
// };
class IterfaceBuilder {
 public:
  // virtual void Reset() = 0;
  IterfaceBuilder SetDestination(std::string destination);
  IterfaceBuilder SetPrice(int price);
  IterfaceBuilder SetDifficulty(int difficulty);
  IterfaceBuilder SetDurationHours(int durationHours);
  IterfaceBuilder SetMaxParticipants(int maxParticipants);
  IterfaceBuilder SetDescription();
  IterfaceBuilder SetSalesContext();
  // virtual Product GetProduct() = 0;
  Product Build();
};

// Concrete Builder
// 在這class內function會將引數直接傳入Product的func，因為這些細節都改成在Product內實現。
class ConcreteBuilder : public IterfaceBuilder {
 public:
  ConcreteBuilder() {
    product = new Product();
  }
  ~ConcreteBuilder() {
    delete product;
  }
  ConcreteBuilder SetDestination(std::string destination) {
    product->SetDestination(destination);
    return *this;
  }
  ConcreteBuilder SetPrice(int price) {
    product->SetPrice(price);
    return *this;
  }
  ConcreteBuilder SetDifficulty(int difficulty) {
    product->SetDifficulty(difficulty);
    return *this;
  }
  ConcreteBuilder SetDurationHours(int durationHours) {
    product->SetDurationHours(durationHours);
    return *this;
  }
  ConcreteBuilder SetMaxParticipants(int maxParticipants) {
    product->SetMaxParticipants(maxParticipants);
    return *this;
  }
  ConcreteBuilder SetDescription() {
    product->SetDescription(this->description);
    return *this;
  }
  ConcreteBuilder SetSalesContext() {
    product->SetSalesContext(this->salesContext);
    return *this;
  }
  Product Build() {
    return *product;
  }

 private:
  Product *product;
  std::string description = "立式槳板運動（英語：Stand Up Paddle, SUP)，也俗稱「槳板」， 是起源於夏威夷的一種運動，由衝浪與傳統的手划槳板（Paddleboard）結合而成。活動器材係由槳板（類似大型衝浪板）加上一支高於身高的單槳所組成。運用於衝浪時又稱立式單槳衝浪（簡稱立槳衝浪），也可在湖泊及河流等水域，從事探索、激流及救生等多方面的活動。";
  std::string salesContext = "7/1-8/31 SUP 行程 85 折";
};

// Client
class Client {
 public:
  static void PrintProductDetail(Product product) {
    product.PrintDetail();
  }
};

int main() {
  std::cout << "main start" << std::endl;

  Product product;
  ConcreteBuilder concreteBuilder;
  std::cout << "----------方案一----------" << std::endl;
  std::cout << "SUP 象鼻岩行程" << std::endl;
  product = concreteBuilder.SetSalesContext().SetDestination("深澳象鼻岩").SetPrice(2000).SetDifficulty(2).SetDurationHours(4).SetMaxParticipants(15).SetDescription().Build();
  Client::PrintProductDetail(product);

  std::cout << "----------方案二----------" << std::endl;
  std::cout << "SUP 龜山島行程" << std::endl;
  product = concreteBuilder.SetSalesContext().SetDestination("龜山島牛奶湖").SetPrice(5000).SetDifficulty(4).SetDurationHours(6).SetMaxParticipants(10).SetDescription().Build();
  Client::PrintProductDetail(product);

  std::cout << "main end" << std::endl;
}

#endif