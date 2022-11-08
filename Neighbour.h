#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

using namespace std;

class Neighbour{ 

std::vector<std::vector<float>> cells;
float dead = 0.5; //color value for a dead cell
float alive = 0.2; //color value for a live cell


public:

 Neighbour(){
    cells.resize(5, std::vector<float>(5, dead)); //sets the dimension and value of each cell
 }



//checks whether the cell is a corner cell
    bool isCorner(int x, int y){
        if((x==0&&y==0)||(x==0&&y==4)||(x==14&&y==0)||(x==4&y==4)){
            return true;
        }
        return false;
     }
    //checks whether the cell is along the edge of the matrix
     bool isEdge(int x, int y){
        int cell [30][30];
        std::fill(cell[0], cell[0] + 30 * 30, 0);
        for(int i = 0;i<5;i++){
            cell[14][i] = 1;
        } 
        for(int j = 0;j<5;j++){
            cell[0][j] = 1;
        } 
        for(int k = 0;k<5;k++){
            cell[k][0] = 1;
        } 
        for(int l = 0;l<5;l++){
            cell[l][9] = 1;
        } 
        if(cell[x][y] == 1){
            return true;
        }
        return false;
     }
    // checks whether the specified cell coordinate is within our matrix
     bool cellExists(int x, int y){
        int cell [30][30];
        std::fill(cell[0], cell[0] + 30 * 30, 0);
        for(int i = 0;i<5;i++){
         for(int j = 0;j<5;j++){
            cell[i][j] = 1;
         }
        } 
        if(cell[x][y] == 1){
            return true;
        }
        return false;
     }
    //a struct object which contains the x and y coordinates of every neighbour of a cell
     struct Neighbors{
        int x;
        int y;
     };
     
     Neighbors neighbor[10]; //an array that stores about 10 neighbors of a cell(we only eight tho)

     //populates the above Neighbors struct with the neighbor of cells[x][y]
     void findNeighbor(int x, int y){
        for(int i = 0;i<10;i++){
                neighbor[i].x = 100;
                neighbor[i].y = 100;
        }
        int n = 0;
        if(cellExists(x,y-1)){
          neighbor[n].x = x;
          neighbor[n].y = y-1;
          n++;   
        }
        if(cellExists(x-1,y)){
          neighbor[n].x = x-1;
          neighbor[n].y = y;
          n++; 
        }
        if(cellExists(x,y+1)){
            neighbor[n].x = x;
            neighbor[n].y = y+1;
            n++; 
        }
        if(cellExists(x+1,y)){
            neighbor[n].x = x+1;
            neighbor[n].y = y;
            n++; 
        }
        if(cellExists(x-1,y-1)){
            neighbor[n].x = x-1;
            neighbor[n].y = y-1;
            n++; 
        }
        if(cellExists(x+1,y+1)){
            neighbor[n].x = x+1;
            neighbor[n].y = y+1;
            n++; 
        }
        if(cellExists(x+1,y-1)){
            neighbor[n].x = x+1;
            neighbor[n].y = y-1;
            n++; 
        }
        if(cellExists(x-1,y+1)){
            neighbor[n].x = x-1;
            neighbor[n].y = y+1;
            n++; 
        }
        if (isEdge(x,y)){
            
            if (x == 0){
                for(int i = -1;i<2;i++){
                  neighbor[n].x = 4;
                  neighbor[n].y = y-i;
                  n++; 
                }
            }
            if (x == 14){
                for(int i = -1;i<2;i++){
                  neighbor[n].x = 0;
                  neighbor[n].y = y-i;
                  n++; 
                }
            }
            if (y == 0){
                for(int i = -1;i<2;i++){
                  neighbor[n].x = x-i;
                  neighbor[n].y = 4;
                  n++; 
                }
            }
            if (y == 9){
                for(int i = -1;i<2;i++){
                  neighbor[n].x = x-i;
                  neighbor[n].y = 0;
                  n++; 
                }
            }
            if(isCorner(x,y)){
                if((x==0)&(y==0)){
                    neighbor[n].x = 4;
                    neighbor[n].y = 4;
                    n++; 
                }
                if((x==4)&(y==0)){
                    neighbor[n].x = 0;
                    neighbor[n].y = 4;
                    n++;
                }
                if((x==0)&(y==4)){  
                    neighbor[n].x = 4;
                    neighbor[n].y = 0;
                    n++; 
                }
                if((x==4)&(y==4)){
                    neighbor[n].x = 0;
                    neighbor[n].y = 0;
                    n++;
                }
                
            }
        }
    }
        //returns the count of live neighbors by seeing their value(alive if alive, dead if dead)
        int countLiveNeighbor(std::vector<std::vector<float>> oldCells, int x, int y){
            int liveNeighbors = 0;
            float shade = alive;
            findNeighbor(x,y);
            for(int i = 0;i<5;i++){
             if(cellExists(neighbor[i].x,neighbor[i].y)){
                if(oldCells[neighbor[i].x][neighbor[i].y]==shade){
                    liveNeighbors++;
                }
             }
            }
            return liveNeighbors;
        }

        //flushes our cells vector with its initial value of dead
        void reset(){
            for (int x = 0; x < cells.size();x++ ){
              for (int y = 0; y < cells[x].size();y++){
                cells[x][y] = dead;
              }
            }
        }

        Neighbors getNeighbours(){
           return neighbor;
        }

};
        