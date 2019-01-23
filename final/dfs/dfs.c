#include "stdlib.h"
#include "stdio.h"
#include "lib.h"
#include "time.h"
void dfs(int** mat, int x, int y, int len, int wid, int** visited);
void dfsaTheMap(int** mat, int x, int y, int len, int wid, int** visited);

int main(){
    //generate matrix 0 1 -1
    int** mat = malloc(sizeof(int*)*7);
    int** visited = malloc(sizeof(int*)*5);
    for(int i=0; i<7; i++){
        mat[i] = malloc(sizeof(int)*7);
        visited[i] = malloc(sizeof(int)*5);
    }
    
    srand((int)time(0));
    for(int i=0 ;i<7; i++){
        for(int j=0;j<7;j++){
            if(i==0){
                mat[i][j]=0;
                continue;
            }
            if(j==0){
                mat[i][j]=0;
                continue;
            }
            if(i==6){
                mat[i][j]=0;
                continue;
            }
            if(j==6){
                mat[i][j]=0;
                continue;
            }
                
            int rn = rand()%100;
            if(rn>=50) mat[i][j] = 1;
            else mat[i][j] = 0;
            if(i<6 && j<6)
            visited[i][j]=0;
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    
    dfsaTheMap(mat,1,1,7,7,visited);
    
    //generate a linked list based on the matrix.
    //the vertexs are
    
    return 0;
}

void dfsaTheMap(int** mat, int x, int y, int len, int wid, int** visited){
    dfs(mat, x,y,len,wid,visited);
}

void dfs(int** mat, int x, int y, int len, int wid, int** visited){
    if(visited[x][y]) return;
    if(x==6 || y==6 || x==0 || y==0) return;
    int n_z = 0;
    
    visited[x-1][y-1] = 1;
    
    if(mat[x-1][y] == 1){
        n_z++;
        dfs(mat,x-1,y,5,5,visited);
    }
    if(mat[x+1][y] == 1){
        n_z++;
        dfs(mat,x+1,y,5,5,visited);
    }
        
   if(mat[x][y-1] == 1){
        n_z++;
        dfs(mat,x,y-1,5,5,visited);
    }
    
    if(mat[x][y+1] == 1){
        n_z++;
        dfs(mat,x,y+1,5,5,visited);
    }
            
    if(n_z == 1){
        printf("The end!");
    }
}
