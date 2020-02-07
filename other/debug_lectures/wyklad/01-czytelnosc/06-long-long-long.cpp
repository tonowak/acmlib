long long int tab[501][501];

long long int sum(long long int a,long long int b,long long int t)
{
    long long int w=0;
    for(int i=a; i<=b; i++)
        w+=tab[t][i];
    return w;
}

long long int wyn(int n)
{
