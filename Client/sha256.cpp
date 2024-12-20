#include "sha256.h"

string sha256(const string &data)
{
    SHA256 type;
    string hash;
    StringSource(
        data, true, new HashFilter(
            type, new HexEncoder(
                new StringSink(hash), true)));
    return hash;
}
