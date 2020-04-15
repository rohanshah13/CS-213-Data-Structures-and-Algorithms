#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<string> sorted_min_strings;
bool lesser(int a,int b){
    if(sorted_min_strings[a]<sorted_min_strings[b]){
        return true;
    }
    else{
        return false;
    }
}
vector<string> duval(string const& s) {
    int n = s.size();
    int i = 0;
    vector<string> factorization;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] >= s[j]) {
            if (s[k] > s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k) {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}
string min_cyclic_string(string s) {
    s += s;
    int n = s.size();
    int i = 0, ans = 0;
    while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k)
            i += j - k;
    }
    return s.substr(ans, n / 2);
}


vector<string> string_list;
int main(){
    int n;
    cin>>n;
    for(int i= 0;i<n;i++){
        string temp;
        cin>>temp;
        string_list.push_back(temp);
    }
    
    vector<int> indices;
    for(int i=0;i<n;i++){
        sorted_min_strings.push_back(min_cyclic_string(string_list[i]));
        //cout<<sorted_min_strings[i]<<endl;
        indices.push_back(i);
    }
    sort(indices.begin(),indices.end(),lesser);
    int count=1;
    for(vector<int>:: iterator it=indices.begin();it<(indices.end()-1);it++){
        if(sorted_min_strings[*it]!=sorted_min_strings[*it+1]){
            count++;
        }
    }
    cout<<count<<endl;
    vector<string> v1=duval(string_list[0]);
    vector<string> v2=duval(string_list[1]);
    vector<string>:: iterator it1=v1.begin();
    vector<string>:: iterator it2=v2.begin();
    vector<string> ans;
    char inf='z';
    inf++;
    while(it1!=v1.end()&&it2!=v2.end()){
        if(*it1+inf<*it2+inf){
            ans.push_back(*it1);
            it1++;
        }
        else{
            ans.push_back(*it2);
            it2++;
        }
    } 
    if(it1!=v1.end()){
        while(it1!=v1.end()){
            ans.push_back(*it1);
            it1++;
        }
    }
    if(it2!=v2.end()){
        while(it2!=v2.end()){
            ans.push_back(*it2);
            it2++;
        }
    }
    for(vector<string>:: iterator it=ans.begin();it!=ans.end();it++){
        cout<<*it;
    }
}