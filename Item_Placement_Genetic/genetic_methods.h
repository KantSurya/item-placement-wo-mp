#include "utility.h"
#include "variables.h"


/*
    MUTATION
*/

vector<vector<int>> mutation_rsm(vector<vector<int>>warehouse){
    int n = warehouse.size();
    if(n<1){
        return warehouse;
    }
    int m = warehouse[0].size();

    Cell i = Cell();
    Cell j = Cell();

    i.Setter(rand(0,n-1) , rand(0,m-1));
    j.Setter(rand(0,n-1) , rand(0,m-1));
 
    if (j < i) {
        swap(i,j);
    }

    while( i < j ){
        swap(warehouse[i.x][i.y] , warehouse[j.x][j.y]);
        
        i = GetNextCell(i,n,m);
        j = GetPrevCell(j,n,m);
    }

    return warehouse;
}


vector<vector<int>> mutation_psm(vector<vector<int>>warehouse){
    // TODO : implement me
    return {};
}

