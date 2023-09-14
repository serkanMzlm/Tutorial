#include <stdio.h>

void info();
float area_calc(float height, float width);
float environment_calc(float height, float width);

float area, environment;
float height, width;

int main(){
  info();
  printf("Enter the length of the wall: "); scanf("%f", &height);
  printf("Enter the breadth of the wall: "); scanf("%f", &width);
  
  area = area_calc(height, width);
  environment = environment_calc (height, width);

  printf("area: %.2f\t|\tenvironment: %.2f\n", area, environment);
  return 0;
}

float area_calc(float height, float width){
  return (height * width);
}

float environment_calc(float height, float width){
  return (2 *(height + width));   //formula for calculating envirnomental factor
}

void info(){
  printf("\n************************************************************\n");
  printf("* This is a program that calculates the area of rectangle. *");
  printf("\n************************************************************\n");
}