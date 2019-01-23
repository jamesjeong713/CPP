/**********************************************************************
Filename: RasterGraphic.cpp
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
Purpose: This file is to do add the objects.
*********************************************************************/
#include <iostream>
#include <string> 
#include <vector>
using namespace std;

#include "Image.h"
#include "GraphicElement.h"
#include "GPUMemoryImage.h"
#include "SystemMemoryImage.h"
/*********************************************************************
Function Name: GraphicElement::GraphicElement
Purpose: it is to add the objects 
Function In parameters: const GraphicElement& graphicElement
Function Out parameters: GraphicElement
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
GraphicElement::GraphicElement(const GraphicElement& graphicElement) {
	fileName = graphicElement.fileName;

	for (vector<Image*>::const_iterator i = graphicElement.Images.begin();
		i != graphicElement.Images.end(); i++)
	{
		if (SystemMemoryImage* systemMemory = dynamic_cast<SystemMemoryImage*>(*i))
		{
			Images.push_back(new SystemMemoryImage(*systemMemory));
		}
		else if (GPUMemoryImage* gpuMemory = dynamic_cast<GPUMemoryImage*> (*i))
		{
			Images.push_back(new GPUMemoryImage(*gpuMemory));
		}
	}
}
/*********************************************************************
Function Name: operator<<
Purpose: overloaded operates graphic elements in the class
Function In parameters: ostream& os, GraphicElement& graphicElement
Function Out parameters: ostream&
Version: 1.0
Student Name: Seongyeop Jeong
*********************************************************************/
ostream& operator<<(ostream& os, GraphicElement& graphicElement) {
	int counter = 0;
	vector<Image*>::iterator i;

	// iterate and display it 
	os << "         fileName = " << graphicElement.fileName << endl;
	i = graphicElement.Images.begin();
	while (i != graphicElement.Images.end())
	{
		os << "         Image #" << counter++ << ":";
		if (dynamic_cast<SystemMemoryImage*>(*i) != nullptr)
			os << "System Memory Image" << endl;
		else
			os << "GPU Memory Image. Shader = " 
			<< dynamic_cast<GPUMemoryImage*>(*i)->GetShader() 
			<< endl;
		
		os << **i << endl;
		i++;
	}
	return os;
}