////////////////////////////////////////////////////////////////////////////////
/** 
  \file
  \brief \ru ������. \~

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef __MB_VECTOR_H_
#define __MB_VECTOR_H_


#include <cmath>
#include <iostream>
#include <fstream>


using std :: ofstream;
using std :: ifstream;


//------------------------------------------------------------------------------
/** \brief \ru ����� �������. \~
  \details \ru ����� ������� ����������� ����� ������������ � �������� ������������: ����������� x � ����������� y. \n
*/
//------------------------------------------------------------------------------


class MbVector
{

public:

  double ax;  /// \ru ���������� ������� x.
  double ay;  /// \ru ���������� ������� y.

  /// \ru ����������� �� ���������.
  MbVector ();
  /// \ru ����������� �� �����������.
  MbVector( double xx, double yy );
  /// \ru ����������� �����������.
  MbVector( const MbVector & );
  /// \ru ����������.
  ~MbVector();

  /// \ru ������������� �� �������� �����������.
  void 	Initialization( double xx, double yy );
  /// \ru ������������� �������� ��������.
  void 	Initialization( const MbVector & );
  /// \ru ���������� ����� �������.
  double LengthOfVector() const;
  /// \ru �������� ������ ���������� �������.
  double GetAx () const;
  /// \ru �������� ������ ���������� �������.
  double GetAy () const;
  /// \ru ���������� ������ ���������� �������.
  void SetAx( double );
  /// \ru ���������� ������ ���������� �������.
  void SetAy( double );
  /// \ru ������������ �������.
  MbVector Normalization();


  /// \ru �������� ������������.
  MbVector & operator= ( const MbVector & );
  /// \ru �������� ���������.
  bool 	operator== ( const MbVector & ) const;
  /// \ru �������� �����������.
  bool 	operator!= ( const MbVector & ) const;


  MbVector operator- () const;
  /// \ru ����� ���� ��������.
  MbVector 	operator+ ( const MbVector & ) const;
  /// \ru �������� ���� ��������.
  MbVector 	operator- ( const MbVector & ) const;
  /// \ru ��������� ������� �� �����.
  MbVector 	operator* ( double number ) const;
  /// \ru ������� ������� �� �����.
  MbVector 	operator/ ( double number ) const;

  /// \ru ����� ���� ��������.
  void 	operator+= ( const MbVector & );
  /// \ru �������� ���� ��������.
  void 	operator-= ( const MbVector & );
  /// \ru ��������� ������� �� �����.
  void 	operator*= ( double );
  /// \ru ������� ������� �� �����.
  void 	operator/= ( double );
  /// \ru ��������� ������������ ���� ��������.
  double operator* ( const MbVector & ) const;
  /// \ru ��������� ������������ ��� ���������� ��������.
  double VectorProduct( const MbVector & ) const;

  /// \ru ��������������� ������� ��� ������ � �����.
  friend ofstream & operator<< ( ofstream & out, const MbVector & );
  friend ifstream & operator>> ( ifstream & in, MbVector & );
};


#endif //__MB_VECTOR_H_
