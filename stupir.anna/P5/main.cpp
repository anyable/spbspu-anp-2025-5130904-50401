#include <iostream>
namespace stupir
{
  struct point_t;
  struct rectangle_t;
  struct seg_t;
  struct Shape;
  struct Rectangle;
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
  virtual void move(point_t p) = 0;
  virtual void move(double x, double y) = 0;
  virtual void scale(double k) = 0;
  virtual ~Shape() = default;
};
struct stupir::seg_t
{
  point_t a, b;
};
struct stupir::Rectangle : Shape
{
  Rectangle(double weight, double hight, point_t center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t) override;
  void move(double x, double y) override;
  void scale(double k) override;
  private:
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

stupir::Rectangle::Rectangle(double weight, double hight, point_t center):
  c_(center), w_(weight), h_(hight)
  {}

double stupir::Rectangle::getArea() const
{
  return w_ * h_;
}

stupir::rectangle_t stupir::Rectangle::getFrameRect() const
{
  return {w_, h_, c_};
}

int main()
{
  using namespace stupir;
  stupir::Rectangle f1(2, 3, {2, 3});
  double s1 = f1.getArea();
  rectangle_t ss1 = f1.getFrameRect();

  f1.scale(4);
  double s2 = f1.getArea();
  rectangle_t ss2 = f1.getFrameRect();

  std::cout << s1 << ' ' << ss1.height << ' ' << ss1.width << '\n';
  std::cout << s2 << ' ' << ss2.height << ' ' << ss2.width << '\n';
}
