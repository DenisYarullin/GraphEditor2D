    ////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru �����. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __MB_CART_POINT_H_
#define __MB_CART_POINT_H_

#include <iostream>
#include <fstream>
#include <cmath>


using std :: ofstream;
using std :: ifstream;
class MbVector;


//------------------------------------------------------------------------------
/** \brief \ru ����� �����. \~
  \details \ru ����� ����� ����������� ����� ������������: ����������� x � ����������� y. \n
*/
//------------------------------------------------------------------------------


class MbCartPoint
{

public:

  double x; ///< \ru ���������� x.
  double y; ///< \ru ���������� y.

  /// \ru ����������� �� ���������.
  MbCartPoint();
  /// \ru ����������� �����������.
  MbCartPoint( const MbCartPoint & );
  /// \ru ����������� �� �����������.
  MbCartPoint( double, double );
  /// \ru ����������� �� �������.
  MbCartPoint( const MbVector & other );
  /// \ru ���������� �� ���������.
  ~MbCartPoint();

  /// \ru ����� ���������� �� ����� �� �����.
  double GetLength( const MbCartPoint & ) const;
  /// \ru �������� �� �������� ����������.
  void Move( double, double );
  /// \ru ������������� ����� ������ ������.
  void InitPoint( const MbCartPoint & );
  /// \ru ������������� ����� ������������.
  void InitPoint( double, double );
  /// \ru �������� x ����������.
  double GetXCoord() const;
  /// \ru �������� y ����������.
  double GetYCoord() const;
  /// \ru ���������� x ����������.
  void SetXCoord( double );
  /// \ru ���������� y ����������.
  void SetYCoord( double );

  /// \ru �������� ������������ �� ���������.
  MbCartPoint & operator= ( const MbCartPoint &);
  /// \ ������������ ��������� ������� �����.
  void operator= ( const MbVector & );

  /// \ru ����� ���� �����.
  MbVector operator+ ( const MbCartPoint & );
  /// \ru �������� ���� �����.
  MbVector operator- ( const MbCartPoint & );
  /// \ru ����� ����� � �������.
  MbCartPoint operator+ ( const  MbVector & );
  /// \ru �������� ����� � �������.
  MbCartPoint operator- ( const MbVector & );
  /// \ru ������� �������� �����.
  MbCartPoint operator- ();

  /// \ru ��������� ����� �� �����.
  MbCartPoint operator* ( double ) const;
  /// \ru ������� ����� �� �����.
  MbCartPoint operator/ ( double ) const;

  /// \ru ����� ���� �����.
  void operator+= ( const MbCartPoint & );
  /// \ru �������� ���� �����.
  void operator-= ( const MbCartPoint & );
  /// \ru ��������� ����� �� �����.
  void operator*= ( double number );
  /// \ru ������� ����� �� �����.
  void operator/= ( double number );

  /// \ru �������� �� �����������.
   bool operator!= ( const MbCartPoint & ) const;
  /// \ru �������� �� ���������.
  bool operator== ( const MbCartPoint & ) const;
  /// \ru �������� �� <.
  bool operator< ( const MbCartPoint & ) const;
  /// \ru �������� �� >.
  bool operator> ( const MbCartPoint & ) const;

  /// \ru ��������������� ������� ��� ������ � �����.
  friend ofstream & operator<< ( ofstream & out, const MbCartPoint & );
  friend ifstream & operator>> ( ifstream & in, MbCartPoint & );
};


#endif //_MBCARTPOINT_H_
