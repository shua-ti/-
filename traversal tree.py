#coding=utf-8
#/usr/bin/env python
"图遍历算法测试"
from collections import deque
N ={
    'a':set('bcdef'),
    'b':set('ce'),
    'c':set('d'),
    'd':set('e'),
    'e':set('f'),
    'f':set('cgh'),
    'g':set('fh'),
    'h':set('fg')
}
def walk(G,s):              #单一连通分量
    P,Q = dict(),set()      #初始化数据结构
    P[s]=None               #P保存当前节点的父节点
    Q.add(s)                #保存已发现节点
    while Q:
        u = Q.pop()
        for v in G[u].difference(P):#从当前节点出发，所遇邻居节点中未未发现的节点加入Q
            Q.add(v)
            P[v] = u
    return  P

def iter_dfs(G,s):
    S,Q = set(),[]
    Q.append(s)
    while Q:                #Q栈结构，保存当前节点的所有邻居节点
        u = Q.pop()
        if u in S: continue  #等效于对访问过的节点做标记，不再重复访问
        S.add(u)              #保存已经访问过的节点
        Q.extend(G[u])
    return S

def rec_dfs(G,s,S = None):
    if S==None: S = set()
    S.add(s)
    print s,
    for u in G[s]:
        if u in S: continue
        rec_dfs(G,u,S)

#带有时间戳的dfs算法
#S保存已访问过的节点
#对当前节点的所有未访问邻居节点递归调用dfs()
def dfs(G,s,d,f,S=None,t=0):
    if S==None: S = set()
    d[s] = t ; t += 1 #首次访问该节点
    S.add(s)
    for u in G[s]:
        if u in S: continue
        t = dfs(G,u,d,f,S,t)
    f[s]=t;t+=1     #所有邻居节点访问结束
    return t

#深度受限的dfs
def iddfs(G,s):
    yielded = set()
    def recurse(G,s,d,S=None):
        if S==None:S = set()
        if d==0: return #递归深度控制
        if s not in yielded:
            yield s
            yielded.add(s)
        S.add(s)
        for u in G[s]:
            if u in S:continue
            for v in recurse(G,u,d-1,S):
                yield v  #返回yield s 类似于 return recurse()
    n= len(G)
    for d in range(n):    #可能的最大递归深度len(G)-1
        if len(yielded) == n:break #所有节点都访问完成
        for u in recurse(G,s,d): #返回yielded添加元素的顺序
            yield u


def dfs_topsort(G):
    S,res = set(),[]
    def recurse(u):
        if u in S: return #函数嵌套 S是外层函数中定义的
        S.add(u)
        for v in G[u]:
            recurse(v)
        res.append(u) #记录访问结束的点
    for u in G:  #每个节点单一连通域
        recurse(u)
    res.reverse()
    return res

def component(G):
    comp,seen = list(),set()
    for u in G:
        if u in seen: continue
        C = walk(G,u),
        seen.update(C)
        comp.append(C)
    return comp

def bfs(G,s):
    P,Q = dict(),deque()
    P[s] = None; Q.append(s)
    while Q:
        u = Q.popleft()
        for v in G[u]:
            if v in P: continue
            P[u] = v
            Q.append(v)
    return P
if __name__ == '__main__':
    print bfs(N,'a')