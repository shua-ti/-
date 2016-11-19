#coding=utf-8
#/usr/bin/env python
"图遍历算法测试"
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

if __name__ == '__main__':
    print rec_dfs(N,'a')