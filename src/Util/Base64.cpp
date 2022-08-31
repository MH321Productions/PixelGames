/**
 * This code is mainly copied from a modified version of René Nyffenegger's implementation
 * (see https://stackoverflow.com/a/13935718 for the modified version and
 * http://www.adp-gmbh.ch/cpp/common/base64.html for the original implementation)
 */ 

#include "Util.hpp"

using namespace std;

const string Base64::b64Chars = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

inline bool Base64::isBase64(const Byte& c) {
    return (isalnum(c) || c == '+' || c == '/');
}

string Base64::encode(const vector<Byte>& buf) {
    return encode(buf.data(), buf.size());
}

string Base64::encode(const Byte* buf, size_t len) {
    string ret;
    int i = 0, j = 0;
    Byte cArray3[3], cArray4[4];

    while (len--) {
        cArray3[i++] = *(buf++); //Read 3 Bytes

        if (i == 3) { //Decode into 4 chars
            cArray4[0] = (cArray3[0] & 0xfc) >> 2;
            cArray4[1] = ((cArray3[0] & 0x03) << 4) + ((cArray3[1] & 0xf0) >> 4);
            cArray4[2] = ((cArray3[1] & 0x0f) << 2) + ((cArray3[2] & 0xc0) >> 6);
            cArray4[3] = cArray3[2] & 0x3f;

            //Write into string
            for (i = 0; i < 4; i++) ret.push_back(b64Chars.at(cArray4[i]));

            i = 0;
        }
    }

    if (i) { //If there are still bytes left, encode them as well
        for (j = i; j < 3; j++) cArray3[j] = '\0';

        cArray4[0] = (cArray3[0] & 0xfc) >> 2;
        cArray4[1] = ((cArray3[0] & 0x03) << 4) + ((cArray3[1] & 0xf0) >> 4);
        cArray4[2] = ((cArray3[1] & 0x0f) << 2) + ((cArray3[2] & 0xc0) >> 6);
        cArray4[3] = cArray3[2] & 0x3f;

        for (j = 0; j <= i; j++) ret.push_back(b64Chars.at(cArray4[j]));

        while ((i++ < 3)) ret.push_back('=');
    }

    return ret;
}

vector<Byte> Base64::decode(const string& encoded) {
    size_t len = encoded.size();
    int i = 0, j = 0, in = 0;
    Byte cArray3[3], cArray4[4];
    vector<Byte> ret;

    while (len-- && encoded.at(in) != '=' && isBase64(encoded.at(in))) {
        cArray4[i++] = encoded.at(in); //Read 4 chars
        in++;

        if (i == 4) { //Decode into 3 Bytes
            for (i = 0; i < 4; i++) cArray4[i] = b64Chars.find(cArray4[i]); //Replace char values with base64 indices

            cArray3[0] = (cArray4[0] << 2) + ((cArray4[1] & 0x30) >> 4);
            cArray3[1] = ((cArray4[1] & 0xf) << 4) + ((cArray4[2] & 0x3c) >> 2);
            cArray3[2] = ((cArray4[2] & 0x3) << 6) + cArray4[3];

            for (i = 0; i < 3; i++) ret.push_back(cArray3[i]);

            i = 0;
        }
    }

    if (i) { //If there are still chars left, decode them as well
        for (j = i; j < 4; j++) cArray4[j] = 0;

        for (j = 0; j < 4; j++) cArray4[j] = b64Chars.find(cArray4[j]);

        cArray3[0] = (cArray4[0] << 2) + ((cArray4[1] & 0x30) >> 4);
        cArray3[1] = ((cArray4[1] & 0xf) << 4) + ((cArray4[2] & 0x3c) >> 2);
        cArray3[2] = ((cArray4[2] & 0x3) << 6) + cArray4[3];

        for (j = 0; j < i - 1; j++) ret.push_back(cArray3[j]);
    }

    return ret;
}