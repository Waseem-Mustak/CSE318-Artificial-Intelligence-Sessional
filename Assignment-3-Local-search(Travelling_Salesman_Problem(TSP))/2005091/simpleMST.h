

struct DSU{
    vector<int>siz,rnk,parent,degree;
    vector<vector<int>>graph;
    DSU(int totalCity)
    {
        siz.resize(totalCity+3,0);
        rnk.resize(totalCity+3,0);
        parent.resize(totalCity+3,0);
        degree.resize(totalCity+3,0);
        graph.resize(totalCity+3);
        for(int i=1;i<=totalCity;i++)
        {
            graph[i].clear();
            make(i);
        }
    }

    void make(int n) {// create node
        parent[n]=n;rnk[n]=1;
        siz[n]=1;
    }

    int find(int n) {     // return the supreme parent of n
        if(parent[n]==n)return n;
        else return parent[n]=find(parent[n]);
    }
    int checkValid(int i,int j){
        int ans=-1;
        if(find(i)==find(j))ans=0;
        if(degree[i]>1 || degree[j]>1)ans=0;
        if(ans==-1)ans= 1;

        // if(i==1 && j==2)
        // {
        //     cout<<find(i)<<"    ...   "<<find(j)<<endl;
        //     // cout<<ans<<endl;
        // }
        return ans;
    }
    void Union(int a,int b){ 
        if(checkValid(a,b)==0)return;
        degree[a]++;
        degree[b]++;
        graph[a].push_back(b);
        graph[b].push_back(a);

        a=find(a);
        b=find(b);
        if(siz[a]<siz[b])
        {
            swap(a,b);
        }
        parent[b]=a;
        siz[a]+=siz[b];
        // a=find(a);
        // b=find(b);
        // if(a!=b)   // union by rank
        // {
        //   if(rnk[a]<rnk[b])
        //   {
        //       swap(a,b);
        //   }
        //   parent[b]=a;
        //   if(rnk[a]==rnk[b])
        //   {
        //       rnk[a]++;
        //   }
        // }

        // if(a!=b)   // union by size
        // {
            
        // }
    }

    void dfs(int u,int parent,vector<int>&path)
    {
        path.push_back(u);
        for(auto v:graph[u])
        {
            if(v!=parent)
            {
                dfs(v,u,path);
            }
        }
    }

    int getdegree(int i){return degree[i];}
};

vector<int>simpleMinimumSpanningTreeBasedHeuristic()
{
    vector<pair<lld,pair<int,int>>>allEadges;
    for(int i=1;i<=totalNumberOfCity;i++)
    {
        for(int j=i+1;j<=totalNumberOfCity;j++)
        {
            allEadges.push_back({distanceOfTwoCity(i,j),{i,j}});
        }
    }
    sort(allEadges.begin(),allEadges.end());
    DSU dsu(allEadges.size());

    for(auto va:allEadges)
    {
        // cout<<va.second.first<<" "<<va.second.second<<endl;
        dsu.Union(va.second.first,va.second.second);
    }

    int leafNode;
    for(int i=1;i<=totalNumberOfCity;i++)
    {
        if(dsu.getdegree(i)==1)leafNode=i;
    }
    vector<int>path;
    dsu.dfs(leafNode,0,path);
    return path;
}