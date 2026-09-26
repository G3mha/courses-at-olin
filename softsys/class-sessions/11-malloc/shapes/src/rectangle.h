#pragma once

typedef struct {
  double x;
  double y;
} point;

typedef struct {
  point* corner;
  double height;
  double width;
} rectangle;

point* make_point(double x, double y);

void free_point(point* pt);

rectangle* make_rectangle(point* pt, double height, double width);

void free_rectangle(rectangle* rect);

int contains_point(const rectangle* rect, const point* pt);
