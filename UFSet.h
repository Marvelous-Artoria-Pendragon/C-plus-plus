/*���鼯*/
#ifndef UFSET_H
#define UFSET_H
#include <string.h>
//���鼯
class UFSet
{
    public:
        UFSet(int sz = 10);                                 //���캯��
        ~UFSet() {delete[] parent;}                         //��������
        UFSet &operator = (const UFSet &R);                 //���ظ�ֵ�����ϸ�ֵ
        void Union(int root1, int root2);                   //�����Ӽ��ϲ�
        int find(int x);                                    //��Ѱ����x�ĸ�
        void weightedUnion(int root1, int root2);           //��Ȩ�ĺϲ��㷨

    private:
        int *parent;                                        //����Ԫ������(��ָ������)
        int size;                                           //����Ԫ�ص���Ŀ
};

//���캯����szΪ����Ԫ�ظ��������鷶Χ��0 ~ size-1
UFSet::UFSet(int sz)
{
    size = sz;                                              //����Ԫ�ظ���
    parent = new int[size];                                 //������ָ������
    memset(parent, -1, sizeof(int) * size);                 //ÿ���Գɵ�Ԫ�ؼ���
}

//���������ذ���Ԫ��x�����ĸ�
int UFSet::find(int x)
{
    while (parent[x] >= 0) x = parent[x];                   //ѭ��Ѱ��x�ĸ�
    return x;                                               //����parent[]ֵС��0
}

//���������ཻ���ϵĲ���Ҫ��root1��root2�ǲ�ͬ�ģ��ұ�ʾ���Ӽ��ϵ�����
void UFSet::Union(int root1, int root2)
{
    parent[root1] += parent[root2];
    parent[root2] = root1;
}

//ʹ�ý�����̽�鷽��������UFSet���ϵĲ�
void UFSet::weightedUnion(int root1, int root2)
{
    int r1 = find(root1), r2 = find(root2), temp;
    if (r1 != r2) temp = parent[r1] + parent[r2];           //��r2Ϊ�������Ľ���
    if (parent[r2] < parent[r1])
        {parent[r1] = r2; parent[r2] = temp;}               //��r1����r2����
    else {parent[r2] = r1; parent[r1] = temp;}              //��r1��Ϊ�µĸ�
}
#endif  //UFSET_H