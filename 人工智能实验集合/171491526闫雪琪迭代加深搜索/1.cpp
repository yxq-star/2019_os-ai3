#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
using namespace std;
const int N = 9;
bool ok;
int flag[N][N];
int cover[N][N];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int n,m,b,ans;
struct node
{
    int x,y,val;
}barrier[50];
int cmp(struct node a,struct node b)
{
    return a.val < b.val;
}
int nextint()
{
    int ret;
    char c;
    bool sig = false;
    while(isspace(c = getchar()))
        ;
    if(c == '-')
    {
        sig = true;
        c = getchar();
    }
    ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9')
        ret = ret * 10 + c - '0';
    return sig?-ret:ret;
}
 
bool jud(int x,int y)
{
    return !(x >= 1 && y >= 1 && x <= n && y <= m);
}
 
int h()
{
    int i,j;
    int ret = 0;
    for(i = 1;i <= n;i ++)
    {
        for(j = 1;j <= m;j ++)
        {
            if(!cover[i][j] && flag[i][j] != 2)
            {
                if((flag[i - 1][j] == 2 || jud(i - 1,j))
                   && (flag[i + 1][j] == 2 || jud(i + 1,j))
                   && (flag[i][j - 1] == 2 || jud(i,j - 1))
                    && (flag[i][j + 1] == 2 || jud(i,j + 1)))
                    ret ++;
            }
        }
    }
    return ret;
}
 
int put(int x,int y)
{
    int ret = 1;
    int i,j;
    i = x - 1;
    j = y;
    while(i > 0 && flag[i][j] != 2)
    {
        cover[i][j] ++;
        if(cover[i][j] == 1)
            ret ++;
        i --;
    }
    i = x + 1;
    j = y;
    while(i <= n && flag[i][j] != 2)
    {
        cover[i][j] ++;
        if(cover[i][j] == 1)
            ret ++;
        i ++;
    }
    i = x;
    j = y - 1;
    while(j > 0 && flag[i][j] != 2)
    {
        cover[i][j] ++;
        if(cover[i][j] == 1)
            ret ++;
        j --;
    }
    j = y + 1;
    while(j <= m && flag[i][j] != 2)
    {
        cover[i][j] ++;
        if(cover[i][j] == 1)
            ret ++;
        j ++;
    }
    return ret;
}
 
void deput(int x,int y)
{
    int ret = 1;
    int i,j;
    i = x - 1;
    j = y;
    while(i > 0 && flag[i][j] != 2)
    {
        cover[i][j] --;
        i --;
    }
    i = x + 1;
    while(i <= n && flag[i][j] != 2)
    {
        cover[i][j] --;
        i ++;
    }
    i = x;
    j = y - 1;
    while(j > 0 && flag[i][j] != 2)
    {
        cover[i][j] --;
        j --;
    }
    j = y + 1;
    while(j <= m && flag[i][j] != 2)
    {
        cover[i][j] --;
        j ++;
    }
}
 
 
int check()//0 irllegal 1 ok 2 right
{
    int i,j;
    int tmp;
    int ret = 2;
    for(i = 0;i < b;i ++)
    {
        if(barrier[i].val == -1)
            continue;
        tmp = 0;
        for(j = 0;j < 4;j ++)
        {
            int tx = barrier[i].x + dx[j];
            int ty = barrier[i].y + dy[j];
            if(tx < 1 || ty < 1 || tx > n || ty > m)
                continue;
            if(flag[tx][ty] == 3)
                tmp ++;
        }
        if(tmp > barrier[i].val)
            return 0;
        if(tmp != barrier[i].val)
            ret = 1;
    }
    return ret;
}
 
void print()
{
    int i,j;
    for(i = 1;i <= n;i ++)
    {
        for(j = 1;j <= m;j ++)
            printf("%d ",flag[i][j]);
        putchar(10);
    }
    putchar(10);
    for(i = 1;i <= n;i ++)
    {
        for(j = 1;j <= m;j ++)
            printf("%d ",cover[i][j]);
        putchar(10);
    }
}
 
void Dfs(int x,int y,int cnt,int ca)
{
    if(ca > ans)
        return;
    int i,j;
    if(ok)
        return;
    if(cnt == m * n - b)
    {
        ok = true;
        return;
    }
    for(i = x;i <= n;i ++)
    {
        for(j = 1;j <= m;j ++)
        {
            if(flag[i][j] == 0 && cover[i][j] == 0)
            {
                flag[i][j] = 3;
                if(check() != 2)
                {
                    flag[i][j] = 0;
                    continue;
                }
                int tp = put(i,j);
                Dfs(i,j,cnt + tp,ca + 1);
                deput(i,j);
                flag[i][j] = 0;
            }
        }
    }
}
 
void dfs(int id,int cnt,int ca)
{
    if(ca > ans)
        return;
    if(ok)
        return;
    if(id == b)
    {
        if(check() == 2)//right
        {
            Dfs(1,1,cnt,ca);
        }
        return;
    }
    int i,j;
    for(i = j = 0;i < 4;i ++)
    {
        if(flag[barrier[id].x + dx[i]][barrier[id].y + dy[i]] == 3)
            j ++;
    }
    if(j > barrier[id].val)
        return;
    else
    {
        if(j == barrier[id].val)
            dfs(id + 1,cnt,ca);
        else
        {
            for(i = 0;i < 4;i ++)
            {
                int tx = barrier[id].x + dx[i];
                int ty = barrier[id].y + dy[i];
                if(tx < 1 || ty < 1 || tx > n || ty > m)
                    continue;
                if(flag[tx][ty] == 0 && cover[tx][ty] == 0)
                {
                    flag[tx][ty] = 3;
                    if(check() == 0)
                    {
                        flag[tx][ty] = 0;
                        continue;
                    }
                    int tp = put(tx,ty);
                    dfs(id,cnt + tp,ca + 1);
                    deput(tx,ty);
                    flag[tx][ty] = 0;
                }
            }
        }
    }
}
 
int main()
{
    int i,j;
    while(n = nextint())
    {
        m = nextint();
        if(m + n == 0)
            break;
        b = nextint();
        memset(flag,0,sizeof(flag));
        memset(cover,0,sizeof(cover));
        for(i = 0;i < b;i ++)
        {
            barrier[i].x = nextint();
            barrier[i].y = nextint();
            barrier[i].val = nextint();
            flag[barrier[i].x][barrier[i].y] = 2;//
        }
        sort(barrier,barrier + b,cmp);
 
        ok = false;
        for(i = 0;i < b;i ++)
            if(barrier[i].val > 0)
                break;
        ans = h();
        //print();
        while(1)
        {
            if(ok || ans > m * n - b)
                break;
            dfs(i,0,0);
            if(ok)
                break;
            ans ++;
        }
        if(ok == false)
            printf("No solution\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}

