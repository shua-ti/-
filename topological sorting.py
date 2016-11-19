#coding=utf-8
#/usr/bin/env python
"拓扑 排序测试"
N ={
    'a':set('bf'),
    'b':set('cdf'),
    'c':set('d'),
    'd':set('fe'),
    'e':set('f'),
    'f':set()
}
def topsort(G):
    count = dict((u,0) for u in G)
    for u in G:
        for v in G[u]:
            count[v] += 1             #统计每个节点的入度
    Q = [u for u in G if count[u]==0]
    S =[]
    while Q:
        u = Q.pop()
        S.append(u)      #将入度为0的点加入拓扑序列中
        for v in G[u]:
            count[v] -= 1   #更新每个节点的入度和栈Q
            if count[v]==0:
                Q.append(v)
    return S

if __name__ == '__main__':
    print topsort(N)