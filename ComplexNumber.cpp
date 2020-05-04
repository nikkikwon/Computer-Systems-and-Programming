//introduction: 
//This program contains the constructor implementation of ComplexNumber as well as its implementations among many different 
//numerical types such as Real number, rational number. Since complex number has its special characteristic which is imaginary 
//number component, the calculations had to be managed in the way that the end result matches the mathematical convention. 
//When main program calls this with complex number being one of the number associated with the calculation, it does the 
//evaluation as specified and returns the result. 


#include "ComplexNumber.h"

//to_String converts real and imaginary components to string of type a+bi
string ComplexNumber::to_String(void){
	stringstream my_output;
	my_output << realComponent;
	if(imagComponent >= 0){
		my_output << " + " << imagComponent << "i";
	}
	else if(imagComponent < 0){
		my_output << "-" << imagComponent*(-1) << "i";
	}
	return my_output.str();
}

//Empty Constructor
ComplexNumber::ComplexNumber() { NumberType = COMPLEX; realComponent = 0.0; imagComponent = 0.0; }
//Complete Constructor
ComplexNumber::ComplexNumber(double real, double imag) { NumberType = COMPLEX; realComponent = real; imagComponent = imag; } 

//Setter and getter functions
void ComplexNumber::set_realComponent(double rval) { realComponent = rval; }
void ComplexNumber::set_imagComponent(double ival) { imagComponent = ival; }
double ComplexNumber::get_realComponent(void) const { return realComponent; }
double ComplexNumber::get_imagComponent(void) const { return imagComponent; }
void ComplexNumber::set_value(double rval, double ival) { realComponent = rval; imagComponent = ival;}

//Class member functions
double ComplexNumber::magnitude() 
// return the magnitude
{ 
  return sqrt((realComponent * realComponent) + (imagComponent * imagComponent) );
}

//Operation overload for ComplexNumber (op) ComplexNumber
ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
  ComplexNumber sum;
  sum.realComponent = realComponent + arg.realComponent;
  sum.imagComponent = imagComponent + arg.imagComponent;
  return sum;
}
ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
  ComplexNumber sub;
  sub.realComponent = realComponent - arg.realComponent;
  sub.imagComponent = imagComponent - arg.imagComponent;
  return sub;
}
ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
  ComplexNumber mul;
  mul.realComponent = (realComponent * arg.realComponent) - (imagComponent * arg.imagComponent);
  mul.imagComponent = (realComponent * arg.imagComponent) + (imagComponent * arg.realComponent);
  return mul;
}
ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
  ComplexNumber div;
  div.realComponent = ((realComponent * arg.realComponent) + (imagComponent * arg.imagComponent)) / ((arg.realComponent * arg.realComponent) + (arg.imagComponent * arg.imagComponent));

  div.imagComponent = ((imagComponent * arg.realComponent) - (realComponent * arg.imagComponent)) / ((arg.realComponent * arg.realComponent) + (arg.imagComponent * arg.imagComponent));
  return div;  
}

//Operation overload for ComplexNumber (op) RealNumber	
//in +, and - operations, imaginary component is left unchanged	
ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
  ComplexNumber sum;
  sum.realComponent = realComponent + arg.get_value();
  sum.imagComponent = imagComponent;
  return sum;
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
  ComplexNumber sub;
  sub.realComponent = realComponent - arg.get_value();
  sub.imagComponent = imagComponent;
  return sub;
}
//unlike other operations, multiplication and division associate imaginary number.
ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
  ComplexNumber mul;
  mul.realComponent = realComponent * arg.get_value();
  mul.imagComponent = imagComponent * arg.get_value();
  return mul;
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
  ComplexNumber div;
  div.realComponent = realComponent / arg.get_value();
  div.imagComponent = imagComponent / arg.get_value();
  return div;
}

//Operation overload for ComplexNumber (op) RationalNumber
//when using rational numbers, it should be changed to double as well as the divided value should be extracted for correct outcome. 	
ComplexNumber ComplexNumber::operator + (const RationalNumber& arg)
{
  ComplexNumber sum;
  double rational = (1.0 * arg.get_numerator()) / (1.0 * arg.get_denominator() );
  sum.realComponent = realComponent + rational;
  sum.imagComponent = imagComponent;
  return sum;  
}

ComplexNumber ComplexNumber::operator - (const RationalNumber& arg)
{
  ComplexNumber sub;
  double rational = (1.0 * arg.get_numerator()) / (1.0 * arg.get_denominator() );
  sub.realComponent = realComponent - rational;
  sub.imagComponent = imagComponent;
  return sub;  
}

ComplexNumber ComplexNumber::operator * (const RationalNumber& arg)
{
  ComplexNumber mul;
  double rational = (1.0 * arg.get_numerator()) / (1.0 * arg.get_denominator() );
  mul.realComponent = realComponent * rational;
  mul.imagComponent = imagComponent * rational;
  return mul;  
}

ComplexNumber ComplexNumber::operator / (const RationalNumber& arg)
{
  ComplexNumber div;
  double rational = (1.0 *arg.get_denominator()) / (1.0 * arg.get_numerator());
  div.realComponent = realComponent * rational;
  div.imagComponent = imagComponent * rational;
  return div;
}

		




















