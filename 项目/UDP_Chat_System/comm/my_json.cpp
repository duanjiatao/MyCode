#include "my_json.h"

void my_json::serialize(Json::Value& val, std::string& out)
{
#ifdef _FASTER_WRITER_
    Json::FasterWriter _w;
#else
    Json::StyledWriter _w;
#endif

    out = _w.write(val);
}

void my_json::unserialize(std::string& in, Json::Value& val)
{
    Json::Reader _r;

    _r.parse(in, val, false);
}

#ifdef _MY_JSON_MAIN_
int main()
{
    return 0;
}
#endif



