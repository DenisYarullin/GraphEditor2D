////////////////////////////////////////////////////////////////////////////////
//
//                          ����������� ����� ��� ������
//
////////////////////////////////////////////////////////////////////////////////



#include "constraint.h"
#include "curv_abstract_curve.h"
#include "mb_vector.h"


//------------------------------------------------------------------------------
// ����������� �� ���������
// ---
MbCurve::MbCurve()
{
}


//------------------------------------------------------------------------------
// ����������
// ---
MbCurve::~MbCurve()
{
}


//------------------------------------------------------------------------------
// �������� ������ (��� ������� � Nurbs)
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
// �������� ���������, ��������������� ��������.
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
// ������ � �����
// ---
ofstream & operator<< ( ofstream & out, const MbCurve * curve )
{
  return curve->out( out );
}


//------------------------------------------------------------------------------
// ������ �� ������
// ---
ifstream & operator>> ( ifstream & in, MbCurve * curve )
{
  return curve->in( in );
}
