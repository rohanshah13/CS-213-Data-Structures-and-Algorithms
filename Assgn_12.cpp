#include<bits/stdc++.h>

using namespace std;
struct path{
	int v2;
	int length;
	path(int v,int l){
		v2=v;
		length=l;
	}
};

int num_visited=0;
int num_finished=0;
int longest_path=0;

void DFS(int root, vector<set<int>>& adjacency_dead, vector<int>& dfs_no, vector<int>& dfs_finish_no, vector<bool>& visited, vector<int>& parent, vector<int>& dfs_finish_inv){
	visited[root]=true;
	dfs_no[root]=num_visited;
	num_visited++;
	for(auto it = adjacency_dead[root].begin();it!=adjacency_dead[root].end();it++){
		if(!visited[*it]){
			parent[*it]=root;
			DFS(*it, adjacency_dead, dfs_no, dfs_finish_no, visited, parent, dfs_finish_inv);
		}		
	}
	dfs_finish_no[root]=num_finished;
	dfs_finish_inv[num_finished]=root;
	num_finished++;
	//cout<<root<<" "<<num_finished<<endl;
}

void DFS_SCC(int root, vector<set<int>>& reverse_dead, vector<bool>& visited_scc, vector<int>& parent_scc, int& ctr, vector<int>& scc_no, vector<path>& height, vector<path>& height2){
	visited_scc[root]=true;
	scc_no[root]=ctr;
	for(auto it = reverse_dead[root].begin();it!=reverse_dead[root].end();it++){
		if(!visited_scc[*it]){
			parent_scc[*it]=root;
			DFS_SCC(*it, reverse_dead, visited_scc, parent_scc, ctr, scc_no,height, height2);
			/*if(1+height[*it].length>height[root].length){
				height2[root]=height[root];
				height[root]=path(*it,height[*it].length+1);
			}*/
		}
		
	}
}

void DFS_HEIGHT(int root, vector<set<int>>& adjacency_dead,vector<bool>& visited_height, vector<int>& scc_no, vector<path>& height, vector<path>& height2, vector<path>& path1, vector<path>& path2){
	visited_height[root]=true;
	for(auto it = adjacency_dead[root].begin();it!=adjacency_dead[root].end();it++){
		//cout<<"F"<<root<<" "<<*it<<height[root].length<<endl;

		if(!visited_height[*it]){
			DFS_HEIGHT(*it, adjacency_dead, visited_height, scc_no, height, height2, path1, path2);
			if(height[*it].length+1>height[root].length){
				height2[root]=height[root];
				height[root]=path(*it,height[*it].length+1);
			}
			else if(height[*it].length+1>height2[root].length){
				height2[root]=path(*it,height[*it].length+1);
			}
		}
		if(scc_no[*it]!=scc_no[root]){
			if(path1[*it].length+1>height[root].length){
				height2[root]=height[root];
				height[root]=path(*it,path1[*it].length+1);
			}
			else if(path1[*it].length+1>height2[root].length){
				height2[root]=path(*it,path1[*it].length+1);
			}
		}
	}
}

