// �سy�̼Ҧ� (Builder Design Pattern)
// �Ѧ�: https://medium.com/wenchin-rolls-around/%E8%A8%AD%E8%A8%88%E6%A8%A1%E5%BC%8F-%E5%BB%BA%E9%80%A0%E8%80%85%E6%A8%A1%E5%BC%8F-builder-design-pattern-7c8eac7c9a7

/*
����:
  - �سy�� (Builder) �Ҧ��N���󪺡u�غc�v�P�u��ܡv�����A���èëʸ˫غc�L�{���Ӹ`�C
    ���ڭ̥i�H�N���󥻨���Ѧ����P������A�@�B�@�B�سy�C�@�����A�̫Უ�ͥX��
    �̷Q�n����������C
  - �Ocreational design pattern�C�D�n�ت��O���A�i�H�@�B�B���غc����������C
    �o�س]�p�Ҧ����\�A�ϥΤ@�˪��{�����c�Ӳ��ͥX���P�����Ϊ�ܪ��{���C

�u�I:
  ��@��class�ŧi�F�۷�h���ܼơA���O�o�ݭn���U�ؤ��P�զX(�Ʀܦ��ǰѼƬO�i�諸)�A�N�i�H�ϥ�builder�Ҧ��A
  �i�H�קK�ܪ����غc�l�άO�L�h���޼ƾɭP�V�áC

For Example:
  ���O�U�C����@
  new House(2, 4, 3, true, true, true, false, false, false);
  new House(2, 4, 3, true, true, true, false, null, null);
  �z�Lbuilder�Ҧ��A�i�H�ܦ�
  HouseBuilder.SetDoorNum(2);            
  HouseBuilder.SetWindowNum(4);            
  HouseBuilder.SetRoomNum(3);        
  HouseBuilder.SetHasGarden(true);
  HouseBuilder.SetHasPool(true);       
  ...    
  HouseBuilder.GetHouse();
  �άO
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
�H�U�d��:
���]�n�}�@�����W���ʤu�@��
���]���ѧA�֦� SUP�B�W���B�B��B�Į��K�K�������M�M�~�A����}�@�Ӥ��W���ʤu�@�ǡA�]�p���P�����ʨӾP��C
*/

/**
 * 1 : SUP ��{����B�x���סB�ɶ��K�K���ۦP�A�Ȧa�I���t��
 * 2 : �N1����ʡA�ϱo�Ҧ��ѼƳ��i�H�Ȼs��
**/
#define test_idx 2

#if test_idx == 1
// ------��k�@------
// �z�LClient�BDirector�BBuilder �M Product �Φ����سy�̼Ҧ�

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

// Builder ������(�W�d�Ҧ�)
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

// ��@Builder��class
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
    product->AddDetail("�a�I: " + destrination);
  }
  void SetPrice() {
    product->AddDetail("�C�H����: NTD " + std::to_string(price));
  }
  void SetDifficulty() {
    product->AddDetail("�x����: " + std::to_string(difficulty) + "/5");
  }
  void SetDurationHours() {
    product->AddDetail("�ɶ�: " + std::to_string(durationHours));
  }
  void SetMaxParticipants() {
    product->AddDetail("�C�ΤH�ƭ���: " + std::to_string(maxParticipants));
  }
  void SetDescription() {
    product->AddDetail("SUP ���ʱԭz: " + description);
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
  std::string description = "�ߦ��ժO�B��";
  std::string note = "7/1-8/31 SUP ��{ 85 ��";
};

// Director : Director�i�H��ܩI�s���P��ConcreteBuilder�ӹ�@
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

// Client : �Q��Director���y��{
class Client {
  static void PrintProductDetail(Product *product) {
    product->PrintDetail();
  }
};

int main() {
  Director *director;
  Product product;

  std::cout << "----------��פ@----------" << std::endl;
  std::cout << "SUP �H�󩥦�{" << std::endl;
  product = director->CreateProduct(new ConcreteBuilder(), "�`�D�H��");
  product.PrintDetail();

  std::cout << "----------��פG----------" << std::endl;
  std::cout << "SUP �t�s�q��{" << std::endl;
  product = director->CreateProduct(new ConcreteBuilder(), "�t�s�q������");
  product.PrintDetail();

  std::cout << "----------��פT----------" << std::endl;
  std::cout << "�W��� �F�D��{" << std::endl;
  product = director->CreateProduct(new ConcreteBuilder(), "�F�D���k�}");
  product.PrintDetail();
}

#elif test_idx == 2
// �覡�G�G�z�L�R�A�������覡��{�سy�̼Ҧ�

// Product
class Product {
 public:
  std::vector<std::string> GetDetail() {
    return this->product_detail;
  }
  void SetDestination(std::string destrination) {
    this->destination = destrination;
    this->product_detail.emplace_back("�a�I: " + destrination);
  }
  void SetPrice(int price) {
    this->price = price;
    this->product_detail.emplace_back("�C�H����: NTD " + std::to_string(price));
  }
  void SetDifficulty(int difficulty) {
    this->difficulty = difficulty;
    this->product_detail.emplace_back("�x����: " + std::to_string(difficulty) + "/5");
  }
  void SetDurationHours(int durationHours) {
    this->durationHours = durationHours;
    this->product_detail.emplace_back("�ɶ�: " + std::to_string(durationHours));
  }
  void SetMaxParticipants(int maxParticipants) {
    this->maxParticipants = maxParticipants;
    this->product_detail.emplace_back("�C�ΤH�ƭ���: " + std::to_string(maxParticipants));
  }
  void SetDescription(std::string description) {
    this->description = description;
    this->product_detail.emplace_back("SUP ���ʱԭz: " + description);
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

// Builder ������(�W�d�Ҧ�)
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
// �b�oclass��function�|�N�޼ƪ����ǤJProduct��func�A�]���o�ǲӸ`���令�bProduct����{�C
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
  std::string description = "�ߦ��ժO�B�ʡ]�^�y�GStand Up Paddle, SUP)�A�]�U�١u�ժO�v�A �O�_����L�¦i���@�عB�ʡA�ѽĮ��P�ǲΪ���E�ժO�]Paddleboard�^���X�Ӧ��C���ʾ����Y�ѼժO�]�����j���Į��O�^�[�W�@�䰪�󨭰�����թҲզ��C�B�Ω�Į��ɤS�٥ߦ���սĮ��]²�٥߼սĮ��^�A�]�i�b��y�Ϊe�y������A�q�Ʊ����B�E�y�αϥ͵��h�譱�����ʡC";
  std::string salesContext = "7/1-8/31 SUP ��{ 85 ��";
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
  std::cout << "----------��פ@----------" << std::endl;
  std::cout << "SUP �H�󩥦�{" << std::endl;
  product = concreteBuilder.SetSalesContext().SetDestination("�`�D�H��").SetPrice(2000).SetDifficulty(2).SetDurationHours(4).SetMaxParticipants(15).SetDescription().Build();
  Client::PrintProductDetail(product);

  std::cout << "----------��פG----------" << std::endl;
  std::cout << "SUP �t�s�q��{" << std::endl;
  product = concreteBuilder.SetSalesContext().SetDestination("�t�s�q������").SetPrice(5000).SetDifficulty(4).SetDurationHours(6).SetMaxParticipants(10).SetDescription().Build();
  Client::PrintProductDetail(product);

  std::cout << "main end" << std::endl;
}

#endif