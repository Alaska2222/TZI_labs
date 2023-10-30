#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

void FileHandler::saveDataToFile(const string& filename, const  string& data, bool append) {
    ofstream outFile(filename, append ? ios::app : ios::out);

    if (outFile.is_open()) {
        outFile << data << endl;
        cout << "Data saved to file: " << filename << endl;
    }
    else {
        throw  runtime_error("Unable to open the file for writing.");
    }
}

bool FileHandler::fileExists(const  string& filename) {
    ifstream file(filename);
    return file.good();
}

string FileHandler::handleFileInput(bool& appendData) {
    string fullFilePath;
    bool validFile = false;

    while (!validFile) {
        string filename = getValidFilename();

        if (filename.empty()) {
            cout << "Operation canceled." << endl;
            return "";
        }

        string filepath = getFullPath();

        if (filepath == "exit" ) {
            cout << "Operation canceled." << endl;
            return "";
        }
        if (filepath.empty()) {
            fullFilePath = "C:/Users/Alaska/Desktop/" + filename;
        }
        else {
            fullFilePath = filepath + "/" + filename;
        }

        if (fileExists(fullFilePath)) {
            cout << "File already exists at: " << fullFilePath << endl;
            if (getOverwriteChoice()) {
                validFile = true;
            }
            else {
                return "";
            }
        }
        else {
            validFile = true;
        }
        appendData = getAppendChoice();
    }

    return fullFilePath;
}

string FileHandler::getValidFilename() {
    while (true) {
        string filename;
        cout << "(2) Enter the filename to save data (or type 'exit' to cancel): ";
        cin >> filename;

        if (filename == "exit") {
            return "";
        }

        if (filename.find('.') == string::npos) {
            filename += ".txt";
            return filename;
        }
        else if (filename.substr(filename.find_last_of('.') + 1) != "txt") {
            cout << "* You have entered the wrong extension *" << endl;
            cout << "Please use only .txt or no extension at all" << endl;
        }
        else {
            return filename;
        }
    }
}

string FileHandler::getFullPath() {
    string filepath;
    cout << "(3) Enter the FULL path where you want to save the file (or type 'exit' to cancel)" << endl;
    cout << "* It should look like this C:\\Users\\Alaska\\Desktop *" << endl;
    cout << "* If you leave it EMPTY, the file will automatically be saved to DESKTOP *" << endl;
    cout << ": ";
    cin.ignore();
    getline(cin, filepath);
    return filepath;
}

bool FileHandler::getOverwriteChoice() {
    while (true) {
        cout << "(4) Do you want to overwrite it? (Y/N): ";
        string overwriteFile;
        cin >> overwriteFile;
        cin.ignore();

        if (overwriteFile[0] == 'Y' || overwriteFile[0] == 'y') {
            return true;
        }
        else if (overwriteFile[0] == 'N' || overwriteFile[0] == 'n') {
            return false;
        }
        else {
            cout << "* Invalid choice. Please enter 'Y' to overwrite or 'N' to cancel *" << endl;
        }
    }
}

bool FileHandler::getAppendChoice() {
    while (true) {
        cout << "(5) Do you want to append to the file? (Y/N): ";
        string appendFile;
        cin >> appendFile;
        cin.ignore();

        if (appendFile[0] == 'Y' || appendFile[0] == 'y') {
            return true;
        }
        else if (appendFile[0] == 'N' || appendFile[0] == 'n') {
            return false;
        }
        else {
            cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
        }
    }
}
