/*并查集*/
#ifndef UFSET_H
#define UFSET_H
#include <string.h>
//并查集
class UFSet
{
    public:
        UFSet(int sz = 10);                                 //构造函数
        ~UFSet() {delete[] parent;}                         //析构函数
        UFSet &operator = (const UFSet &R);                 //重载赋值：集合赋值
        void Union(int root1, int root2);                   //两个子集合并
        int find(int x);                                    //搜寻集合x的根
        void weightedUnion(int root1, int root2);           //加权的合并算法

    private:
        int *parent;                                        //集合元素数组(父指针数组)
        int size;                                           //集合元素的数目
};

//构造函数：sz为集合元素个数。数组范围：0 ~ size-1
UFSet::UFSet(int sz)
{
    size = sz;                                              //集合元素个数
    parent = new int[size];                                 //创建父指针数组
    memset(parent, -1, sizeof(int) * size);                 //每个自成单元素集合
}

//搜索并返回包含元素x的树的根
int UFSet::find(int x)
{
    while (parent[x] >= 0) x = parent[x];                   //循环寻找x的根
    return x;                                               //根的parent[]值小于0
}

//求两个不相交集合的并。要求root1和root2是不同的，且表示了子集合的名字
void UFSet::Union(int root1, int root2)
{
    parent[root1] += parent[root2];
    parent[root2] = root1;
}

//使用结点个数探查方法求两个UFSet集合的并
void UFSet::weightedUnion(int root1, int root2)
{
    int r1 = find(root1), r2 = find(root2), temp;
    if (r1 != r2) temp = parent[r1] + parent[r2];           //以r2为根的树的结点多
    if (parent[r2] < parent[r1])
        {parent[r1] = r2; parent[r2] = temp;}               //让r1接在r2下面
    else {parent[r2] = r1; parent[r1] = temp;}              //让r1成为新的根
}
#endif  //UFSET_H