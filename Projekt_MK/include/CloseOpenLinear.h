#pragma once

#include "Headers.h"

public ref class CloseOpenLinear
{
	public:
		CloseOpenLinear(Bitmap^ Image);
		~CloseOpenLinear();

		Bitmap^ imclose();
		Bitmap^ imopen();

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

		Bitmap^ Dilate(Bitmap^ source_image);

		Bitmap^ Erode(Bitmap^ source_image);

		void print_structural_el();

};