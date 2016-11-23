#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <io.h>
#include <cstring>
using namespace std;

const int rows = 2500;
const int cols = 2500;
double a[rows][cols];
double b[rows][cols];
int c[cols];

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
    string str;
    fstream fin4, fin5, fout, fout1;
    int m1=241, n=1400, m2=1176, t;

    fin4.open( "data_mal.txt", fstream::in );
//    freopen("out.txt","w", stdout);
    for(int i=0; i<m1; i++)
        for(int j=0; j<n; j++)
            fin4>>a[i][j];

    fin4.close();
    fin4.clear();

    fin5.open( "data_detect.txt", fstream::in );
    for(int i=0; i<m2; i++)
        for(int j=0; j<n; j++)
            fin5 >> b[i][j];
    fin5.close();
    fin5.clear();
    //遍历对应下标
    int flag,cnt ;
    for(int i=0; i<m1; i++) c[i] = 99999999;
    for(int i=0; i<m1; i++){
        flag = 0;
        for(int j=0; j<m2; j++){
            t = j;
            cnt = 0;
            for(int k=0; k<n; k++){
                if(fabs(a[i][k]-a[j][k]) < 1.0e-5) cnt++;
            }
            if(cnt == n) {flag = 1;break;}
        }
        if(flag) c[i] = t;
       // cout << c[i] <<endl;
    }

    string sstr, s1, s2;
    string filePath = "G:\\malicious";
    vector<string> files;
    getFiles(filePath, files);
//找到对应的文件名

    fstream fin3;
    fin3.open( "malicious.txt", fstream::in );
    fout1.open("cert.txt", fstream::out);
    int k=0;
    string ss[rows];
    while(getline(fin3,sstr)) ss[k++] = sstr;
    for(int i=0; i<m1; i++)
    {
        string str = files[ c[i] ] ;
//        fout1<<str<<endl;
        //找到对应文件的签名信息
        for(int l = 0; l<k; l++)
        {
            s1 = "";
            int len = ss[l].size();
            for(int j = 0 ; j < len; j++)
            {
                t = j;
                if(ss[l][j] == ' ')  break;
                s1 += ss[l][j];
            }
            s2 = ss[l].substr(t+1, len-t-1);
            //cout<<str<<" "<<s2<<endl;
           /* for(int j=0; j<str.size(); j++)
                if(str[j]>='a' && str[j]<='z') str[j]-=32;
            for(int j=0; j<s1.size(); j++)
                if(s1[j]>='a' && s1[j]<='z') s1[j]-=32;*/
            if(str.find(s1) != string::npos) fout1 << s1<<" "<< s2 <<endl;
        }
    }
    fin3.close();
    fin3.clear();
    fout1.close();

//用恶意软件的签名筛选待检测APK的签名信息，达到预处理

    fstream fin, fin1, fin2;
    fout.open("out.txt", fstream::out);

    string md[cols], beni[cols], mal[cols];
//    string s1, s2;
    int a = 0, b = 0, c = 0;

    fin.open( "cert.txt", fstream::in );
    while(getline(fin,str)){
        md[a++] = str;
        //cout<<str<<endl;
    }
    fin.close();
    fin.clear();

    fin1.open( "benign.txt", fstream::in );
    while(getline(fin1,str)){
        beni[b++] = str;
        //cout<<str<<endl;
    }
    fin1.close();
    fin1.clear();

    fin2.open( "malicious.txt", fstream::in );
    while(getline(fin2,str)){
        mal[c++] = str;
        //cout<<str<<endl;
    }
    fin2.close();
    fin2.clear();


    for(int i=0; i<a; i++){

        for(int k=0; k<b; k++){
            /*int len = beni[k].size();
            s1 = "";
            for(int j = 0 ; j < len; j++){
                t = j;
                if(beni[k][j] == ' ') break;
                s1 += beni[k][j];
            }
            s2 = beni[k].substr(t+1, len-t-1);*/
            if(beni[k] == md[i]) {
                fout << s1 <<" " << s2<<endl;
            }
        }

        for(int k=0; k<c; k++){
           /* s1="";
            int len = mal[k].size();
            for(int j = 0 ; j < len; j++){
                t = j;
                if(mal[k][j] == ' ') break;
                s1 += mal[k][j];
            }
            s2 = mal[k].substr(t+1, len-t-1);*/
            if(mal[k] == md[i]) {
                fout << s1 <<" " << s2<<endl;
            }
        }
    }

    fout.close();
    fout.clear();

    return 0;
}
