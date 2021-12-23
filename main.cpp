#include <bits/stdc++.h>

using namespace std;

ifstream f("royfloyd.in");
ofstream g("royfloyd.out");



class graf
{

    int nr_noduri, nr_muchii, tipul;


    vector<vector<int>> lista_muchii;
    vector<vector<int>>  lista_muchii_transpusa;
    vector<int> havel;
    vector<vector<pair<int, int>>> lista_cu_costuri;
    vector<pair<int, int>> lista_dijkstra[5005];
    vector<vector<pair<int, int>>> lista_cu_operatii;
    vector<int> ind;
    vector<int> gr;

    int matrice[101][101];

    void dfs1(int nod, int nr, vector<bool> &vizitat, int &maxx, int &x);
    void DFSx(int nod, vector<int>&v);
    void DFS_TR(int nod,vector<int> &vizitat, int nr, vector<vector<int>>&CTC);
    void DFS_CTC(int nod, vector<int> &vizitat, stack<int> &st);
    void dfs_mic(int x, vector<bool> &vizitat, stack<int>&stiva);
    bool dfs_cuplaj(int nod, vector<int> &vizitat, int st[], int dr[]);
public:

    graf();

    graf(int nr_noduri, int nr_muchii, int tipul);

    ~graf() {}

    void BFS(int start);
    void DFS(int start);
    void CTCC();
    void TOPO();
    void APM();
    void HH();
    void RF();
    void diametru();
    void disj();
    void dijkstra();
    void cuplaj();
};

graf::graf()
{
    nr_noduri = 0;
    nr_muchii = 0;
    tipul = 0;
}

graf::graf(int nr_noduri, int nr_muchii, int tipul)
{

    this->tipul = tipul;
    this->nr_noduri = nr_noduri;
    this->nr_muchii = nr_muchii;

    if(tipul < 2)
    {
        int i = 0, nod1, nod2;

        lista_muchii.resize(nr_noduri+1);

        this->nr_noduri = nr_noduri;
        this->nr_muchii = nr_muchii;


        while(i < nr_muchii)
        {
            f>>nod1>>nod2;
            if(tipul)
                lista_muchii[nod1].push_back(nod2);
            else
            {
                lista_muchii[nod1].push_back(nod2);
                lista_muchii[nod2].push_back(nod1);
            }
            i++;
        }
    }
    else if(tipul == 2)
    {
        int x;
        havel.clear();
        while(f >> x)
            havel.push_back(x);
    }
    else if(tipul > 2 && tipul < 10)
    {
        this->nr_noduri = nr_noduri;
        this->nr_muchii = nr_muchii;
        lista_muchii.clear();
        lista_muchii.resize(nr_noduri+1);
        int i, x, y;
        for(i = 1; i <= nr_muchii; i++)
        {
            f>>x>>y;
            lista_muchii[x].push_back(y);
            lista_muchii_transpusa[y].push_back(x);
        }
    }
    else if(tipul == 10)
    {
        lista_cu_costuri.clear();
        lista_cu_costuri.resize(nr_noduri + 1);

        int i, nod1, nod2, cost;
        this->nr_noduri = nr_noduri;
        this->nr_muchii = nr_muchii;
        pair<int,int> aux;
        for(i = 1; i <= nr_muchii; i++)
        {
            f>>nod1>>nod2>>cost;
            aux.first = nod2;
            aux.second = cost;
            lista_cu_costuri[nod1].push_back(aux);
            aux.first = nod1;
            lista_cu_costuri[nod2].push_back(aux);
        }
    }
    else if(tipul == 11)
    {
        this->nr_noduri = nr_noduri;
        int i, j;
        for(i = 1; i <= nr_noduri; i++)
            for(j = 1; j <= nr_noduri; j++)
                f>>matrice[i][j];
    }
    else if(tipul == 12)
    {
        lista_cu_operatii.clear();
        lista_cu_operatii.resize(nr_noduri + 1);
        int i, nod1, nod2, operatie;
        this->nr_noduri = nr_noduri;
        this->nr_muchii = nr_muchii;
        pair<int,int> aux;
        for(i = 1; i <= nr_muchii; i++)
        {
            f>>operatie>>nod1>>nod2;
            aux.first = nod2;
            aux.second = operatie;
            lista_cu_operatii[nod1].push_back(aux);
        }
    }
    else if(tipul == 13)
    {
        //lista_dijkstra.clear();
        //lista_dijkstra.resize(nr_noduri + 1);
        int i, nod1, nod2, cost;
        this->nr_noduri = nr_noduri;
        this->nr_muchii = nr_muchii;

        //assert(1 <= nr_noduri && nr_noduri <= 50000);
        //assert(1 <= nr_muchii && nr_muchii <= 250000);
        for(i = 0; i < nr_muchii; i++)
        {
            f>>nod1>>nod2>>cost;

            //assert(1 <= nod1 && nod1 <= nr_noduri);
            //assert(1 <= nod2 && nod2 <= nr_noduri);
            //assert(0 <= cost && cost <= 20000);
            lista_dijkstra[nod1].push_back(make_pair(nod2, cost));
        }
    }
    else if(tipul == 14)
    {
        int i, nod1, nod2, e;
        f>>e;
        lista_muchii.clear();
        lista_muchii.resize(nr_noduri+1);
        for(i = 1; i <= e; i++)
        {
            f>>nod1>>nod2;
            lista_muchii[nod1].push_back(nod2);
        }
    }
}

