#coding=utf-8
#/usr/bin/env python
'强连通分量scc,有向路径上所有节点彼此到达的最大子图'
G = {
    'a':set('bc'),
    'b':set('d'),
    'c':set('d'),
    'd':set('a')
}
def walk(G,s,S):              #单一连通分量
    P,Q = dict(),set()      #初始化数据结构
    P[s]=None               #P保存当前节点的父节点
    Q.add(s)                #保存已发现节点
    while Q:
        u = Q.pop()
        for v in G[u].difference(P,S):#从当前节点出发，所遇邻居节点中未未发现的节点加入Q
            Q.add(v)
            P[v] = u
    return  P

def dfs_topsort(G):
    S,res = set(),[]
    def recurse(u):
        if u in S: return #函数嵌套--S是外层函数中定义的
        S.add(u)
        for v in G[u]:
            recurse(v)
        res.append(u) #记录访问结束的点
    for u in G:  #每个节点单一连通域
        recurse(u)
    res.reverse()
    return res

#翻转图中所有边线
def tr(G):
    GT = {}
    for u in G:
        GT[u] = set()
    for u in G:
        for v in G[u]:
            GT[v].add(u)
    return GT

def scc(G):
    GT = tr(G)
    sccs,seen = [],set()
    for u in dfs_topsort(G):
        if u in seen: continue
        C = walk(GT,u,seen)
        seen.update(C)
        sccs.append(C)  #C是单个强连通分量
    return sccs
