#pragma once

#include "Headers.h"

public ref class LinearClosure
{
	public:
		LinearClosure(Bitmap^ Image);
		~LinearClosure();

		Bitmap^ Compute();

	private:
		Bitmap^ Img;
		Bitmap^ OutputImage;
		vector<int>* StructuralElement;

		/* -------------------  Auxiliary Functions -------------------  */
		void CreateStructuralElement(int length, int degree);

		int GetLength();

		int GetDegree();

		void Dilatation();

		void Erosion();

};