///----------------------------------------------------------------------------------bfs
void graf::BFS(int inceput)
{
    int i = 0, nod_curent;

    queue<int> q;

    vector<int>vizitat;
    vector<int>distanta;

    q.push(inceput);

    do
    {
        vizitat.push_back(0);
        distanta.push_back(-1);
        i++;

    }
    while(i <= nr_noduri);

    vizitat[inceput] = 1;
    distanta[inceput] = 0;

    while(!q.empty())
    {
        nod_curent = q.front();
        q.pop();
        for (auto j = lista_muchii[nod_curent].begin(); j != lista_muchii[nod_curent].end(); j++)
            if(!vizitat[*j])
            {
                vizitat[*j] = 1;
                q.push(*j);
                distanta[*j] = distanta[nod_curent] + 1;
            }
    }
    int marime = distanta.size();
    for(i = 1; i < marime; i++)
        g<<distanta[i]<<" ";
}
///----------------------------------------------------------------------------------DFS

void graf::DFSx(int start, vector<int> &vizitat)
{
    vizitat[start] = 1;
    auto jos = lista_muchii[start].begin();
    auto sus = lista_muchii[start].end();
    auto j = jos;
    while(j != sus)
    {
        if(vizitat[*j] == 0)
            DFSx(*j, vizitat);
        j++;
    }
}

void graf::DFS(int start)
{

    int i = 0, nr_componente_conexe = 0,  marime;

    vector<int> vizitat;
    do
    {
        vizitat.push_back(0);
        i++;

    }
    while(i <= nr_noduri);

    marime = vizitat.size();

    for(i = 1; i < marime; i++)
        if(vizitat[i] == 0)
        {
            DFSx(i,vizitat);
            nr_componente_conexe++;
        }
    g<<nr_componente_conexe;
}
///----------------------------------------------------------------------------------HH

void graf::HH()
{
    int i, ok = 1;
    do
    {
        sort(havel.begin(), havel.end(),greater<int>());

        if(havel[0] == 0)
            break;

        int x = havel[0];
        havel.erase(havel.begin());

        if(x > havel.size())
            ok = 0;

        for(i = 0; i < x && ok == 1; i++)
        {
            havel[i]--;
            if(havel[i] < 0)
                ok  = 0;
        }

    }
    while(ok);
    if(ok == 0)
        g<<"NU";
    else
        g<<"DA";
}



