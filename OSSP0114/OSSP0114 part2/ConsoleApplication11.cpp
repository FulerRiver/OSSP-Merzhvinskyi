
#include "pch.h"
#include <iostream>
#include <xmmintrin.h>	// Need this for SSE compiler intrinsics
#include <math.h>		// Needed for sqrt in CPU-only version

#include <windows.h>
#include <intrin.h>
#include <bitset>
#include <vector>
#include <array>
#include <string>

//#define TIME_SSE	// Define this if you want to run with SSE

bool InfoSSE()
{
	std::vector<std::array<int, 4>> data;
	std::array<int, 4> CPUInfo;

	__cpuid(CPUInfo.data(), 0);
	int nIds = CPUInfo[0];

	for (int i = 0; i <= nIds; i++)
	{
		__cpuidex(CPUInfo.data(), i, 0);
		data.push_back(CPUInfo);
	}

	std::string ven;
	char vendor[0x20];

	memset(vendor, 0, sizeof(vendor));
	*reinterpret_cast<int*>(vendor) = data[0][1];
	*reinterpret_cast<int*>(vendor + 4) = data[0][3];
	*reinterpret_cast<int*>(vendor + 8) = data[0][2];

	ven = vendor;
	std::bitset<32> f;
	f = data[1][3];

	return (f[25] ? true : false);
}

int main()
{
	printf("Starting calculation...\n");
	const int length = 64000;

	// We will be calculating Y = Sin(x) / x, for x = 1->64000

	// If you do not properly align your data for SSE instructions, you may take a huge performance hit.
	float *pResult = (float*)_aligned_malloc(length * sizeof(float), 16);	// align to 16-byte for SSE
	__m128 x;
	__m128 xDelta = _mm_set1_ps(4.0f);		// Set the xDelta to (4,4,4,4)
	__m128 *pResultSSE = (__m128*) pResult;

	const int SSELength = length / 4;
	for (int stress = 0; stress < 100; stress++)	// lots of stress loops so we can easily use a stopwatch
	{
		if (InfoSSE())
		{
			x = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);	// Set the initial values of x to (4,3,2,1)
			for (int i = 0; i < SSELength; i++)
			{
				__m128 xSqrt = _mm_sqrt_ps(x);
				__m128 xRecip = _mm_rcp_ps(x);
				pResultSSE[i] = _mm_mul_ps(xRecip, xSqrt);
				x = _mm_add_ps(x, xDelta);	// Advance x to the next set of numbers
			}
		}
		else {
			float xFloat = 1.0f;
			for (int i = 0; i < length; i++)
			{
				pResult[i] = sqrt(xFloat) / xFloat;	// Even though division is slow, there are no intrinsic functions like there are in SSE
				xFloat += 1.0f;
			}
		}
	}

	// To prove that the program actually worked
	for (int i = 0; i < 20; i++)
	{
		printf("Result[%d] = %f\n", i, pResult[i]);
	}
}

