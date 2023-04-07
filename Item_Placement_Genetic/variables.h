

int ROWS = 250, COLS = 250;     // 250m x 250m 
int docking_time;    //==> T ==> dist + D 
int num_of_robots;
int num_of_orders;
double velocity;
int number_of_total_items;

vector<Order>allOrders;
vector<Item>allItems;



/*
    Genetic Variables
*/
int POPSIZE;
int MAXGENS;
double PMUTATION;

vector<Genotype>population;
