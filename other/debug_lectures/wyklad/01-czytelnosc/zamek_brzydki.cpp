#include <bits/stdc++.h>

using namespace std;

int n, d;
int X, Y;
int x, y;
int xp, yp, xs, ys;
int depth[1000000];
int czyje[2001][2001][4];
bool odw[1000000];
pair< pair<int, int>, pair<int ,int> > wsp[1000000];
vector <int> listy[1000000];

int main()
{
    scanf("%d%d%d%d", &X, &Y, &n, &d);
    scanf("%d%d", &xp, &yp);
    scanf("%d%d", &xs, &ys);

    if(X<=2000 && Y<=2000)
    {
        for(int i=0; i<n; ++i)
        {
            scanf("%d%d%d%d", &wsp[i].first.first, &wsp[i].second.first, &wsp[i].first.second, &wsp[i].second.second);
            if(wsp[i].first.first>wsp[i].first.second) swap(wsp[i].first.first, wsp[i].first.second);
            if(wsp[i].second.first>wsp[i].second.second) swap(wsp[i].second.first, wsp[i].second.second);

            for(int j=wsp[i].first.first; j<=wsp[i].first.second; ++j)
            {
                for(int h=wsp[i].second.first; h<=wsp[i].second.second; ++h)
                {
                    for(int k=0; k<3; ++k)
                    {
                        if(czyje[j][h][k]==0)
                        {
                            czyje[j][h][k]=i+1;
                            break;
                        }
                        else
                        {
                            if((j==wsp[i].first.first || j==wsp[i].first.second) && (h==wsp[i].second.first || h==wsp[i].second.second)) /// mamy do czynienia z wierzcholkiem
                            {
                                if((wsp[i].first.first==wsp[czyje[j][h][k]-1].first.second && wsp[i].second.first==wsp[czyje[j][h][k]-1].second.second) || (wsp[i].first.second==wsp[czyje[j][h][k]-1].first.first && wsp[i].second.first==wsp[czyje[j][h][k]-1].second.second) || (wsp[i].first.first==wsp[czyje[j][h][k]-1].first.second && wsp[i].second.second==wsp[czyje[j][h][k]-1].second.first) || (wsp[i].first.second==wsp[czyje[j][h][k]-1].first.first && wsp[i].second.second==wsp[czyje[j][h][k]-1].second.first));
                                else
                                {
                                    listy[czyje[j][h][k]-1].push_back(i);
                                    listy[i].push_back(czyje[j][h][k]-1);
                                }
                            }
                            else
                            {
                                    listy[czyje[j][h][k]-1].push_back(i);
                                    listy[i].push_back(czyje[j][h][k]-1);
                            }
                        }
                    }
                }
            }
        }


        for(int i=0; i<d; ++i)
        {
            scanf("%d%d" ,&x, &y);
            odw[czyje[x][y][0]-1]=1;
        }

        vector <int> x, y;
        x.push_back(czyje[xp][yp][0]-1);
        odw[czyje[xp][yp][0]-1]=1;

        int dep=1;
        depth[czyje[xp][yp][0]-1]=1;

        /// BFS

        while(x.size()>0)
        {
            for(int i=0; i<x.size(); ++i)
            {
                for(int j=0; j<listy[x[i]].size(); ++j)
                {
                    if(!odw[listy[x[i]][j]])
                    {
                        depth[listy[x[i]][j]]=dep+1;
                        odw[listy[x[i]][j]]=1;
                        y.push_back(listy[x[i]][j]);
                    }
                }
            }
            swap(x, y);
            y.clear();
            dep++;
        }

        printf("%d", depth[czyje[xs][ys][0]-1]);
        return 0;
    }

    else
    {
        for(int i=0; i<n; ++i)
        {
            scanf("%d%d%d%d", &wsp[i].first.first, &wsp[i].second.first, &wsp[i].first.second, &wsp[i].second.second);
            if(wsp[i].first.first>wsp[i].first.second) swap(wsp[i].first.first, wsp[i].first.second);
            if(wsp[i].second.first>wsp[i].second.second) swap(wsp[i].second.first, wsp[i].second.second);
        }

        for(int i=0; i<n; ++i)
        {
            for(int j=i+1; j<n; ++j)
            {
                if(!(wsp[j].first.first>wsp[i].first.second) && !(wsp[j].first.second<wsp[i].first.first) && !(wsp[j].second.first>wsp[i].second.second) && !(wsp[j].second.second<wsp[i].second.first))
                {
                    if(!((wsp[i].first.first==wsp[j].first.second && wsp[i].second.first==wsp[j].second.second) || (wsp[i].first.second==wsp[j].first.first && wsp[i].second.first==wsp[j].second.second) || (wsp[i].first.first==wsp[j].first.second && wsp[i].second.second==wsp[j].second.first) || (wsp[i].first.second==wsp[j].first.first && wsp[i].second.second==wsp[j].second.first)))
                    {
                                            listy[i].push_back(j);
                    listy[j].push_back(i);
                    }
                }
            }
        }

        for(int i=0; i<d; ++i)
        {
            scanf("%d%d" ,&x, &y);
            for(int j=0; j<n; ++j)
            {
                if(wsp[j].first.first<x && x<wsp[j].first.second && wsp[j].second.first<y && y<wsp[j].second.second) odw[j]=1;
            }
        }

        int podr;
        int skarb;

        for(int j=0; j<n; ++j)
        {
            if(wsp[j].first.first<xs && xs<wsp[j].first.second && wsp[j].second.first<ys && ys<wsp[j].second.second) skarb=j;
            if(wsp[j].first.first<xp && xp<wsp[j].first.second && wsp[j].second.first<yp && yp<wsp[j].second.second) podr=j;
        }

        vector <int> x, y;
        x.push_back(podr);
        odw[podr]=1;

        int dep=1;
        depth[podr]=1;

        /// BFS

        while(x.size()>0)
        {
            for(int i=0; i<x.size(); ++i)
            {
                for(int j=0; j<listy[x[i]].size(); ++j)
                {
                    if(!odw[listy[x[i]][j]])
                    {
                        depth[listy[x[i]][j]]=dep+1;
                        odw[listy[x[i]][j]]=1;
                        y.push_back(listy[x[i]][j]);
                    }
                }
            }
            swap(x, y);
            y.clear();
            dep++;
        }

        printf("%d", depth[skarb]);
        return 0;

    }
}