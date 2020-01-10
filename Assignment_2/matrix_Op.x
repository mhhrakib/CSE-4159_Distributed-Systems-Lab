const sz = 50;
struct matrix {
	int row;
	int col;
	double mat<sz>;
};

typedef struct matrix matrix;
	
struct data1 {
    matrix A;
    matrix B;
    char operator;
};

struct data2 {
    matrix A;
    char operator;
};

program CALCULATE_PROG {
    version CALCULATE_VER {
        matrix ADD(data1)=1;
        matrix MUL(data1)=2;
        matrix INV(data2)=3;
        matrix TRA(data2)=4;
    }=1;
}=0x2fffffff;
