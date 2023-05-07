/*
    WAREHOUSE
*/


// Structure to store details of a single cell
struct Cell{
    int x,y; 
    
    Cell(){
        x = -1;
        y = -1;
    }

    Cell(int x,int y){
        this->x = x;
        this->y = y;
    }

    bool operator<(const Cell &o)  const {
        return (x < o.x) || (x == o.x && y < o.y);
    }
    friend ostream& operator << (ostream &os, const Cell &m) {return os << "{" << m.x << "," << m.y << "}";}
};

// Structure to store details of a single item
struct Item{
    int item_number;
    vector<Cell>cells;  // cells where the item is available
};

/*
Struct{
    vector<int> items
    vector<pair<int,Cell>> optimalPath
}
*/
struct Order{
    vector<int>items;  // Item Numbers of all items in the order
    vector<pair<int,Cell>>optimalpath;  // Contains the sequence of steps robot needs to follow to cater the order
                                        // Each element (item_number,cell) : Go to this cell and pick up this item
    vector<int>subOrderIndexes;
    int time;
    Order(){   
        time = 0;
    }
    int getOrderSize(){
        return items.size();
    }
};




/*
    GENETIC
*/

struct Genotype {
    vector<vi>Warehouse;   // warehouse[i][j] : item in i,j cell
    unordered_map<int,vector<Cell>>AllItems;
    double fitness;
    
    Genotype(){
        this->Warehouse.clear();
        this->AllItems.clear();
    }

    Genotype(vector<vi>warehouse){
        this->Warehouse = warehouse;
    }
};