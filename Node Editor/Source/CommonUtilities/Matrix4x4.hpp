#pragma once
#include <array>
#include <math.h>
#include <assert.h>
#include "Vector3.hpp"
#include "Vector4.hpp"

namespace CommonUtilities
{
	template <class T>
	class Matrix4x4
	{
	public:
		Matrix4x4<T>();
		Matrix4x4<T>(const Matrix4x4<T>& aMatrix);
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;

		Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T>& operator+=(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T>& operator-=(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T>& operator*=(const Matrix4x4<T>& aMatrix);

		Matrix4x4<T>& operator=(const Matrix4x4<T>& aMatrix);
		bool operator==(const Matrix4x4<T>& aMatrix);
		static Matrix4x4<T> CreateRotationAroundX(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundY(T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundZ(T aAngleInRadians);
		static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose);
		static Matrix4x4<T> GetFastInverse(const Matrix4x4<T>& aTransform);
		const Vector3<T> Forward() const;
		const Vector3<T> Right() const;
		const Vector3<T> Up() const;
		//Vector3<T> GetRight();
		//Vector3<T> GetUP();
		//Vector3<T> GetForward();
		//Vector3<T> GetPosition();

	private:
		std::array<std::array<T, 4>, 4> myMatrix;
	};

	template <class T>
	inline Matrix4x4<T>::Matrix4x4()
	{
		myMatrix[0][0] = 1;
		myMatrix[0][1] = 0;
		myMatrix[0][2] = 0;
		myMatrix[0][3] = 0;

		myMatrix[1][0] = 0;
		myMatrix[1][1] = 1;
		myMatrix[1][2] = 0;
		myMatrix[1][3] = 0;

		myMatrix[2][0] = 0;
		myMatrix[2][1] = 0;
		myMatrix[2][2] = 1;
		myMatrix[2][3] = 0;

		myMatrix[3][0] = 0;
		myMatrix[3][1] = 0;
		myMatrix[3][2] = 0;
		myMatrix[3][3] = 1;
	}
	template<class T>
	inline const Vector3<T> Matrix4x4<T>::Right() const
	{
		return { myMatrix[0][0], myMatrix[0][1], myMatrix[0][2] };
	}

	template<class T>
	inline const Vector3<T> Matrix4x4<T>::Up() const
	{
		return { myMatrix[1][0], myMatrix[1][1], myMatrix[1][2] };
	}

	template<class T>
	inline const Vector3<T> Matrix4x4<T>::Forward() const
	{
		return { myMatrix[2][0], myMatrix[2][1], myMatrix[2][2] };
	}
	template <class T>
	inline Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
	{
		myMatrix = aMatrix.myMatrix;
	}

	template <class T>
	inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
	{
		assert(aRow >= 1 && aRow < 4 + 1);
		assert(aColumn >= 1 && aColumn < 4 + 1);
		return myMatrix[aRow - 1][aColumn - 1];
	}

	template <class T>
	inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
	{
		assert(aRow >= 1 && aRow < 4 + 1);
		assert(aColumn >= 1 && aColumn < 4 + 1);
		return myMatrix[aRow - 1][aColumn - 1];
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> temp;
		for (unsigned int rows = 0; rows < 4; rows++)
		{
			for (unsigned int columns = 0; columns < 4; columns++)
			{
				temp.myMatrix[rows][columns] = myMatrix[rows][columns] + aMatrix(rows + 1, columns + 1);
			}
		}
		return temp;
	}

	template <class T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator+=(const Matrix4x4<T>& aMatrix)
	{
		return (*this) = (*this) + aMatrix;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> temp;
		for (unsigned int rows = 0; rows < 4; rows++)
		{
			for (unsigned int columns = 0; columns < 4; columns++)
			{
				temp.myMatrix[rows][columns] = myMatrix[rows][columns] - aMatrix(rows + 1, columns + 1);
			}
		}
		return temp;
	}

	template <class T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator-=(const Matrix4x4<T>& aMatrix)
	{
		return (*this) = (*this) - aMatrix;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> temp;
		for (unsigned int rows = 0; rows < 4; rows++)
		{
			for (unsigned int colums = 0; colums < 4; colums++)
			{
				T result = 0;
				for (unsigned int i = 0; i < 4; i++)
				{
					result += myMatrix[rows][i] * aMatrix(i + 1, colums + 1);
				}
				temp.myMatrix[rows][colums] = result;
			}
		}
		return temp;
	}

	template <class T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator*=(const Matrix4x4<T>& aMatrix)
	{
		return (*this) = (*this) * aMatrix;
	}

	template <class T>
	inline Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix)
	{
		Vector4<T> tempColumn1(aMatrix(1, 1), aMatrix(2, 1), aMatrix(3, 1), aMatrix(4, 1));
		Vector4<T> tempColumn2(aMatrix(1, 2), aMatrix(2, 2), aMatrix(3, 2), aMatrix(4, 2));
		Vector4<T> tempColumn3(aMatrix(1, 3), aMatrix(2, 3), aMatrix(3, 3), aMatrix(4, 3));
		Vector4<T> tempColumn4(aMatrix(1, 4), aMatrix(2, 4), aMatrix(3, 4), aMatrix(4, 4));

		return Vector4<T>(aVector.Dot(tempColumn1), aVector.Dot(tempColumn2), aVector.Dot(tempColumn3),
						  aVector.Dot(tempColumn4));
	}

	template <class T>
	inline Vector4<T> operator*=(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix)
	{
		return (aMatrix * aVector);
	}

	template <class T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator=(const Matrix4x4<T>& aMatrix)
	{
		for (unsigned int rows = 0; rows < 4; rows++)
		{
			for (unsigned int columns = 0; columns < 4; columns++)
			{
				myMatrix[rows][columns] = aMatrix(rows + 1, columns + 1);
			}
		}
		return *this;
	}

	template <class T>
	inline bool Matrix4x4<T>::operator==(const Matrix4x4<T>& aMatrix)
	{
		for (unsigned int rows = 0; rows < 4; rows++)
		{
			for (unsigned int columns = 0; columns < 4; columns++)
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
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(T aAngleInRadians)
	{
		Matrix4x4<T> matrix;
		matrix(1, 1) = 1;
		matrix(1, 2) = 0;
		matrix(1, 3) = 0;
		matrix(1, 4) = 0;

		matrix(2, 1) = 0;
		matrix(2, 2) = static_cast<T>(cos(aAngleInRadians));
		matrix(2, 3) = static_cast<T>(sin(aAngleInRadians));
		matrix(2, 4) = 0;

		matrix(3, 1) = 0;
		matrix(3, 2) = static_cast<T>(-sin(aAngleInRadians));
		matrix(3, 3) = static_cast<T>(cos(aAngleInRadians));
		matrix(3, 4) = 0;

		matrix(4, 1) = 0;
		matrix(4, 2) = 0;
		matrix(4, 3) = 0;
		matrix(4, 4) = 1;

		return matrix;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(T aAngleInRadians)
	{
		Matrix4x4<T> matrix;
		matrix(1, 1) = static_cast<T>(cos(aAngleInRadians));
		matrix(1, 2) = 0;
		matrix(1, 3) = static_cast<T>(-sin(aAngleInRadians));
		matrix(1, 4) = 0;

		matrix(2, 1) = 0;
		matrix(2, 2) = 1;
		matrix(2, 3) = 0;
		matrix(2, 4) = 0;

		matrix(3, 1) = static_cast<T>(sin(aAngleInRadians));
		matrix(3, 2) = 0;
		matrix(3, 3) = static_cast<T>(cos(aAngleInRadians));
		matrix(3, 4) = 0;

		matrix(4, 1) = 0;
		matrix(4, 2) = 0;
		matrix(4, 3) = 0;
		matrix(4, 4) = 1;

		return matrix;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(T aAngleInRadians)
	{
		Matrix4x4<T> matrix;
		matrix(1, 1) = static_cast<T>(cos(aAngleInRadians));
		matrix(1, 2) = static_cast<T>(sin(aAngleInRadians));
		matrix(1, 3) = 0;
		matrix(1, 4) = 0;

		matrix(2, 1) = static_cast<T>(-sin(aAngleInRadians));
		matrix(2, 2) = static_cast<T>(cos(aAngleInRadians));
		matrix(2, 3) = 0;
		matrix(2, 4) = 0;

		matrix(3, 1) = 0;
		matrix(3, 2) = 0;
		matrix(3, 3) = 1;
		matrix(3, 4) = 0;

		matrix(4, 1) = 0;
		matrix(4, 2) = 0;
		matrix(4, 3) = 0;
		matrix(4, 4) = 1;

		return matrix;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4<T>& aMatrixToTranspose)
	{
		Matrix4x4<T> matrix;
		matrix(1, 1) = aMatrixToTranspose(1, 1);
		matrix(1, 2) = aMatrixToTranspose(2, 1);
		matrix(1, 3) = aMatrixToTranspose(3, 1);
		matrix(1, 4) = aMatrixToTranspose(4, 1);

		matrix(2, 1) = aMatrixToTranspose(1, 2);
		matrix(2, 2) = aMatrixToTranspose(2, 2);
		matrix(2, 3) = aMatrixToTranspose(3, 2);
		matrix(2, 4) = aMatrixToTranspose(4, 2);

		matrix(3, 1) = aMatrixToTranspose(1, 3);
		matrix(3, 2) = aMatrixToTranspose(2, 3);
		matrix(3, 3) = aMatrixToTranspose(3, 3);
		matrix(3, 4) = aMatrixToTranspose(4, 3);

		matrix(4, 1) = aMatrixToTranspose(1, 4);
		matrix(4, 2) = aMatrixToTranspose(2, 4);
		matrix(4, 3) = aMatrixToTranspose(3, 4);
		matrix(4, 4) = aMatrixToTranspose(4, 4);
		return matrix;
	}

	template <class T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& aTransform)
	{
		Matrix4x4 tempMatrix = Transpose(aTransform);

		Vector4<T> translation;
		translation.x = -aTransform(4, 1);
		translation.y = -aTransform(4, 2);
		translation.z = -aTransform(4, 3);
		translation.w = 0;

		tempMatrix(1, 4) = 0;
		tempMatrix(2, 4) = 0;
		tempMatrix(3, 4) = 0;
		tempMatrix(4, 4) = 1;

		translation = translation * tempMatrix;

		Matrix4x4 returnMatrix;
		returnMatrix.myMatrix[0][0] = tempMatrix.myMatrix[0][0];
		returnMatrix.myMatrix[0][1] = tempMatrix.myMatrix[0][1];
		returnMatrix.myMatrix[0][2] = tempMatrix.myMatrix[0][2];
		returnMatrix.myMatrix[0][3] = tempMatrix.myMatrix[0][3];

		returnMatrix.myMatrix[1][0] = tempMatrix.myMatrix[1][0];
		returnMatrix.myMatrix[1][1] = tempMatrix.myMatrix[1][1];
		returnMatrix.myMatrix[1][2] = tempMatrix.myMatrix[1][2];
		returnMatrix.myMatrix[1][3] = tempMatrix.myMatrix[1][3];

		returnMatrix.myMatrix[2][0] = tempMatrix.myMatrix[2][0];
		returnMatrix.myMatrix[2][1] = tempMatrix.myMatrix[2][1];
		returnMatrix.myMatrix[2][2] = tempMatrix.myMatrix[2][2];
		returnMatrix.myMatrix[2][3] = tempMatrix.myMatrix[2][3];

		returnMatrix.myMatrix[3][0] = translation.x;
		returnMatrix.myMatrix[3][1] = translation.y;
		returnMatrix.myMatrix[3][2] = translation.z;
		returnMatrix.myMatrix[3][3] = translation.w;

		returnMatrix(1, 4) = aTransform(1, 4);
		returnMatrix(2, 4) = aTransform(2, 4);
		returnMatrix(3, 4) = aTransform(3, 4);
		returnMatrix(4, 4) = aTransform(4, 4);

		return returnMatrix;
	}

	/*template <class T>
	Vector3<T> Matrix4x4<T>::GetRight()
	{
		Vector3<T> right(myMatrix[0, 0], myMatrix[1, 2], myMatrix[1, 3]);
		return right.GetNormalized();
	}

	template <class T>
	Vector3<T> Matrix4x4<T>::GetUP()
	{
		Vector3<T> up(myMatrix[2, 1], myMatrix[2, 2], myMatrix[2, 3]);
		return up.GetNormalized();
	}

	template <class T>
	Vector3<T> Matrix4x4<T>::GetForward()
	{
		Vector3<T> foward(myMatrix[3, 1], myMatrix[3, 2], myMatrix[3, 3]);
		return foward.GetNormalized();
	}

	template <class T>
	Vector3<T> Matrix4x4<T>::GetPosition()
	{
		Vector3<T> position(myMatrix[4, 1], myMatrix[4, 2], myMatrix[4, 3]);
		return position.GetNormalized();
	}*/

	template <class T>
	inline bool operator==(const Matrix4x4<T>& aMatrix0, const Matrix4x4<T>& aMatrix1)
	{
		for (unsigned int rows = 0; rows < 4; rows++)
		{
			for (unsigned int columns = 0; columns < 4; columns++)
			{
				if (aMatrix0(rows + 1, columns + 1) != aMatrix1(rows + 1, columns + 1))
				{
					return false;
				}
			}
		}
		return true;
	}
}

namespace CU = CommonUtilities;