void DFS_PATH(int root, vector<set<int>>& adjacency_dead, vector<bool>& visited_path, vector<int>& parent_scc, vector<int>& scc_no, vector<path>& height, vector<path>& height2, vector<path>& path1, vector<path>& path2){
	visited_path[root]=true;
	if(parent_scc[root]==-1){
		path1[root] = height[root];
		path2[root] = height2[root];
		//cout<<"F";
	}
	else{

		path1[root] = height[root];
		path2[root] = height2[root];
		int dad = parent_scc[root];
		//cout<<dad<<endl;
		//cout<<path1[dad].v2<<endl;
		//cout<<path2[dad].v2<<endl;
		if(path1[dad].v2!=root){
			if(1+path1[dad].length>path1[root].length){
				path2[root]=path1[root];
				path1[root]=path(dad,path1[dad].length+1);
				
			}
			else if(1+path1[dad].length>path2[root].length){
				path2[root]=path(dad,path1[dad].length+1);
			}
		}
		else if(path2[dad].v2!=root){
			if(1+path2[dad].length>path1[root].length){
				path2[root]=path1[root];
				path1[root]=path(dad,path2[dad].length+1);
				
			}
			else if(1+path2[dad].length>path2[root].length){
				path2[root]=path(dad,path2[dad].length+1);
			}
		}
	}
	for(auto it = adjacency_dead[root].begin();it!=adjacency_dead[root].end();it++){
		if(!visited_path[*it]){
			//cout<<path1[v2]+" "
			DFS_PATH(*it, adjacency_dead, visited_path, parent_scc, scc_no, height, height2, path1, path2);

		}
		/*else if(scc_no[root]!=scc_no[*it]){
			if(1+path1[*it].length>path1[root].length){
				path2[root]=path1[root];
				path1[root]=path(*it,path1[*it].length+1);
				
			}
			else if(1+path1[*it].length>path2[root].length){
				path2[root]=path(*it,path1[*it].length+1);
			}
			if(1+path2[*it].length>path1[root].length){
				path2[root]=path1[root];
				path1[root]=path(*it,path2[*it].length+1);
				
			}
			else if(1+path2[*it].length>path2[root].length){
				path2[root]=path(*it,path2[*it].length+1);
			}
		}*/		
	}
	if(path1[root].length>longest_path){
		longest_path=path1[root].length;
	}
	
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int n,m;
	int dead=0;
	cin>>n;
	cin>>m;
	vector<set<int>> adjacency(n);
	vector<set<int>> reverse(n);
	vector<set<int>> adjacency_dead(n);
	vector<set<int>> reverse_dead(n);
	vector<int> dfs_no(n);
	vector<int> dfs_finish_no(n);
	vector<int> dfs_finish_inv(n);
	vector<path> height(n,path(-1,0));
	vector<path> height2(n,path(-1,0));
	vector<bool> pushed(n,false);
	vector<path> path1(n,path(-1,0));
	vector<path> path2(n,path(-1,0));
	vector<int> scc_no(n);
	vector<int> parent(n,-1);
	vector<bool> visited(n,false);
	vector<bool> visited_path(n,false);
	vector<bool> visited_height(n,false);
	queue<int> remove;
	for(int i=0;i<m;i++){
		int temp1,temp2;
		cin>>temp1;
		cin>>temp2;
		adjacency[temp1].insert(temp2);
		reverse[temp2].insert(temp1);
	}
	for(int i=0;i<n;i++){
		if(adjacency[i].size()<=1){
			remove.push(i);
			pushed[i]=true;
		}
	}
	
	while(!remove.empty()){
		int x = remove.front();
		//cout<<x<<endl;
		if(adjacency[x].size()==1){
			pushed[x]=false;
			int suc =*adjacency[x].begin();
			if(adjacency[suc].find(x)!=adjacency[suc].end()){
				adjacency[suc].erase(x);
				adjacency_dead[suc].insert(x);
				reverse[x].erase(suc);
				reverse_dead[x].insert(suc);
				dead++;
				if(adjacency[suc].size()<=1&&pushed[suc]==false){
					remove.push(suc);
					pushed[suc]=true;
				}
			}
		}
		else{
			auto it = reverse[x].begin();
			while(it!=reverse[x].end()){
				int val = *it;
				it++;
				reverse[x].erase(val);
				adjacency[val].erase(x);
				adjacency_dead[val].insert(x);
				reverse_dead[x].insert(val);
				//cout<<val<<endl;
				dead++;
				if(adjacency[val].size()<=1&&!pushed[val]){
					//cout<<val<<endl;
					remove.push(val);
					pushed[val]=true;
				}
				//cout<<reverse[x].size()<<endl;
				//cout<<val<<endl;
			}
		}
		remove.pop();
	}
	//cout<<dead<<endl;
	for(int i=0;i<n;i++){
		if(!visited[i]){
			DFS(i, adjacency_dead, dfs_no, dfs_finish_no, visited, parent, dfs_finish_inv);
		}
	}
	vector<bool> visited_scc(n,false);
	vector<int> parent_scc(n,-1);
	int ctr=0;
	for(int i = n-1;i>=0;i--){
		//cout<<dfs_finish_inv[i]<<endl;
		if(!visited_scc[dfs_finish_inv[i]]){
			DFS_SCC(dfs_finish_inv[i], reverse_dead, visited_scc, parent_scc, ctr, scc_no, height, height2);
			ctr++;
		}
	}
	vector<int> scc_vertex(ctr);
	
	for(int i=0;i<n;i++){
		if(parent_scc[i]==-1){
			scc_vertex[scc_no[i]]=i;
		}
	}
	for(int i=0;i<ctr;i++){
		//cout<<scc_vertex[i]<<endl;
	}
	for(int i=ctr-1;i>=0;i--){
		if(!visited_path[scc_vertex[i]]){
			//DFS_HEIGHT()
			DFS_HEIGHT(scc_vertex[i], adjacency_dead, visited_height, scc_no, height, height2, path1, path2);
			DFS_PATH(scc_vertex[i], adjacency_dead, visited_path, parent_scc, scc_no, height, height2, path1, path2);
		}
	}
	for(int i=0;i<n;i++){
		//cout<<path1[i].length<<" "<<i<<endl;
	}
	cout<<dead<<" "<<max(longest_path-1,0);

}