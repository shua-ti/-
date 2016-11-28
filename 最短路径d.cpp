#include <iostream>
#include <vector>
using namespace std;
#include "stdio.h" 
#include "stdlib.h" 
#include "io.h" 
#include "math.h" 
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDgE 20
#define MAXVEX 20
#define INFINITY 100

typedef int Status;    /* Status是函数的类型,其值是函数结果状态代码，如OK等 */ 


typedef struct
{
	int vexs[MAXVEX];               //邻接矩阵表示图
	int arc[MAXVEX][MAXVEX];        //节点集数组表示 ，边集二维数组表示
	int numVertexes, numEdges;      
}Mgraph;

typedef int Patharc[MAXVEX];            /* 用于存储最短路径下标的数组 */
typedef int ShortPathTable[MAXVEX];        /* 用于存储到各点最短路径的权值和 */


void CreateMgraph(Mgraph *g)
{
	int i, j;

	/* printf("请输入边数和顶点数:"); */
	g->numEdges=16;
	g->numVertexes=9;

	for (i = 0; i < g->numVertexes; i++)/* 初始化图 */
	{
		g->vexs[i]=i;
	}

	for (i = 0; i < g->numVertexes; i++)/* 初始化图 */
	{
		for ( j = 0; j < g->numVertexes; j++)
		{
			if (i==j)
				g->arc[i][j]=0;
			else
				g->arc[i][j] = g->arc[j][i] = INFINITY;
		}
	}

	g->arc[0][1]=1;
	g->arc[0][2]=5; 
	g->arc[1][2]=3; 
	g->arc[1][3]=7; 
	g->arc[1][4]=5; 

	g->arc[2][4]=1; 
	g->arc[2][5]=7; 
	g->arc[3][4]=2; 
	g->arc[3][6]=3; 
	g->arc[4][5]=3;

	g->arc[4][6]=6;
	g->arc[4][7]=9; 
	g->arc[5][7]=5; 
	g->arc[6][7]=2; 
	g->arc[6][8]=7;

	g->arc[7][8]=4;


	for(i = 0; i < g->numVertexes; i++)
	{
		for(j = i; j < g->numVertexes; j++)
		{
			g->arc[j][i] =g->arc[i][j];
		}
	}

}

/* Dijkstra算法，求有向网g的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v] */ 
/* P[v]的值为前驱顶点下标,D[v]表示v0到v的最短路径长度和 */ 
void ShortestPath_Dijkstra(Mgraph g, int v0, Patharc *P, ShortPathTable *D)
{ 
	int v,w,k,min; 
	int final[MAXVEX];                    /* final[w]=1表示求得顶点v0至vw的最短路径 */

	/* 初始化数据 */
	for(v=0; v<g.numVertexes; v++)        
	{ 
		final[v] = 0;                   /* 全部顶点初始化为未知最短路径状态 */
		(*D)[v] = g.arc[v0][v];         /* 最短路径初始化为当前图各边权值 */
		(*P)[v] = 0;                    /* 初始化路径数组P为0 */ 
	}

	(*D)[v0] = 0;                        /* v0至v0路径为0 */ 
	final[v0] = 1;                        /* v0至v0不需要求路径 */ 

	/* 开始主循环，每次求得v0到某个v顶点的最短路径 */ 
	for(v=1; v<g.numVertexes; v++) 
	{
		 /* 寻找当前离v0顶点的最近距离 */ 
		min=INFINITY;                   
		for(w=0; w<g.numVertexes; w++)  
		{ 
			if(!final[w] && (*D)[w]<min) 
			{ 
				k=w; 
				min = (*D)[w];            /* min 表示当前最近顶点k到v0的距离*/ 
			} 
		} 
		final[k] = 1;                    /* 将目前找到的最近的顶点置为1， */
		                                 /* 该顶点到V0的最短距离确定*/
	
		/* 更新当前最短路径及距离 */
		for(w=0; w<g.numVertexes; w++) 
		{
			/* 如果经过v顶点的路径比现在这条路径的长度短的话 */
			if(!final[w] && (min+g.arc[k][w]<(*D)[w])) 
			{ 
				/* 说明找到了更短的路径，修改D[w]和P[w] */
				(*D)[w] = min + g.arc[k][w]; /* 修改当前路径长度 */ 
				(*P)[w]=k; //记录顶点w到V0路径上前驱节点
			} 
		} 
	}
}

int main(void)
{ 
	int i,j,v0;
	Mgraph g; 
	Patharc P; 
	ShortPathTable D; /* 求某点到其余各点的最短路径 */ 
	vector<int> path;
	v0=0;
	path.clear();
	CreateMgraph(&g);
	ShortestPath_Dijkstra(g, v0, &P, &D); 

	for(i=1;i<g.numVertexes;++i) 
	{ 
		printf("v%d - v%d : ",v0,i);
		j=i;
		while(P[j]!=0)
		{
			path.insert(path.begin(),P[j]);
			j=P[j];
		}
		cout << 'v' << v0 ;
		for(int index=0;index < path.size();index++)
			cout <<'-'<<'v'<< path[index];
		cout << '-' << 'v' << i ;
		path.clear();
		printf("\n");
	} 
	printf("\n源点到各顶点的最短路径长度为:\n"); 
	for(i=1;i<g.numVertexes;++i) 
		printf("v%d - v%d : %d \n",g.vexs[0],g.vexs[i],D[i]); 
	return 0;
}