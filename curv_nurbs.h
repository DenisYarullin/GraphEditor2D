////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru NURBS. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __CURVE_NURBS_H_
#define __CURVE_NURBS_H_


#include "mb_vector.h"
#include <vector>


using std :: vector;


class MbVector;
class MbCartPoint;
class MbCurve;


//------------------------------------------------------------------------------
/** \brief \ru ����� NURBS. \~
  \details \ru NURBS (������������ ������������ B-������) �������� �������� ������ MbCurve. \n
*/
//------------------------------------------------------------------------------


class MbNurbs : public MbCurve
{

private:

  vector< MbCartPoint > points;                    ///< \ru ������ ����������� ������� �����.
  size_t                degree;                    ///< \ru ������� B-�������.
  bool periodic;

  mutable vector< double > knot;                   ///< \ru ������� ������.
  mutable vector< double > weight;                 ///< \ru ������ � ����� ����������� �����.

  mutable double w;                                ///< \ru �����������  ������ ����� ���������.
  mutable double dw;                               ///< \ru ������ ����������� �����������.
  mutable double d2w;                              ///< \ru ������ ����������� �����������.

  mutable MbVector wr;                             ///< \ru ��������� ������ ����� ���������.
  mutable MbVector dwr;                            ///< \ru ������ ����������� ���������.
  mutable MbVector d2wr;                           ///< \ru ������ ����������� ���������.

public:

  /// \ru ����������� �� ���������.
  MbNurbs();
  /// \ru ����������� �� ���������� ������� ����� � ������� ������������ B-�������.
  MbNurbs( const vector< MbCartPoint > & _points, size_t _degree, bool _periodic = true );
  /// \ru ����������� ������������
  MbNurbs( const MbNurbs & );
  /// \ru �������� ������������
  MbNurbs & operator= ( const MbNurbs & );
  /// \ru ����������.
  virtual ~MbNurbs();

  /// \ru ���������� �������� ��������� ����� ��� ���������������� ���������.
  virtual void CalcPointCurve( double, MbCartPoint & point ) const;
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

private:

  /// \ru ���������� �������� �������.
  void SetKnotVector() const;
  /// \ru ���������� ������� � ������ ������.
  void SetWeightArray() const;
  /// \ru ���������� ������������� B-�������� ��� ������������� �������� ���������.
  void CalcNormBSplineFunc( double t, vector< vector< double> > & ) const;
  /// \ru ���������� ������-������� ������ ����� ������������� B-�������.
  void CalcNurbsFromNormB( double t, MbCartPoint & point ) const;
};


#endif //__CURVE_NURBS_H_
