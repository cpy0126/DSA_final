#include<fstream>
#include<set>
#include<vector>
#include<iostream>
using namespace std;
vector<string>token[10005];
string chrlist="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
string H(int x)
{
	int base=chrlist.size();
	string res="";
	res+=chrlist[x/base];
	res+=chrlist[x%base];
	return res;
}
bool is_token(char c)
{
    if('0'<=c && c<='9') return 1;
    if('a'<=c && c<='z') return 1;
    if('A'<=c && c<='Z') return 1;
    return 0;
}
char lower_case(char c)
{
    if('A'<=c&&c<='Z') c=c-'A'+'a';
    return c;
}
void get_token(string filename,int id)
{
    ifstream filein;
    filein.open(filename);
    string tmp;
    getline(filein,tmp);
    getline(filein,tmp);
    getline(filein,tmp);
    filein>>tmp;
    getline(filein,tmp);

    set<string> tokens;
    int cnt=0;
    string tmp_token;
    while(cnt<tmp.size())
    {
        tmp[cnt]=lower_case(tmp[cnt]);
        if(is_token(tmp[cnt]))
            tmp_token.push_back(tmp[cnt]);
        else
        {
            if(tmp_token.size()>0)
            {
                tokens.insert(tmp_token);
                tmp_token.clear();
            }
        }
        cnt++;
    }
    if(tmp_token.size()>0)
    {
        tokens.insert(tmp_token);
        tmp_token.clear();
    }
    getline(filein,tmp);
    getline(filein,tmp);
    getline(filein,tmp);
    cnt=0;
    while(cnt<tmp.size())
    {
        tmp[cnt]=lower_case(tmp[cnt]);
        if(is_token(tmp[cnt]))
            tmp_token.push_back(tmp[cnt]);
        else
        {
            if(tmp_token.size()>0)
            {
                tokens.insert(tmp_token);
                tmp_token.clear();
            }
        }
        cnt++;
    }
    if(tmp_token.size()>0)
    {
        tokens.insert(tmp_token);
        tmp_token.clear();
    }
	tokens.insert("i");
	tokens.insert("read");
	tokens.insert("the");
	tokens.insert("paragraph");
	tokens.insert("on");
	tokens.insert("http");
	tokens.insert("wikipedia");
	tokens.insert("org");
    for(auto o:tokens)
        token[id].push_back(o);
}
string int_to_string(int t)
{
    string tmp;
    while(t>0)
    {
        tmp.push_back(t%10+'0');
        t/=10;
    }
    for(int i=0;i<tmp.size()/2;i++)
        swap(tmp[i],tmp[tmp.size()-1-i]);
    return tmp;
}
int main()
{
    for(int i=1;i<=10000;i++)
    {
        string num=int_to_string(i);
        string mailname="test_data/mail"+num;
        get_token(mailname,i);
        if(i/200*200==i)
            cout<<i<<' '<<token[i].size()<<'\n';
    }
    ofstream fout;
    fout.open("sim_AND.txt");
    for(int i=1;i<=10000;i++)
    {
        if(i/50*50==i)cout<<i<<'\n';
        for(int j=1;j<=10000;j++)
        {
            int len1=token[i].size(),len2=token[j].size();
            int tmp1=0,tmp2=0;
            int equal_cnt=0;
            while(tmp1<len1&&tmp2<len2)
            {
                if(token[i][tmp1]==token[j][tmp2])
                {
                    equal_cnt++;
                    tmp1++;
                    tmp2++;
                }
                else if(token[i][tmp1]<token[j][tmp2])
                {
                    tmp1++;
                }
                else tmp2++;
            }
            fout<<H(equal_cnt);
        }
    }
}

