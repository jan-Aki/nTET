#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#define N 12 //the number of divisions in the octave
#define MAX 9 //the maximum numerator
#define BASE 440.0 //the initial note
#define OCTAVEMULTIPLIER 2//if this is 2, we're dividing the octave, if it's 4 then 2 octaves, etc (must be at least 2)

double findnearest(double notes[],double a,double b){
    double target = (a/b)*BASE;
    double candidate1,candidate2;
    int j;

    for (j=1;notes[j-1]<target;j++){//find the two values that "sandwich" the target
        candidate2=notes[j];
        candidate1=notes[j-1];
    }
    if(fabs(candidate1-target)<fabs(candidate2-target)){//find which is closest
        return candidate1;
    }else{return candidate2;}
}

int gcd(double c,double d){//idk i cheated and got chatgpt to do this for me. supposedly, it uses euler's method
    int a=(int)c;
    int b=(int)d;
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


int main(){
    char end;
    int n=N;
    int i;
    double numerator,denominator,ratiobetweennotes,nearest,percenterror;

    printf("How many notes in an octave?\n");scanf("%d",&n);printf("\n\n");
    double notes[n];
    ratiobetweennotes=pow(OCTAVEMULTIPLIER,1.0/(double)n);
    notes[0]=BASE;
    for (i=1;i<n;i++){//find all the notes in the octave
        notes[i]=notes[i-1]*ratiobetweennotes;
    }

    printf("The notes:\n");
    for(i=0;i<n;i++){
        printf("%d   %.2lfHz\n",i,notes[i]);
    }
    printf("%d   %.2lfHz\n\n",i,BASE*OCTAVEMULTIPLIER);

    printf("How well they approximate ratios:\n");
    for (numerator=2;numerator<=MAX;numerator++){
        for(denominator=floor(numerator/2)+1;denominator<numerator;denominator++){
            if (gcd(numerator,denominator)==1){
            nearest=findnearest(notes,numerator,denominator);
            percenterror=fabs((nearest-((numerator/denominator)*BASE))/((numerator/denominator)*BASE)*100);
            printf("%.0lf/%.0lf is %.3lf%% off at %.3lf\n",numerator,denominator,percenterror,nearest);
            }
        }
    }
    Sleep(10000000);
return 0;
}