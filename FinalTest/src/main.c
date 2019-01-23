#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "time.h"

//The function f
double f(double x);

//The function that can generate random location x and y.
double* generateRan(double a, double b, double K);

//The function that can find the Max between a and b of function f
double findMax(double a, double b, int N);

//The function that can return the max of two values.
double max(double a, double b);

//The function that can generate random double value.
double genRandomDouble(double a, double b);

int main(int argc, char* argv[]){
    //Seed the random function
    srand(time(0));
    
    //Input a and b
    double a,b;
    printf("Enter a value for a: ");
    scanf("%lf", &a);
    printf("Enter a value for b: ");
    scanf("%lf", &b);
    printf("You entered a=%f and b=%f\n", a, b);
    
    if(b==a){
        printf("The b and a are the same, the result is 0!");
        return 1;
    }
    
    if(b<a){
        printf("b should be larger! And they should be numbers!\n");
        exit(1);
    }
    
    double res = 0;
    
    //This array stores all the values of the N
    int nArray[10] = {100,1000,10000,100000,200000,500000,1000000,5000000,10000000,20000000};
    
    //Test the N's value on the results
    for(int m=0;m<10;m++){
        int n = 0;
        int N = nArray[m];
        
        //********************************
        //The definition of K!!
        //The coefficient of K can be modified, here it's 1.1
        // I calculate the Maxvalue of funtion f in the (a,b) and then multiplied it by 1.1 to get the K
        //********************************
        double K = 1.1*findMax(a,b,N);
        if(K<0){
            printf("K should be positive!");
        }
        
        double** points = malloc(sizeof(double*)*N);{
            if(points==NULL){
                printf("malloc error!");
                exit(1);
            }
        }
        
        
        for(int i=0; i<N; i++){
            points[i] = generateRan(a,b,K);
            //printf("%lf %lf\n",points[i][0],points[i][1]);
            
            //count the number of the points beneath the curve
            if(points[i][1]<=f(points[i][0])) n++;
        }
        res = n*K*(b-a)/N;
        //printf("n is %d\n",n);
        //printf("K is %lf\n",K);
        printf("N:%d Z:%lf\n",N,res);
        
        //Free memory
        for(int i=0;i<N;i++){
            free(points[i]);
        }
        
        free(points);
    }
    
    return 0;
}

//This function can be modified
double f(double x){
    return x*x;
}


//This function is used to generate the random double value between a and b
double genRandomDouble(double a, double b){
    
    //The integral part
    int temp = rand()%100000;
    
    //The decimal part
    double decimal = temp/100000.0;
    
    temp = temp%(int)(b-a)+a;
    
    //The final random value
    double ans = (double) (temp + decimal);
    
    return ans;
}

//The function that generate random points.
double* generateRan(double a, double b, double K){
    double* point = malloc(sizeof(double)*2);
    if(point==NULL){
        printf("malloc error!");
        exit(1);
    }
    
    //Generate random points
    double x = genRandomDouble(a,b);
    double y = genRandomDouble(0,K);
    
    point[0] = x;
    point[1] = y;
    
    return point;
}


//Find the maximum of the function in a period
double findMax(double a, double b, int N){
    double interval = (double)(b-a)/N;
    double maxvalue = 0;
    
    for(int i=0; i<N; i++){
        double tempX = a+i*interval;
        double tempY = f(tempX);
        maxvalue = max(tempY,maxvalue);
    }
    
    //printf("The findmax return is %lf\n", maxvalue);
    return maxvalue;
}


//The function that can return the maximum between two input values
double max(double a, double b){
    if(a>=b) return a;
    if(a<b) return b;
    return 0;
}
