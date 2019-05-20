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

		int structural_element_anchor_x;
		int structural_element_anchor_y;
		int structural_element_width;
		int structural_element_height;

		/* -------------------  Auxiliary Functions -------------------  */
		void CreateStructuralElement(int length, int degree);

		int GetLength();

		int GetDegree();

		Bitmap^ Dilatation(Bitmap^ source_image);

		Bitmap^ Erosion(Bitmap^ source_image);

};