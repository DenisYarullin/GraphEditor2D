////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru Вспомогательные функции, функциональные объекты и функторы. \~

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


/// \ru Вычисление расстояния между отрезком приямой и произвольной точкой.
double DistBetweenPointSegment( const MbCartPoint &, const MbCartPoint &, const MbCartPoint & );


/// \ru Нахождение пресечение между кривыми.
void ComputeIntersects( const MbCurvePtr curve1, const MbCurvePtr curve2 , vector< MbCartPoint > & roots );


/// \ru Нахождение начальных приближений с помощью прямых.
void FindInitApprLine( const MbCurvePtr, const MbCurvePtr, vector< pair< double, double> > & );


/// \ru Функтор, использующийся при сортировке кривых по признаку наименьшего расстояния клика мыши от кривой.
bool SortPair( const pair< GraphCurve, double> &, const pair< GraphCurve, double > & );


/// \ru Функтор, использующийся для удаления выделенных кривых из vector< pair >.
bool DeleteSelect( const GraphCurve & );


/// \ru Функтор, использующийся для удаления совпадающих решений vector< pair >.
bool DeleteDuplicate( const pair< double, double > &, const pair< double, double >  & );


/// \ru Функциональный объект, использующийся для поиска кривой в vector< pair >.
struct FindFirst
{
    const MbCurvePtr toFind;
    FindFirst( const MbCurvePtr & i );
    bool operator() ( const GraphCurve & p ) const;
};


#endif // __FUNC_SUPPORT_H_
