#include "/home/WJFeng/dataStruct/List/List.h"

int main()
{
    LTNode* phead = ListInit();
    ListPushBack(phead, 1);
    ListPushBack(phead, 2);
    ListPushBack(phead, 3);
    ListPushBack(phead, 4);
    ListPushBack(phead, 5);
    ListPrint(phead);
    return 0;
}
