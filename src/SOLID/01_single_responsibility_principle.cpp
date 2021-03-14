/*
參考: https://medium.com/@f40507777/%E5%96%AE%E4%B8%80%E8%81%B7%E8%B2%AC%E5%8E%9F%E5%89%87-single-responsibility-principle-7b4eb03f1fff
大家習慣把相關的行為、資料通通封裝在一起
但實際上已經超過一種以上責任
甚至把不相關的(Utility、Util之類的)也通通封裝在一起

理念核心:
  一個class只有一個原因會使其改變。

可能發生問題:
  1. 改A壞B(程式相當脆弱，修改時容易產生bug)
  2. 一個class的行數過多 (表示有些工作可能可以分離開來)
  3. 無法寫測試 (高耦合，需要傳入參數過多，不好寫測試)

解決方法:
  根據function使用的目的不同，應該將其分開。
  例如有一個class為Rectangle，內容有兩個方法(area算面積、draw在GUI上畫圖)
  同一個class內會因為計算面積方法的改變而去影響其使用者(畫圖改變)
  所以"面積運算"與"畫圖"是兩個不同的用途，為了避免一個類別有兩個職責
  需要將兩種性質分開
  Computational Geometry Application : class Geometric Rect::area()
  Graphcal Application : class rect::draw()

SRP困難點:
  1. 職責的劃分。
  2. 類別的命名: 名稱被須清楚表達其用途
  3. 劃分的細度: 分割太細會使得程式過於複雜
  4. 類別之間的依賴: 如果兩個職責永遠連動且同時變化，就不必分離，否則會產生不必要的複雜性。

總結:
  SRP最難的地方在於就算知道職責分布也不太容易分離，需要依照實際情況決定。
*/

#include <boost/lexical_cast.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace boost;

// 只負責撰寫日記
struct Journal {
  string title;
  vector<string> entries;
  Journal(const string& title) : title(title) {}
  // add new lines on journal
  void add_entry(const string& entry) {
    static int count = 1;
    entries.push_back(lexical_cast<string>(count++) + ": " + entry);
  }
  // // Save journal
  // void save(const string& filename) {
  //   ofstream ofs(filename);
  //   for (auto& es : entries) {
  //     ofs << e << endl;
  //   }
  // }
};
// 只負責儲存日記
struct PersistenceManager {
  static void save(const Journal& j, const string& filename) {
    ofstream ofs(filename);
    for (auto& e : j.entries)
      ofs << e << endl;
  }
};

int main() {
  // 單一職責：兩個struct分別對不同的功能做回應，減少耦合性，避免一個功能同時對多個對象負責
  // 撰寫日記
  Journal journal("Dear Diary");
  journal.add_entry("I ate a bug");
  journal.add_entry("I cried today");

  // journal.save("diary.txt");

  // 儲存日記
  PersistenceManager pm;
  pm.save(journal, "diary.txt");

  getchar();
  return 0;
}