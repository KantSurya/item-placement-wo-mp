int dist(pair<int,int> &a,pair<int,int> &b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}


int calc(Order &order,unordered_map<int,pair<int,int>> &coord,vector<int> &perm){
    int tot = 0;
    int last = -1;

    for(auto &x:perm){
        if(last != -1){
            tot += dist(coord[order.items[last]],coord[order.items[x]]);
        }

        last = x;
    }
    
    return tot;
}

int recur(int mask,int last_element,vector<vector<int>> &dp,vector<pair<int,int>> &tmp){
    if(dp[mask][last_element] != inf) return dp[mask][last_element];
    int n = dp[0].size();
    int new_mask = (mask ^ (1<<last_element));
    for(int i = 0; i < n; i++){
        if((new_mask>>i)&1){
            dp[mask][last_element] = min(dp[mask][last_element],recur(new_mask,i,dp,tmp) + dist(tmp[last_element],tmp[i]));
        }
    }
    return dp[mask][last_element];
}

int recur_calc(vector<pair<int,int>> tmp){
    int n = tmp.size();
    int bit_mask = (1<<n);
    vector<vector<int>> dp(bit_mask,vector<int>(n,inf));
    for(int i = 0; i < n; i++){
        dp[(1<<i)][i] = 0;
    }
    int ans = inf;
    for(int i = 0; i < n; i++){
        ans = min(ans,recur((1<<n) - 1,i,dp,tmp));
    }
    return ans;

}

void find_best_path_2(vector<Order> &orders,vector<vi> &mat){
    //permutation
    unordered_map<int,pair<int,int>> m;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            m[mat[i][j]] = {i,j};
        }
    }   
    for(auto &order:orders){
        vector<pair<int,int>> tmp;
        for(auto &x:order.items) tmp.push_back(m[x]);
        order.time = recur_calc(tmp);
    }
}


void find_best_path(vector<Order> &orders,vector<vi> &mat){
    //permutation
    unordered_map<int,pair<int,int>> m;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            m[mat[i][j]] = {i,j};
        }
    }   

    for(auto &order:orders){
        int n = order.getOrderSize();
        vector<int> perm(n);
        iota(perm.begin(),perm.end(),0);

        vector<int> ans = perm;
        int best_val = calc(order,m,perm);

        do{
            int val = calc(order,m,perm);
            if(val < best_val){
                best_val = val;
                ans = perm;
            }
        }while(next_permutation(perm.begin(),perm.end()));

        vector<int> new_item = order.items;
        int ind = 0;
        for(auto &x:perm){
            new_item[ind] = order.items[x];
            ind++;
        }

        order.items = new_item;
        order.time = best_val;
    }
}

bool cmp(Order a,Order b){
    return a.time < b.time;
}

int cater_orders(vector<Order> &allOrders){
    vector<int>sortedOrders;  // Stores indices of orders sorted according to individual order total catering time.
    for(int i=0;i<allOrders.size();i++){
        sortedOrders.push_back(i);
    }

    // Priority queue will store the earliest free time of all robots
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>robotFreeTimes;

    // initially all the robots are free at t = 0
    for(int i = 0 ; i < num_of_robots ; ++i){
        robotFreeTimes.push({0,i});
    }

    int totalTime = 0;     // total time taken to cater all order
    vector<vector<int>>robotTasks(num_of_robots);

    // cater all the order one by one
    // allot the earliest free robot to current order
    num_of_orders = allOrders.size();

    for(int i = 0 ; i < num_of_orders ; ++i){
        // pick the earliest free robot 
        int earliestFreeRobot=robotFreeTimes.top().second;
        int freeTime=robotFreeTimes.top().first;
        
        robotFreeTimes.pop();
        robotTasks[earliestFreeRobot].push_back(sortedOrders[i]);

        // assign ith task to that robot
        int cateringTime = allOrders[sortedOrders[i]].time;
        int finishTime = freeTime + cateringTime;
        totalTime = max(totalTime,finishTime);

        // current robot will be free after finishing the ith task
        robotFreeTimes.push({finishTime,earliestFreeRobot});
    }
    return totalTime;
}


void merge_order(vector<Order> &allorders){
    //to do implement
}
