#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define F(i,j,k) for (int i=j;i<=k;++i)
#define D(i,j,k) for (int i=j;i>=k;--i)
char s[100005];
int l,a[100005],cnt[4],sum,del[100005],fuck=0;
void out()
{
	int ans=1,flag=0;
	F(i,1,l) ans&=del[i];
	if (ans) printf("-1\n");
	else
	{
		F(i,1,l)
		if (!del[i])
		{
			if (s[i]!='0'||flag) printf("%c",s[i]);
			if (s[i]!='0') flag=1;
		}
		if (!flag) printf("0\n");
		else printf("\n");
	}
}
int main()
{
	scanf("%s",s+1);
	l=strlen(s+1);a[1]=s[1]-'0';
	F(i,2,l)
	{
		a[i]=s[i]-'0';
		if (a[i])
		{
			cnt[a[i]%3]++;
			sum+=a[i]%3;
		}
	}
//	cout<<(sum+a[1])%3<<endl;
	switch ((sum+a[1])%3)
	{
		case 0: printf("%s",s+1); return 0;break;
		case 1:
			if (cnt[1]>0)
			{
//				printf("del %d\n",1);
				D(i,l,2) if (a[i]%3==1)
				{
//					printf("del %d\n",1);
					del[i]=1;
					break;
				}
			}
			else if (a[1]%3==1&&a[2]!=0)
			{
//				printf("del %d\n",1);
				del[1]=1;
			}
			else if (cnt[2]>=2)
			{
//				printf("del %d\n",2);
				int all=2;
				D(i,l,2) if (a[i]%3==2)
				{
					del[i]=1;
					all--;
					if (!all) break;
				}
			}
			else fuck=1;
			break;
		case 2:
			if (cnt[2])
			{
				D(i,l,2) if (a[i]%3==2) {del[i]=1; break;}
			}
			else if (a[1]%3==2&&a[2]!=0)
			{
				del[1]=1;
			}
			else if (cnt[1]>=2)
			{
				int all=2;
				D(i,l,2) if (a[i]%3==1)
				{
					del[i]=1;
					all--;
					if (!all) break;
				}
			}
			else fuck=1;
			break;
	}
	if (!fuck) out();
//	cout<<fuck<<endl;
	else
	{
		cnt[a[1]%3]++;sum+=a[1]%3;
		switch (sum%3)
		{
			case 0: printf("%s",s+1); return 0;break;
			case 1:
				if (cnt[1]>0)
				{
					D(i,l,1) if (a[i]%3==1)
					{
						del[i]=1;
						break;
					}
				}
				else if (cnt[2]>=2)
				{
//					printf("del %d\n",2);
					int all=2;
					D(i,l,1) if (a[i]%3==2)
					{
						del[i]=1;
						all--;
						if (!all) break;
					}
				}
				else {printf("-1\n");return 0;}
				break;
			case 2:
				if (cnt[2])
				{
					D(i,l,1) if (a[i]%3==2) {del[i]=1; break;}
				}
				else if (cnt[1]>=2)
				{
//					printf("del 2 of 1\n");
					int all=2;
					D(i,l,1) if (a[i]%3==1)
					{
						del[i]=1;
						all--;
						if (!all) break;
					}
				}
				else {printf("-1\n");return 0;}
				break;
		}
		out();
	}
}
