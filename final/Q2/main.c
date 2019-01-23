#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define E   0
#define R   1
#define G   2
#define UNHAPPY_R  11
#define UNHAPPY_G  12
int** Init();
void print(int** Map);
int** Judge(int** Map);
int** Move(int** Map);
void sim(int timestep, int** Map);

int main(int argc, char* argv[]){
    
    srand(time(0));
    int** Map = Init();
    print(Map);
    //Judge(Map);
    sim(1000,Map);
    //printf("%f\n",0/0);
    
    
    return 0;
}

void sim(int timestep, int** Map){
    for(int i=1;i<timestep+1;i++){
        Map = Judge(Map);
        Map = Move(Map);
        if(i%10==0){
            printf("\n\n");
            print(Map);
        }
    }
}


int** Judge(int** Map){
    int x;
    int y;
    int left;
    int right;
    int up;
    int buttom;
    for(x=0;x<50;x++){
        for(y=0;y<50;y++){
            if(x==0) left=49;else left=x-1;
            if(x==49) right=0;else right=x+1;
            if(y==0) up=49; else up=y-1;
            if(y==49) buttom=0;else buttom=y+1;
            int n1 = Map[left][up];int n2 = Map[x][up]; int n3 = Map[right][up];
            int n4 = Map[left][y]; int n5 = Map[right][y];
            int n6 = Map[left][buttom]; int n7 = Map[x][buttom]; int n8 = Map[right][buttom];
            int Neigbors[8] = {n1,n2,n3,n4,n5,n6,n7,n8};
            float R_neigh=0; int G_neigh=0; int E_neigh=0;
            for(int i=0; i<8;i++){
                if(Neigbors[i]==R) R_neigh++;
                if(Neigbors[i]==G) G_neigh++;
                if(Neigbors[i]==E) E_neigh++;
            }
            float R_percent = (float)(R_neigh/(R_neigh+G_neigh));
            float G_percent = (float)(G_neigh/(R_neigh+G_neigh));
            //printf("%f\n",R_percent);
            if(Map[x][y]==R && R_percent<0.3) Map[x][y] = UNHAPPY_R;
            if(Map[x][y]==G && G_percent<0.3) Map[x][y] = UNHAPPY_G;
        }
    }
    return Map;
}

int** Init(){
    int** Map = malloc(sizeof(int*)*50);
    if(Map==NULL){
        printf("Malloc fail!");
        exit(1);
    }
    
    for(int i=0; i<50; i++){
        Map[i] = malloc(sizeof(int)*50);
        if(Map[i]==NULL){
            printf("Malloc fail!");
            exit(1);
        }
    }
    
    for(int i=0;i<50; i++){
        for(int j=0; j<50; j++){
            int init_rand = rand()%100;
            if(init_rand<40)
                Map[i][j] = R;
            if(init_rand<80 && init_rand>=40)
                Map[i][j] = G;
            if(init_rand<100 && init_rand>=80)
                Map[i][j] = E;
        }
    }
    
    return Map;
}

void print(int** Map){
    for(int i=0;i<50; i++){
        for(int j=0; j<50; j++){
            if(Map[i][j]==R) printf("R");
            else if(Map[i][j]==G) printf("G");
            else if(Map[i][j]==E) printf(" ");
        }
        printf("\n");
    }
}

int** Move(int** Map){
    for(int i=0;i<50;i++){
        for(int j=0;j<50;j++){
            if(Map[i][j]==UNHAPPY_R){
                int x = rand()%50;
                int y = rand()%50;
                while(Map[x][y]!=E){
                    x = rand()%50;
                    y = rand()%50;
                }
                Map[x][y] = R;
                Map[i][j] = E;
            }
            
            if(Map[i][j]==UNHAPPY_G){
                int x = rand()%50;
                int y = rand()%50;
                while(Map[x][y]!=E){
                    x = rand()%50;
                    y = rand()%50;
                }
                Map[x][y] = G;
                Map[i][j] = E;
            }
        }
    }
    return Map;
}
