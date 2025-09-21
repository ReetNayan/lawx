#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>

std::string workingFolder="";

void setWorkingFolder(std::string workingFolderName){
    workingFolder=workingFolderName;
}

std::string getHomePath(){
    char* homePath = getenv("HOME");
    
    std::string homeFolderPath="";
    for (int i=0;homePath[i]!='\0';i++) homeFolderPath.push_back(homePath[i]);
    homeFolderPath.push_back('/');

    // returns:: /home/$USER/

    return homeFolderPath;
}

// only makeDirInHome() is checking HOME is set in env, therefore
// it should always be used before overwriteFile()
// even getHomePath() should always be called after makeDirInHome() because of this

int makeDirInHome(){

    if (getenv("HOME")==nullptr) {
        std::cout<<"error: $HOME not set in environment variables\n"<<std::flush;
        return -1;
    }

    std::string folderPath=getHomePath();
    folderPath.append(workingFolder);
    

    return std::filesystem::create_directories(folderPath);
}

void overwriteFile(std::string fileName, std::string data){
    std::string folderPath=getHomePath();
    folderPath.append(workingFolder);
    folderPath.push_back('/');

    std::string filePath="";
    filePath.append(folderPath);
    filePath.append(fileName);

    std::ofstream file;
    file.open(filePath);
    file<<data;
    file.close();

    return;
}

bool doesFileExists(std::string filePath){
    return std::filesystem::exists(filePath);
}