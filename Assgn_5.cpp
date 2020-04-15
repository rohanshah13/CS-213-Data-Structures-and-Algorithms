#include<iostream>
#include<list>
#include<vector>

using namespace std;

class memory_block{
public:	
	long long int start;
	long long int end;
	long long int size;

	memory_block(long long int s,long long int e){
		start=s;
		end=e;
		size=end-start;
	}
};
class request{
public:
	long long int pid;
	long long int size;

	request(long long int p,long long int s){
		pid=p;
		size=s;
	}
};
class program{
public:
	list<memory_block> allocated_memory;
	program(){}

	program(memory_block m){
		allocated_memory.push_back(m);
	}
};
int allocate_memory(long long int size, list<memory_block>& free){
	list <memory_block> :: iterator it; 
    for(it = free.begin(); it != free.end(); it++){
    	if(it->size>=size){
    		long long int temp=it->start;
    		if(it->size==size){
    			free.erase(it);
    		}
    		else{
    			it->start+=size;
    			it->size-=size;
    		}
    		return temp;   		
    	}
    } 
    return -1;
}
memory_block deallocate(long long int start,list<memory_block>& memory){
	list <memory_block> :: iterator it; 
    for(it = memory.begin(); it != memory.end(); it++){
    	if(it->start==start){
    		memory_block temp=*it;
    		memory.erase(it);
    		return temp;
    	}
    }
    return memory_block(-1,-1);
}
long long int add_memory(memory_block memory,list<memory_block>& free_memory){
	list <memory_block> :: iterator it; 
    for(it = free_memory.begin(); it->start<=memory.end&&it!=free_memory.end(); it++){
    	if(memory.end==it->start){
    		it->start=memory.start;
    		it->size+=memory.size;
    		return it->size;
    	}
    	else if(memory.start==it->end){
    		it->end=memory.end;
    		it->size+=memory.size;
    		list <memory_block> :: iterator next_it=it;
    		next_it++;
    		if(next_it!=free_memory.end()&&memory.end==next_it->start){
    			it->end=next_it->end;
    			it->size+=next_it->size;
    			free_memory.erase(next_it);
    		}
    		return it->size;
    	}
    	else{}
    }
	free_memory.insert(it,memory);
	return memory.size;
}
void deallocate_all(list<memory_block>& free_memory ,list<memory_block>& memory,list<request>& pending,vector<program*>& programs,long long int pid,list<long long int>& pendingnos){
	list <memory_block> :: iterator it; 
    for(it = memory.begin(); it != memory.end();){   	
    	memory_block temp=*it;
    	int x=0;
    	x+=add_memory(temp,free_memory);
    	it=memory.erase(it);
    }
    list<request> :: iterator it1;
    list<long long int> :: iterator i=pendingnos.begin();
    for(it1=pending.begin();it1!=pending.end();){
    	if(it1->pid==pid){
    		it1=pending.erase(it1);
    		
    		i=pendingnos.erase(i);
    	}
    	else{i++;it1++;}
    }	
    return ;
}
/*void print(list<memory_block>& free,list<request> pending){
	list <memory_block> :: iterator it; 
    for(it = free.begin(); it != free.end(); it++){
    	cout<<it->start<<" "<<it->end<<endl;
    }
    cout<<endl;
    for(list<request>:: iterator it1=pending.begin();it1!=pending.end();){
    	cout<<it1->pid<<" "<<it1->size<<endl;
    }
    cout<<endl;
}*/

int main(){
	long long int no_prog, memory1;
	cin>>no_prog;
	cin>>memory1;
	vector<program*> programs(no_prog,NULL);		
	list<memory_block> free_memory;
	free_memory.push_back(memory_block(0,memory1));
	char input;
	cin>>input;
	list<request> pending;
	vector<long long int> output;
	list<long long int> pendingnos;
	long long int count=1;			//count of no of inputs
	while(input!='H'){		
		if(input=='A'){
			long long int pid,size;
			cin>>pid;
			cin>>size;
			if(programs[pid]==NULL){programs[pid]=new program();}
			int index=allocate_memory(size,free_memory);
			if(index!=-1){
				programs[pid]->allocated_memory.push_back(memory_block(index,index+size));
				output.push_back(index);
			}
			else{
				pending.push_back(request(pid,size));
				output.push_back(-1);
				pendingnos.push_back(count-1);
			}
		} 		
		else if(input=='D'){
			long long int pid,start;
			cin>>pid;
			cin>>start;
			if(programs[pid]==NULL){programs[pid]=new program();}
			memory_block memory=deallocate(start,programs[pid]->allocated_memory);
			if (memory.start==-1){
				output.push_back(1);
			}
			else{
				output.push_back(0);
				long long int x=add_memory(memory, free_memory);
				list<request> :: iterator it;
				list<long long int> :: iterator pos=pendingnos.begin();
				for(it=pending.begin();it!=pending.end();it++){					
					if(it->size<=x){
						long long int index=allocate_memory(it->size,free_memory);
						if(programs[it->pid]==NULL){
							programs[it->pid]=new program();
						}
						programs[it->pid]->allocated_memory.push_back(memory_block(index,index+it->size));
						x-=it->size;
						it=pending.erase(it);
						it--;
						
						output[*pos]=index;
						pos=pendingnos.erase(pos);
					}
					else{pos++;}
				}		
			}
		}
		else if(input=='T'){
			long long int pid;
			cin>>pid;
			if(programs[pid]==NULL||programs[pid]->allocated_memory.empty()){
				output.push_back(1);
				list<request> :: iterator it1;
				list<long long int> :: iterator i=pendingnos.begin();
    			for(it1=pending.begin();it1!=pending.end();){
    				if(it1->pid==pid){
    				it1=pending.erase(it1);    		
    				i=pendingnos.erase(i);
    				}
    				else{i++;it1++;}
    			}	
			}
			else{
				deallocate_all(free_memory, programs[pid]->allocated_memory, pending,programs,pid,pendingnos);
				output.push_back(0);
				list<long long int> :: iterator pos=pendingnos.begin();
				for(list<request>:: iterator it1=pending.begin();it1!=pending.end();){
    				long long int index=allocate_memory(it1->size,free_memory);
					if(index!=-1){			
						programs[it1->pid]->allocated_memory.push_back(memory_block(index,index+it1->size));
						it1=pending.erase(it1);
						output[*pos]=index;
						pos=pendingnos.erase(pos);
					}
					else{
						pos++;
						it1++;
					}
    			}
			}

		}
		cin>>input;
		count++;
	}
	for(vector<long long int> :: iterator it=output.begin();it!=output.end();it++){
		cout<<*it<<endl;
		//print(free_memory,pending);
	}
}