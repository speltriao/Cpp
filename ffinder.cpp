//COMPILE WITH GCC FLAGS --std=c++17 -lstdc++fs//
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;


struct Input{
    std::string prmt; //parameter being searched
    bool extension=false; //user included the file extension or not (.something)//
    bool hidden=false; //search or not in hidden directories
};

Input input(int argc,char* argv[]){
    Input i;
    std::string str;
    for (int j = 1; j < argc; j++){
      str.append(argv[j]);
      if (j!=(argc-1)) str+=" ";
    }
    if (str.find("-h") != std::string::npos){
        i.hidden=true;
        str.erase(str.find(" -h"),str.size());        
    }
    i.prmt=str;
    if (str.find(".") != std::string::npos) i.extension = true;
    return i;
}

std::string file_name(std::string s,bool extension){ //ignore files extension from files list
    std::string f = s.erase(0,s.rfind("/")+1);
    if ((!extension) && (f.rfind(".") != std::string::npos) && (f.find(".")!=0)){
        f.erase(f.rfind("."),f.size());
    }
    return f;
}

std::vector<std::string> vectorize (std::string str){
    std::vector<std::string> v;
    while(str.size()){
        int index = str.find(" ");
        if(index!=std::string::npos){
            v.push_back(str.substr(0,index));
            str = str.substr(index+1);
            if(str.size()==0)v.push_back(str);
        }else{
            v.push_back(str);
            str = "";
        }
    }
    return v;
}

bool compare(std::string way, std::string file){
    std::vector <std::string>  w = vectorize(way); //curent way
    std::vector <std::string>  f = vectorize(file); //searching
    int count = 0;
    int size = w.size();
    if (size == 1){
         if(strcasecmp(way.c_str(),file.c_str())==0) return true; 
        }
    else{
        for(std::string s1: w){
            for(std::string s2: f){
                if(strcasecmp(s1.c_str(),s2.c_str())==0) count++; //case insensitive comparison
            }
        }
    }
    size = size - 2; //quantity of maximum different words between search and result
    if ((count>size)&&(size>0)) return true;
    else return false;
}   



void ffinder(std::string file,std::string home, bool extension,bool inclh){ // include hidden files on search or not 
    for (const auto & entry : fs::directory_iterator(home)){
        std::string path = entry.path();
        std::string way = file_name(path,extension);
        if(entry.is_regular_file()&&(compare(way,file))) std::cout<<"File found at: "<< path <<"\n";
        else if (entry.is_directory()){
            if (inclh)  ffinder(file,path,extension,inclh); //search includes hidden directories
            else if(way.find(".") != 0) ffinder(file,path,extension,inclh); //folders that start with "." are hidden.
        } 
    }
}

int main(int argc, char* argv[]){
    Input in = input(argc,argv);
    if(in.prmt.empty()){
        std::cout<<"Please, add a paramter\n";
    } 
    else ffinder(in.prmt,getenv("HOME"),in.extension,in.hidden);
    return 0;
}

