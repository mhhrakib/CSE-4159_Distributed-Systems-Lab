/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "matrix_Op.h"

/*
    takes pointer to a matrix and prints the matrix.
*/

void print_matrix(matrix *mat)
{
    int i,j;
    int cnt = 0;
    int r = mat->row;
    int c = mat->col;
    double *x = mat->mat.mat_val;

    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            printf("%lf ", x[cnt++]);
        }
        printf("\n");
    }
    printf("\n");

}

/*
    takes two integer a and b as input and returns a^b.
*/
double power(int a, int b) {
	double prod = 1.0;
	int i;
	for(int i = 0; i < b; i++) {
		prod *= a;
	}

	return prod;
}

/*
    finds minor of matrix A and stores it in matrix B.
*/
void minor(double b[100][100],double a[100][100],int i,int n)
{
    int j,l,h=0,k=0;
    for(l=1; l<n; l++)
        for( j=0; j<n; j++)
        {
            if(j == i)
                continue;
            b[h][k] = a[l][j];
            k++;
            if(k == (n-1)) {
                h++;
                k=0;
            }
        }
}

//	calculate determinant of matrix
double det(double a[100][100],int n)
{
    int i;
    double b[100][100],sum=0;
    if (n == 1)
        return a[0][0];
    else if(n == 2)
        return (a[0][0]*a[1][1]-a[0][1]*a[1][0]);
    else
        for(i=0; i<n; i++)
        {
            minor(b,a,i,n);
            sum = (double) (sum+a[0][i]* power(-1,i)*det(b,(n-1)));	// sum = determinant matrix
        }
    return sum;
}

//	calculate transpose of matrix
void transpose(double c[100][100],double d[100][100],double n,double det)
{
    int i,j;
    double b[100][100];
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            b[i][j] = c[j][i];
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            d[i][j] = b[i][j]/det;	// array d[][] = inverse matrix
}

//	calculate cofactor of matrix
void cofactor(double a[100][100],double d[100][100],double n,double determinant)
{
    double b[100][100],c[100][100];
    int l,h,m,k,i,j;
    for (h=0; h<n; h++)
        for (l=0; l<n; l++) {
            m=0;
            k=0;
            for (i=0; i<n; i++)
                for (j=0; j<n; j++)
                    if (i != h && j != l) {
                        b[m][k]=a[i][j];
                        if (k<(n-2))
                            k++;
                        else {
                            k=0;
                            m++;
                        }
                    }
            c[h][l] = power(-1,(h+l))*det(b,(n-1));	// c = cofactor Matrix
        }
    transpose(c,d,n,determinant);
}


//	calculate inverse of matrix
void inverse(double a[100][100],double d[100][100],int n,double det)
{
    if(det == 0)
        printf("\nInverse of Entered Matrix is not possible\n");
    else if(n == 1)
        d[0][0] = 1;
    else
        cofactor(a,d,n,det);
}


// server-side implementation of matrix addition
matrix *
add_1_svc(data1 *argp, struct svc_req *rqstp)
{
    static matrix  result;

    matrix A = argp->A;
    matrix B = argp->B;
    double matA[A.row][A.col];
    double matB[B.row][B.col];

    printf("printing received matrix\n");
    printf("Matrix A: \n");
    print_matrix(&A);
    printf("Matrix B: \n");
    print_matrix(&B);

    int i,j;
    int cnt = 0;
    // set matrix A
    for(i = 0; i < A.row; i++)
    {
        for(j = 0; j < A.col; j++)
        {
            matA[i][j] = A.mat.mat_val[cnt++];
        }
    }

    // set matrix B
    cnt = 0;
    for(i = 0; i < B.row; i++)
    {
        for(j = 0; j < B.col; j++)
        {
            matB[i][j] = B.mat.mat_val[cnt++];
        }
    }

    // set result in matrix C
    double matC[A.row][A.col];
    for(i = 0; i < B.row; i++)
    {
        for(j = 0; j < B.col; j++)
        {
            matC[i][j] = matA[i][j] + matB[i][j];
        }
    }

    cnt = 0;
    result.row = A.row;
    result.col = A.col;
    result.mat.mat_val = (double*) malloc(A.row*B.row*sizeof(double));
    result.mat.mat_len = A.row * B.row;

    //copy matrix C to result
    for(i = 0; i < result.row; i++)
    {
        for(j = 0; j < result.col; j++)
        {
            result.mat.mat_val[cnt++] = matC[i][j];
        }
    }
    /*
     * insert server code here
     */

    printf("printing result before sending\n\n");
    print_matrix(&result);
    return &result;
}

