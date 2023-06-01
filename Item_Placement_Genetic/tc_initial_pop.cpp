/*
Input Format

ROWS COLUMNS DOCKING_TIME VELCOCITY ROBOT_CAPACITY
NUM_OF_ROBOTS NUM_OF_ORDERS 
TOTAL_NUM_ITEMS

(for each of next TOTAL_NUM_ITEMS)
    NUM_CELLS_FOR_ITEM
    (for each of next NUM_CELLS_FOR_ITEM)
        COORD_X COORD_Y

(for each of next NUM_OF_ORDERS)
    SIZE_OF_NEW_ORDER
    (for each of next SIZE_OF_NEW_ORDER)
        ITEM_NUMBER
*/

/*
Docking time ==> time required pick a single item from rack/cell
    t = dist/v + x*d    
    v*t = dist + x*d*v ==> sanity check to reduce precision issue (temprory solution)
                    d*v = 12 // taking d as 9s and v as 80.4672metre/minute
*/

/*
(Total Items in warehouse) * (Avg cells at which an item is stored) = (Total cells in warehouse) * (Capacity of each cell)
Assuming (Capacity of each cell) = 30
    ==> (Total Items in warehouse) * ((1+5)/2) = (250*250) * (30)
    ==> (Total Items in warehouse) = 6*10^5
*/

/*
    Warehouse size : 250*250        //810,000 sq ft => 900ft x 900ft => 270m x 270m ~~ 250m x 250m 
    robot velocity : 80.4672 metre/minute
    no. of robots  : 800            // 800 robots can be deployed in one floor
    no. of orders  : 1.6*10^5       // max number of orders a warehouse receives in a day
                                    // amazon gets 1.6 million orders per day, but a warehouse will cater smaller no. of orders
    robot capacity : 10             // robot can pick 15 items at total
    docking time   : no data 
                     taking it as 9s = 0.15minutes => d*v = 12.07, round off to 12 
    Total items    : 6*10^5         // Total number of distinct items in warehouse
*/

#include<bits/stdc++.h>
using namespace std;
#define FASTIO	ios_base::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T>
T rand(T a, T b) {
    return uniform_int_distribution<T>(a, b)(rng);
}
template<class T>
T rand() {
    return uniform_int_distribution<T>()(rng);
}

const int max_docking_time = 12;        
const int max_number_robots = 5;      
const int max_number_order = 100;   
const int max_order_size = 5;
const double max_velocity = 80.4672;  // metre/min
int capacity_of_robot = 6;  
const int max_cells_in_item = 1;  


int ROWS = 50, COLS = 50;     // 250m x 250m 
int docking_time;    //==> T ==> dist + D 
int num_of_robots;
int num_of_orders;
double velocity;
int number_of_total_items;
int max_number_of_total_items;




void dfs1(int v,vector<bool> &used,vector<vector<int>> &adj,vector<int> &order) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(u,used,adj,order);

    order.push_back(v);
}

void dfs2(int v,vector<bool> &used,vector<vector<int>>&adj_rev,vector<int> &component) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(u,used,adj_rev,component);
}


vector<vector<int>> generate_ini_pop(vector<vector<int>> orders,int number_of_items){
    vector<vector<int>> g(num_of_orders),g_rev(num_of_orders);
    vector<bool> used;
    for(auto &x:orders){
        int a = x[0];
        int b = x[1];
        g[a].push_back(b);
        g_rev[b].push_back(a);
    }
    used.clear();
    used.resize(number_of_items);
    vector<int> iterate_ord;
    for(int i = 0; i < number_of_items; i++){
        if(!used[i]){
            dfs1(i,used,g,iterate_ord);
        }
    }
    used.clear();
    used.resize(number_of_items);
    vector<vector<int>> mat(ROWS,vector<int>(COLS));
    int curr_i = 0,curr_j = 0;
    for(auto &x:iterate_ord){
        if(!used[x]){
            vector<int> component;
            dfs2(x,used,g_rev,component);
            for(auto &y:component){ 
                mat[curr_i][curr_j] = y;
                curr_j++;
                if(curr_j == COLS){
                    curr_i++;
                    curr_j = 0;
                }
            }
        }
    }
    return mat;
}


vector<vector<int>> take_attribute_gen_input(){
// docking_time = rand(0,max_docking_time);
    // num_of_orders = rand(1,max_number_order);
    // num_of_robots = rand(1,max_number_robots);
    // velocity = rand(()1,max_velocity);
    int t;
    cin >> t;
    cin>> ROWS >> COLS ;
    cin>> docking_time >> velocity; 
    cin >> capacity_of_robot ;
    cin>> num_of_robots >> num_of_orders ;
    cin>> number_of_total_items ;
    vector<vector<int>> order;
    for(int i = 0 ; i < num_of_orders ; ++i){
        int orderSize;
        cin >> orderSize;
        int a,b;
        cin >> a >> b;
        order.push_back({a,b});
    }

    return order;
}

void out_for_test(vector<vector<int>>order){
    // dummy -1 is printed to distinguish between multiple initial population in input text file
    cout<<-1<<endl;

    set<int> s;
    auto mat = generate_ini_pop(order,number_of_total_items);
    for(auto &x:mat){
        for(auto &y:x){ 
            cout << y << ' ';
            s.insert(y);
        }
    }
}


int main(){
    FASTIO;
    //Now run attribute generator first.
    freopen("input.txt", "r", stdin);
    freopen("init_pop_input.txt", "w", stdout);


    // no of initial population = no. of orders = no of test_cases
    vector<vector<int>>order = take_attribute_gen_input();
    int test_case = order.size();
    cout << test_case << endl;

    while(test_case--){
        out_for_test(order);
    }
}