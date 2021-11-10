
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <list>
#include <cmath>
#include <cstdlib>

class Polynomial;

#define MAX_DEG 100

using namespace std;

struct Term
  {
    float coef;
    int exp;
  };

class Polynomial
{
private:
  Term *polyterm;
public:
  Polynomial();
  Polynomial(vector<Term>);
  Polynomial(Polynomial const &);
  ~Polynomial();
  void setCoef(int k, double value);
  void clear(); // sets degree to -1. No term = -1(default flag)
  double getCoef(int k) const;
  int getDegree() const;
  double evaluate(double value) const; // plug in value and compute it
  Polynomial operator +(Polynomial const &p);
  Polynomial operator -(Polynomial const &p);
  //bool operator ==(Polynomial const &p);
  bool operator ==(Polynomial const &p);
  Polynomial& operator =(Polynomial const &p);
  void addTerm(Term const &t);
  friend ostream& operator << (ostream& out, Polynomial const &);
};



Polynomial::Polynomial()
{
  polyterm = new Term[MAX_DEG + 1];
  for (int i = 0; i <= MAX_DEG; i++)
  {
    polyterm[i].exp = -1;
    polyterm[i].coef = 0;
  }
}

Polynomial::Polynomial(vector<Term> vt)
{
  auto it = vt.begin();
  for (; it != vt.end(); it++)
  {
    int texp;
    float tcoef;
    texp = it -> exp;
    tcoef = it -> coef;
    //polyterm[exp].exp = texp;
    //polyterm[exp].coef = tcoef;
    polyterm[texp].exp = texp;
    polyterm[texp].coef = tcoef;
  }
}

// copy constructor
Polynomial::Polynomial(Polynomial const& p)
{
  polyterm = new Term[MAX_DEG + 1];
  for (int i = 0; i <= MAX_DEG; i++)
  {
    *(polyterm + i) = p.polyterm[i];
  }
}

Polynomial::~Polynomial()
{
  delete [] polyterm;
}

void Polynomial::setCoef(int k, double value)
{
  polyterm[k].exp = k;
  polyterm[k].coef = value;
}

void Polynomial::clear()
{
  for (int i = 0; i <= MAX_DEG; i++)
  {
    polyterm[i].coef = 0;
    polyterm[i].exp = -1;
  }
}

double Polynomial::getCoef(int k) const
{
  return (polyterm[k].coef);
}

int Polynomial::getDegree() const
{
  for (int i = MAX_DEG; i >= 0; i--)
  {
    if (polyterm[i].coef != 0)
    {
      return i;
    }
  }
  if (polyterm[0].exp == 0)
  {
    return 0;
  }
  else
  {
    return -1;
  }
  //return -1;
}

double Polynomial::evaluate(double value) const
{
  double sum = 0;
  for (int i = 0; i < MAX_DEG + 1; i++)
  {
    sum += polyterm[i].coef * pow(value, i);
  }
  return sum;
}

Polynomial Polynomial::operator +(Polynomial const &p)
{
  Polynomial sum;
  for (int i = 0; i < MAX_DEG + 1; i++)
  {
    sum.polyterm[i].coef = polyterm[i].coef + p.polyterm[i].coef;
  }
  for (int i = 0; i < MAX_DEG + 1; i++)
  {
    if (sum.polyterm[i].coef == 0)
    {
      sum.polyterm[i].exp = -1;
      //return sum;
    }
    //return sum;
  }
  return sum;
}

Polynomial Polynomial::operator -(Polynomial const &p)
{
  Polynomial diff;
  for (int i = 0; i <= MAX_DEG; i++)
  {
    diff.polyterm[i].coef = polyterm[i].coef - p.polyterm[i].coef;
  }
  for (int i = 0; i <= MAX_DEG; i++)
  {
    if (diff.polyterm[i].coef == 0)
    {
      diff.polyterm[i].exp = -1;
      //return diff;
    }
    //return diff;
  }
  return diff;
}

bool Polynomial::operator ==(Polynomial const &p)
{
  for (int i = 0; i < MAX_DEG; i++)
  {
    if (polyterm[i].coef != p.polyterm[i].coef)
    {
      return false;
    }
  }
  return true;
}

Polynomial& Polynomial::operator =(Polynomial const &p)
{
  if (&p != this)
  {
    delete [] polyterm;
    polyterm = new Term[MAX_DEG + 1];
    for (int i = 0; i <= MAX_DEG; i++)
    {
      polyterm[i].coef = p.polyterm[i].coef;
      polyterm[i].exp = p.polyterm[i].exp;
    }
  }
  return *this;
}

void Polynomial::addTerm(Term const &t)
{
  polyterm[t.exp].coef = t.coef;
}

ostream &operator <<(ostream &out, Polynomial const &p)
{
  for (int i = MAX_DEG; i >= 0; i--)
  {
    if (p.polyterm[i].coef != 0)
    {
      out << p.polyterm[i].coef << " x^" << p.polyterm[i].exp;
    }
  }
  out << endl;
  return out;
}

// Main method
int main(int argc, char *argv[])
{
/*
  // copy for poly y. z = x + y
  // poly x
  vector<Term> v;
  srand(time(0));
  for (int i = MAX_DEG; i >= 0; i--)
  {
    int tcoef; // -20 -> 20
    tcoef = rand() % 41 - 20;
    Term p;
    p.coef = tcoef;
    p.exp = i;
    v.push_back(p);
  }
  Polynomial x(v);
  // poly y
  vector<Term> v;
  srand(time(0));
  for (int i = MAX_DEG; i >= 0; i--)
  {
    int tcoef; // -20 -> 20
    tcoef = rand() % 41 - 20;
    Term p;
    p.coef = tcoef;
    p.exp = i;
    v.push_back(p);
  }
  Polynomial y(v);
  //poly z
  Polynomial z;
  z = x + y;
  cout << z;
*/
  // quick test
  Polynomial a, b, c;
  a.setCoef(0, 1);
  a.setCoef(2, 7.2);
  a.setCoef(6, 2.1);

  b.setCoef(1, -2);
  b.setCoef(2, 2.5);
  b.setCoef(5, -2);

  c = a + b;
  cout << c << endl;
  cout << c.getDegree() << endl;
  c.clear();
  cout << c;

  return 0;
}