// server-side implementation of matrix multiplication
matrix *
mul_1_svc(data1 *argp, struct svc_req *rqstp)
{
    static matrix  result;
    matrix A = argp->A;
    matrix B = argp->B;
    double matA[A.row][A.col];
    double matB[B.row][B.col];

    printf("printing received matrix\n\n");
    printf("Matrix A: \n");
    print_matrix(&A);
    printf("Matrix B: \n");
    print_matrix(&B);

    int i,j;
    int cnt = 0;
    // set matrix A
    for(i = 0; i < A.row; i++) {
        for(j = 0; j < A.col; j++) {
            matA[i][j] = A.mat.mat_val[cnt++];
        }
    }

    // set matrix B
    cnt = 0;
    for(i = 0; i < B.row; i++) {
        for(j = 0; j < B.col; j++) {
            matB[i][j] = B.mat.mat_val[cnt++];
        }
    }

    // set result in matrix C
    double matC[A.row][B.col];
    int k, sum = 0;
    for(i = 0; i < A.row; i++)
    {
        for(j = 0; j < B.col; j++)
        {
            for(k = 0; k < A.col; k++)
            {
                sum += matA[i][k] * matB[k][j];
            }
            matC[i][j] = sum;
            sum = 0;
        }
    }

    result.row = A.row;
    result.col = B.col;
    int len = A.row * B.col;
    result.mat.mat_val = (double*) malloc(len*sizeof(double));
    result.mat.mat_len = len;

    //copy matrix C to result
    cnt = 0;
    for(i = 0; i < result.row; i++)
    {
        for(j = 0; j < result.col; j++)
        {
            result.mat.mat_val[cnt++] = matC[i][j];
        }
    }
    /*
     * insert server code here
     */
    printf("printing result before sending\n\n");
    print_matrix(&result);
    return &result;
}


// server-side implementation of matrix inverse
matrix *
inv_1_svc(data2 *argp, struct svc_req *rqstp)
{
    static matrix  result;

    matrix A = argp->A;
    double matA[A.row][A.col];

    printf("printing received matrix\n\n");
    printf("Matrix A: \n");
    print_matrix(&A);

    int i,j;
    int cnt = 0;
    /// set matrix A
    for(i = 0; i < A.row; i++)
    {
        for(j = 0; j < A.col; j++)
        {
            matA[i][j] = A.mat.mat_val[cnt++];
        }
    }

    ///calculating inverse matrix
    double a[100][100],d[100][100],deter;
    for(i = 0; i < A.row; i++)
    {
        for(j = 0; j < A.col; j++)
        {
            a[i][j] = matA[i][j];
        }
    }

    deter =  det(a,A.row);
    inverse(a,d,A.row,deter);

    double matC[A.col][A.row];
    for(i = 0; i < A.row; i++)
    {
        for(j = 0; j < A.col; j++)
        {
            matC[i][j] = d[i][j];
        }
    }

    result.row = A.col;
    result.col = A.row;
    int len = A.row * A.col;
    result.mat.mat_val = (double*) malloc(len*sizeof(double));
    result.mat.mat_len = len;

    //copy matrix C to result
    cnt = 0;
    for(i = 0; i < result.row; i++)
    {
        for(j = 0; j < result.col; j++)
        {
            result.mat.mat_val[cnt++] = matC[i][j];
        }
    }
	printf("printing result before sending\n\n");
    print_matrix(&result);

    /*
     * insert server code here
     */

    return &result;
}


// server-side implementation of matrix transpose
matrix *
tra_1_svc(data2 *argp, struct svc_req *rqstp)
{
    static matrix result;
    matrix A = argp->A;
    double matA[A.row][A.col];

    printf("printing received matrix\n\n");
    printf("Matrix A: \n");
    print_matrix(&A);

    int i,j;
    int cnt = 0;
    /// set matrix A
    for(i = 0; i < A.row; i++)
    {
        for(j = 0; j < A.col; j++)
        {
            matA[i][j] = A.mat.mat_val[cnt++];
        }
    }

    ///matC will contain transpose matrix hence dimension inverted
    double matC[A.col][A.row];
    for(i = 0; i < A.col; i++)
    {
        for(j = 0; j < A.row; j++)
        {
            matC[i][j] = matA[j][i];
        }
    }

    result.row = A.col;
    result.col = A.row;
    int len = A.row * A.col;
    result.mat.mat_val = (double*) malloc(len*sizeof(double));
    result.mat.mat_len = len;

    //copy matrix C to result
    cnt = 0;
    for(i = 0; i < result.row; i++)
    {
        for(j = 0; j < result.col; j++)
        {
            result.mat.mat_val[cnt++] = matC[i][j];
        }
    }


    /*
     * insert server code here
     */
    printf("printing result before sending\n\n");
    print_matrix(&result);
    return &result;
}