////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru ������. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __CURVE_ELLIPSE_H_
#define __CURVE_ELLIPSE__H_


#include "mb_vector.h"
#include <fstream>


class MbVector;
class MbCartPoint;
class MbCurve;


using std::ofstream;
using std::ifstream;


//------------------------------------------------------------------------------
/** \brief \ru ����� �������. \~
  \details \ru ������ �������� �������� ������ MbCurve. \n
*/
//------------------------------------------------------------------------------


class MbEllipse : public MbCurve
{

private:

  mutable MbCartPoint         center;       ///< \ru ����������� �����.
          MbVector            xa;           ///< \ru ������ ��� ����� ��������� �� ��� X.
          MbVector            yb;           ///< \ru ������ ��� ����� ��������� �� ��� Y.

private:
  /// \ru ����������� �� ����������� ����� � ���� ��������.
  MbEllipse( MbCartPoint & centerPoint, MbVector & xaVec, MbVector & xbVec );

public:

  /// \ru ����������� �� ���������.
  MbEllipse();
  /// \ru ����������� �� ���� ������.
  MbEllipse( MbCartPoint & centerPoint, MbCartPoint & minPoint, MbCartPoint & maxPoint );

  /// \ru ����������� �����������.
  MbEllipse( const MbEllipse & );
  /// \ru ����������� ����������.
  virtual ~MbEllipse();

  /// \ru �������� ������������.
  MbEllipse & operator= ( const MbEllipse & );

  /// \ru ����� ��������� ����� ������� �� ���������.
  virtual void CalcPointCurve( double t,  MbCartPoint & point ) const;
  /// \ru ���������� ��� ������.
  virtual TypeCurve Type() const;
  /// \ru ���������� ������ ����������� �� ���������.
  virtual void FirstDerivative( double t, MbVector & vector ) const;
  /// \ru ���������� ������ ����������� �� ���������.
  virtual void SecondDerivative( double t, MbVector & vector ) const;
  /// \ru �������� ������ ������� �����.
  virtual void GetDataCurve( vector< MbCartPoint > & controlPoints, vector< MbVector > & vectors ) const;
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


#endif //__CURVE_ELLIPSE_H_
