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

void getFiles( string path, vector<string>& file )
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
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), file );
            }
            else
            {
                file.push_back(p.assign(path).append("\\").append(fileinfo.name) );
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
    int m1=471, n=1400, m2 =2353, t;

    fin4.open( "testSet2.txt", fstream::in );
    freopen("out.txt","w", stdout);
    for(int i=0; i<m1; i++)
        for(int j=0; j<n; j++)
            fin4>>a[i][j];

    fin4.close();
    fin4.clear();

    fin5.open( "data.txt", fstream::in );
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
        for(int j=0; j< m2; j++){
            t = j;
            cnt = 0;
            for(int k=0; k<n; k++){
                if(fabs(a[i][k]-b[j][k]) < 0.000001 ) cnt++;
            }
            if(cnt == n) {flag = 1;break;}
        }
        if(flag) c[i] = t;
  //      cout << c[i] <<endl;
    }

    string sstr, s1, s2;
    string filePath = "G:\\Experiment\\testSet2";
    vector<string> file;
    getFiles(filePath, file);
    vector<string> ::iterator it;
    vector<string> files;
    files.clear();

    for(it = file.begin(); it!=file.end(); it++){
        if((*it).find(".RSA") != string::npos) files.push_back(*it);
    }

//找到对应的文件名

    fstream fin3, fin6;
    fin3.open( "malicious.txt", fstream::in );

    int k=0;
    string ss[rows];
    while(getline(fin3,sstr)) ss[k++] = sstr;
    fin3.close();
    fin3.clear();

    fin6.open( "benign.txt", fstream::in );
    while(getline(fin6,sstr)) ss[k++] = sstr;
    fin6.close();
    fin6.clear();

    fout1.open("cert2.txt", fstream::out);

    while(getline(fin3,sstr)) ss[k++] = sstr;
    for(int i=0; i<m1; i++)
    {
        string str = files[ c[i] ] ;
        fout1<<str<<endl;
        //找到对应文件的签名信息
    }

    fout1.close();

//用恶意软件的签名筛选待检测APK的签名信息，达到预处理
//让sert2的签名去匹配sert信息，找到sert2的位置，并更新testSet2的值
//增加其权重*5,提高检测率。
    fstream fin, fin1, fin2;
    fout.open("new_testSet.txt", fstream::out);

    string cert[cols], cert2[cols], mal[cols];
//    string s1, s2;
    int c = 0, d = 0;

    fin.open( "cert.txt", fstream::in );
    while(getline(fin,str)){
        cert[c++] = str;
        //cout<<str<<endl;
    }
    fin.close();
    fin.clear();

    fin1.open( "cert2.txt", fstream::in );
    while(getline(fin1,str)){
        cert2[d++] = str;
        //cout<<str<<endl;
    }
    fin1.close();
    fin1.clear();

    int m=0;
    bool flags[m1+1];
    memset(flags,false, sizeof(flags));
    for(int i=0; i<d; i++){
        m= 0;
        for(int j=0; j<c; j++){
            s1="";
            int len = cert[j].size();
            for(int k= 0 ; k < len; k++){
                t = k;
                if(cert[j][k] == ' ') break;
                s1 += cert[j][k];
            }
            s2 = cert[j].substr(t+1, len-t-1);
            if(cert2[i].find(s1) != string::npos) {m = i;  cout<<m<<endl; break; }
        }
        if(m) flags[m] = true;
    }


    for(int i=0; i<m1; i++){
        for(int j=0; j<n; j++){
            if(flags[i] && j!=n-1) a[i][j] = a[i][j]*10.0;
            if(j==n-1) fout<<a[i][j]<<endl;
            else fout<<a[i][j]<<" ";
        }
    }
    fout.close();
    fout.clear();

    return 0;
}