///------------------------------------------------------------------------------TOPOLOGICA
void graf::dfs_mic(int x, vector<bool>&vizitat, stack<int> &stiva)
{
    vizitat[x] = 1;
    int marime = lista_muchii[x].size(), i = 0;
    while(i < marime)
    {
        if(vizitat[lista_muchii[x][i]] == 0)
            dfs_mic(lista_muchii[x][i], vizitat, stiva);
        i++;
    }
    stiva.push(x);

}

void graf::TOPO()
{
    stack <int> stiva;
    vector<bool> vizitat;
    int i = 0;

    do
    {
        vizitat.push_back(0);
        i++;
    }
    while(i <= nr_noduri + 1);

    for(i = 1; i <= nr_noduri; i++)
        if(vizitat[i] == 0)
            dfs_mic(i, vizitat, stiva);
    while(stiva.empty() == 0)
    {
        g<<stiva.top()<<" ";
        stiva.pop();
    }
}

///------------------------------------------------------------------------CTC

void graf::DFS_CTC(int nod, vector<int>&vizitat, stack<int> &st){
    int i = 0, urm;
    vizitat[nod] = 1;

    int marime;
    marime = lista_muchii[nod].size();
    for(i = 0; i < marime; i++)
    {
        urm = lista_muchii[nod][i];
        if(!vizitat[urm])
            DFS_CTC(urm, vizitat, st);
    }
    st.push(nod);
}
void graf::DFS_TR(int nod, vector<int> &vizitat, int nr, vector<vector<int>>&CTC){
    int i, urm;
    vizitat[nod] = 2;
    CTC[nr].push_back(nod);
    int marime = lista_muchii_transpusa[nod].size();
    for(i = 0; i < marime; i++)
        {
            urm = lista_muchii_transpusa[nod][i];
            if(vizitat[urm] == 1)
                DFS_TR(urm, vizitat, nr, CTC);
}
}
void graf::CTCC(){
    int i = 0,nod, nr = 0;
    vector<vector<int>> CTC;
    stack<int> st;
    while(!st.empty())
        st.pop();
    vector<int> vizitat;
    for(i = 1; i <= nr_noduri; i++)
        vizitat.push_back(0);
    for(i = 1; i <= nr_noduri; i++)
        if(vizitat[i] == 0)
            DFS_CTC(i,vizitat, st);
    while(!st.empty())
    {
        int nod = st.top();
        if(vizitat[nod] == 1)
        {
            nr++;
            DFS_TR(nod, vizitat, nr, CTC);
        }
        st.pop();
    }
    g<<nr<<"\n";
    for(i = 1; i <= nr; i++)
        {
            int marime = CTC[i].size();
            for(int j = 0; j < marime; j++)
            g<<CTC[i][j]<<" ";
        g<<"\n";
        }
}

