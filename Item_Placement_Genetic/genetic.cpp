#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>
using namespace std;
#include "headers.h"

// ------------------------------------------------------------------------------------------------ 
// ------------------------------------------------------------------------------------------------ 

void take_input(){
    freopen("input.txt","r",stdin);
    int t;   
    cin>>t;

    cin>> ROWS >> COLS ;
    cin>> docking_time >> velocity >> capacity_of_robot ;
    cin>> num_of_robots >> num_of_orders ;
    cin>> number_of_total_items ;

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
}

int main(){
    FASTIO;
    hola;
    _log("Input started");
    take_input();

    _log("Initial population started");
    initialize(ROWS,COLS);
    
    _log("");
    cout<<"Warehouse : " << ROWS << "x" << COLS << endl;
    cout<<"Number of orders : " << allOrders.size() << endl;

    // Order merging 
    // vector<vector<Cell>>allItems = GetItemsMappingForWarehouse(population[0].Warehouse,number_of_total_items);
    // allOrders = CW2_merge(allOrders,allItems);

    allOrders = greedyMergeOrdersSize(allOrders);
    cout<<"Number of orders (after merging): " << allOrders.size() << endl;

    cout<<"Capacity of robots : " << capacity_of_robot << endl;
    cout<<"Distinct items in warehouse : " << ROWS * COLS << endl;
    clock_t geneticStartTime = clock();

    _log("GA started : ");
    for( int currGen = 1 ; currGen <= MAXGENS ; currGen++){
        clock_t tStart=clock();

        vector<pair<int,int>>parent_pairs=select_parent_pairs(POPSIZE/2);
        vector<Genotype>children;

        for(auto &ind : parent_pairs){
            Genotype child= crossover(population[ind.first].Warehouse , population[ind.second].Warehouse);

            children.push_back(child);
        }

        vector<Genotype> newPopulation = population;
        for(auto & child : children){
            double rand = r8_uniform_ab(0.0,1.0);
            if(rand < PMUTATION_RSM){
                mutation_rsm(child);
            }else{
                mutation_psm(child);
            }

            // if (rand < 0.6){
            //     mutation_psm(child);
            // }

            child.fitness = GetFitness(child,allOrders);
            newPopulation.push_back(child);
        }

        for(int i = 0 ; i < 0.2 * POPSIZE ; ++i){
            Genotype randomMember = GetRandomMember(ROWS,COLS);
            randomMember.fitness = GetFitness(randomMember,allOrders);
            
            newPopulation.push_back(randomMember);
        }
        
        keepTheBest(newPopulation);

        report ( currGen );

        cout<<"Computation Time: "<<((double)(clock()-tStart)/CLOCKS_PER_SEC)/1.0<<" seconds"<<endl<<endl;

        for(int i = 0 ; i < POPSIZE ; ++i){
            if(!ValidateGene(population[i])){
                _log("panic : invalid genotype ")
                exit(0);
            }
        }
    }
    _log("")    
    printTimeElapsedMins(geneticStartTime,"Total time for GA :- ");
}