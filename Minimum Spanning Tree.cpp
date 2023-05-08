/*7 11
5 0 3
0 1 5
1 2 10
2 3 5
3 4 7
4 5 6
1 4 1
1 6 4
2 6 8
3 6 9
4 6 2*/
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    int vertexnum,edgenum,weight;
    cin>>vertexnum>>edgenum;
    char a,b;
    vector<vector <int>> graph;
    graph.push_back(vector<int>());
    graph[0].push_back(0);
    for(int i=0;i<edgenum;i++){
        cin>>a>>b>>weight;
        int TF1=0,TF2=0;
        int aloc=1,bloc=1;
        for(int j=1;j<graph[0].size();j++){
            if(graph[0][j]==(int)a){
                aloc=j;
                TF1=1;
            }
            if(graph[0][j]==(int)b){
                bloc=j;
                TF2=1;
            }
            if(TF1==1&&TF2==1){
                goto out;
            }
        }
        out:;
        if(TF1==0){
            graph.push_back(vector<int>());
            graph[graph.size()-1].push_back((int)a);
            graph[0].push_back((int)a);
            for(int j=1;j<graph[0].size();j++){
                graph[graph.size()-1].push_back(0);
            }
            for(int j=1;j<graph.size()-1;j++){
                graph[j].push_back(0);
            }
            while(graph[aloc][0]!=(int)a){
                aloc++;
            }
        }
        if(TF2==0){
            graph.push_back(vector<int>());
            graph[graph.size()-1].push_back((int)b);
            graph[0].push_back((int)b);
            for(int j=1;j<graph[0].size();j++){
                graph[graph.size()-1].push_back(0);
            }
            for(int j=1;j<graph.size()-1;j++){
                graph[j].push_back(0);
            }
            while(graph[bloc][0]!=(int)b){
                bloc++;
            }
        }
        graph[aloc][bloc]=weight;
        graph[bloc][aloc]=weight;
    }
    int min=graph[1][0],loc=1;
    for(int i=2;i<graph.size();i++){
        if(graph[i][0]<min){
            min=graph[i][0];
            loc=i;
        }
    }
    for(int i=0;i<graph.size();i++){
        int tmp=graph[loc][i];
        graph[loc][i]=graph[1][i];
        graph[1][i]=tmp;
    }
    for(int i=0;i<graph.size();i++){
        int tmp=graph[i][loc];
        graph[i][loc]=graph[i][1];
        graph[i][1]=tmp;
    }
    vector<int> pre;
    vector<int> key;
    vector<int> vis;
    for(int i=1;i<graph.size();i++){
        pre.push_back(-1);
        key.push_back(9999);
    }
    vis.push_back(1);
    key[0]=0;
    while(vis.size()<graph.size()-1){
        for(int i=0;i<vis.size();i++){
            for(int j=0;j<graph.size()-1;j++){
                int TF=0;
                for(int k=0;k<vis.size();k++){
                    if(j+1==vis[k]){
                        TF=1;
                        break;
                    }
                }
                if(graph[vis[i]][j+1]<=key[j]&&graph[vis[i]][j+1]!=0&&TF==0){
                    key[j]=graph[vis[i]][j+1];
                    pre[j]=graph[vis[i]][0];
                }
            }
        }
        int minkey=99999,lockey=0;
        for(int i=0;i<key.size();i++){
            int TF=0;
            for(int j=0;j<vis.size();j++){
                if(i+1==vis[j]){
                    TF=1;
                    break;
                }
            }
            if(TF==0&&key[i]<minkey){
                minkey=key[i];
                lockey=i;
            }
        }
        vis.push_back(lockey+1);
    }
    int weightsum=0;
    vector<int> weightall;
    vector<int> ver0;
    vector<int> ver1;
    for(int i=1;i<pre.size();i++){
        int j=1;
        while(graph[0][j]!=pre[i]){
            j++;
        }
        weightsum+=graph[i+1][j];
        weightall.push_back(graph[i+1][j]);
        if(graph[i+1][0]<graph[0][j]){
            ver0.push_back(graph[i+1][0]);
            ver1.push_back(graph[0][j]);
        }
        else{
            ver0.push_back(graph[0][j]);
            ver1.push_back(graph[i+1][0]);
        }
    }
    for(int i=0;i<weightall.size();i++){
        for(int j=i+1;j<weightall.size();j++){
            if(weightall[i]>weightall[j]){
                int tmp=weightall[i];
                weightall[i]=weightall[j];
                weightall[j]=tmp;
                tmp=ver0[i];
                ver0[i]=ver0[j];
                ver0[j]=tmp;
                tmp=ver1[i];
                ver1[i]=ver1[j];
                ver1[j]=tmp;
            }
            if(weightall[i]==weightall[j]){
                if(ver0[i]>ver0[j]){
                    int tmp=ver0[i];
                    ver0[i]=ver0[j];
                    ver0[j]=tmp;
                    tmp=ver1[i];
                    ver1[i]=ver1[j];
                    ver1[j]=tmp;
                }
                else if(ver0[i]==ver0[j]&&ver1[i]>ver1[j]){
                    int tmp=ver0[i];
                    ver0[i]=ver0[j];
                    ver0[j]=tmp;
                    tmp=ver1[i];
                    ver1[i]=ver1[j];
                    ver1[j]=tmp;
                }
            }
        }
    }
    cout<<weightsum<<endl;
    for(int i=0;i<weightall.size();i++){
        cout<<(char)ver0[i]<<" "<<(char)ver1[i]<<" "<<weightall[i];
        if(i!=weightall.size()-1){
            cout<<endl;
        }
    }
    return 0;
}
