////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru �������. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __CURVE_LINE_SEGMENT_H_
#define __CURVE_LINE_SEGMENT_H_


#include <fstream>


class MbCurve;
class MbCartPoint;
class MbVector;


using std::ofstream;
using std::ifstream;


//------------------------------------------------------------------------------
/** \brief \ru ����� �������. \~
  \details \ru ������� �������� �������� ������ MbCurve. \n
*/
//------------------------------------------------------------------------------


class MbLineSegment : public MbCurve
{

private:

  MbCartPoint p1;                       ///< \ru ������ �����.
  MbCartPoint p2;                       ///< \ru ������ �����.

public:
  /// \ru ����������� �� ���������.
  MbLineSegment();
  /// \ru ����������� �� ���� ������.
  MbLineSegment( const MbCartPoint &, const MbCartPoint & );
  /// \ru ����������� �� ���� ������, ���������� � �����������.
  MbLineSegment( double x0, double y0, double x1, double y1 );
  /// \ru ����������� �� ����� � �������.
  MbLineSegment( const MbCartPoint &, const MbVector & );
  /// \ru ����������� �����������.
  MbLineSegment( const MbLineSegment & );

  /// \ru ����������.
  virtual ~MbLineSegment();

  /// \ru �������� ������������.
  MbLineSegment & operator = ( const MbLineSegment & );

  /// \ru �������� ����� ��������.
  double GetLengthSegment() const;
  /// \ru �������� ������ �����.
  const MbCartPoint & GetPointOne() const;
  /// \ru �������� ������ �����.
  const MbCartPoint & GetPointTwo() const;

  /// \ru ����� ����� ������� �� ���������.
  virtual void CalcPointCurve( double t, MbCartPoint & point ) const;
  /// \ru ���������� ��� ������.
  virtual TypeCurve Type() const;
  /// \ru ���������� ������ ����������� �� ���������.
  virtual void FirstDerivative(double, MbVector & vector ) const;
  /// \ru ���������� ������ ����������� �� ���������.
  virtual void SecondDerivative( double , MbVector & vector ) const;
  /// \ru ���������� �������� ������ � �����.
  virtual double Curvature( double t );
  /// \ru �������� ������ ������� �����.
  virtual void GetDataCurve( vector< MbCartPoint > & controlPoints, vector< MbVector > & ) const;
  /// \ru �������� ����������� �������� ���������.
  virtual double GetMinParam() const;
  /// \ru �������� ������������ �������� ���������.
  virtual double GetMaxParam() const;
  /// \ru �������� ������ ������.
  virtual void SetDataCurve( vector< MbCartPoint > & points, vector< MbVector > & vectors, size_t degree );
  /// \ru ������ � ����.
  virtual ofstream & out( ofstream & ofs ) const;
  /// \ru ������ �� �����.
  virtual ifstream & in( ifstream & ifs );  
};


#endif //__CURVE_LINE_SEGMENT_H_
