double FindMaxRec ( const double arr[ ],  int   low, int   high, int   maxInd) {
    if(low == high) {
        return arr[maxInd];
    }
    else {
        if(arr[maxInd] < arr[low]){
            maxInd = low;
        }
        return FindMaxRec(arr, low+1, high, maxInd);
    }
}