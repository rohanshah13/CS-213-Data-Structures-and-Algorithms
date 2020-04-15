#include<iostream>
#include <bits/stdc++.h>
#include<vector>

using namespace std;
typedef list<string> :: iterator it;

struct node{
	int parent;
	int capacity;
	int cost;
	list<string> latest;
	unordered_map<string,it> cache;
};

int main(){
	int n,m;
	cin>>n;
	cin>>m;
	vector<node*> nodes(n);
	long long int total_cost=0;
	for(int i=0;i<n;i++){
		nodes[i]=new node();
	}
	for(int i=0;i<n;i++){
		if(i==0){
			nodes[i]->parent=-1;
		}
		else{
			int temp;
			cin>>temp;
			nodes[i]->parent=temp;
		}
	}
	for(int i=0;i<n;i++){
		if(i==0){
			nodes[i]->capacity=m;
			nodes[i]->cost=floor(log2(m))+1;
		}
		else{
			int temp;
			cin>>temp;
			nodes[i]->capacity=temp;
			nodes[i]->cost=floor(log2(temp))+1;
		}
	}
	for(int i=0;i<m;i++){
		string query;
		cin>>query;
		int index;
		cin>>index;
		bool found=false;
		while(!found&&nodes[index]->parent!=-1){
			if(nodes[index]->cache.find(query)==nodes[index]->cache.end()){
				nodes[index]->latest.push_back(query);
				it last=nodes[index]->latest.end();
				last--;
				if(nodes[index]->cache.size()<nodes[index]->capacity){
					nodes[index]->cache[query]=last;
				}
				else{
					string to_remove=nodes[index]->latest.front();
					nodes[index]->latest.pop_front();
					nodes[index]->cache.erase(to_remove);
					nodes[index]->cache[query]=last;
				}
			}	
			else{
				it old=nodes[index]->cache[query];
				nodes[index]->latest.erase(old);
				nodes[index]->latest.push_back(query);
				it last=nodes[index]->latest.end();
				last--;				
				nodes[index]->cache[query]=last;
				found=true;
			}
			total_cost+=nodes[index]->cost;
			index=nodes[index]->parent;
		}
		if(nodes[index]->parent==-1&&!found){
			total_cost+=nodes[index]->cost;
		}

	}
	cout<<total_cost;

}