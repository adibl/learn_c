
int binsearch(int x, int v[], int n);

main()
{
    int len = 1000000;
    int arr[len];
    int i;
    for (i = 0; i < len; i++) {
        arr[i] = i;
    }
    binsearch(-1, arr, len);

}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high && x != v[mid]) {
        if (x < v[mid])
            high = mid - 1;
        else 
            low = mid + 1;
        mid = (low+high)/2;
    }
    if (x = v[mid])
        return mid;
    return -1;
}
