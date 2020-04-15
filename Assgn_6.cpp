#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void swap(vector<int>& arr,int pos1,int pos2){
	int temp=arr[pos1];
	arr[pos1]=arr[pos2];
	arr[pos2]=temp;
}
int main(){
	int n;
	cin>>n;
	vector<int> perm,v1,v2;
	vector<int> inverse;
	vector<bool> find_min;
	for(int i=0;i<n;i++){
		int temp;
		cin>>temp;
		perm.push_back(temp);
		find_min.push_back(true);
		inverse.push_back(0);
	}
	vector <int> weight;
	for(int i=0;i<n;i++){
		inverse[perm[i]]=i;
		int temp;
		cin>>temp;
		weight.push_back(temp);
	}
	vector<int> dist;
	for(int i=0;i<n-1;i++){
		int temp;
		cin>>temp;
		dist.push_back(temp);
	}
	long long int sum=0;
	vector<long long int> cdf;
	cdf.push_back(0);
	for(int i=0;i<n-1;i++){
		sum=sum+dist[i];
		cdf.push_back(sum);
	}
	long long int min_wt=0;
	for(int i=0;i<n;i++){
		min_wt=min_wt+abs(weight[i]*abs(cdf[perm[i]]-cdf[i]));
	}
	cout<<min_wt<<endl;
	int x=n-1;
	//cout<<x<<endl;
	stack<int> s1;
	stack<int> s2;
	for(int i=0;i<n;i++){
		if(perm[i]>i){
			s1.push(perm[i]);
		}
	}
	while(!s1.empty()){
		int index=s1.top();
		while(perm[index]>inverse[s1.top()]){
			s2.push(perm[index]);
			index=perm[index];
		}
		if(perm[index]!=s1.top()){
			//cout<<inverse[perm[index]]<<" "<<inverse[s1.top()]<<endl;
			v1.push_back(inverse[perm[index]]);
			v2.push_back(inverse[s1.top()]);
			int temp1=perm[index];
			int temp2=s1.top();
			swap(perm,inverse[temp1],inverse[temp2]);
			swap(inverse,temp1,temp2);
		}
		while(!s2.empty()){
			//cout<<inverse[s1.top()]<<" "<<inverse[s2.top()]<<endl;
			v1.push_back(inverse[s1.top()]);
			v2.push_back(inverse[s2.top()]);
			int temp1=s1.top(),temp2=s2.top();
			swap(perm,inverse[temp1],inverse[temp2]);
			swap(inverse,temp1,temp2);
			s2.pop();
		}
		s1.pop();

	}
	cout<<v1.size()<<endl;
	for(int i=0;i<v1.size();i++){
		cout<<v1[i]<<" "<<v2[i]<<endl;
	}
		
}