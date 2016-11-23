#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <sstream>
#include <io.h>
#include <algorithm>
using namespace std;

double a[3000][2000];

int main()
{
    string str;
    freopen("out1.txt","w",stdout);
    ifstream file1;
    file1.open("out.txt");

    vector <string > vec;
    vector <string > v;

    while(getline(file1,str))
    {
        vec.push_back(str);
    }
    int j;
    for(int i=0; i<vec.size(); i++)
    {
        stringstream sin(vec[i]);
        int k;
        j = 0;
        while(sin>>k){
            a[i][j++] = k;
        }
    }

    double weight[3005][2];

    for(int i=0; i<j-1; i++){
        double benign = 0, malic = 0;
        for(int t = 0 ; t<vec.size(); t++){
            if(a[t][j-1]==0) benign += a[t][i];
            else malic += a[t][i];
            //cout<<a[t][i]<<" ";
        }
        weight[i][0] = benign;
        weight[i][1] = malic;
        //printf("%.2f %.2f\n", weight[i][0], weight[i][1]);
    }

    for(int i=0; i<vec.size(); i++){
        for(int k=0; k<j-1; k++){
            int t = max(weight[k][1]-weight[k][0],weight[k][0]-weight[k][1]);
            a[i][k] = a[i][k]*t/(weight[k][1]+weight[k][0]);
            printf("%.2f ",a[i][k]);
        }
        printf("%.2f\n",a[i][j-1]);
    }


    return 0;
}
