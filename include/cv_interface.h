#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

// struct PcbaInspectionItem {
//   struct CapacitorType{
//     enum class MissingPart{

//     };
//   };
//   enum class CapacitorType {
//     Missing_part,
//     Wrong_part,
//     Wrong_polarity,
//   };
// };
// PcbaInspectionItem::CapacitorType::MissingPart

// template <typename EnumT>
namespace InspectionItems {
namespace PCBA {
namespace Capacitor {
enum class MissingPart {
  Min_inRange,
  Max_inRange,
};
enum class WrongPart {

};
enum class WrongPolarity {

};
};  // namespace Capacitor
namespace Label {

};  // namespace Label
namespace Jumper {

};
namespace Connector {

};
};  // namespace PCBA
};  // namespace InspectionItems

template <class EnumT>
class BaiscOperation {
 public:
  virtual int SetParameterBool(EnumT type, bool value) = 0;
  virtual virtual int GetResult() = 0;
};
/*
class PCBA : BaiscOperation {
 public:
  int SetParameter();
};
*/

class Positaioning {
 public:
  virtual int Locate() = 0;
  virtual int GetPositioning() = 0;

 private:
};
class Stitching {
 public:
  virtual int Stitch() = 0;
  virtual int GetStitching() = 0;

 private:
};
class SetGet {
};
class ProductA : Positaioning, Stitching {
  enum class InspectType {
    A,
    B,
    C,
  };

 public:
  // 定位
  int Locate();
  int GetPositioning();
  // 拼接
  int Stitch();
  int GetStitching();
  // 檢測內容
  int GetInspectionResult(InspectType type);

 private:
  // pimpl include Positaioning & Stitching
};