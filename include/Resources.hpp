#ifndef PG_RESOURCES_HPP
#define PG_RESOURCES_HPP

#include <vector>
#include <map>
#include <string>

using Byte = unsigned char;

enum ResourceType: unsigned char {Undefined, Text, Number, Binary};
class ResourceHandler;
class EntryPanelImpl; //Resource formatter
class FormatterFrameImpl;

/**
 * A class wrapper for a resource.
 * It can contain EITHER a text,
 * a number, or a vector of binary
 * data. It is immutable (read-only)
 */ 
class Resource {
    friend class ResourceHandler;
    friend class EntryPanelImpl;
    private:
        ResourceType type;
        std::string name, text;
        long number;
        std::vector<Byte> bin;

        Resource(const std::string& name, const std::string& text) : name(name), type(Text), text(text), number(0) {}
        Resource(const std::string& name, const long& number) : name(name), type(Number), text(""), number(number) {}
        Resource(const std::string& name, const std::vector<Byte>& bin) : name(name), type(Binary), text(""), number(0), bin(bin) {}

        size_t getSize() const;

    public:
        static const Resource emptyResource;

        Resource() : name("null"), type(Undefined), text(""), number(0) {}

        bool isText()   const {return type == Text;}
        bool isNumber() const {return type == Number;}
        bool isBinary() const {return type == Binary;}
        bool isValid()  const {return type != Undefined;}

        ResourceType getType()        const {return type;}
        std::string getName()         const {return name;}
        std::string getText()         const {return text;}
        long getNumber()              const {return number;}
        std::vector<Byte> getBinary() const {return bin;}
        std::string getBinaryAsString() const {
            if (bin.empty()) return "";
            else return std::string((char*) bin.data(), bin.size());
        }
};

/**
 * The I/O handler for resources
 */ 
class ResourceHandler {
    friend class FormatterFrameImpl;
    private:
        static const std::string pathPrefix, pathSuffix;
        std::string mainPath;
        std::map<std::string, Resource> resources;

        bool saveFile(const std::string& filePath);
        bool loadIntern(const std::string filePath, const bool& clear = true);

        ResourceHandler(const std::map<std::string, Resource>& res) : resources(res) {}

    public:
        ResourceHandler(const std::string& mainPath) : mainPath(mainPath) {}

        /**
         * Loads a resource file and parses it.
         * @param resFileName The name of the resource file (not the extension)
         * @param clear If the loaded resources shall be cleared when loading new ones
         * @returns If the reading and parsing were successful
         */
        bool loadFile(const std::string& fileName, const bool& clear = true);

        /**
         * Searches the loaded resources for the given name
         * @param resName The internal name of the resource
         * @returns The loaded resource or an invalid one
         */
        Resource getResource(const std::string& resName) const;

        /**
         * Searches the loaded resources for the given name
         * @param resName The internal name of the resource
         * @returns If the resource exists
         */ 
        bool hasResource(const std::string& resName) const;
};

#endif //PG_RESOURCES_HPP