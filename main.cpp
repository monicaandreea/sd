#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
using namespace std;

//generating numbers
vector<int> teste( int &n, int &m)
{
    int i;
    vector<int> v;
    srand( time(0));

    //n = rand() % 10000000 + 1; // genereaza numarul de numere
    n=1000000;
    m=1000000;
    for( i=0 ; i<n ; i++)
        v.push_back( rand() %1000000 ); //genereaza numere mai mici ca 10^4

    return v;
}

//Bubble sort
//interschimbarea elementelor adiacente pana ajung in ordinea buna(crescatoare)
vector<int> BubbleSort(vector<int> v, int n)
{
    auto start = chrono::high_resolution_clock::now();
    int i, j;
    for( i=0 ; i<n-1 ; i++)
        for( j=0 ; j<n-i-1 ; j++)
        {
            auto timp = chrono::high_resolution_clock::now();
            auto durata = chrono::duration_cast<chrono::microseconds>(timp - start);
            if( durata.count() / 1000 > 120000) break;
            if( v[j] > v[j+1] )
                swap(v[j], v[j+1]);
        }


    return v;
}

//Counting sort
//vector de frecventa
vector<int> CountingSort(vector<int> v, int n, int m)
{
    int i;
    vector<int> frecventa(m, 0); //vector de lungime m(cel mai mare numar)

    for( i=0 ; i<n ; i++)
    {
        frecventa[v[i]]++;
        v[i] = 0;
    }

    int j=-1;
    for( i=0 ; i<m ; i++)
    {
        while(frecventa[i] > 0)
        {
            j++;
            v[j] = i;
            frecventa[i]--;
        }
    }

    return v;
}

void afisare(vector<int> v, int n)
{
    int i;
    cout<<endl<<"Vectorul initial "<<endl;
    for( i=0 ; i<n ; i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

bool verificare(vector<int> v, int n)
{
    int i;
    vector<int> copie = v;
   /* for( i=0 ; i<n ; i++)
        cout<<v[i]<<" "; */
    sort(copie.begin(), copie.end());
    for( i=0 ; i<n ; i++)
        if( copie[i] != v[i] ) return 0;

    return 1;
}

int main() {
    int n, m;
    vector <int> v, bs, cs;
    v = teste( n, m );

    /*cout << n << '\n';
    for( int i = 0; i < n; ++i )
        cout << v[i] << ' ';
    cout << '\n'; */

    cout<<"Bubble sort: ";
    auto start = chrono::high_resolution_clock::now();
    bs = BubbleSort(v, n);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() / 1000 << "ms\n";
    if( verificare(bs, n) == 1) cout<<"Vectorul a fost sortat corect.";
    else cout<<"Vectorul a fost sortat gresit.";

    cout<<endl<<"Counting sort: ";
    start = chrono::high_resolution_clock::now();
    cs = CountingSort(v, n, m);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() / 1000 << "ms\n";
    if( verificare(cs, n) == 1) cout<<"Vectorul a fost sortat corect.";
    else cout<<"Vectorul a fost sortat gresit.";
    //afisare(v, n);
    return 0;
}
