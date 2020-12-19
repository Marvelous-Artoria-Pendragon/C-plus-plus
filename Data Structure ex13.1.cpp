/*分别写出用 prim 和 Kruskal 算法求最小生成树*/
#include <iostream>
#include "MinSpanTree.h"
using namespace std;


int main()
{
    Graphlnk<int, int> G; cin >> G;
    
    MinSpanTree<int, int> *M = new MinSpanTree<int, int>(G.Vertices());
    cout << "Kruskal算法：\n";
    Kruskal(G, *M);
    cout << *M << endl;
    delete M;
    
    M = new MinSpanTree<int, int>(G.Vertices());
    cout << "Prim算法：\n";
    Prim(G, 0, *M);
    cout << *M << endl;
    delete M;
    system("pause");
    return 0;
}

/*
7
0 1 2 3 4 5 6
9
0 1 28
0 5 10
1 2 16
1 6 14
2 3 12
3 6 18
3 4 22
4 6 24
4 5 25
*/