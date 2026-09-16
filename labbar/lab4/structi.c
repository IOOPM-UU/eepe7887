#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct point
{
  int x;
  int y;
};

typedef struct point point_t;

struct rectangle 
{
  point_t upper_left;
  point_t lower_right;
};

typedef struct rectangle rectangle_t;

void print_point(point_t *p) 
{
printf("point(%d, %d)\n", p->x, p->y);
}

point_t make_point(int x, int y)
{
  point_t p = {.x = x, .y = y};
  return p;
}

void print_rect(rectangle_t *r)
{
  point_t ulef = r->upper_left;
  point_t lrig = r->lower_right;
  printf("Upper left: ");
  print_point(&ulef);
  printf("Lower right: ");
  print_point(&lrig);
}


 rectangle_t make_rect(int x1, int y1, int x2, int y2)
{
  int lux = x1 < x2 ? x1 : x2;
  int lrx = x1 < x2 ? x2 : x1;
  int luy = y1 > y2 ? y1 : y2;
  int lry = y1 > y2 ? y2 : y1;

  point_t p1 = make_point(lux, luy);
  point_t p2 = make_point(lrx, lry);
  rectangle_t r = {.upper_left = p1, .lower_right = p2};
  return r;
}


  
  


int area_rect(rectangle_t *r)
{
  int x_1 = r->upper_left.x;
  int y_1 = r->upper_left.y;
  int x_2 = r->lower_right.x;
  int y_2 = r->lower_right.y;
  int width = abs(x_1 - x_2);
  int height = abs(y_1 - y_2);
  int area = width * height;
  return area;
}

bool intersects_rect(rectangle_t *r1, rectangle_t *r2)
{
  int x_11 = r1->upper_left.x;
  int y_11 = r1->upper_left.y;
  int x_12 = r1->lower_right.x;
  int y_12 = r1->lower_right.y;

  int x_21 = r2->upper_left.x;
  int y_21 = r2->upper_left.y;
  int x_22 = r2->lower_right.x;
  int y_22 = r2->lower_right.y;

  if((x_21 <= x_12 && x_22 >= x_11) && (y_21 >= y_12 && y_22 <= y_11)){
    return true;
  }
  else { return false;}
}

int main(){
rectangle_t r1 = make_rect(1, 2, 3, 4);
rectangle_t r2 = make_rect(1, 1, 2, 2);

int a1 = area_rect(&r1);
int a2 = area_rect(&r2);
bool inter_r1_r2 = intersects_rect(&r1, &r2);
printf("Area of rectangle 1 is: %d and area of rectangle 2 is: %d!\n", a1, a2);
printf("%d", inter_r1_r2);

return 0;
}