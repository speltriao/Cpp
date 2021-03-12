//COMPILE WITH G++ FLAGS --std=c++17 -lstdc++fs//
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <vector>

#define RED     "\x1b[31m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"
#define BOLD "\e[1;37m"

namespace fs = std::filesystem;

struct Input{
    std::string prmt; //parameter being searched
    std::string dir=getenv("HOME"); //Base directory to start search
    bool extension=false; //user included the file extension or not (.something)//
    bool hidden=false; //search or not in hidden directories
};

Input input(int argc,char* argv[]){
    Input i;
    std::string str;
    std::string dir;
    for (int j = 1; j < argc; j++){
      str.append(argv[j]);
      if (j!=(argc-1)) str+=" ";
    }
    if (str.find("-h") != std::string::npos){
        i.hidden=true;
        if (str.size()==2) str.erase(); //user only inputed '-h', 
        else (str.erase(str.find("-h"),(str.find(" ")+1)));       
    }

    if (str.find("-c") != std::string::npos){
        dir=fs::current_path();
        if (str.size()==2) str.erase(); //user only inputed '-c', 
        else (str.erase(str.find("-c"),(str.find(" ")+1)));
        i.dir=dir;       
    }
    else if((str.find("/")!=std::string::npos)){ //user specified an directory
        dir=str.substr(str.find("/"),(str.find(" ")));
        if (!fs::exists(dir)) {
            std::cout<<"Invalid directory."<<"\n";
            exit(0);
        }
        if(dir.find(".")!=std::string::npos) i.hidden=true; //user manually entered a hidden directory
        str.erase(str.find("/"),str.find(" ")+1);
        i.dir=dir;
    }
    i.prmt=str;
    if (str.find(".") != std::string::npos) i.extension = true;  //user inputed the file extension
    return i;
}

std::string file_name(std::string s,bool extension){ //ignore files extension from files list
    std::string f = s.erase(0,s.rfind("/")+1);
    if ((!extension) && (f.rfind(".") != std::string::npos) && (f.find(".")!=0))  f.erase(f.rfind("."),f.size());
    return f;
}

std::string rSpecialChar(std::string s) {//remove speecial chars
    std::string space = " ";
    for (int i = 0; i < s.size(); i++) { 
        if ( (s[i] < '0' || s[i] > '9' ) && (s[i] < 'A' || s[i] > 'Z') &&  (s[i] < 'a' || s[i] > 'z')&&(s[i]!=' ')&&(s[i]!='.')){    
            if(s[i]=='_'||s[i]=='-'||s[i]==',') s.replace(i,1,space); //Underline and line are usually marking spaces
            else{
                s.erase(i, 1);
                i--;   
            }
        } 
    } 
    return s; 
} 

std::vector<std::string> vectorize (std::string str){//create a vector in which every element is a single word from str
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
    if (file.find(" ") == std::string::npos){ //search input does not contain spaces, it's a single word.
         if(strcasecmp(way.c_str(),file.c_str())==0)return true;
         return false; 
        }
    std::vector <std::string>  w = vectorize(way); //curent way
    std::vector <std::string>  f = vectorize(file); //search paramater
    int size = f.size();
    int count = 0;

    for(std::string s1: w){
        for(std::string s2: f){
            if(strcasecmp(s1.c_str(),s2.c_str())==0) count++; //case insensitive comparison
        }
    }
    
    size = size - 2; //quantity of maximum different words between paramater and result
    if ((count>size)&&(size>0)) return true;
    return false;
}   

void ffinder(std::string file,std::string home, bool extension,bool inclh){ // include hidden files on search or not 
    for (const auto & entry : fs::directory_iterator(home)){
        std::string path = entry.path();
        std::string way =rSpecialChar(file_name(path,extension));
        if(entry.is_regular_file()&&(compare(way,file))) std::cout<<BLUE<<"File found at: "<< entry.path() <<"\n"<<RESET;
        else if (entry.is_directory()){
            if (inclh) ffinder(file,path,extension,inclh); //search includes hidden directories
            else if(way.find(".") != 0) ffinder(file,path,extension,inclh); //folders that start with "." are hidden.
        } 
    }
}

int main(int argc, char* argv[]){
    Input in = input(argc,argv);
    std::string file = rSpecialChar(in.prmt);
    if(in.prmt.empty()) std::cout<<BOLD<<RED<<"Please, add a paramter\n"<<RESET;
    else ffinder(file,in.dir,in.extension,in.hidden);
    return 0;
}
