#include<iostream>
#include<string>
using namespace std;

int main(){

	string word;
	long long int rankx;
	cin>>word;
	cin>>rankx;
	rankx++;
	int freq[26];

	long long int fact[26];
	int freq1[26];
	long long int fact1[26];


	for(int i=0; i<26; i++){
        freq[i]=0;
        fact[i]=1;
        freq1[i]=0;
        fact1[i]=1;
	}
	long long int fact_word=1;
	long long int fact_word1=1;

    string reqd_word = "";



	for(int i=0;i<word.length();i++){
            freq[word[i]-'a']++;
            fact[word[i]-'a']*=freq[word[i]-'a'];
            fact_word*=(i+1);
            freq1[word[i]-'a']++;
            fact1[word[i]-'a']*=freq1[word[i]-'a'];
            fact_word1*=(i+1);


	}
	long long int sum;
	long long int sum1=0;
for(int i=0;i<word.length();i++){
            int lowest=0;
            for(int j=0;j<26;j++){
                if(freq1[j]>0){
                    lowest=j;
                    break;
                }
                else{}
            }
            fact_word1=fact_word1/(word.length()-i);
            sum=fact_word1;
            for (int j=0;j<26;j++){
                if(j==lowest&&fact1[j]>1){
                    sum=sum/fact1[j]*freq1[j];
                }
                else{
                    sum=sum/fact1[j];
                }
            }
            sum1=sum+sum1;
            long long int temp_sum=sum;
            for(int j=lowest+1;j<26;j++){
                if(sum1>=rankx){
                    sum=sum-temp_sum;
                    sum1=sum1-temp_sum;
                    break;
                }
                else if(freq1[j]>0){
                    temp_sum=temp_sum*freq1[j]/(freq1[lowest]);
                    lowest=j;
                    sum=sum+temp_sum;
                    sum1=sum1+temp_sum;
                }
                else{}

            }
            reqd_word=reqd_word+char(97+lowest);
            fact1[lowest]=fact1[lowest]/freq1[lowest];
            freq1[lowest]--;
	}
	long long int word_rank=0;
	for(int i=0; i<word.length();i++){
        long long int temp_rank=0;
        int no_less=0;
        for(int j=i+1; j<word.length();j++){
             if(word[j]<word[i]){
                no_less++;
            }
            else{}
        }
        fact_word=fact_word/(word.length()-i);
        temp_rank=no_less*fact_word;
        for (int i=0;i<26;i++){
            temp_rank=temp_rank/fact[i];
        }
        word_rank+=temp_rank;
        fact[word[i]-'a']=fact[word[i]-'a']/freq[word[i]-'a'];
        freq[word[i]-'a']--;

	}
	cout<<word_rank<<" ";
	cout<<reqd_word;

}
