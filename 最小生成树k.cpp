#include <iostream>
using namespace std;
#define VertexNum 7
#define EdgeNum 11
#define INFINITY 100
typedef struct          
{        
	char vertex[VertexNum];                                //�����         
	int edges[VertexNum][VertexNum];                       //�ڽӾ���,�ɿ����߱�         
	int numVertexes,numEdges;                                               //ͼ�е�ǰ�Ķ������ͱ���         
}MGraph; 

typedef struct node  
{  
	int u;                                                 //�ߵ���ʼ����   
	int v;                                                 //�ߵ���ֹ����   
	int w;                                                 //�ߵ�Ȩֵ   
}Edge; 

void sort(Edge * p,int n);
void CreateMgraph(MGraph *g);
void kruskal(MGraph G);
int main(){
	MGraph G;
	CreateMgraph(&G);
	kruskal(G);
	return 0;
}
void sort(Edge * p ,int n){
	bool sorted = false;
	Edge temp;
	for(int i = 1; sorted = !sorted; i++){
		for(int j = 0 ; j < n-i;j++)
		{   
			if(p[j].w > p[j+1].w){
				temp = p[j];p[j] = p[j+1];p[j+1]=temp;
				sorted = false;
			}
		}
  }
}

void CreateMgraph(MGraph *g)
{
	int i, j;
	g->numVertexes=VertexNum;
	g->numEdges=11;

	for (i = 0; i < g->numVertexes; i++)/* ��ʼ��ͼ */
	{
		g->vertex[i]=i;
	}

	for (i = 0; i < g->numVertexes; i++)/* ��ʼ��ͼ */
	{
		for ( j = 0; j < g->numVertexes; j++)
		{
			if (i==j)
				g->edges[i][j]=0;
			else
				g->edges[i][j] = INFINITY;
		}
	}
	g->edges[0][1]=7;g->edges[0][3]=5;g->edges[1][2]=8;g->edges[1][3]=9;g->edges[1][4]=7;
	g->edges[2][4]=5;g->edges[3][4]=15;g->edges[3][5]=6;g->edges[4][5]=8;g->edges[4][6]=9;
	g->edges[5][6]=11;
	for(i = 0; i < g->numVertexes; i++)
	{
		for(j = 0; j < i; j++)
		{
			g->edges[i][j] =g->edges[j][i];
		}
	}

}

void kruskal(MGraph G)  
{  
	int i,j,u1,v1,sn1,sn2,k;  
	int vset[VertexNum];                                    //�������飬�ж����������Ƿ���ͨ   
	Edge E[EdgeNum];                                         //������еı�   
	k=0;                                                    //E������±��0��ʼ   
	for (i=0;i<G.numVertexes;i++)  
	{  
		for (j=0;j<i;j++)  
		{  
			if (G.edges[i][j]!=0 && G.edges[i][j]!=INFINITY)  
			{  
				E[k].u=i;
				E[k].v=j;  
				E[k].w=G.edges[i][j];  
				k++;  
			}  
		}  
	}     
	sort(E,k);                            //�����򣬰�Ȩֵ��С��������       
	for (i=0;i<G.numVertexes;i++)                                    //��ʼ����������   
	{  
		vset[i]=i;  
	}   
	k=1;                                                   //���ɵı��������Ҫ�պ�Ϊ�ܱ���   
	j=0;                                                   //E�е��±�   
	while (k<G.numEdges)  
	{   
		sn1=vset[E[j].u];  
		sn2=vset[E[j].v];                                  //�õ����������ڵļ��ϱ��   
  		if (sn1!=sn2)                                      //����ͬһ���ϱ���ڵĻ����ѱ߼�����С������   
		{
			printf("%c ---> %c, %d\n",E[j].u+65,E[j].v+65,E[j].w);       
			k++;  
			for (i=0;i<G.numVertexes;i++)  
			{  
				if (vset[i]==sn2)  
				{  
					vset[i]=sn1;  
				}  
			}             
		}  
		j++;  
	}  
}