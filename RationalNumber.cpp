//Introduction:
//This function contains information and implementation of the rational number. It not only contains the constructor implementations, 
//but also contains calculation processes needed when rational number is operated on any other numerical types given by the problem. 
//In many operations, its integer numerator and denominator should be converted to double by multipling 1.0, to make sure the 
//data type is proper in corresponding operations.  

#include "RationalNumber.h"

//to_String converts numerator and denominator to string of type num/denom
string RationalNumber::to_String(void){
	stringstream my_output;
	my_output << numerator << "/" << denominator;
	return my_output.str();
}
//Empty Constructor		
RationalNumber::RationalNumber() {NumberType = RATIONAL; numerator = 0; denominator = 1; }
//Complete Constructor
RationalNumber::RationalNumber(int numer, int denom) {NumberType = RATIONAL; numerator = numer; denominator = denom; }

//Setter and getter functions
void RationalNumber::set_numerator(int numer){numerator = numer;}
void RationalNumber::set_denominator(int denom){denominator = denom;}
int RationalNumber::get_numerator(void) const{return numerator;}
int RationalNumber::get_denominator(void) const{return denominator;}

//Class member functions
void RationalNumber::set_value (int numer, int denom)
{
  numerator = numer;
  denominator = denom;
}

int RationalNumber::gcd(int a, int b)
{
  int r = a % b;
  while (r != 0)
  {
    a = b;
    b = r; 
    r = a % b;
  } 
  return b;
}

double RationalNumber::magnitude()
{
  double num = numerator * 1.0;
  double denom = denominator * 1.0;
  return num / denom;
}
//make numerator and denominator to have type double
double RationalNumber::decimal_value() const
{
  double num = numerator * 1.0;
  double denom = denominator * 1.0;
  return num / denom;
}

//Operation overload for RationalNumber (op) RationalNumber
RationalNumber RationalNumber:: operator + (const RationalNumber& arg)
{
// gcd used to make sure the final answer is in reduced form
  int g_c_d;
  RationalNumber sum;
  sum.denominator = denominator * arg.denominator ;
  sum.numerator = ((numerator * arg.denominator) + (arg.numerator * denominator));
  g_c_d = gcd(sum.numerator, sum.denominator);
  sum.denominator = sum.denominator / g_c_d;
  sum.numerator = sum.numerator / g_c_d; 

  return sum;
}

RationalNumber RationalNumber:: operator - (const RationalNumber& arg)
{
  int g_c_d;
  RationalNumber sub;
  sub.denominator = denominator * arg.denominator ;
  sub.numerator = ((numerator * arg.denominator) - (arg.numerator * denominator));
  g_c_d = gcd(sub.numerator, sub.denominator);
  sub.denominator = sub.denominator / g_c_d;
  sub.numerator = sub.numerator / g_c_d; 

  return sub;
}
RationalNumber RationalNumber::operator * (const RationalNumber& arg)
{
  int g_c_d;
  RationalNumber mul;
  mul.denominator = denominator * arg.denominator ;
  mul.numerator = numerator * arg.numerator;
  g_c_d =gcd(mul.numerator, mul.denominator);
  mul.denominator = mul.denominator / g_c_d;
  mul.numerator = mul.numerator / g_c_d; 

  return mul;
}

RationalNumber RationalNumber::operator / (const RationalNumber& arg)
{
  int g_c_d;
  RationalNumber div;
//division same as multiplication but with num, denom swapped

  div.denominator = denominator * arg.numerator ;
  div.numerator = numerator * arg.denominator;
  g_c_d =gcd(div.numerator, div.denominator);
  div.denominator = div.denominator / g_c_d;
  div.numerator = div.numerator / g_c_d; 

  return div;    
}

//Operation overload for RationalNumber (op) ComplexNumber
ComplexNumber RationalNumber::operator + (const ComplexNumber& arg)
{
  ComplexNumber sum;
  double rational = (1.0*numerator)/(1.0*denominator);
  sum.set_realComponent(arg.get_realComponent() + rational);
  sum.set_imagComponent(arg.get_imagComponent());
  return sum;
}

ComplexNumber RationalNumber::operator - (const ComplexNumber& arg)
{
  ComplexNumber sub;
  double rational = (1.0*numerator)/(1.0*denominator);
  sub.set_realComponent(rational - arg.get_realComponent());
  sub.set_imagComponent(-1.0 * arg.get_imagComponent());
  return sub;   
}

ComplexNumber RationalNumber::operator * (const ComplexNumber& arg)
{
  ComplexNumber mul;
  double rational = (1.0*numerator)/(1.0*denominator);
  mul.set_realComponent(arg.get_realComponent() * rational);
  mul.set_imagComponent(arg.get_imagComponent() * rational);
  return mul; 
}

ComplexNumber RationalNumber::operator / (const ComplexNumber& arg)
{
  double rational = (1.0*numerator)/(1.0*denominator);
  double rc = rational * arg.get_realComponent();
  double ic = rational * arg.get_imagComponent()*(-1.);
  double d = arg.get_realComponent()*arg.get_realComponent()+arg.get_imagComponent()*arg.get_imagComponent();
  return ComplexNumber (rc/d, ic/d); 
}

//Operation overload for RationalNumber (op) RealNumber
RealNumber RationalNumber::operator + (const RealNumber& arg)
{
  double rn = decimal_value();
  return RealNumber(arg.get_value() + rn);
}

RealNumber RationalNumber::operator - (const RealNumber& arg)
{
  double rn = decimal_value();
  return RealNumber(rn - arg.get_value());  
}		

RealNumber RationalNumber::operator * (const RealNumber& arg)
{
  double rn = decimal_value();
  return RealNumber(arg.get_value() * rn); 
}

RealNumber RationalNumber::operator / (const RealNumber& arg)
{
  double rn = decimal_value();
  return RealNumber( rn / arg.get_value() );
}





		
		




