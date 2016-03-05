////////////////////////////////////////////////////////////////////////////////
//
//                          Абстрактный класс для кривых
//
////////////////////////////////////////////////////////////////////////////////



#include "constraint.h"
#include "curv_abstract_curve.h"
#include "mb_vector.h"


//------------------------------------------------------------------------------
// конструктор по умолчанию
// ---
MbCurve::MbCurve()
{
}


//------------------------------------------------------------------------------
// деструктор
// ---
MbCurve::~MbCurve()
{
}


//------------------------------------------------------------------------------
// кривизна кривой (для эллипса и Nurbs)
// ---
double MbCurve::Curvature( double t ) const
{
  double k, deltaT;
  MbVector firstDer, secondDer;

  FirstDerivative ( t, firstDer );
  SecondDerivative( t, secondDer );

  double lengthFirstDer = firstDer.LengthOfVector();

  k = fabs( firstDer.VectorProduct( secondDer ) / pow( lengthFirstDer, 3.0) );

  deltaT = deltaAlfa / ( k * lengthFirstDer );

  return deltaT;
}


//------------------------------------------------------------------------------
// значения параметра, удовлетворяющие кривизне.
// ---
void MbCurve::StepParameter( double minT, double maxT, vector<double> & parameters )
{
  double deltaT = 0.0;

  if( Type() == Segment ) {
     parameters.push_back( minT );
  }

  for ( double t = minT; t < maxT; t += deltaT ) {

    parameters.push_back( t );
    deltaT = this->Curvature( t );
    if ( deltaT > maxDeltaT )
        deltaT = maxDeltaT;
    else if ( deltaT < minDeltaT )
        deltaT = minDeltaT;
    else
        continue;
  }
  parameters.push_back( maxT );
}


//------------------------------------------------------------------------------
// запись в поток
// ---
ofstream & operator<< ( ofstream & out, const MbCurve * curve )
{
  return curve->out( out );
}


//------------------------------------------------------------------------------
// чтение из потока
// ---
ifstream & operator>> ( ifstream & in, MbCurve * curve )
{
  return curve->in( in );
}
