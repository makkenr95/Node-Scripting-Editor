#pragma once
#include <array>
#include "Matrix4x4.hpp"
#include <math.h>
#include <assert.h>
#include "Vector3.hpp"

namespace CommonUtilities
{
	template <class T>
	class Matrix3x3
	{
	public:
		Matrix3x3<T>();
		Matrix3x3<T>(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>(const Matrix4x4<T>& aMatrix);
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;
		Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>& operator+=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T> operator-(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>& operator-=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>& operator*=(const Matrix3x3<T>& aMatrix);

		Matrix3x3<T>& operator=(const Matrix3x3<T>& aMatrix);
		bool operator==(Matrix3x3<T>& aMatrix);
		static Matrix3x3<T> CreateRotationAroundX(T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundY(T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundZ(T aAngleInRadians);
		static Matrix3x3<T> Transpose(const Matrix3x3<T>& aMatrixToTranspose);

	private:
		std::array<std::array<T, 3>, 3> myMatrix;
	};

	template <class T>
	inline Matrix3x3<T>::Matrix3x3()
	{
		myMatrix[0][0] = 1;
		myMatrix[0][1] = 0;
		myMatrix[0][2] = 0;
		myMatrix[1][0] = 0;
		myMatrix[1][1] = 1;
		myMatrix[1][2] = 0;
		myMatrix[2][0] = 0;
		myMatrix[2][1] = 0;
		myMatrix[2][2] = 1;
	}

	template <class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& aMatrix)
	{
		myMatrix = aMatrix.myMatrix;
	}

	template <class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
	{
		for (unsigned int rows = 0; rows < 3; rows++)
		{
			for (unsigned int columns = 0; columns < 3; columns++)
			{
				myMatrix[rows][columns] = aMatrix(rows + 1, columns + 1);
			}
		}
	}

	template <class T>
	inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
	{
		assert(aRow >= 1 && aRow < 3 + 1);
		assert(aColumn >= 1 && aColumn < 3 + 1);
		return myMatrix[aRow - 1][aColumn - 1];
	}

	template <class T>
	inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
	{
		assert(aRow >= 1 && aRow < 3 + 1);
		assert(aColumn >= 1 && aColumn < 3 + 1);
		return myMatrix[aRow - 1][aColumn - 1];
	}

	template <class T>
	inline Matrix3x3<T> Matrix3x3<T>::operator+(const Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> temp;
		for (unsigned int rows = 0; rows < 3; rows++)
		{
			for (unsigned int columns = 0; columns < 3; columns++)
			{
				temp.myMatrix[rows][columns] = myMatrix[rows][columns] + aMatrix(rows + 1, columns + 1);
			}
		}
		return temp;
	}

	template <class T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator+=(const Matrix3x3<T>& aMatrix)
	{
		return (*this) = (*this) + aMatrix;
	}

	template <class T>
	inline Matrix3x3<T> Matrix3x3<T>::operator-(const Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> temp;
		for (unsigned int rows = 0; rows < 3; rows++)
		{
			for (unsigned int columns = 0; columns < 3; columns++)
			{
				temp.myMatrix[rows][columns] = myMatrix[rows][columns] - aMatrix(rows + 1, columns + 1);
			}
		}
		return temp;
	}

	template <class T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator-=(const Matrix3x3<T>& aMatrix)
	{
		return (*this) = (*this) - aMatrix;
	}

	template <class T>
	inline Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> temp;
		for (unsigned int rows = 0; rows < 3; rows++)
		{
			for (unsigned int colums = 0; colums < 3; colums++)
			{
				T result = 0;
				for (unsigned int i = 0; i < 3; i++)
				{
					result += myMatrix[rows][i] * aMatrix(i + 1, colums + 1);
				}
				temp.myMatrix[rows][colums] = result;
			}
		}
		return temp;
	}

	template <class T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator*=(const Matrix3x3<T>& aMatrix)
	{
		return (*this) = (*this) * aMatrix;
	}

	template <class T>
	inline Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix)
	{
		Vector3<T> temp;
		temp.x = aVector.x * aMatrix(1, 1) + aVector.y * aMatrix(2, 1) + aVector.z * aMatrix(3, 1);
		temp.y = aVector.x * aMatrix(1, 2) + aVector.y * aMatrix(2, 2) + aVector.z * aMatrix(3, 2);
		temp.z = aVector.x * aMatrix(1, 3) + aVector.y * aMatrix(2, 3) + aVector.z * aMatrix(3, 3);
		return temp;
	}

