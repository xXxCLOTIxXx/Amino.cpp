#include <vector>

class Gender {
public:
    static const int male = 1;
    static const int female = 2;
    static const int non_binary = 255;

    static const std::vector<int> all;
};

const std::vector<int> Gender::all = { Gender::male, Gender::female, Gender::non_binary };