/**********************************************************************
Filename: Image.cpp
Version: 1.0
Author: Seong-yeop Jeong
Student No: 040885882
Course Name/Number: C++ Programming CST8219
Lab Sect: 302
Assignment #: 3
Assignment name: RasterGraphic Project in C++ using Polymorphic Inheritance and RTTI
Due Date: December 1st 2018
Submission Date: December 1st 2018
Professor: Andrew Tyler
Purpose: This file is for holding locations, then display the objects.
		 Because of using delete function wtih virtual in image.h, 
		 this file doesn't need to use the new function for delete here.
*********************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 
using namespace std;

#include "Image.h"
#include "GPUMemoryImage.h"
#include "SystemMemoryImage.h"
/*********************************************************************
Function Name: Image()
Purpose: insert elements to the RasterGraphic
Function In parameters: int x, int y, int duration, char* name
Function Out parameters: Image
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
Image::Image(int x, int y, int duration, char* name) {
	this->pixel_x = x;
	this->pixel_y = y;
	this->duration = duration;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}
/*********************************************************************
Function Name: Image()
Purpose: initialize object, and allocate memory to copy strings to the name 
Function In parameters: const Image& display
Function Out parameters: Image
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
Image::Image(const Image& image) {
	this->pixel_x = image.pixel_x;
	this->pixel_y = image.pixel_y;
	this->duration = image.duration;
	this->name = new char[strlen(image.name) + 1];
	strcpy_s(this->name, (strlen(image.name) + 1), image.name);
}

/*********************************************************************
Function Name: operator<<
Purpose: overloaded << to display them all
Function In parameters: ostream& os, Image& image
Function Out parameters: ostream&
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
ostream& operator<<(ostream& os, Image& image) {

	os << "         Image name = " << image.name
		<< "; pixel_x = " << image.pixel_x
		<< ", pixel_y = " << image.pixel_y
		<< ", duration = " << image.duration << endl;
	
	os << "         Counting the seconds for this Image: ";
	for (int i = 1; i <= image.duration; i++)
	{
		os << i << ", ";
	}
	os << endl;
	os << "         Memory requirements = " << image.BufferSize()
		<< " bytes" << endl;

	return os;
}