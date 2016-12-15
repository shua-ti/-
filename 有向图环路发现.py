#-*-coding=utf-8-*-
#!/usr/bin/env python
"有向图中是否存在环路"

#通过数字标记每个点的状态 未发现0 已发现-1 已访问1
class Solution(object):
    def canFinish(self, numCourses, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: bool
        """
        graph=[[] for _ in range(numCourses)]
        visited=[0 for _ in range(numCourses)]
        for x,y in prerequisites:
            graph[x].append(y)
        def dfs(x):
            if visited[x]==-1:  #构成环路
                return False
            if visited[x]==1:   
                return True
            visited[x]=-1
            for v in graph[x]:
                if not dfs(v): #任意一个节点出现环路
                    return False
            visited[x]=1   #所有的邻居节点安全发现
            return True
        for v in range(numCourses):
            if not dfs(v):
                return False
        return True



