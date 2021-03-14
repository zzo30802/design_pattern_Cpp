#include <boost/lexical_cast.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace boost;
// enum class Capacitor {
//   MissingPart,
//   WrongPart,
//   WrongPolarity,
// };
// enum class Label {
//   MissingLabel,
//   DeformedLabel,
//   StainedLabel,
// };
// template <typename EnumT>
namespace InspectionItems {
namespace PCBA {
namespace Capacitor {
enum class EnalbeBool {
  ENABLE_MISSING_PART,
  ENABLE_WRONG_PART,
  ENABLE_WRONG_POLARITY,
};
enum class Common {
  GAUSSIAN_KSIZE,
  MIN_PIXEL_VALUE,
  MAX_PIXEL_VALUE,
};
enum class MissingPart {
  THRESHOLD_MIN_PIXEL_COUNT,  // 低於此值表示缺件
};
enum class WrongPart {
  RGB_R,
  RGB_G,
  RGB_B,
  RGB_TOLERANCE,
  THRESHOLD_MIN_PIXEL_COUNT,  // 低於此值表示錯件
  THRESHOLD_MAX_PIXEL_COUNT,  // 高於此值表示錯件
};
enum class WrongPolarity {
  THRESHOLD_MIN_ANGLE,
  THRESHOLD_MAX_ANGLE,
};
};  // namespace Capacitor
namespace Label {
enum class Common {

};

};  // namespace Label
namespace Jumper {

};
namespace Connector {

};
};  // namespace PCBA
};  // namespace InspectionItems

template <typename T>
struct ComponentProperties {
  virtual ~ComponentProperties() = default;
  virtual void SetParameter(EnumT, T value) = 0;
};

template <typename T>
struct CapacitorProperties : ComponentProperties{
  CapacitorProperties() = default;
  CapacitorProperties(bool m_enable_missing_part, bool m_enable_wrong_part, bool m_enable_wrong_polarity,
                      int m_gaussian_ksize, int m_min_pixel_value, int m_max_pixel_value,
                      int m_pixel_count_MissingPart,
                      int m_rgb_r, int m_rgb_g, int m_rgb_b, double m_rgb_tolerance,
                      int m_pixel_count_WrongPart, double m_min_angle,
                      double m_max_angle) : enable_missing_part(m_enable_missing_part),
                                            enable_wrong_part(m_enable_wrong_part),
                                            enable_wrong_polarity(m_enable_wrong_polarity),
                                            gaussian_ksize(m_gaussian_ksize),
                                            min_pixel_value(m_min_pixel_value),
                                            max_pixel_value(m_max_pixel_value),
                                            pixel_count_MissingPart(m_pixel_count_MissingPart),
                                            rgb_r(m_rgb_r),
                                            rgb_g(m_rgb_g),
                                            rgb_b(m_rgb_b),
                                            rgb_tolerance(m_rgb_tolerance),
                                            pixel_count_WrongPart(m_pixel_count_WrongPart),
                                            min_angle(m_min_angle),
                                            max_angle(m_max_angle) {}
  CapacitorProperties(CapacitorProperties& m_capacitor) {
    enable_missing_part = m_capacitor.enable_missing_part;
    enable_wrong_part = m_capacitor.enable_wrong_part;
    enable_wrong_polarity = m_capacitor.enable_wrong_polarity;
    gaussian_ksize = m_capacitor.gaussian_ksize;
    min_pixel_value = m_capacitor.min_pixel_value;
    max_pixel_value = m_capacitor.max_pixel_value;
    pixel_count_MissingPart = m_capacitor.pixel_count_MissingPart;
    rgb_r = m_capacitor.rgb_r;
    rgb_g = m_capacitor.rgb_g;
    rgb_b = m_capacitor.rgb_b;
    rgb_tolerance = m_capacitor.rgb_tolerance;
    pixel_count_WrongPart = m_capacitor.pixel_count_WrongPart;
    min_angle = m_capacitor.min_angle;
    max_angle = m_capacitor.max_angle;
  }
  SetParameter()
  bool enable_missing_part{true};
  bool enable_wrong_part{true};
  bool enable_wrong_polarity{true};
  int gaussian_ksize{3};     // 3~51
  int min_pixel_value{230};  // 0~255
  int max_pixel_value{255};  // 0~255
  // MissingPart
  int pixel_count_MissingPart{100000};  // >= 0
  // WrongPart
  int rgb_r{32};                     // 0~255
  int rgb_g{255};                    // 0~255
  int rgb_b{239};                    // 0~255
  double rgb_tolerance{0.4};         // 0 ~ 1.0
  int pixel_count_WrongPart{27000};  // >= 0
  // WrongPolarity
  double min_angle{270};  //90~270 //在角度範圍內表示電極的方向沒有偏掉或是相反
  double max_angle{90};
};

template <typename EnumT>
void SetParameter(EnumT, int value) {
}

struct CVResult {
  vector<int> error_num;
};
//***********
template <typename T>
struct Component {
  virtual bool IsPassed(T* item) const = 0;  // 回傳此元件是否pass
  // virtual vector<int> DefectEnum(T* item) const = 0;  // 回傳此元件所有的defect
};

template <typename T>
struct Filter {
  virtual vector<T*> DefectEnum(vector<T*> items,
                                Component<T>& inspect) = 0;
};
struct InspectionFilter : Filter<CVResult> {
  vector<CVResult*> DefectEnum(vector<CVResult*> items,
                               Component<CVResult>& inspect) {
    vector<CVResult*> result;
    for (auto& p : items) {
      if (inspect.IsPassed(p))
        result.push_back()
    }
  }
};

int main() {
  SetParameter(InspectionItems::PCBA::Capacitor::Common::GAUSSIAN_KSIZE, 5);
}