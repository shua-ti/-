#include <iostream>
using namespace std;
#define MAX  100000
#define VNUM  7                                             

int edge[VNUM][VNUM]={{100,7,100,5,100,100,100},{7,100,8,9,7,100,100},{100,8,100,100,5,100,100},{5,9,100,100,15,6,100},{100,7,5,15,100,8,9},{100,100,100,6,8,100,11},{100,100,100,100,9,11,100}};
int lowcost[VNUM]={0};                                         //记录V中各点到Vnew的最短距离
int addvnew[VNUM];                                             //标记某点是否加入Vnew                               
void prim(int start);

int main(){
	for(int i = 0; i < VNUM;i++)
	      prim(i+1);
	return 0;
}

void prim(int start)
{
     int sumweight=0;
     int i,j,k=0;

	 //初始化
     for(i=0;i<VNUM;i++)                                      //lowcost数组初始化为到起始节点的距离
     {
        lowcost[i]=edge[start-1][i];
        addvnew[i]=-1;                                         //选定节点集V{}初始化为空
     }

     addvnew[start-1]=0;                                        //将起始点start加入V{}
     //cout << "初始化节点集:" << start << endl;  
                                                 
     for(i=0;i<VNUM-1;i++)                                        
     {
        int min=MAX;
        int v=-1;
        for(j=0;j<VNUM;j++)                                      
        {
            if(addvnew[j]==-1&&lowcost[j]<min)                 //在Vnew之外寻找最短路径
            {
                min=lowcost[j];
                v=j;
            }
        }
        if(v!=-1)
        {
            addvnew[v]=0;                                      //将v加入V{}
			//cout << "新加入的节点" << v+1 ; 
	        //cout << "   距离：" << min << endl;
            sumweight+=lowcost[v];                             //计算路径长度之和
			
           //局部更新lowcost数组
            for(j=0;j<VNUM;j++)
            {
                if(addvnew[j]==-1&&edge[v][j]<lowcost[j])      //仅和刚刚加入的节点v有关
                {
                    lowcost[j]=edge[v][j];                     //此时v点加入Vnew 需要更新lowcost                           
                }
            }
        }
    }
    cout << "最小生成树的权值： " << sumweight << endl;
}