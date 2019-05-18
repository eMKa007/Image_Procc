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
		array<int, 9>* StructuralElement;


};