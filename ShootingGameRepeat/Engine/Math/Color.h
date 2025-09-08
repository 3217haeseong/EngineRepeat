#pragma once

enum class Color : int
{
	Blue = 1,
	Green = 2,
	Cyan = Blue | Green,
	Red = 4,
	Magenta = Red | Blue,
	White = Red | Green | Blue,
	Intensity = 8,
	BackgroundBlue = 16,
	BackgroundGreen = 32,
	BackgroundIntensity = 128,
};