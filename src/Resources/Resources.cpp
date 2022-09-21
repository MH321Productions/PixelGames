#include "Util.hpp"
#include "Resources.hpp"

using namespace std;

const string ResourceHandler::pathPrefix = "res";
const string ResourceHandler::pathSuffix = ".res";
const Resource Resource::emptyResource;

Resource ResourceHandler::getResource(const string& resName) {
    if (resources.contains(resName)) return resources.at(resName);
    return Resource::emptyResource;
}

bool ResourceHandler::hasResource(const string& resName) {
    return resources.contains(resName);
}

size_t Resource::getSize() const {
    size_t ret = name.size() + 2; //Name, 1 byte for null-termination, 1 Byte for type

    switch (type) {
        case Text:
            ret += text.size() + 1; //Text, 1 byte for null-termination
            break;
        case Number:
            ret += 8; //8 bytes for 64 Bit number
            break;
        case Binary:
            ret += bin.size() + 8; //Binary, 8 bytes for size
            break;
        default:
            return 0; //Invalid resource, shouldn't be saved
    }

    return ret;
}