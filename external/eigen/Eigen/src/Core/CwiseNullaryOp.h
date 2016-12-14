// Copyright (C) 2008-2010 Gael Guennebaud <gael.guennebaud@inria.fr>
// Public License v. 2.0. If a copy of the MPL was not distributed

#ifndef EIGEN_CWISE_NULLARY_OP_H
#define EIGEN_CWISE_NULLARY_OP_H

namespace Eigen {


namespace internal {
template<typename NullaryOp, typename PlainObjectType>
struct traits<CwiseNullaryOp<NullaryOp, PlainObjectType> > : traits<PlainObjectType>
{
  enum {
    Flags = (traits<PlainObjectType>::Flags
      & (  HereditaryBits
         | (functor_has_linear_access<NullaryOp>::ret ? LinearAccessBit : 0)
         | (functor_traits<NullaryOp>::PacketAccess ? PacketAccessBit : 0)))
      | (functor_traits<NullaryOp>::IsRepeatable ? 0 : EvalBeforeNestingBit),
    CoeffReadCost = functor_traits<NullaryOp>::Cost
  };
};
}

template<typename NullaryOp, typename PlainObjectType>
class CwiseNullaryOp : internal::no_assignment_operator,
  public internal::dense_xpr_base< CwiseNullaryOp<NullaryOp, PlainObjectType> >::type
{
  public:

    typedef typename internal::dense_xpr_base<CwiseNullaryOp>::type Base;
    EIGEN_DENSE_PUBLIC_INTERFACE(CwiseNullaryOp)

    CwiseNullaryOp(Index nbRows, Index nbCols, const NullaryOp& func = NullaryOp())
      : m_rows(nbRows), m_cols(nbCols), m_functor(func)
    {
      eigen_assert(nbRows >= 0
            && (RowsAtCompileTime == Dynamic || RowsAtCompileTime == nbRows)
            &&  nbCols >= 0
            && (ColsAtCompileTime == Dynamic || ColsAtCompileTime == nbCols));
    }

    EIGEN_STRONG_INLINE Index rows() const { return m_rows.value(); }
    EIGEN_STRONG_INLINE Index cols() const { return m_cols.value(); }

    EIGEN_STRONG_INLINE const Scalar coeff(Index rowId, Index colId) const
    {
      return m_functor(rowId, colId);
    }

    template<int LoadMode>
    EIGEN_STRONG_INLINE PacketScalar packet(Index rowId, Index colId) const
    {
      return m_functor.packetOp(rowId, colId);
    }

    EIGEN_STRONG_INLINE const Scalar coeff(Index index) const
    {
      return m_functor(index);
    }

    template<int LoadMode>
    EIGEN_STRONG_INLINE PacketScalar packet(Index index) const
    {
      return m_functor.packetOp(index);
    }

    
    const NullaryOp& functor() const { return m_functor; }

  protected:
    const internal::variable_if_dynamic<Index, RowsAtCompileTime> m_rows;
    const internal::variable_if_dynamic<Index, ColsAtCompileTime> m_cols;
    const NullaryOp m_functor;
};


template<typename Derived>
template<typename CustomNullaryOp>
EIGEN_STRONG_INLINE const CwiseNullaryOp<CustomNullaryOp, Derived>
DenseBase<Derived>::NullaryExpr(Index rows, Index cols, const CustomNullaryOp& func)
{
  return CwiseNullaryOp<CustomNullaryOp, Derived>(rows, cols, func);
}

template<typename Derived>
template<typename CustomNullaryOp>
EIGEN_STRONG_INLINE const CwiseNullaryOp<CustomNullaryOp, Derived>
DenseBase<Derived>::NullaryExpr(Index size, const CustomNullaryOp& func)
{
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
  if(RowsAtCompileTime == 1) return CwiseNullaryOp<CustomNullaryOp, Derived>(1, size, func);
  else return CwiseNullaryOp<CustomNullaryOp, Derived>(size, 1, func);
}

template<typename Derived>
template<typename CustomNullaryOp>
EIGEN_STRONG_INLINE const CwiseNullaryOp<CustomNullaryOp, Derived>
DenseBase<Derived>::NullaryExpr(const CustomNullaryOp& func)
{
  return CwiseNullaryOp<CustomNullaryOp, Derived>(RowsAtCompileTime, ColsAtCompileTime, func);
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::ConstantReturnType
DenseBase<Derived>::Constant(Index nbRows, Index nbCols, const Scalar& value)
{
  return DenseBase<Derived>::NullaryExpr(nbRows, nbCols, internal::scalar_constant_op<Scalar>(value));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::ConstantReturnType
DenseBase<Derived>::Constant(Index size, const Scalar& value)
{
  return DenseBase<Derived>::NullaryExpr(size, internal::scalar_constant_op<Scalar>(value));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::ConstantReturnType
DenseBase<Derived>::Constant(const Scalar& value)
{
  EIGEN_STATIC_ASSERT_FIXED_SIZE(Derived)
  return DenseBase<Derived>::NullaryExpr(RowsAtCompileTime, ColsAtCompileTime, internal::scalar_constant_op<Scalar>(value));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::SequentialLinSpacedReturnType
DenseBase<Derived>::LinSpaced(Sequential_t, Index size, const Scalar& low, const Scalar& high)
{
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
  return DenseBase<Derived>::NullaryExpr(size, internal::linspaced_op<Scalar,false>(low,high,size));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::SequentialLinSpacedReturnType
DenseBase<Derived>::LinSpaced(Sequential_t, const Scalar& low, const Scalar& high)
{
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
  EIGEN_STATIC_ASSERT_FIXED_SIZE(Derived)
  return DenseBase<Derived>::NullaryExpr(Derived::SizeAtCompileTime, internal::linspaced_op<Scalar,false>(low,high,Derived::SizeAtCompileTime));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::RandomAccessLinSpacedReturnType
DenseBase<Derived>::LinSpaced(Index size, const Scalar& low, const Scalar& high)
{
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
  return DenseBase<Derived>::NullaryExpr(size, internal::linspaced_op<Scalar,true>(low,high,size));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::RandomAccessLinSpacedReturnType
DenseBase<Derived>::LinSpaced(const Scalar& low, const Scalar& high)
{
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
  EIGEN_STATIC_ASSERT_FIXED_SIZE(Derived)
  return DenseBase<Derived>::NullaryExpr(Derived::SizeAtCompileTime, internal::linspaced_op<Scalar,true>(low,high,Derived::SizeAtCompileTime));
}

template<typename Derived>
bool DenseBase<Derived>::isApproxToConstant
(const Scalar& val, const RealScalar& prec) const
{
  for(Index j = 0; j < cols(); ++j)
    for(Index i = 0; i < rows(); ++i)
      if(!internal::isApprox(this->coeff(i, j), val, prec))
        return false;
  return true;
}

template<typename Derived>
bool DenseBase<Derived>::isConstant
(const Scalar& val, const RealScalar& prec) const
{
  return isApproxToConstant(val, prec);
}

template<typename Derived>
EIGEN_STRONG_INLINE void DenseBase<Derived>::fill(const Scalar& val)
{
  setConstant(val);
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived& DenseBase<Derived>::setConstant(const Scalar& val)
{
  return derived() = Constant(rows(), cols(), val);
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived&
PlainObjectBase<Derived>::setConstant(Index size, const Scalar& val)
{
  resize(size);
  return setConstant(val);
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived&
PlainObjectBase<Derived>::setConstant(Index nbRows, Index nbCols, const Scalar& val)
{
  resize(nbRows, nbCols);
  return setConstant(val);
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived& DenseBase<Derived>::setLinSpaced(Index newSize, const Scalar& low, const Scalar& high)
{
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
  return derived() = Derived::NullaryExpr(newSize, internal::linspaced_op<Scalar,false>(low,high,newSize));
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived& DenseBase<Derived>::setLinSpaced(const Scalar& low, const Scalar& high)
{
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
  return setLinSpaced(size(), low, high);
}


template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::ConstantReturnType
DenseBase<Derived>::Zero(Index nbRows, Index nbCols)
{
  return Constant(nbRows, nbCols, Scalar(0));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::ConstantReturnType
DenseBase<Derived>::Zero(Index size)
{
  return Constant(size, Scalar(0));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::ConstantReturnType
DenseBase<Derived>::Zero()
{
  return Constant(Scalar(0));
}

template<typename Derived>
bool DenseBase<Derived>::isZero(const RealScalar& prec) const
{
  for(Index j = 0; j < cols(); ++j)
    for(Index i = 0; i < rows(); ++i)
      if(!internal::isMuchSmallerThan(this->coeff(i, j), static_cast<Scalar>(1), prec))
        return false;
  return true;
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived& DenseBase<Derived>::setZero()
{
  return setConstant(Scalar(0));
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived&
PlainObjectBase<Derived>::setZero(Index newSize)
{
  resize(newSize);
  return setConstant(Scalar(0));
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived&
PlainObjectBase<Derived>::setZero(Index nbRows, Index nbCols)
{
  resize(nbRows, nbCols);
  return setConstant(Scalar(0));
}


template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::ConstantReturnType
DenseBase<Derived>::Ones(Index nbRows, Index nbCols)
{
  return Constant(nbRows, nbCols, Scalar(1));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::ConstantReturnType
DenseBase<Derived>::Ones(Index newSize)
{
  return Constant(newSize, Scalar(1));
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename DenseBase<Derived>::ConstantReturnType
DenseBase<Derived>::Ones()
{
  return Constant(Scalar(1));
}

template<typename Derived>
bool DenseBase<Derived>::isOnes
(const RealScalar& prec) const
{
  return isApproxToConstant(Scalar(1), prec);
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived& DenseBase<Derived>::setOnes()
{
  return setConstant(Scalar(1));
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived&
PlainObjectBase<Derived>::setOnes(Index newSize)
{
  resize(newSize);
  return setConstant(Scalar(1));
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived&
PlainObjectBase<Derived>::setOnes(Index nbRows, Index nbCols)
{
  resize(nbRows, nbCols);
  return setConstant(Scalar(1));
}


template<typename Derived>
EIGEN_STRONG_INLINE const typename MatrixBase<Derived>::IdentityReturnType
MatrixBase<Derived>::Identity(Index nbRows, Index nbCols)
{
  return DenseBase<Derived>::NullaryExpr(nbRows, nbCols, internal::scalar_identity_op<Scalar>());
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename MatrixBase<Derived>::IdentityReturnType
MatrixBase<Derived>::Identity()
{
  EIGEN_STATIC_ASSERT_FIXED_SIZE(Derived)
  return MatrixBase<Derived>::NullaryExpr(RowsAtCompileTime, ColsAtCompileTime, internal::scalar_identity_op<Scalar>());
}

template<typename Derived>
bool MatrixBase<Derived>::isIdentity
(const RealScalar& prec) const
{
  for(Index j = 0; j < cols(); ++j)
  {
    for(Index i = 0; i < rows(); ++i)
    {
      if(i == j)
      {
        if(!internal::isApprox(this->coeff(i, j), static_cast<Scalar>(1), prec))
          return false;
      }
      else
      {
        if(!internal::isMuchSmallerThan(this->coeff(i, j), static_cast<RealScalar>(1), prec))
          return false;
      }
    }
  }
  return true;
}

namespace internal {

template<typename Derived, bool Big = (Derived::SizeAtCompileTime>=16)>
struct setIdentity_impl
{
  static EIGEN_STRONG_INLINE Derived& run(Derived& m)
  {
    return m = Derived::Identity(m.rows(), m.cols());
  }
};

template<typename Derived>
struct setIdentity_impl<Derived, true>
{
  typedef typename Derived::Index Index;
  static EIGEN_STRONG_INLINE Derived& run(Derived& m)
  {
    m.setZero();
    const Index size = (std::min)(m.rows(), m.cols());
    for(Index i = 0; i < size; ++i) m.coeffRef(i,i) = typename Derived::Scalar(1);
    return m;
  }
};

} 

template<typename Derived>
EIGEN_STRONG_INLINE Derived& MatrixBase<Derived>::setIdentity()
{
  return internal::setIdentity_impl<Derived>::run(derived());
}

template<typename Derived>
EIGEN_STRONG_INLINE Derived& MatrixBase<Derived>::setIdentity(Index nbRows, Index nbCols)
{
  derived().resize(nbRows, nbCols);
  return setIdentity();
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename MatrixBase<Derived>::BasisReturnType MatrixBase<Derived>::Unit(Index newSize, Index i)
{
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
  return BasisReturnType(SquareMatrixType::Identity(newSize,newSize), i);
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename MatrixBase<Derived>::BasisReturnType MatrixBase<Derived>::Unit(Index i)
{
  EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived)
  return BasisReturnType(SquareMatrixType::Identity(),i);
}

template<typename Derived>
EIGEN_STRONG_INLINE const typename MatrixBase<Derived>::BasisReturnType MatrixBase<Derived>::UnitX()
{ return Derived::Unit(0); }

template<typename Derived>
EIGEN_STRONG_INLINE const typename MatrixBase<Derived>::BasisReturnType MatrixBase<Derived>::UnitY()
{ return Derived::Unit(1); }

template<typename Derived>
EIGEN_STRONG_INLINE const typename MatrixBase<Derived>::BasisReturnType MatrixBase<Derived>::UnitZ()
{ return Derived::Unit(2); }

template<typename Derived>
EIGEN_STRONG_INLINE const typename MatrixBase<Derived>::BasisReturnType MatrixBase<Derived>::UnitW()
{ return Derived::Unit(3); }

} 

#endif 
