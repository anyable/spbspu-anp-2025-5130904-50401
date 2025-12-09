#include <iostream>
#include <cmath>
namespace stupir
{
  struct point_t;
  struct rectangle_t;
  struct seg_t;
  struct Shape;
  struct Rectangle;
  struct Square;
  struct Xquare;
}

struct stupir::point_t
{
  double x;
  double y;
};

struct stupir::rectangle_t
{
  double width;
  double height;
  point_t pos;
};

struct stupir::Shape
{
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(point_t) = 0;
  virtual void move(double , double) = 0;
  virtual void scale(double) = 0;
  virtual ~Shape() = default;
};


struct stupir::Rectangle : Shape
{
  Rectangle(point_t center, double weight, double hight);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t) override;
  void move(double x, double y) override;
  void scale(double k) override;
  protected:
    point_t c_;
    double w_;
    double h_;
};

void stupir::Rectangle::scale(double k)
{
  h_ *= k, w_ *= k;
}

void stupir::Rectangle::move(double x, double y)
  {
    c_.x += x;
    c_.y += y;
  }

void stupir::Rectangle::move(point_t p)
{
  c_ = p;
}

stupir::Rectangle::Rectangle(point_t center, double weight, double hight):
  Shape(), c_(center), w_(weight), h_(hight)
  {}

double stupir::Rectangle::getArea() const
{
  return w_ * h_;
}

stupir::rectangle_t stupir::Rectangle::getFrameRect() const
{
  return {w_, h_, c_};
}

struct stupir::Square : Rectangle
{
  Square(point_t , double);
};

stupir::Square::Square(point_t center, double len):
  Rectangle(center, len, len)
  {}

struct stupir::Xquare : Square
{
  Xquare(point_t, double);
  rectangle_t getFrameRect() const override;
};

stupir::Xquare::Xquare(point_t center, double len):
  Square(center, len)
  {}

stupir::rectangle_t stupir::Xquare::getFrameRect() const
{
  double d = std::sqrt(w_ * w_ + h_ * h_);
  return {d , d , c_};
}

int main()
{
 
}
