#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "Util.hpp"
#include "Resources.hpp"

using namespace std;
using namespace filesystem;
using nlohmann::json;

json formatResource(const Resource& r);

bool ResourceHandler::loadFile(const string& fileName, const bool& clear) {
    if (fileName.empty()) {
        cerr << "Resource file name is empty" << endl;
        return false;
    }

    //create full path
    path p(mainPath);
    p.append(pathPrefix).append(fileName + pathSuffix);

    //open file and read the contents of it
    ifstream file(p);
    if (!file) {
        cerr << "Couldn't open the file " << p.string() << endl;
        return false;
    }

    stringstream buf;
    buf << file.rdbuf();
    string raw = buf.str();
    file.close();

    //Decode the Base64 text into json
    vector<Byte> decodedVec = Base64::decode(raw);
    string decoded(decodedVec.size(), ' ');
    for (size_t i = 0; i < decodedVec.size(); i++) decoded.at(i) = (char) decodedVec.at(i);

    cout << decoded << endl;

    json j = json::parse(decoded);

    if (!j.contains("resources") || !j.at("resources").is_array()) {
        cerr << "The resource file doesn't contain any resources" << endl;
        return false;
    }

    //clear the old resources
    if (clear) resources.clear();

    //Read the values
    string name, text;
    ResourceType type;
    long number;
    vector<Byte> bin;
    Resource r;
    for (json& res: j.at("resources")) {
        if (!res.is_object()) continue;

        try {
            name = res.at("name");
            type = res.at("type") > 0 && res.at("type") < 4 ? ResourceType(res.at("type")) : Undefined;

            switch (type) {
                case Text:
                    text = res.at("text");
                    r = Resource(name, text);
                    break;
                case Number:
                    number = res.at("number");
                    r = Resource(name, number);
                    break;
                case Binary:
                    bin = Base64::decode(res.at("binary"));
                    r = Resource(name, bin);
                    break;
                default:
                    continue;
            }

            if (type) resources.insert_or_assign(name, r);

        } catch(exception& e) {
            continue;
        }
    }

    return true;
}

bool ResourceHandler::saveFile(const string& fileName) {
    if (fileName.empty()) {
        cerr << "Resource file name is empty" << endl;
        return false;
    }

    //create full path
    path p(mainPath);
    p.append(pathPrefix).append(fileName + pathSuffix);

    ofstream file(p);
    if (!file) {
        cerr << "Couldn't open file " << p.string() << endl;
        return false;
    }

    //Format resources into json
    vector<json> jRes;
    for (const pair<string, Resource>& r: resources) jRes.push_back(formatResource(r.second));

    //Create json file
    json j = {
        {"resources", jRes}
    };

}

json formatResource(const Resource& r) {
    if (!r.isValid()) return {};

    json j = {
        {"name", r.getName()},
        {"type", r.getType()}
    };

    switch(r.getType()) {
        case Text:
            j.at("text") = r.getText();
            break;
        case Number:
            j.at("number") = r.getNumber();
            break;
        case Binary:
            j.at("binary") = Base64::encode(r.getBinary());
            break;
    }

    return j;
}