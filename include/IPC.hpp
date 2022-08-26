#ifndef PG_IPC_HPP
#define PG_IPC_HPP

#include <map>
#include <string>

enum Games;
class wxFrame;

struct GameReturn {
    int returnCode;
    std::string errors;
    bool closeStarter;
};

class IPC {
    private:
        static const std::map<Games, std::string> paths;
        static const std::string pathPrefix, pathSuffix;

        std::string mainPath;

        std::string getPath(Games game);
        GameReturn runGameNative(const std::string& path);

    public:
        IPC(const std::string& programPath);

        bool checkAllGames();
        bool isGameAvailable(Games game);

        bool runGame(Games game, wxFrame* frame);
};

#endif//PG_IPC_HPP