#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct node{ // 一个完整的训练数据，包括分类和特征向量
    string result;
    double data[20];
}train[71];    //训练数据
node test[31]; //测试数据
/*
见鬼，用vector就内存不够了
terminate called after throwing an instance of 'std::bad_alloc'
  what():  std::bad_alloc
还是数组吧，数据量不大
 */

int K = 6;

struct distances{    //对训练集求欧式距离
    string result;
    double dis;
};

int n = 0;
double c = 0.0;
bool cmp(distances &a, distances &b){   //降序排列
    return a.dis<b.dis;
}

int read_train(){
    ifstream infile;
    int i = 0;
    int id;
    infile.open("train_data.txt",ios::in);//打开文件，文件目录可以是.cpp文件所在目录，也可以是指定的绝对路径
    if(!infile)                       //打开失败
    {
        cout<<"open failed"<<endl;
        exit(1);
    }
    while(!infile.eof())
    {
        infile>>id>>train[i].result>>train[i].data[0]>>train[i].data[1]>>train[i].data[2]>>train[i].data[3]>>train[i].data[4]>>train[i].data[5]>>train[i].data[6]>>train[i].data[7];//文件流输入结构体中
        i++;
    }
}

int read_test(){
    ifstream infile;
    int i = 0;
    int id;
    infile.open("test_data.txt",ios::in);//打开文件，文件目录可以是.cpp文件所在目录，也可以是指定的绝对路径
    if(!infile)                       //打开失败
    {
        cout<<"open failed"<<endl;
        exit(1);
    }
    while(!infile.eof())
    {
        infile>>id>>test[i].result>>test[i].data[0]>>test[i].data[1]>>test[i].data[2]>>test[i].data[3]>>test[i].data[4]>>test[i].data[5]>>test[i].data[6]>>test[i].data[7];//文件流输入结构体中
        i++;
    }
}

double get_distance(double x[], double y[]){ // x:测试数据，y:训练数据，获取一个测试数据的欧式距离
    double sum = 0.0;
    for(int i=0;i<8;i++){
        sum += (y[i]-x[i])*(y[i]-x[i]);
    }
    return sqrt(sum);
}

string knn(distances predeict[]){
    //取前K个
    double results[2];
    results[0] = 0.0;
    results[1] = 0.0;

    double sum=0;
    for(int i=0;i<K;i++){
        sum+=predeict[i].dis;
    }
    for(int i=0;i<K;i++){
        if(predeict[i].result == "B"){
            results[0] += (1-predeict[i].dis/sum);
        }
        else
        {
            results[1]+= (1-predeict[i].dis/sum);
        }
    }

    if(results[0]>results[1]){
        return "B";
    }
    else
    {
        return "M";
    }

}

int main(){
    read_train();
    read_test();
    vector<distances>::iterator it;
    for(int z=1;z<=70;z++){
            K = z;
    for(int i=0;i<30;i++){
        distances predeict[70];
        for(int j=0;j<70;j++){ // 每一个测试数据求对于所有的训练数据的欧式距离
            predeict[j].dis = get_distance(test[i].data, train[j].data);
            predeict[j].result = train[j].result;
        }
        sort(predeict, predeict+70, cmp);
        string pt;
        pt = knn(predeict);
        if(pt[0] == test[i].result[0])
            c++;
    }
    cout<<"K = "<<K<<"  KNN Accuracy Percent:"<<c/30.0<<endl;
    c = 0;
    }
    return 0;
}
