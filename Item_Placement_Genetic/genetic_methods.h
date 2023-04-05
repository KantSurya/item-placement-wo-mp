#include "utility.h"
#include "variables.h"


/*
    MUTATION
*/

vector<vector<int>> mutation_rsm(vector<vector<int>>warehouse){
    Cell i = Cell();
    Cell j = Cell();

    i.Setter(rand(0,ROWS) , rand(0,COLS));
    j.Setter(rand(0,ROWS) , rand(0,COLS));

    if (j < i) {
        swap(i,j);
    }

    while( i < j ){
        swap(warehouse[i.x][i.y] , warehouse[j.x][j.y]);
        i = GetNextCell(i,ROWS,COLS);
        j = GetPrevCell(j,ROWS,COLS);
    }

    return warehouse;
}


