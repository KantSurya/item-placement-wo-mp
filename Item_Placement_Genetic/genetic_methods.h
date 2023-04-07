/*
    MUTATION
*/

// Implemented for Distinct item in each cell. 
vector<vector<int>> mutation_rsm(vector<vector<int>>warehouse){
    int n = warehouse.size();
    if(n<1){
        return warehouse;
    }
    int m = warehouse[0].size();

    Cell i = GetRandomCell(n,m);
    Cell j = GetRandomCell(n,m);

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


vector<vi> mutation_psm(vector<vi>warehouse){
    // TODO : implement me
    return {};
}

// Implemented for Distinct item in each cell. 
vector<vi> crossover(vector<vi> a, vector<vi> b){
    int n = a.size();
    if(n<1){
        return {{-1}};
    }
    int m = a[0].size();

    vector<vi>child(n,vi(m));
    Cell i = Cell(0,0);

    map< int, Cell >itemIndexA, itemIndexB;
    set<int>itemSet;

    fi(0,n-1){
        fj(0,m-1){
            itemSet.insert(b[i][j]);

            itemIndexB[ b[i][j] ] = Cell(i,j);
            itemIndexA[ a[i][j] ] = Cell(i,j);
        }
    }
    
    Cell startInd = GetRandomCell(n,m);
    Cell invalidInd = Cell(-1,-1);

    int currItem = a[startInd.x][startInd.y];
    child[i.x][i.y] = currItem;

    i = GetNextCell(i,n,m);
    itemSet.erase(currItem);

    while(itemSet.size()>0){
        Cell nextCellA = GetNextCell(itemIndexA[currItem],n,m);
        Cell nextCellB = GetNextCell(itemIndexB[currItem],n,m);

        itemIndexA[currItem] = invalidInd;
        itemIndexB[currItem] = invalidInd;

        int nextItemA = a[nextCellA.x][nextCellA.y];
        int nextItemB = b[nextCellB.x][nextCellB.y];

        // keep incrementing the index untill cell with item is found
        while( IsEqualCell(itemIndexA[nextItemA] , invalidInd)){
            nextCellA = GetNextCell(nextCellA,n,m);
            nextItemA = a[nextCellA.x][nextCellA.y];
        }
    
        while( IsEqualCell(itemIndexB[nextItemB] , invalidInd)){
            nextCellB = GetNextCell(nextCellB,n,m);
            nextItemB = b[nextCellB.x][nextCellB.y];
        }

        int nextItem = nextItemA;
        if(distance(i,nextCellB) < distance(i,nextCellA)){
            nextItem = nextItemB;
        }

        child[i.x][i.y] = nextItem;
        i = GetNextCell(i,n,m);

        currItem = nextItem;
        itemSet.erase(currItem);
    }
    return child;  
}
