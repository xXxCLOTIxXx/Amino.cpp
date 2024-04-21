#include <string>
#include "json.hpp"
using json = nlohmann::json;

class FanClubList {
public:
    std::vector<json> data;
    
    FanClubList(std::vector<json> data); 

};