/**********************************************************************
Filename: GraphicElement.cpp
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
Purpose: This file is to prompt user input and add & delete each elements to vectors
         with inheritance.
*********************************************************************/
#include <string>
#include <vector>
#include <forward_list>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Image.h"
#include "GraphicElement.h"
#include "RasterGraphic.h"
#include "SystemMemoryImage.h"
#include "GPUMemoryImage.h"
/*********************************************************************
Function Name: InsertGraphicElement()
Purpose: insert elements to the RasterGraphic
Function In parameters: none
Function Out parameters: none
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
void RasterGraphic::InsertGraphicElement() {
	vector<Image*> temp_images;
	string temp_fileName;
	// calculates the elements' number between first and last
	int elementCount = distance(GraphicElements.begin(), GraphicElements.end());
	int index = 0;
	int temp_size;
	int temp_x;
	int temp_y;
	int temp_duration;
	int temp_type;
	char* temp_name = new char[512];
	// prompt user input
	cout << "Insert a GraphicElement in the RasterGraphic" << endl;
	cout << "Please enter the GraphicElement filename: ";
	cin >> temp_fileName;
	cout << "Entering the GraphicElement Images (the sets of dimensions and durations)" << endl;
	cout << "Please enter the number of Images: ";
	cin >> temp_size;
	cout << endl;
	// adding the each element to the display
	for (int i = 0; i < temp_size; i++)
	{
		cout << "Please enter pixel x-width for Image # " << i << " pixel_x:";
		cin >> temp_x;
		cout << "Please enter pixel y-width for Image # " << i << " pixel_y:";
		cin >> temp_y;
		cout << "Please enter the duration for this Image: ";
		cin >> temp_duration;
		cout << "Please enter the name for this Image: ";
		cin >> temp_name;
		// check range 
		do
		{
			cout << "Please enter the type for this Image (1 = SystemMemoryImage, 2 = GPUMemoryImage): ";
			cin >> temp_type;
		} while (temp_type > 2 || temp_type < 1);

		Image* image(nullptr);
		/* add the types into the different types */
		if (temp_type == 1)
		{
			image = new SystemMemoryImage(temp_x, temp_y, temp_duration, temp_name);
			temp_images.push_back(image);
			cout << endl;
		}
		else if (temp_type == 2)
		{
			string tempShaderName;

			cout << "Please enter the file name of the associated GPU Shader: ";
			cin >> tempShaderName;
			image = new GPUMemoryImage(temp_x, temp_y, temp_duration, temp_name, tempShaderName);
			temp_images.push_back(image);
			cout << endl;
		}
	}
	// create object
	GraphicElement graphicElement(temp_fileName, temp_images);
	// if GraphicElement is empty, push GraphicElement into originall one
	if (GraphicElements.empty())
	{
		cout << "This is the first GraphicElement in the list" << endl;
		GraphicElements.push_front(graphicElement);
	}
	else {
		// add the GraphicElement in the specified position if the elements is over 2 
		if (elementCount > 1) {
			do
			{
				cout << "There are " << elementCount << " GraphicElement(s) in the list" << endl;
				cout << "Please specify the position, between 0 and " << elementCount - 1 << " to insert after : ";
				cin >> index;
				while (index > elementCount)
				{
					cout << "Please specify the position, between 0 and " << elementCount - 1 << " to insert after : ";
					cin >> index;
				}
				//GraphicElements.insert_after(GraphicElements.begin(), GraphicElement(temp_fileName, temp_images));
			} while (index < 0 || index > elementCount - 1);

			forward_list<GraphicElement>::iterator i;
			i = GraphicElements.begin();
			if (index == 0)
			{
				i = GraphicElements.insert_after(i, graphicElement);
			}
			else
			{
				forward_list<GraphicElement>::iterator i2;
				i2 = i;
				++i2;
				GraphicElements.insert_after(i2, graphicElement);
			}
		}
		else {
			GraphicElements.push_front(graphicElement);
			// to swap the elements' order
			GraphicElements.reverse();
		}
	}
	cout << endl;
	delete[] temp_name;
}
/*********************************************************************
Function Name: DeleteGraphicElement()
Purpose: to delete the first element from top of the vector
Function In parameters: none
Function Out parameters: none
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
void RasterGraphic::DeleteGraphicElement() {

	if (GraphicElements.empty())
		cout << "The GraphicElement is empty" << endl;
	else {
		GraphicElements.pop_front();
		cout << "To clear GraphicElement, now it is empty" << endl;
	}
	cout << endl;
}
/*********************************************************************
Function Name: operator<<
Purpose: to display the elements, it has to be overloaded to the ostream.
Function In parameters: ostream& ostream, RasterGraphic& rasterGraphic
Function Out parameters: ostream&
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
ostream& operator<<(ostream& ostream, RasterGraphic& rasterGraphic) {
	// iteratoe and display 
	if (rasterGraphic.GraphicElements.empty()) {
		ostream << "The GraphicElement is empty" << endl;
	}
	else {
		int counter = 0;
		forward_list<GraphicElement>::iterator i;

		ostream << "RasterElement " << rasterGraphic.name << endl << "Run the RasterElement" << endl;
		i = rasterGraphic.GraphicElements.begin();
		while (i != rasterGraphic.GraphicElements.end())
		{
			ostream << "GraphicElement #" << counter++ << ":" << endl << *i;
			i++;
		}
		ostream << endl;
	}
	ostream << "Output finished" << endl;
	return ostream;
}