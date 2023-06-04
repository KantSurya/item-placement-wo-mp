#include<bits/stdc++.h>
using namespace std;
#include "headers.h"


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



int main(){
    freopen("input.txt","r",stdin);
    cin >> ROWS >> COLS;
    vector<vector<int>> mat(ROWS,vector<int>(COLS));
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            cin >> mat[i][j];
        }
    }
    cin >> num_of_orders;
    allOrders = vector<Order>(num_of_orders);
    for(int i = 0 ; i < num_of_orders ; ++i){
        int orderSize;
        cin >> orderSize;

        Order currOrder;
        for(int j = 0 ; j < orderSize ; ++j){
            int o;
            cin>>o;

            currOrder.items.push_back(o);
        }

        allOrders[i] = currOrder;
    }
    find_best_path_2(allOrders,mat);
    cout << "DONE" << endl;

    return 0;
}