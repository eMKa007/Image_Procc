#pragma once

#include "Headers.h"

public ref class ConvexHull
{
	public:
		ConvexHull(Bitmap^ Image);
		~ConvexHull();

		Bitmap^ Compute();

	private:
		Bitmap^ SourceImage;
		array< array<int, 9>*, 8>* convex_masks;

		/* -------------------  Auxiliary Functions -------------------  */

		void fill_masks();

		void rotate_mask45(array<int, 9>* Mask);

		Bitmap^ compute_hull();

};