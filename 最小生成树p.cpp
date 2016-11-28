#include <iostream>
using namespace std;
#define MAX  100000
#define VNUM  7                                             

int edge[VNUM][VNUM]={{100,7,100,5,100,100,100},{7,100,8,9,7,100,100},{100,8,100,100,5,100,100},{5,9,100,100,15,6,100},{100,7,5,15,100,8,9},{100,100,100,6,8,100,11},{100,100,100,100,9,11,100}};
int lowcost[VNUM]={0};                                         //��¼V�и��㵽Vnew����̾���
int addvnew[VNUM];                                             //���ĳ���Ƿ����Vnew                               
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

	 //��ʼ��
     for(i=0;i<VNUM;i++)                                      //lowcost�����ʼ��Ϊ����ʼ�ڵ�ľ���
     {
        lowcost[i]=edge[start-1][i];
        addvnew[i]=-1;                                         //ѡ���ڵ㼯V{}��ʼ��Ϊ��
     }

     addvnew[start-1]=0;                                        //����ʼ��start����V{}
     //cout << "��ʼ���ڵ㼯:" << start << endl;  
                                                 
     for(i=0;i<VNUM-1;i++)                                        
     {
        int min=MAX;
        int v=-1;
        for(j=0;j<VNUM;j++)                                      
        {
            if(addvnew[j]==-1&&lowcost[j]<min)                 //��Vnew֮��Ѱ�����·��
            {
                min=lowcost[j];
                v=j;
            }
        }
        if(v!=-1)
        {
            addvnew[v]=0;                                      //��v����V{}
			//cout << "�¼���Ľڵ�" << v+1 ; 
	        //cout << "   ���룺" << min << endl;
            sumweight+=lowcost[v];                             //����·������֮��
			
           //�ֲ�����lowcost����
            for(j=0;j<VNUM;j++)
            {
                if(addvnew[j]==-1&&edge[v][j]<lowcost[j])      //���͸ոռ���Ľڵ�v�й�
                {
                    lowcost[j]=edge[v][j];                     //��ʱv�����Vnew ��Ҫ����lowcost                           
                }
            }
        }
    }
    cout << "��С��������Ȩֵ�� " << sumweight << endl;
}