#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
using namespace std;

class FileHandler {
public:
    void saveDataToFile(const string& filename, const string& data, bool append = false);
    bool fileExists(const string& filename);
    string handleFileInput(bool& appendData);
private:
    string getValidFilename();
    string getFullPath();
    bool getOverwriteChoice();
    bool getAppendChoice();
};

#endif