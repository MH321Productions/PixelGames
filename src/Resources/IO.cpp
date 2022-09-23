#include <iostream>
#include <fstream>
#include <string.h>
#include <filesystem>
#include "Util.hpp"
#include "Resources.hpp"
#include "zlib.h"

//Hack to avoid MS-DOS line-conversions
#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

using namespace std;
using namespace filesystem;
using Byte = unsigned char;

//Read helper methods
#define readLong(data, index, target) memcpy(target, data + index, 8); index += 8
#define readString(data, index, str) str = string((char*) (data + index)); index += str.size() + 1
#define readByte(data, index) data[index++]
#define readChar(data, index) (char) data[index++]
#define checkRange(index, max) if (index >= max) break

//Write helper methods
#define writeLong(data, index, value) memcpy(data + index, value, 8); index += 8
#define writeString(Data, index, str) memcpy(Data + index, (Byte*) str.data(), str.size()); index += str.size(); Data[index++] = 0
#define writeBinary(Data, index, bin) memcpy(Data + index, bin.data(), bin.size()); index += bin.size()
#define writeByte(data, index, value) data[index++] = value


bool ResourceHandler::loadFile(const string& fileName, const bool& clear) {
    if (fileName.empty()) {
        cerr << "Resource file name is empty" << endl;
        return false;
    }

    //create full path
    path p(mainPath);
    p.append(pathPrefix).append(fileName + pathSuffix);

    return loadIntern(p.string(), clear);
}

bool ResourceHandler::loadIntern(const std::string filePath, const bool& clear) {
    if (filePath.empty()) {
        cerr << "Resource file name is empty" << endl;
        return false;
    }

    if (!exists(filePath)) {
        cerr << "The file doesn't exist" << endl;
        return false;
    }

    //Read file into array
    path p(filePath);
    size_t fileSize = file_size(p);
    ifstream file(p, ios::binary);
    if (!file) {
        cerr << "The file couln't be read" << endl;
        file.close();
        return false;
    }

    Byte* raw = new Byte[fileSize];
    file.read((char*) raw, fileSize);
    file.close();

    //Check for magic value
    string magic((char*) raw, 5);
    if (magic != "PGRES") {
        cerr << "The file doesn't contain the magic value!" << endl;
        return false;
    }

    //Decompress data
    size_t dataSize;
    size_t index = 5;
    readLong(raw, index, &dataSize);
    Byte* decompressed = new Byte[dataSize];
    int result = uncompress(decompressed, &dataSize, raw + 13, fileSize - 13);
    if (result != Z_OK) {
        cerr << "Couldn't decompress file: " << zError(result) << endl;
        delete raw;
        delete decompressed;

        return false;
    } else {
        delete raw;
    }

    //clear the old resources
    if (clear) resources.clear();

    //Read from decompressed data
    index = 0;
    size_t binSize;
    string name, text;
    long number;
    vector<Byte> bin;
    ResourceType type;
    Resource r;

    while (index < dataSize) {
        readString(decompressed, index, name); //name
        checkRange(index, dataSize); //safety measures
        type = ResourceType(readByte(decompressed, index)); //Type
        checkRange(index, dataSize);

        switch (type) {
            case Text:
                readString(decompressed, index, text);
                r = {name, text};
                break;
            case Number:
                readLong(decompressed, index, &number);
                r = {name, number};
                break;
            case Binary:
                readLong(decompressed, index, &binSize);
                checkRange(index, dataSize);
                bin.clear();
                bin.resize(binSize);
                memcpy(bin.data(), decompressed + index, binSize);
                index += binSize;
                r = {name, bin};
                break;
            default:
                continue; //Shouldn't happen, bc the formatter deletes invalid resources
        }

        //Add/overwrite resource
        resources.insert_or_assign(name, r);
    }

    //Free data
    delete decompressed;

    return true;
}

bool ResourceHandler::saveFile(const string& filePath) {
    if (filePath.empty()) {
        cerr << "Resource file name is empty" << endl;
        return false;
    }

    //Calculate size of compression array
    size_t resSize = 0;
    for (const pair<string, Resource>& p: resources) resSize += p.second.getSize();

    //Save all resources into compression array
    Byte* raw = new Byte[resSize];
    size_t index = 0, binSize;
    Resource r;

    for (const pair<string, Resource>& p: resources) {
        if (!p.second.isValid()) continue; //Invalid resources aren't saved
        r = p.second;

        writeString(raw, index, r.name);
        writeByte(raw, index, (Byte) r.type);

        switch (r.type) {
            case Text:
                writeString(raw, index, r.text);
                break;
            case Number:
                writeLong(raw, index, &r.number);
                break;
            case Binary:
                binSize = r.bin.size();
                writeLong(raw, index, &binSize);
                writeBinary(raw, index, r.bin);
                break;
        }
    }

    //Compress array
    size_t compressedSize = compressBound(resSize);
    Byte* compressed = new Byte[compressedSize];
    int result = compress(compressed, &compressedSize, raw, resSize);
    if (result != Z_OK) {
        cerr << "Couldn't compress resources: " << zError(result) << endl;

        delete raw;
        delete compressed;

        return false;
    }

    //Write into file
    ofstream file(filePath, ios::binary);
    if (!file) {
        cerr << "Couldn't open file" << endl;

        delete raw;
        delete compressed;

        return false;
    }

    file << "PGRES"; //magic value
    file.write((char*) &resSize, 8); //uncompressed size
    file.write((char*) compressed, compressedSize); //compressed data
    file.close();

    //Free data
    delete raw;
    delete compressed;

    return true;
}