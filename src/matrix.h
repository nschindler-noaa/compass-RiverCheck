#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <QList>



struct matrix {
	int columns;
	int rows;
	QList <double> items;
	double at (int i, int j);
	void insert (int i, int j, double val);
};
typedef struct matrix MATRIX;

void resizeMatrix (MATRIX *mx, int colSize, int rowSize);
MATRIX *newMatrix (int col, int row, double val = 0.0);
void deleteMatrix (MATRIX *m);

#endif // _MATRIX_H_
