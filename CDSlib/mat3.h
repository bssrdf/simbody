

#ifndef __mat3_hh__
#define __mat3_hh__

#include <fixedMatrix.h>

class Mat3 : public FixedMatrix<float_type,3> {
public:
  typedef Mat3  TransposeType;

  typedef float_type Float;
  Mat3() : FixedMatrix<float_type,3>() {}
  Mat3(const FixedMatrixBase<float_type,3,3>& m) : 
    FixedMatrix<float_type,3,3>(m) {}
  explicit Mat3(const Float& x)   //initialize to constant
    : FixedMatrix<float_type,3>(x) {}
  explicit Mat3(const Float* x)   //initialize from row-major array
    : FixedMatrix<float_type,3>(x) {}

  Mat3& operator=(const FixedMatrixBase<float_type,3,3>& m)
  { FixedMatrixBase<float_type,3,3>::operator=(m); return *this;}

  inline
  explicit Mat3(const Float& m11, //specify values of all elements
		const Float& m12,
		const Float& m13,
		const Float& m21,
		const Float& m22,
		const Float& m23,
		const Float& m31,
		const Float& m32,
		const Float& m33);
};

Mat3::Mat3(const float_type& m11,
	   const float_type& m12,
	   const float_type& m13,
	   const float_type& m21,
	   const float_type& m22,
	   const float_type& m23,
	   const float_type& m31,
	   const float_type& m32,
	   const float_type& m33) : FixedMatrix<float_type,3>()
{
 data(0,0) = m11; data(0,1) = m12; data(0,2) = m13;
 data(1,0) = m21; data(1,1) = m22; data(1,2) = m23;
 data(2,0) = m31; data(2,1) = m32; data(2,2) = m33;
}

#endif /* __mat3_hh__ */
