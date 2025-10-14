// 6.1
void MySort(ElementType A[], int N)
{
    int low = 0, mid = 0, high = N - 1;
    ElementType temp;

    while (mid <= high)
    {
        if (A[mid] == false)
        {
            temp = A[low];
            A[low] = A[mid];
            A[mid] = temp;
            low++;
            mid++;
        }
        else if (A[mid] == maybe)
        {
            mid++;
        }
        else
        {
            temp = A[mid];
            A[mid] = A[high];
            A[high] = temp;
            high--;
        }
    }
}

// 6.2
void merge_pass(ElementType list[], ElementType sorted[], int N, int length)
{
    int i, j, k;
    int left, mid, right;
    for (left = 0; left + length < N; left = right + 1)
    {
        mid = left + length - 1;
        right = mid + length;
        if (right >= N)
            right = N - 1;
        i = left;
        j = mid + 1;
        k = left;
        while (i <= mid && j <= right)
        {
            if (list[i] <= list[j])
                sorted[k++] = list[i++];
            else
                sorted[k++] = list[j++];
        }
        while (i <= mid)
            sorted[k++] = list[i++];
        while (j <= right)
            sorted[k++] = list[j++];
    }
    if (left < N)
    {
        for (i = left; i < N; i++)
            sorted[i] = list[i];
    }
}

// 7.1
#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int a[n], pos[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        pos[a[i]] = i;
    }

    int count = 0;
    int next = 1;

    while (1)
    {
        if (pos[0] != 0)
        {
            int t = pos[0];
            int val = a[t];
            a[pos[0]] = val;
            a[t] = 0;
            pos[val] = pos[0];
            pos[0] = t;
            count++;
        }
        else
        {
            while (next < n && pos[next] == next)
                next++;
            if (next == n)
                break;
            int t = pos[next];
            a[0] = next;
            a[t] = 0;
            pos[0] = t;
            pos[next] = 0;
            count++;
        }
    }

    printf("%d", count);
    return 0;
}

// 7.2
#include <stdio.h>
int main()
{
    int n, i;
    scanf("%d", &n);
    int a[n], b[n];
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (i = 0; i < n; i++)
        scanf("%d", &b[i]);
    int idx = 1;
    while (idx < n && b[idx - 1] <= b[idx])
        idx++;
    int flag = 1;
    for (i = idx; i < n; i++)
    {
        if (a[i] != b[i])
            flag = 0;
    }

    if (flag)
    {
        printf("Insertion Sort\n");
        int key = b[idx];
        int j = idx - 1;
        while (j >= 0 && b[j] > key)
        {
            b[j + 1] = b[j];
            j--;
        }
        b[j + 1] = key;
    }
    else
    {
        printf("Merge Sort\n");
        int len = 1;
        int sorted = 1;
        while (sorted)
        {
            sorted = 0;
            for (i = 0; i < n; i++)
            {
                if (b[i] > b[i + 1] && i + 1 < n)
                {
                    sorted = 1;
                    break;
                }
            }
            if (sorted)
                len *= 2;
            else
                break;
        }
        len *= 2;
        for (i = 0; i < n; i += len)
        {
            int end = i + len < n ? i + len : n;
            for (int p = i; p < end - 1; p++)
            {
                for (int q = i; q < end - 1; q++)
                {
                    if (b[q] > b[q + 1])
                    {
                        int t = b[q];
                        b[q] = b[q + 1];
                        b[q + 1] = t;
                    }
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if (i)
            printf(" ");
        printf("%d", b[i]);
    }

    return 0;
}