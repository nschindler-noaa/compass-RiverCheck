#include <qstring.h>
#include <QStringList>
#include <qfile.h>

#include "matrix.h"
#include "Log.h"

#define INDEX  ((i * columns) + j)

double MATRIX::at (int i, int j)
{
	int index = (i * columns) + j;
	if (index > items.count())
		return 0.0;
	return items.at (index);
}

void MATRIX::insert (int i, int j, double val)
{
	int index = (i * columns) + j;
	if (index <= items.count())
		items[index] = val;
}

MATRIX *newMatrix (int n, int m, double val)
{
	MATRIX *mx = new MATRIX;
	mx->rows = n;
	mx->columns = m;

	for (int i = 0; i < m*n; i++)
		mx->items.append (val);

	return mx;
}

void resizeMatrix (MATRIX *mx, int colSize, int rowSize)
{
	int totalItems = colSize * rowSize;
	int col, row;

	mx->columns = colSize;
	mx->rows = rowSize;

	for (row = 0; row < rowSize; row++)
		for (col = 0; col < colSize; col++)
			mx->insert (col, row, 0.0);
}

void deleteMatrix (MATRIX *mx)
{
	mx->items.clear();
//	delete mx;
//	mx = NULL;
}

