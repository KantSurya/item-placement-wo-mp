
int seed=12345678;
const int inf = 1e9;


int ROWS = 50, COLS = 50; 
int docking_time = 1;    //==> T ==> dist + D 
int num_of_robots = 5;
int num_of_orders;
double velocity = 5;
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
double PMUTATION_RSM;
double PMUTATION_PSM;

vector<Genotype>population;



