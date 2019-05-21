#pragma once

#include "Headers.h"

public ref class ConvexHull
{
	public:
		ConvexHull(Bitmap^ Image);
		~ConvexHull();

		Bitmap^ Compute();

	private:
		Bitmap^ Img;
		Bitmap^ OutputImage;
		array< array<int, 9>*, 8>* convex_masks;

		/* -------------------  Auxiliary Functions -------------------  */

		void create_masks();

		void rotate_mask45(array<int, 9>* Mask);

		void compute_hull();

};