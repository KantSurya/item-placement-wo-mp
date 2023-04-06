
// ------------------------------------------------------------------------------------------------ 
#define debug(x) cout<<#x<<": "<<x<<endl;
#define DEBUG(x) cout<<#x<<": \n"; for(int i = 0 ; i < x.size() ; ++i)cout<<x[i]<<" \n"[i==(int)x.size()-1];
#define fi(a,b) for(int i = a ; i<=b ; ++i)
#define fj(a,b) for(int j = a ; j<=b ; ++j)
#define vi vector<int>
#define vvi vector<vi>
// ------------------------------------------------------------------------------------------------ 


// ------------------------------------------------------------------------------------------------ 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
    T rand(T a, T b) {
        return uniform_int_distribution<T>(a, b)(rng);
    }

template<class T>
    T rand() {
        return uniform_int_distribution<T>()(rng);
    }
// ------------------------------------------------------------------------------------------------ 

// ------------------------------------------------------------------------------------------------ 
#define debugCell(cell) cout<<cell.x<<" "<<cell.y<<endl;

// ------------------------------------------------------------------------------------------------ 

Cell GetNextCell(Cell cell,int n,int m){
    cell.y++;

    if( cell.y == m){
        cell.x++;
        cell.y = 0;
    }

    return cell;
}

Cell GetPrevCell(Cell cell,int n,int m){
    cell.y--;

    if( cell.y < 0){
        cell.x--;
        cell.y = m-1;
    }

    return cell;
}

int distance(Cell& a, Cell& b){
    return abs(a.x - b.x) + abs(a.y - b.y);
}