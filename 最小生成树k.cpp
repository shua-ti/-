#include <iostream>
using namespace std;
#define VertexNum 7
#define EdgeNum 11
#define INFINITY 100
typedef struct          
{        
	char vertex[VertexNum];                                //顶点表         
	int edges[VertexNum][VertexNum];                       //邻接矩阵,可看做边表         
	int numVertexes,numEdges;                                               //图中当前的顶点数和边数         
}MGraph; 

typedef struct node  
{  
	int u;                                                 //边的起始顶点   
	int v;                                                 //边的终止顶点   
	int w;                                                 //边的权值   
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

	for (i = 0; i < g->numVertexes; i++)/* 初始化图 */
	{
		g->vertex[i]=i;
	}

	for (i = 0; i < g->numVertexes; i++)/* 初始化图 */
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
	int vset[VertexNum];                                    //辅助数组，判定两个顶点是否连通   
	Edge E[EdgeNum];                                         //存放所有的边   
	k=0;                                                    //E数组的下标从0开始   
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
	sort(E,k);                            //堆排序，按权值从小到大排列       
	for (i=0;i<G.numVertexes;i++)                                    //初始化辅助数组   
	{  
		vset[i]=i;  
	}   
	k=1;                                                   //生成的边数，最后要刚好为总边数   
	j=0;                                                   //E中的下标   
	while (k<G.numEdges)  
	{   
		sn1=vset[E[j].u];  
		sn2=vset[E[j].v];                                  //得到两顶点属于的集合编号   
  		if (sn1!=sn2)                                      //不在同一集合编号内的话，把边加入最小生成树   
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