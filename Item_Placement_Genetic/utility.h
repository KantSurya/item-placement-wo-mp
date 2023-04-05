#include "structs.h"

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