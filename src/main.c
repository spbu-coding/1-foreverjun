#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 6

const double a=0,b=3.14592f;

double sympson(int number){
  double h,result=0;
  for(int i=0;i<number;i++){
      h= (b-a) /number;
      result+=h/6*(sin(a+i*h)+4*sin((a+i*h+b-(h*(number-1-i)))/2)+sin(b-(h*(number-1-i))));
  }
  return result;
}
double rectangles(int number) {
    int i;
    double h, result = 0;
    h = (b - a) / number;
    for (i = 0; i < number; i++) {
        result += sin(a + h / 2 + h * i);
    }
    result = result * h;
    return result;
}
void free_output (char** output,int experements_count){
    for (int i = 0; i <experements_count ; ++i) {
        free(output[i]);
    }
    free(output);
    printf("all ok");
}
char** processing(int *input) {
    int i;
    char **output=(char**)malloc(sizeof(char*)*N);
    if(!output){
        return NULL;
    }
    for (i = 0; i < N; i++) {
        output[i]=(char*)malloc(sizeof(char)*30);
        if(!output[i]){
            free_output(output,i);
            return NULL;
        }
        if(!sprintf(output[i], "%d %.5f %.5f %d", *(input + i),rectangles(*(input + i)),sympson(*(input + i)),i)){

        }
        printf("%s\n", output[i]);
    }
    return output;

}
int main() {
    int input[] ={5,10,20,100,500,1000};
    char** p = processing(input);
    printf("%s\n",p[0]);
    printf("%s",p[1]);
    free_output(p,N);
    return 0;
}