#include "config.h"

// global, master list of components
struct {
    int ComponentType;  // GENERATOR, QUEUE_STATION, FORK, EXIT
    void *Comp;         // Pointer to information on component (Generator, Exit struct, etc.)
} Component_read[MAXCOMPONENTS];

int main() {
    
     char* configPath = malloc(sizeof(char)*20);
     //strcpy(configPath,argv[2]);
     //strcat(configPath,".txt");
    
    FILE* f1;
    configPath = "config.txt";
    f1 = fopen(configPath, "r");
    int TotalNum = read_file(f1);
    //print_read(TotalNum);
    
    for(int i=0; i<TotalNum; i++){
        if(Component[i].ComponentType == GENERATOR){
            struct Generator* G_pointer= (struct Generator*)Component[i].Comp;
            //MakeGenerator(i, G_pointer->IntArrTime, G_pointer->DestComp);
        }
        if(Component[i].ComponentType == FORK){
            struct Fork* F_pointer= (struct Fork*)Component[i].Comp;
            //MakeFork(i, G_pointer->IntArrTime, G_pointer->DestComp);
        }
        if(Component[i].ComponentType == QUEUE_STATION){
            //struct Queue_Station* Q_pointer= (struct Queue_Station*)Component[i].Comp;
        }
        if(Component[i].ComponentType == EXIT){
        }
    }
    
    fclose(f1);
    return 0;
    
}
