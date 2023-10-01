#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int m, n;
int matrix[100][100];
int array[10000];
FILE *out;

void printMatrix(){

    out = fopen("spiralMatrix.txt", "w");
    if (out == NULL) {
        printf("File does not exist!");
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            printf ("%*d ",3,  matrix[i][j]);
            fflush(out);
            fprintf(out, "%*d ",3,  matrix[i][j]);
        }
        fflush(out);
        printf("\n");
        fprintf(out, "\n");
    }
    fclose(out);
}

void createMatrix(){
    printf ("input matrix size N x M (<= 100x100) \n");
    scanf ("%d%d", &n, &m);
    srand(time(NULL));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            matrix[i][j] = rand() % 999 + 1;
        }
    }
    printMatrix();
    printf ("\n");
}

void create1dMatrix(){

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            array[i*m+j] = matrix[i][j];
        }
    }
    /*for (int i = 0; i < n*m; i++){
        printf ("%d ", array[i]);
    }
    printf("\n");
    printf("\n");*/
}

void insertionSort(int arr[], int length){
    int currentElement, j;
    for (int i = 1; i < length; ++i){
        currentElement = arr[i];
        j = i - 1;
        while ((j >= 0) && (arr[j] > currentElement)){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = currentElement;
    }

}

void createSpiral(int endRowIdx, int endColumnIdx){
    int iterator1D = 0;
    int startRowIdx = 0;
    int startColumnIdx = 0;

    while ((startRowIdx < endRowIdx) && (startColumnIdx < endColumnIdx)){
        for (int i = startColumnIdx; i < endColumnIdx; ++i){
            matrix[startRowIdx][i] = array[iterator1D];
            iterator1D++;
        }
        startRowIdx++;

        for (int i = startRowIdx; i < endRowIdx; ++i){
            matrix[i][endColumnIdx - 1] = array[iterator1D];
            iterator1D++;
        }
        endColumnIdx--;

        if (startRowIdx < endRowIdx){
            for (int i = endColumnIdx - 1 ; i >= startColumnIdx; --i){
                matrix[endRowIdx - 1][i] = array[iterator1D];
                iterator1D++;
            }
            endRowIdx--;
        }

        if (startColumnIdx < endColumnIdx){
            for (int i = endRowIdx - 1; i >= startRowIdx; i--){
                matrix[i][startColumnIdx] = array[iterator1D];
                iterator1D++;
            }
            startColumnIdx++;
        }
    }
    printMatrix();
}

int main() {
    createMatrix();
    create1dMatrix();
    insertionSort(array, n*m);
    createSpiral(n,m);
    return 0;
}
