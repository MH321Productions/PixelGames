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