	template <class T>
	inline Vector3<T> operator*=(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix)
	{
		return (aMatrix * aVector);
	}

	template <class T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator=(const Matrix3x3<T>& aMatrix)
	{
		for (unsigned int rows = 0; rows < 3; rows++)
		{
			for (unsigned int columns = 0; columns < 3; columns++)
			{
				myMatrix[rows][columns] = aMatrix(rows + 1, columns + 1);
			}
		}
		return *this;
	}

	template <class T>
	inline bool Matrix3x3<T>::operator==(Matrix3x3<T>& aMatrix)
	{
		for (unsigned int rows = 0; rows < 3; rows++)
		{
			for (unsigned int columns = 0; columns < 3; columns++)
			{
				if (myMatrix[rows][columns] != aMatrix(rows + 1, columns + 1))
				{
					return false;
				}
			}
		}
		return true;
	}

	template <class T>
	inline bool operator==(const Matrix3x3<T>& aMatrix0, const Matrix3x3<T>& aMatrix1)
	{
		for (unsigned int rows = 0; rows < 3; rows++)
		{
			for (unsigned int columns = 0; columns < 3; columns++)
			{
				if (aMatrix0(rows + 1, columns + 1) != aMatrix1(rows + 1, columns + 1))
				{
					return false;
				}
			}
		}
		return true;
	}

	template <class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		Matrix3x3 temp;
		temp(1, 1) = 1;
		temp(1, 2) = 0;
		temp(1, 3) = 0;
		temp(2, 1) = 0;
		temp(2, 2) = static_cast<T>(cos(aAngleInRadians));
		temp(2, 3) = static_cast<T>(sin(aAngleInRadians));
		temp(3, 1) = 0;
		temp(3, 2) = static_cast<T>(-sin(aAngleInRadians));
		temp(3, 3) = static_cast<T>(cos(aAngleInRadians));

		return temp;
	}

	template <class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		Matrix3x3 temp;
		temp(1, 1) = static_cast<T>(cos(aAngleInRadians));
		temp(1, 2) = 0;
		temp(1, 3) = static_cast<T>(-sin(aAngleInRadians));
		temp(2, 1) = 0;
		temp(2, 2) = 1;
		temp(2, 3) = 0;
		temp(3, 1) = static_cast<T>(sin(aAngleInRadians));
		temp(3, 2) = 0;
		temp(3, 3) = static_cast<T>(cos(aAngleInRadians));

		return temp;
	}

	template <class T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		Matrix3x3 temp;
		temp(1, 1) = static_cast<T>(cos(aAngleInRadians));
		temp(1, 2) = static_cast<T>(sin(aAngleInRadians));
		temp(1, 3) = 0;
		temp(2, 1) = static_cast<T>(-sin(aAngleInRadians));
		temp(2, 2) = static_cast<T>(cos(aAngleInRadians));
		temp(2, 3) = 0;
		temp(3, 1) = 0;
		temp(3, 2) = 0;
		temp(3, 3) = 1;

		return temp;
	}

	template <class T>
	inline Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& aMatrixToTranspose)
	{
		Matrix3x3 temp;
		temp(1, 1) = aMatrixToTranspose(1, 1);
		temp(1, 2) = aMatrixToTranspose(2, 1);
		temp(1, 3) = aMatrixToTranspose(3, 1);
		temp(2, 1) = aMatrixToTranspose(1, 2);
		temp(2, 2) = aMatrixToTranspose(2, 2);
		temp(2, 3) = aMatrixToTranspose(3, 2);
		temp(3, 1) = aMatrixToTranspose(1, 3);
		temp(3, 2) = aMatrixToTranspose(2, 3);
		temp(3, 3) = aMatrixToTranspose(3, 3);
		return temp;
	}
}

namespace CU = CommonUtilities;
