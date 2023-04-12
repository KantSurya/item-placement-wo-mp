#include<bits/stdc++.h>
using namespace std;
#include"structs.h"
#include"macros.h"
#include"variables.h"

int dist(pair<int,int> &a,pair<int,int> &b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}


int calc(Order &order,map<int,pair<int,int>> coord,vector<int> &perm){
    int tot = 0;
    int last = -1;
    for(auto &x:perm){
        if(last != -1){
            tot += dist(coord[order.items[perm[last]]],coord[order.items[x]]);
        }
        last = x;
    }
}

void find_best_path(vector<Order> &allorder,vector<vi> &mat){
    //permutation
    map<int,pair<int,int>> m;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            m[mat[i][j]] = {i,j};
        }
    }   
    for(auto &order:allOrders){
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
    }
}


void merge_order(vector<Order> &allorder)

int main(){

}