///----------------------------------------------------------------------APM
void graf::APM()
{
    int i = 0, urm, nod, j;
    int minn = INT_MAX, minni;

    vector <int> parinte;
    vector <int> situatie;
    vector <int> vizitat;

    do
    {
        situatie.push_back(INT_MAX);
        vizitat.push_back(0);
        parinte.push_back(0);
        i++;
    }
    while(i <= nr_noduri + 1);

    situatie[1] = 0;
    parinte[1] = -1;

    for(i = 1; i <= nr_noduri; i++)
    {
        minn = INT_MAX;
        for(nod = 1; nod <= nr_noduri; nod++)
            if(vizitat[nod] == 0)
                if(situatie[nod] < minn)
                {
                    minn = situatie[nod];
                    minni = nod;
                }
        vizitat[minni] = 1;

        int marime = lista_cu_costuri[minni].size();

        for(j = 0; j < marime; j++)
            if(vizitat[lista_cu_costuri[minni][j].first] == 0 && lista_cu_costuri[minni][j].second < situatie[lista_cu_costuri[minni][j].first])
            {
                parinte[lista_cu_costuri[minni][j].first] = minni;
                situatie[lista_cu_costuri[minni][j].first] = lista_cu_costuri[minni][j].second;

            }
    }
    int cost_total = 0;

    for(i = 1; i <= nr_noduri; i++)
        cost_total += situatie[i];

    g<<cost_total<<"\n"<<nr_noduri - 1 <<"\n";
    for(i = 2; i <= nr_noduri; i++)
        g<<parinte[i]<<" "<<i<<"\n";

}
///----------------------------------------------------------------------ROY FLOYD
void graf::RF()
{
    int i, j, k;

    for(i = 1; i <= nr_noduri; i++)
        for(j = 1; j <= nr_noduri; j++)
            for(k = 1; k <= nr_noduri; k++)
                if(matrice[j][i] && matrice[i][k] && (matrice[j][k] > matrice[j][i] + matrice[i][k] || !matrice[j][k]) && j != k )
                    matrice[j][k] = matrice[j][i] + matrice[i][k];

    for(i = 1; i <= nr_noduri; i++)
    {
        for(j = 1; j <= nr_noduri; j++)
            g<<matrice[i][j]<<" ";
        g<<"\n";
    }
}
///----------------------------------------------------------------------Diametru
void graf::dfs1(int nod, int nr, vector<bool> &vizitat, int &maxx, int &x)
{
    vizitat[nod] = 1;
    nr++;
    for(auto j = lista_muchii[nod].begin(); j != lista_muchii[nod].end(); j++)
        if(vizitat[*j] == 0)
        {
            if(nr >= maxx)
            {
                maxx = nr;
                x = *j;
            }
            dfs1(*j, nr, vizitat, maxx, x);
        }
}
void graf::diametru()
{
    vector<bool> vizitat;
    vector<bool> vizitat2;
    int nr = 0, maxx = INT_MIN, x = 0, i = 0;

    for(i = 0; i <= nr_noduri; i++)
        vizitat.push_back(0);
    dfs1(1, nr + 1, vizitat, maxx, x);


    nr = 0;

    for(i = 0; i <= nr_noduri; i++)
        vizitat2.push_back(0);
    dfs1(x, nr + 1, vizitat2, maxx, x);

    g<<maxx;


}
///----------------------------------------------------------------------Paduri de multimi disjuncte
void graf::disj()
{
    int i, j, rez, aux, rez2, aux2;;
    vector<int>rang;
    vector<int>point;
    for(i = 1; i <= nr_noduri; i++)
    {
        point.push_back(i);
        rang.push_back(1);
    }
    for(i = 1; i <= nr_noduri; i++)
        for(j = 1; j <= lista_cu_operatii[i].size(); j++)
        {
            if(lista_cu_operatii[i][j].second == 2)
            {

                for(rez = i; point[rez] != rez; rez = point[rez]);
                for(; point[i] != i; )
                {
                    aux = point[i];
                    point[i] = rez;
                    i = aux;
                }
                for(rez2 = lista_cu_operatii[i][j].first; point[rez] != rez2; rez2 = point[rez2]);
                for(; point[lista_cu_operatii[i][j].first] != lista_cu_operatii[i][j].first; )
                {
                    aux2 = point[lista_cu_operatii[i][j].first];
                    point[lista_cu_operatii[i][j].first] = rez2;
                    lista_cu_operatii[i][j].first = aux2;
                }
                if(rez == rez2)
                    g<<"DA\n";
                else
                    g<<"NU\n";


            }
            else
            {
                for(rez = i; point[rez] != rez; rez = point[rez]);
                for(; point[i] != i; )
                {
                    aux = point[i];
                    point[i] = rez;
                    i = aux;
                }
                for(rez2 = lista_cu_operatii[i][j].first; point[rez] != rez2; rez2 = point[rez2]);
                for(; point[lista_cu_operatii[i][j].first] != lista_cu_operatii[i][j].first; )
                {
                    aux2 = point[lista_cu_operatii[i][j].first];
                    point[lista_cu_operatii[i][j].first] = rez2;
                    lista_cu_operatii[i][j].first = aux2;
                }
                if(rez == rez2)
                {
                    g<<i<<"\n";
                    //return 0;
                }
                if(rang[rez] > rang[rez2])
                    point[rez2] = rez;
                else
                    point[rez] = rez2;
                if(rang[rez] == rang[rez2])
                    rang[rez2]++;
            }
        }
}
///----------------------------------------------------------------------dijkstra
void graf::dijkstra()
{
    const int NMAX = 50005;
    const int INF = 0x3f3f3f3f;
    int nod, i, dist[NMAX] = {0};
    bool inq[NMAX] = {0};
    queue<int> q;
    q.push(1);
    memset(dist, INF, sizeof dist);
    dist[1] = 0;
    while(!q.empty())
    {
        nod = q.front();
        inq[nod] = 0;
        q.pop();
        for(vector<pair<int, int>>::iterator it = lista_dijkstra[nod].begin(); it != lista_dijkstra[nod].end(); ++it)
        {
            int nod2 = it->first;
            int cost = it->second;
            if(dist[nod2] > dist[nod] + cost)
            {
                dist[nod2] = dist[nod] + cost;
                if(!inq[nod2])
                {
                    inq[nod2] = 1;
                    q.push(nod2);
                }
            }
        }
    }
    for(i = 2; i <= nr_noduri; i++)
    {
        if(dist[i] == INF)
            dist[i] = 0;
        g<<dist[i]<<" ";
    }


}
///----------------------------------------------------------------------cuplaj
bool graf::dfs_cuplaj(int nod, vector<int> &vizitat, int st[], int dr[])
{
    if(vizitat[nod])
        return 0;
    vizitat[nod] = 1;
    vector<int>::iterator it;
    for(it = lista_muchii[nod].begin(); it < lista_muchii[nod].end(); it++)
        if(!dr[*it])
        {
            dr[*it] = nod;
            st[nod] = *it;
            return 1;
        }
    for(it = lista_muchii[nod].begin(); it < lista_muchii[nod].end(); it++)
        if(dfs_cuplaj(dr[*it], vizitat, st, dr))
        {
            dr[*it] = nod;
            st[nod] = *it;
            return 1;
        }
    return 0;

}

