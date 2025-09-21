#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "file.h"

int main(int argc, char* argv[]){
    if (argc==1){
        std::cout<<"error: no args provided\n"<<std::flush;
        return -1;
    }

    std::string workingFolder=".lawx";
    std::string apiKeyFile = "API_key.txt";

    if (std::strcmp(argv[1], "-s")==0){

        if (argc!=3) {
            std::cout<<"error: all fields for setup not provided\n"<<std::flush;
            return -1;
        }

        setWorkingFolder(workingFolder);
        
        if (makeDirInHome()==-1) return -1;

        std::cout<<"--setting up--\n";
        std::cout<<"working folder:: "<<getHomePath()<<workingFolder<<'\n';
        std::cout<<"api:: "<<argv[2]<<'\n'<<std::flush;

        overwriteFile(apiKeyFile, argv[2]);
    }
    else if (std::strcmp(argv[1], "-f")==0){

        if (argc<=2){
            std::cout<<"error: no files provided\n"<<std::flush;
            return -1;
        }

        // make complete path of the api key file, /home/$USER/{workingFolder}/api_key.txt
        std::string apiFilePath="";
        apiFilePath.append(getHomePath());
        apiFilePath.append(workingFolder);
        apiFilePath.push_back('/');
        apiFilePath.append(apiKeyFile);

        if (!doesFileExists(apiFilePath)) {
            std::cout<<"error: API key file not present, try '-s API_KEY' to set up a new API key\n"<<std::flush;
            return -1;
        }

        std::string fileList="";
        for (int i=2; i<argc; i++) { 
            fileList.append(argv[i]);
            fileList.push_back(' ');
        }

        std::string finalCommand = "python3 api_handler.py ";
        finalCommand.append(apiFilePath);
        finalCommand.push_back(' ');
        finalCommand.append(fileList);

        // std::cout<<finalCommand<<'\n';

        const char * fC = finalCommand.c_str();
        int retCode = system(fC);
        return retCode;
    }

    return 0;
}