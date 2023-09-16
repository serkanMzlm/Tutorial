#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GRN "\x1b[32m"
#define COLOR_YLW "\x1b[33m"
#define COLOR_BLE "\x1b[34m"
#define COLOR_WHT "\x1b[37m"
#define COLOR_RST "\x1b[0m"

#define ERROR(X) printf("\n"COLOR_RED"%s"COLOR_RST"\n",X)
#define WARN(X)  printf("\n"COLOR_YLW"%s"COLOR_RST"\n",X)
#define DEBUG(X) printf("\n"COLOR_GRN"%s"COLOR_RST"\n",X)
#define INFO(X)  printf("\n"COLOR_WHT"%s"COLOR_RST"\n",X)

typedef enum {automatic, manual}Gear_t;

typedef struct {
  char brand[30];
  int year;
  float price;
  Gear_t gear;
}Car_t;

char * file_name = "car.db";
unsigned int counter = 0;

void setFile();
void getFile(Car_t car_[], int number);
void getCar(Car_t car_);
Car_t setCar();

int main(){
  ERROR("The color of error messages is RED");
  WARN("Warning message's color YELLOW");
  DEBUG("Debug message's color GREEN");
  setFile();
  Car_t car_arry[counter];
  getFile(car_arry, counter);
}

void setFile(){
  FILE *fp = fopen(file_name, "wb");
  if(!fp){
    ERROR("Error opening the database!");
    exit(-1);
  }
  Car_t car_1;
  int choice = 0;
  do{
    counter++;
    car_1 = setCar();
    fwrite(&car_1, sizeof(car_1), 1, fp);
    INFO("Do you want to continue? (Yes[1] or No[0])");
    scanf("%d", &choice);
    if(choice == 0){
      INFO("Saving file...");
      fclose(fp);
      sleep(1);
      break;
    }else if(choice != 1){
      WARN("Your choice is wrong!");
      fclose(fp);
      break;
    }
  }while(1);
  strcpy (car_1.brand,"BMW");
}

void getFile(Car_t car_[], int number){
  FILE* fp = fopen(file_name ,"rb+");
  if(!fp){
    ERROR ("Can't open file.");
    exit (-1);
  }
  for(int i = 0; i < number; i++){
    fread(&car_[i], sizeof(Car_t), 1, fp);
    // fseek(fp, (i + 1) * sizeof(Car_t), SEEK_SET);
  }
  fclose(fp);
  DEBUG("Results Found:");
  for(int i = 0; i < number; i++){
    getCar(car_[i]);
  }
}

void getCar(Car_t car_){
  printf("_______________________________________\n");
  printf("Brand of car: %s\n", car_.brand);
  printf("Year: %d\n", car_.year);
  printf("Price: %.2f $\n", car_.price);
  printf("This car has %s gear \n", car_.gear ? "manual" : "automatic");
  printf("_______________________________________\n");

}

Car_t setCar(){
  Car_t save_car = {"NAN", 0, 0.0f, manual};
  printf("\nEnter the car's information \n");
  printf("Brand:"); scanf("%s",save_car.brand);
  printf("Year:");  scanf("%d",&save_car.year);
  printf("Price:"); scanf("%f",&save_car.price);
  printf("Gear(oto 0 man 1):"); scanf("%d",&save_car.gear);
  return save_car;
}
