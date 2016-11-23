#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <vector>
#include <io.h>
using namespace std;

void getFiles( string path, vector<string>& files )

{
    //文件句柄
    long   hFile   =   0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            //如果是目录,迭代之
            //如果不是,加入列表
            if((fileinfo.attrib &  _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
            }
            else
            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
            }
        }
        while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
}

int main()
{
    freopen("out.txt","w",stdout);
    ifstream file1;
    file1.open("all.txt");

    string filePath = "G:\\apktool\\11.4\\virus";
    vector<string> files;
//获取该路径下的所有文件
    getFiles(filePath, files);
    int size1 = files.size();

    string filePath2 = "G:\\apktool\\11.4\\benign";
    vector<string> files2;
//获取该路径下的所有文件
    getFiles(filePath2, files2);
    int size2 = files2.size();
//cout<<size1<<" "<<size2<<endl;
    string str, s;

    vector <string > vec;
    vector <string > v;

    while(getline(file1,str))
    {
        vec.push_back(str);
    }
    int num = 1;

//    printf("    ");
//    for(int i=0; i<vec.size(); i++)
//         cout<<" "<<vec[i];
//    cout<<endl;

    for (int i = 0; i < size1; i++)
    {
        v.clear();
        //cout<<files[i].c_str()<<endl;
        string str = files[i].c_str();

        ifstream inFile(files[i].c_str());
        //inFile.open(str);

        while(getline(inFile,s))
        {
            string st;
            if(s.find("uses-permission android")!=string::npos){
                 int t = s.find("\"");
                 st="";
                 for(int i=t+1; i<s.size(); i++){
                     if(s[i] == '\"') break;
                     st += s[i];
                 }
                 //cout<<str;
                 //cout<<s<<"   "<< s.find("\"")<< "  "<< str<<endl;
            }
            v.push_back(st);
        }



       // printf("apk%d",num++);
        for(int i=0; i<vec.size(); i++)
        {
            int t = vec[i].size();
            int flag = 0;
            for(int j=0; j<v.size(); j++){
                if(vec[i] == v[j]){
                    flag = 1;break;
                }
            }
            //for(int k=0; k<t-1; k++) printf(" ");
            printf("%d ",flag);
        }
        printf("0\n");
    }

    for (int i = 0; i < size2; i++)
    {
        v.clear();
        //cout<<files[i].c_str()<<endl;
        string str = files2[i].c_str();

        ifstream inFile2(files2[i].c_str());
        //inFile.open(str);

        while(getline(inFile2,s))
        {
            string st;
            if(s.find("uses-permission android")!=string::npos){
                 int t = s.find("\"");
                 st="";
                 for(int i=t+1; i<s.size(); i++){
                     if(s[i] == '\"') break;
                     st += s[i];
                 }
                 //cout<<str;
                 //cout<<s<<"   "<< s.find("\"")<< "  "<< str<<endl;
            }
            v.push_back(st);
        }



      //  printf("apk%d",num++);
        for(int i=0; i<vec.size(); i++)
        {
            int t = vec[i].size();
            int flag = 0;
            for(int j=0; j<v.size(); j++){
                if(vec[i] == v[j]){
                    flag = 1;break;
                }
            }
            //for(int k=0; k<t-1; k++) printf(" ");
            printf("%d ",flag);
        }
        printf("1\n");
    }

    return 0;
}
