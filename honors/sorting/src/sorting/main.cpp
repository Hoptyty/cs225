#include <iostream>
#include "sorting.h"
using namespace std;
using std::cout;
using std::endl;

int main()
{
    std::vector< vector <int> > n6;
    std::vector< int > a;
    for (int i = 0; i < 6; i++)
        a.push_back(i);
    std::vector< int > b;
    b.push_back(0);
    b.push_back(2);
    b.push_back(3);
    b.push_back(5);
    std::vector< int > c;
    c.push_back(1);
    c.push_back(4);
    std::vector< int > d;
    for (int i = 0; i < 6; i++)
        d.push_back(i);
    std::vector< int > e;
    for (int i = 1; i < 5; i++)
        e.push_back(i);
    std::vector< int > f;
    f.push_back(2);
    f.push_back(3);
    n6.push_back(a);
    n6.push_back(b);
    n6.push_back(c);
    n6.push_back(d);
    n6.push_back(e);
    n6.push_back(f);
    std::vector< int > arr;
    arr.push_back(3);
    arr.push_back(543);
    arr.push_back(6);
    arr.push_back(7);
    arr.push_back(234);
    arr.push_back(57);
    Sorting * haha = new Sorting ();
    haha->nSort(arr, n6);
    for (int i = 0; i < 6;i++)
        cout<<arr[i]<<endl;
    return 0;
}
