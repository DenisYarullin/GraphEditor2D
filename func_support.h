////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru ��������������� �������, �������������� ������� � ��������. \~

*/
////////////////////////////////////////////////////////////////////////////////


#ifndef __FUNC_SUPPORT_H_
#define __FUNC_SUPPORT_H


#include <QSharedPointer>
#include <vector>


class MbCartPoint;
class GraphCurve;
class MbCurve;


typedef QSharedPointer< MbCurve > MbCurvePtr;


using std::pair;
using std::vector;


/// \ru ���������� ���������� ����� �������� ������� � ������������ ������.
double DistBetweenPointSegment( const MbCartPoint &, const MbCartPoint &, const MbCartPoint & );


/// \ru ���������� ���������� ����� �������.
void ComputeIntersects( const MbCurvePtr curve1, const MbCurvePtr curve2 , vector< MbCartPoint > & roots );


/// \ru ���������� ��������� ����������� � ������� ������.
void FindInitApprLine( const MbCurvePtr, const MbCurvePtr, vector< pair< double, double> > & );


/// \ru �������, �������������� ��� ���������� ������ �� �������� ����������� ���������� ����� ���� �� ������.
bool SortPair( const pair< GraphCurve, double> &, const pair< GraphCurve, double > & );


/// \ru �������, �������������� ��� �������� ���������� ������ �� vector< pair >.
bool DeleteSelect( const GraphCurve & );


/// \ru �������, �������������� ��� �������� ����������� ������� vector< pair >.
bool DeleteDuplicate( const pair< double, double > &, const pair< double, double >  & );


/// \ru �������������� ������, �������������� ��� ������ ������ � vector< pair >.
struct FindFirst
{
    const MbCurvePtr toFind;
    FindFirst( const MbCurvePtr & i );
    bool operator() ( const GraphCurve & p ) const;
};


#endif // __FUNC_SUPPORT_H_
