
int seed=12345678;


int ROWS = 250, COLS = 250;     // 250m x 250m 
int docking_time;    //==> T ==> dist + D 
int num_of_robots;
int num_of_orders;
double velocity;
/*
    TODO : Discuss 
        total number of items and items in cell 
        if each cell has distinct item :- 
            no of distinct items = ROWS * COLS 
*/
int number_of_total_items;
int capacity_of_robot;

vector<Order>allOrders;
vector<Item>allItems;



/*
    Genetic Variables
*/
int POPSIZE;
int MAXGENS;
double PMUTATION;

vector<Genotype>population;



