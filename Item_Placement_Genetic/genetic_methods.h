void initialize(int rows, int cols){
    // Genetic variables
    POPSIZE = 4 * num_of_orders;
    MAXGENS = 30;
    PMUTATION = 0.5;

    population.clear();
    population = vector<Genotype>(POPSIZE);
    
    // Initialize with random population
    for(int i = 0 ; i < POPSIZE ; ++i){
        population[i] = Genotype(GetRandomMember(rows,cols));
        population[i].fitness = GetFitness(population[i].Warehouse,allOrders);
    }

    // TODO : Figure out why 0th population is coming as infinity
    population[0].fitness = GetFitness(population[0].Warehouse,allOrders);
}

double GetFitness(vector<vi>warehouse,vector<Order> allOrders){
    // TODO : implement me 
    find_best_path(allOrders,warehouse);
    double t = cater_orders(allOrders);
    return (1.0)/t;
}

/*
    MUTATION
*/

// Implemented for Distinct item in each cell. 
void mutation_rsm(vector<vector<int>>&warehouse){
    int n = warehouse.size();
    if(n<1){
        warehouse = vector<vi>(1,vi(1,-1));
        _error("Empty warehouse provided for mutation");
        return;
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
}


void mutation_psm(vector<vi>&warehouse){
    // TODO : implement me
    return {};
}

// Implemented for Distinct item in each cell. 
vector<vi> crossover(vector<vi>&parentA, vector<vi>&parentB){
    int n = parentA.size();
    if(n<1){
        return {{-1}};
    }
    int m = parentA[0].size();
    
    vector<vi>child(n,vi(m));
    Cell i = Cell(0,0);

    map< int, Cell >itemIndexA, itemIndexB;
    set<int>itemSet;

    fi(0,n-1){
        fj(0,m-1){
            itemSet.insert(parentB[i][j]);

            itemIndexB[ parentB[i][j] ] = Cell(i,j);
            itemIndexA[ parentA[i][j] ] = Cell(i,j);
        }
    }
    
    Cell startInd = GetRandomCell(n,m);
    Cell invalidInd = Cell(-1,-1);

    int currItem = parentA[startInd.x][startInd.y];
    child[i.x][i.y] = currItem;

    i = GetNextCell(i,n,m);
    itemSet.erase(currItem);

    while(itemSet.size()>0){
        Cell nextCellA = GetNextCell(itemIndexA[currItem],n,m);
        Cell nextCellB = GetNextCell(itemIndexB[currItem],n,m);

        itemIndexA[currItem] = invalidInd;
        itemIndexB[currItem] = invalidInd;

        int nextItemA = parentA[nextCellA.x][nextCellA.y];
        int nextItemB = parentB[nextCellB.x][nextCellB.y];

        // keep incrementing the index untill cell with item is found
        while( IsEqualCell(itemIndexA[nextItemA] , invalidInd)){
            nextCellA = GetNextCell(nextCellA,n,m);
            nextItemA = parentA[nextCellA.x][nextCellA.y];
        }
    
        while( IsEqualCell(itemIndexB[nextItemB] , invalidInd)){
            nextCellB = GetNextCell(nextCellB,n,m);
            nextItemB = parentB[nextCellB.x][nextCellB.y];
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

int roulette_wheel_selection(vector<pair<double,int>>&probability)
{
    int n=probability.size();
    double rand=r8_uniform_ab(0.0,1.0);
    int lo=0,hi=n-1;
    // TTTTTFFFF
    
    while(lo<hi)
    {
        int mid=(lo+hi+1)/2;
        if(rand<=probability[mid].first)
            lo=mid;
        else
            hi=mid-1;
    }

    return probability[lo].second;
}


vector<pair<int,int>> select_parent_pairs(int numParents)
{
    vector<pair<int,int>>parents;
    double TOP=0.1;
    int num_top=TOP*POPSIZE;
    double sum_top=0,sum_bottom=0;
    vector<pair<double,int>>probability_top,probability_bottom;

    for(int i = 0 ; i < POPSIZE ; i++ ){
        if( i < num_top )
            sum_top += population[i].fitness;
        else
            sum_bottom += population[i].fitness;
    }

    for(int i=0;i<POPSIZE;i++){
        if(i<num_top)
            probability_top.push_back({population[i].fitness/sum_top,i});
        else
            probability_bottom.push_back({population[i].fitness/sum_bottom,i});
    }

    for(int i=1;i<probability_top.size();i++)
        probability_top[i].first+=probability_top[i-1].first;

    for(int i=1;i<probability_bottom.size();i++)
        probability_bottom[i].first+=probability_bottom[i-1].first;

    for(int i=0;i<numParents;i++){
        int parent1=roulette_wheel_selection(probability_top);
        int parent2=roulette_wheel_selection(probability_bottom);

        parents.push_back({parent1,parent2});
    }
    return parents;
}

void keepTheBest(vector<Genotype>&new_population)
{
    sort(new_population.begin(),new_population.end(),[](const struct Genotype& a, const struct Genotype& b)->bool{
        return a.fitness>b.fitness;
    });

    for(int i=0;i<POPSIZE;i++){
        population[i]=new_population[i];
    }
}

void report ( int generation )
{
    int bestMember=-1;
    double bestFitness;

    for(int i = 0; i < POPSIZE; i++)
    {
        if( bestMember ==-1 || population[i].fitness > bestFitness )
        {
            bestMember = i;
            bestFitness = population[i].fitness;
        }
    }   

    double catering_time = 1.0 / (bestFitness*1.0);
    catering_time = ( catering_time * 1.0 ) / (velocity*1.0);

    cout << "Generation " << generation << "  ---->  " << catering_time << " mins\n" ; 

}