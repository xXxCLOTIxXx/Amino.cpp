#include <string>
#include "json.hpp"
using json = nlohmann::json;

class MediaObject {
public:

    json data;

    MediaObject(json data); 

};