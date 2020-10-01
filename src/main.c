#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define EXPERIMENT_NUMBER 6
#define MAX_CELL_SIZE 30
#define PI 3.14592653
#define error(...) (fprintf(stderr,__VA_ARGS__))
double simpson_method(int number,double left_border,double right_border){
  double interval,result=0;
  for(int i=0;i<number;i++){
      interval= (right_border-left_border) /number;
      result+=interval/6*(sin(left_border+i*interval)+4*sin((left_border+i*interval+right_border-(interval*(number-1-i)))/2)+sin(right_border-(interval*(number-1-i))));
  }
  return result;
}
double rectangles_method(int number,double left_border,double right_border) {
    int i;
    double interval, result = 0;
    interval = (right_border - left_border) / number;
    for (i = 0; i < number; i++) {
        result += sin(left_border + interval / 2 + interval * i);
    }
    result = result * interval;
    return result;
}
void free_result (char** result,int experiments_count){
    for (int i = 0; i <experiments_count ; ++i) {
        free(result[i]);
    }
    free(result);
}
char** processing(int *partition_sizes,double left_border,double right_border) {
    int i;
    char **result=(char**)malloc(sizeof(char*)*EXPERIMENT_NUMBER);
    if(!result){
        error("Can not allocate memory for **result\n");
        return NULL;
    }
    for (i = 0; i < EXPERIMENT_NUMBER; i++) {
        result[i]=(char*)malloc(sizeof(char)*MAX_CELL_SIZE);
        if(!result[i]){
            free_result(result,i);
            error("Can not allocate memory for result[%d]\n",i);
            return NULL;
        }
        if(!sprintf(result[i], "%d %.5f %.5f", *(partition_sizes + i),rectangles_method(*(partition_sizes + i),left_border,right_border),simpson_method(*(partition_sizes + i),left_border,right_border))){
            error("Can not write string to result[%d]\n",i);
            return NULL;
        }
    }
    return result;
}
int read_interval ( double *left_border,double *right_border){
    if (printf("Enter left border: ")<0){
        error("Cannot write to stdout");
        return -1;
    }
    if (scanf("%lf",left_border)!=1){
        error("Cannot read left border");
        return -1;
    }
    if (printf("Enter right border: ")<0){
        error("Cannot write to stdout");
        return -1;
    }
    if (scanf("%lf",right_border)!=1){
        error("Cannot read right border");
        return -1;
    }
    if (*left_border<0){
        error("Left border less than 0");
        return -1;
    }
    if (*right_border>PI){
        error("Right border greater than PI");
        return -1;
    }
    if (*left_border>*right_border){
        error("Right border less then left border");
        return -1;
    }
    return 0;
}
int main() {
    double left_border =0,right_border=0;
    if(read_interval(&left_border,&right_border)){
        return 1;
    }
    int partition_sizes[] ={6,10,20,100,500,1000};
    char** result = processing(partition_sizes,left_border,right_border);
    if(!result) {
        return 1;
    }
    for (int i = 0; i < EXPERIMENT_NUMBER; ++i) {
        if(printf("%s\n",result[i])<0){
            error("Can not write result[%d] to stdout",i);
            break;
        }
    }
    free_result(result,EXPERIMENT_NUMBER);
    return 0;
}