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

    void Setter(int x,int y){
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

// Structure to store all the details related to a single order
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

struct genotype {
    vector<vector<int>>warehouse;   // warehouse[i][j] : item in i,j cell
};