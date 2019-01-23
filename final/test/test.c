#include "stdio.h"
#include "stdlib.h"
#include "time.h"
int  main(int argc, char* argv[]){
    
    double a  = 1.2321234225;
    
    double b = 8.87231;
    
    srand(time(0));
    
    double gap = b-a;
    
    for(int i=0;i<10;i++){
        int temp = rand()%100000;
        
        double decimal = temp/100000.0;
        
        temp = temp%(int)(b-a)+a;
        
        double ans = (double) (temp + decimal);
        printf("%lf\n",ans);
    }
    
    return 0;
    
}
