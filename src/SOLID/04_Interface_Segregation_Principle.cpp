// 介面隔離原則 Interface Segregation Principle (ISP)
// https://medium.com/@f40507777/%E4%BB%8B%E9%9D%A2%E9%9A%94%E9%9B%A2%E5%8E%9F%E5%89%87-interface-segregation-principle-isp-6854c5b3b42c
/*
理念核心:
  1. 不應該強迫用戶去依賴他們未使用的辦法
  2. 最小化類別與類別之間的介面

遇到的問題:
  1. 避免介面太多
  2. 並非全部的方法都會使用到
  3. 繼承後空實作

沒遵守DIP可能造成情況:
  1. 繼承或抽象類別 : 多餘的界面在子類別可能會有空實作，會使使用方造成不可預期錯誤。
  2. 假使A介面有BCD方法，使用者E使用B，其他人使用C or D，如果為了使用者改變了方法B的介面，其他使用者就必須重新Compile

解決辦法:
  1. 客製使用者的interface，只提供用的到的，在利用組合實現。
  2. 分割組合:將類別分割後，需要reuse實作地方在利用組合方式實現，這裡可以使用多重繼承或Delegate等等
*/

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
// #include <python3.5m/Python.h>
// int main() {
//   // Python initialize
//   Py_Initialize();
//   if (!Py_IsInitialized()) {
//     std::cout << "Python initialization failed" << std::endl;
//     return -1;
//   }

//   // choose 1
//   if (!PyRun_SimpleString("execfile('pythontest.py')"))
//     std::cout << "fail" << std::endl;

//   // choose 2
//   char fileStr[] = "pythontest.py";
//   FILE *fp;
//   if (!(fp = fopen(fileStr, "r")))
//     std::cout << "open python file failed" << std::endl;

//   if (!PyRun_SimpleFile(fp, fileStr))
//     std::cout << "execute python file failed!" << std::endl;
//   fclose(fp);

//   // 釋放資源
//   Py_Finalize();

//   return 0;
// }

struct Document;
/*
struct IMachine {
  virtual void print(Document& doc) = 0;
  virtual void scan(Document& doc) = 0;
  virtual void fax(Document& doc) = 0;
};

struct MFP : IMachine {
  void print(Document& doc) override {
  }
  void scan(Document& doc) override {
  }
  void fax(Document& doc) override {
  }
};
// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much
*/

// virtual interface
struct IPrinter {
  virtual void print(Document& doc) = 0;
};
struct IScanner {
  virtual void scan(Document& doc) = 0;
};

// implement interface
struct Printer : IPrinter {
  void print(Document& doc) override;
};
struct Scanner : IScanner {
  void scan(Document& doc) override;
};

// 如果客戶指要求print && scan，而沒有fax，我們就可以新增一個interface
// 並且只繼承了print && scan
// IMachine 繼承了兩個功能的interface
struct IMachine : IPrinter, IScanner {
};
struct Machine : IMachine {
  IPrinter& printer;
  IScanner& scanner;
  // constructor
  Machine(IPrinter& printer, IScanner& scanner)
      : printer{printer},
        scanner{scanner} {
  }
  void print(Document& doc) override {
    printer.print(doc);
  }
  void scan(Document& doc) override {
    scanner.scan(doc);
  }
};
// IPrinter --> Printer
// everything --> Machine

int main() {
  Document doc;
  Printer print;
  Scanner scan;
  Machine a(print, scan);
  a.print(doc);
}