#include<iostream>
#include<string>
using namespace std;


int main(){
	
	long n;
	cin>>n;
	
	char direction[n];
	long type[n];
	for(long i=0;i<n;i++){
		cin>>direction[i];
		cin>>type[i];
	}
	long score[100000];
	long min[100000];
	bool x[100000];
	for(long i=0;i<100000;i++){
		min[i]=0;
		score[i]=0;
		x[i]=false;
	}
	for(long i=0;i<n;i++){
		
		if(direction[i]=='s'){
			score[type[i]]++;
		}
		else{
			score[type[i]]--;
		}
		if(score[type[i]]<min[type[i]]){
			min[type[i]]=score[type[i]];
		}
		else{}
		if(score[type[i]]==0){x[type[i]]=true;}
		else{x[type[i]]=false;}
	}
	long no_types=0;
	for(long i=0;i<100000;i++){
		if(x[i]==true&min[i]==0){
		no_types++;
		}
	}
	long max_pos=-1;
	long max_types=no_types;
	for(long i=0;i<n;i++){
		
		if(direction[i]=='s' && x[type[i]]==true){
			score[type[i]]++;
			if(score[type[i]]==min[type[i]]+1){no_types--;}
		}
		else if(x[type[i]]==true){
			score[type[i]]--;
			if(score[type[i]]==min[type[i]]){no_types++;}		
		}
		if(no_types>max_types){
			max_types=no_types;
			max_pos=i;
		}
	}
	
	cout<<max_pos+2<<" "<<max_types;
}
	
		
	

