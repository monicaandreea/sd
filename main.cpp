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
    n=100000;
    m=1000;
    for( i=0 ; i<n ; i++)
        v.push_back( rand() %1000 ); //genereaza numere mai mici ca 10^4

    return v;
}

//Bubble sort
//interschimbarea elementelor adiacente pana ajung in ordinea buna(crescatoare)
vector<int> BubbleSort(vector<int> v, int n)
{
    auto start = chrono::high_resolution_clock::now();
    int i, j, intrerupt = 0;
    for( i=0 ; i<n-1 ; i++)
        for( j=0 ; j<n-i-1 ; j++)
        {
            auto timp = chrono::high_resolution_clock::now();
            auto durata = chrono::duration_cast<chrono::microseconds>(timp - start);
            if( durata.count() / 1000 > 120000){intrerupt = 1; break;}
            if( v[j] > v[j+1] )
                swap(v[j], v[j+1]);
        }

    if(intrerupt==1) v[0]=-55;
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

//Radix Sort
//sorting by digits (starting with least significant)
int gasesteMaxim(vector<int> v, int n)
{
    int i, maxim = v[0];
    for( i=1 ; i<n ; i++)
        if( v[i] > maxim) maxim = v[i];

    return maxim;
}

vector<int> CountingSort_Radix(vector<int> v, int n, int m)
{
    int i;
    vector<int> frecventa(10, 0), rezultat(n, 0); //vector de lungime 10 pt 0,1,2...9

    for( i=0 ; i<n ; i++)
        frecventa[(v[i] / m)%10]++; //a m-a litera de la dreapta la stanga

    for( i=1 ; i<10 ; i++)
        frecventa[i] += frecventa[i-1]; //adaugam la poz curenta, cea anterioara pnetru a avea indicii din vector

    for( i=n-1 ; i>=0; i--) //luam de la ultimul la primul ("cel mai mare" -> "cel mai mic")
    {
        rezultat[frecventa[(v[i]/m)%10] -1] = v[i];
        //punem in rez nr curent, pe poz indicata de a m-a litera de la stanga la dreapta (-1 pentru ca incepem de la 0)
        frecventa[(v[i]/m)%10]--; //scadem frecventa => scade pozitia
    }

    for( i=0 ; i<n ; i++)
        v[i] = rezultat[i];

    return v;
}

vector<int> RadixSort(vector<int> v, int n)
{
    int i, maxim = gasesteMaxim(v, n); //maximul dintre numere ca sa stim numarul maxim de cifre

    for( i=1 ; maxim/i>0 ; i=i*10) // i reprezinta o putere a lui 10 la care impartim pt a gasi a i-a litera de la stanga la dreapta
        v= CountingSort_Radix(v, n, i);

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
    vector <int> v, bs, cs, rs;
    v = teste( n, m );

    /*cout << n << '\n';
    for( int i = 0; i < n; ++i )
        cout << v[i] << ' ';
    cout << '\n';*/

    cout<<"n = "<<n<<endl<<"m = "<<m<<endl;

    cout<<"Bubble sort: ";
    auto start = chrono::high_resolution_clock::now();
    bs = BubbleSort(v, n);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() / 1000 << "ms\n";
    if(bs[0] == -55) cout<<"Sortarea a fost oprita dupa 2 minute.";
    else if( verificare(bs, n) == 1) cout<<"Vectorul a fost sortat corect.";
        else cout<<"Vectorul a fost sortat gresit.";

    cout<<endl<<"Counting sort: ";
    start = chrono::high_resolution_clock::now();
    cs = CountingSort(v, n, m);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() / 1000 << "ms\n";
    if( verificare(cs, n) == 1) cout<<"Vectorul a fost sortat corect.";
    else cout<<"Vectorul a fost sortat gresit.";

    cout<<endl<<"Radix sort: ";
    start = chrono::high_resolution_clock::now();
    rs = RadixSort(v, n);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() / 1000 << "ms\n";
    if( verificare(cs, n) == 1) cout<<"Vectorul a fost sortat corect.";
    else cout<<"Vectorul a fost sortat gresit.";
    //afisare(v, n);
    return 0;
}
