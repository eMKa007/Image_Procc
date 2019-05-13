#pragma once

#include "Headers.h"

public ref class KirschFilt
{
public:
	KirschFilt(Bitmap^ Image);
	~KirschFilt();

	Bitmap^ Compute();

private:
	Bitmap^ Img;

};