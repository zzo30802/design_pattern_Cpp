#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

typedef const bool(LINES_FILTER_FUNC)(const double _data);
LINES_FILTER_FUNC LINES_FILTER_NONE;
LINES_FILTER_FUNC LINES_FILTER_WIDTH;
LINES_FILTER_FUNC LINES_FILTER_LENGTH;