void graf::cuplaj()
{
    vector <pair<int, int>> cuplajj;
    vector <int> vizitat;
    int st[10001] = {0}, dr[10001] {0}, i, ok = 1;
    for(i = 1; i <= nr_noduri; i++)
        vizitat.push_back(0);
    while(ok)
    {
        ok = 0;
        for(i = 1; i <= nr_noduri; i++)
            vizitat[i] = 0;

        for(i = 1; i <= nr_noduri; i++)
            if(st[i] == 0)
                if(dfs_cuplaj(i, vizitat, st, dr) == 1)
                    ok = 1;
    }
    for(i = 1; i <= nr_noduri; i++)
        if(st[i])
        cuplajj.push_back(make_pair(i,st[i]));
    g<<cuplajj.size()<<"\n";
    int marime = cuplajj.size();
    for(i = 0; i < marime; i++)
        g<<cuplajj[i].first<<" "<<cuplajj[i].second<<"\n";

}
int main()
{
    int n, m, s;
    f>>n>>m;
    //------------------------|
    //graf test(n,m,0);       |
    //test.DFS(1);            |DFS
    //------------------------|
    //------------------------|
    //graf test(n,m,1);       |
    //test.TOPO();            |TOPO
    //------------------------|
    //------------------------|
    //graf test(0,0,2);       |HH
    //test.HH();              |
    //------------------------|
    //------------------------|
    //graf test(n, m, 3);     |
    //test.CTCC();            |CTC
    //------------------------|
    //------------------------|
    //graf test(n, m, 10);    |
    //test.APM();             |APM
    //------------------------|
    //------------------------|
    //graf test(n, 0, 11);    |ROY FLOYD
    //test.RF();              |
    //------------------------|
    //------------------------|
    //graf test(n, n - 1, 0); |disjoint
    //test.diametru();        |
    //------------------------|
    //------------------------|
    //graf test(n, m, 13);    |Dijkstra
    //test.dijkstra();        |
    //------------------------|
    //------------------------|
    //graf test(n, m, 14);    |
    //test.cuplaj();          |cuplaj
    //------------------------|



    return 0;
}
