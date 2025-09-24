//6.1
Polynomial Add(Polynomial a, Polynomial b)
{
    Polynomial pa = a->Next;
    Polynomial pb = b->Next;
    Polynomial result, rear, temp;
    result = (Polynomial)malloc(sizeof(struct Node));
    result->Next = NULL;
    rear = result;
    while (pa && pb)
    {
        if (pa->Exponent > pb->Exponent)
        { // a 的指数大
            temp = (Polynomial)malloc(sizeof(struct Node));
            temp->Coefficient = pa->Coefficient;
            temp->Exponent = pa->Exponent;
            temp->Next = NULL;
            rear->Next = temp;
            rear = temp;
            pa = pa->Next;
        }
        else if (pa->Exponent < pb->Exponent)
        {
            temp = (Polynomial)malloc(sizeof(struct Node));
            temp->Coefficient = pb->Coefficient;
            temp->Exponent = pb->Exponent;
            temp->Next = NULL;
            rear->Next = temp;
            rear = temp;
            pb = pb->Next;
        }
        else
        {
            int sum = pa->Coefficient + pb->Coefficient;
            if (sum != 0)
            {
                temp = (Polynomial)malloc(sizeof(struct Node));
                temp->Coefficient = sum;
                temp->Exponent = pa->Exponent;
                temp->Next = NULL;
                rear->Next = temp;
                rear = temp;
            }
            pa = pa->Next;
            pb = pb->Next;
        }
    }
    while (pa)
    {
        temp = (Polynomial)malloc(sizeof(struct Node));
        temp->Coefficient = pa->Coefficient;
        temp->Exponent = pa->Exponent;
        temp->Next = NULL;
        rear->Next = temp;
        rear = temp;
        pa = pa->Next;
    }
    while (pb)
    {
        temp = (Polynomial)malloc(sizeof(struct Node));
        temp->Coefficient = pb->Coefficient;
        temp->Exponent = pb->Exponent;
        temp->Next = NULL;
        rear->Next = temp;
        rear = temp;
        pb = pb->Next;
    }

    return result;
}

//6.2
List Reverse( List L )
{
    Position last = NULL, curr = L->Next, next;
    while (curr!=NULL)
    {
        next = curr->Next;
        curr->Next = last;
        last = curr;
        curr = next;
    }
    L->Next = last;
    return L;
}

//6.3
void list_append(List *list, int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = list->tail;
    if (list->tail)
    {
        list->tail->next = node;
    }
    else
    {
        list->head = node;
    }
    list->tail = node;
}
void list_remove(List *list, int value)
{
    Node *p = list->head;
    while (p)
    {
        Node *next = p->next;
        if (p->value == value)
        {
            if (p->prev)
            {
                p->prev->next = p->next;
            }
            else
            {
                list->head = p->next;
            }
            if (p->next)
            {
                p->next->prev = p->prev;
            }
            else
            {
                list->tail = p->prev;
            }
            free(p);
        }
        p = next;
    }
}

//6.4
void Ranking(List A[], int n)
{
    int *isnext = (int *)calloc(n, sizeof(int *)); // 初始化全部为0
    for (int i = 0; i < n; i++)
    {
        if (A[i].next != -1)
        {
            isnext[A[i].next] = 1;
        }
    }
    int head = -1;
    for (int j = 0; j < n; j++)
    {
        if (isnext[j] == 0)
        {
            head = j;
            break;
        }
    }
    int *order = (int *)malloc(sizeof(int) * n); // 链表的顺序
    int len = 0;                                 // 链表的长度
    int cur = head;                              // 从头遍历
    while (cur != -1)
    {
        order[len++] = cur;
        cur = A[cur].next;
    }
    int r = 1;
    for (int i = len - 1; i >= 0; i--)
    {
        A[order[i]].rank = r++;
    }
    free(isnext);
    free(order);
}