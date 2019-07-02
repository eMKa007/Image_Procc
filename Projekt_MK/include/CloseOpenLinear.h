#pragma once

#include "Headers.h"

/*
 * CloseOpenLinear class is used to apply 
 * image open/close procedure. It is implemented
 * by proper assembly of erosion and dilatation.
 * Linear structural element is created during
 * runtime. User have to set length and inclination
 * of linear element.
 */
public ref class CloseOpenLinear
{
	public:
		CloseOpenLinear(Drawing::Bitmap^ Image);
		~CloseOpenLinear();

		Drawing::Bitmap^ imclose();
		Drawing::Bitmap^ imopen();

	private:
		Drawing::Bitmap^ Img;
		Drawing::Bitmap^ OutputImage;
		vector<int>* StructuralElement;

		int structural_element_anchor_x;
		int structural_element_anchor_y;
		int structural_element_width;
		int structural_element_height;

		/* -------------------  Auxiliary Functions -------------------  */
		void CreateStructuralElement(int length, int degree);

		int GetLength();

		int GetDegree();

		Drawing::Bitmap^ Dilate(Drawing::Bitmap^ source_image);

		Drawing::Bitmap^ Erode(Drawing::Bitmap^ source_image);

		void print_structural_el();

};