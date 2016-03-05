////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru ����������� ����� ��� ������.
         \en Abstract class for the curves. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __CURVE_ABSTRACT_CURVE_H_
#define __CURVE_ABSTRACT_CURVE_H_


#include <vector>
#include <fstream>


using std::vector;
using std::ofstream;
using std::ifstream;


class MbCartPoint;
class MbVector;


//------------------------------------------------------------------------------
/** \brief \ru ����������� ����� ��� ������.
           \en Abstract class for the curves. \~
  \details \ru  ����������� ����� ��� ������ �������� ����� ����������� �������, ���������������� � ����������� �������. \n
*/
//------------------------------------------------------------------------------


class MbCurve
{

private:
    /// \ru ����������� ����������� (�� �����������).
    MbCurve( const MbCurve & );
    /// \ru �������� ������������ (�� �����������).
    MbCurve & operator= (const MbCurve & );

public:

  enum TypeCurve ///< \ru ���� ������.
  {
      Segment,  ///< \ru �������.
      Ellipse,  ///< \ru ������.
      Nurbs     ///< \ru Nurbs.
  };

  /// \ru ����������� �� ���������.
  MbCurve();
  /// \ru ����������.
  virtual ~MbCurve();

  /// \ru ������ ����������� ������� ��� ���������� ����� �� ���������.
  virtual void CalcPointCurve( double t, MbCartPoint & point) const = 0;
  /// \ru ������ ����������� ������� ��� ����������� ���� ������.
  virtual TypeCurve Type() const = 0;
  /// \ru ������ ����������� ������� ��� ����������� ������ ����������� �� ���������.
  virtual void FirstDerivative( double t, MbVector & vector ) const = 0;
  /// \ru ������ ����������� ������� ��� ����������� ������ ����������� �� ���������.
  virtual void SecondDerivative( double t, MbVector & vector ) const = 0;
  /// \ru ������� ��� ����������� �������� ������ � �����.
  virtual double Curvature( double t ) const;
  /// \ru ������� ��� ���������� ������������ �������� ��������� � ������������ � ���������.
  virtual void StepParameter( double minT, double maxT, vector< double > & parameters );
  /// \ru �������� ������ ������� �����.
  virtual void GetDataCurve( vector< MbCartPoint > & points, vector< MbVector > & vectors ) const = 0;
  /// \ru �������� ����������� �������� ���������.
  virtual double GetMinParam() const = 0;
  /// \ru �������� ������������ �������� ���������.
  virtual double GetMaxParam() const = 0;
  /// \ru �������� ������ ������.
  virtual void SetDataCurve( vector< MbCartPoint > & points, vector< MbVector > & vectors, size_t degree ) = 0;
  /// \ru ������ � ����.
  virtual ofstream & out( ofstream & ofs ) const = 0;
  /// \ru ������ �� �����.
  virtual ifstream & in( ifstream & ifs ) = 0;

  /// \ru �������� ������ � �����.
  friend ofstream & operator<< ( ofstream & out, const MbCurve * );
  /// \ru �������� ����� � �����.
  friend ifstream & operator>> ( ifstream & in, MbCurve * );
};


#endif //__CURVE_ABSTRACT_CURVE_H_
