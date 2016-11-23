#include <string>
#include <vector>
#include <string.h>
#include <io.h>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

void getFiles( string path, vector<string>& files )
{
    //�ļ����
    long   hFile   =   0;
    //�ļ���Ϣ
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            //�����Ŀ¼,����֮
            //�������,�����б�
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
    //ofstream ("a.out");
    freopen("all.txt","w",stdout);
    string filePath = "G:\\apktool\\11.4\\all";
    vector<string> files;


    map<string,int> ma;
    map<string,int>::iterator it;
//��ȡ��·���µ������ļ�
    getFiles(filePath, files);

 //   char str[30];
    string s;

    int size = files.size();
    for (int i = 0; i < size; i++)
    {
        //cout<<files[i].c_str()<<endl;
        string str = files[i].c_str();

        ifstream inFile(files[i].c_str());
        //inFile.open(str);

        while(getline(inFile,s))
        {
            if(s.find("uses-permission android")!=string::npos){
                 int t = s.find("\"");
                 string str="";
                 for(int i=t+1; i<s.size(); i++){
                     if(s[i] == '\"') break;
                     str+=s[i];
                 }
                 //cout<<str;
                 //cout<<s<<"   "<< s.find("\"")<< "  "<< str<<endl;
                 ma[str]++;
            }
        }
    }


    for(it = ma.begin(); it != ma.end(); it++){
        cout<<it->first<<endl;
    }

    return 0;
}

