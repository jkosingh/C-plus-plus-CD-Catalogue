#include "cdcatalogue.h"
#include <string>
#include <iostream>
#include <ctype.h>
#include <cstdlib>

using namespace std;

CDCatalogue::CDCatalogue() // default constructor
{
	maxsize = 4;// initialize to 4
	cds = new CD[4];// Creates an empty CDCatalogue with default array size (4)
	numcds = 0; // initialize to zero
}

CDCatalogue::CDCatalogue(const CDCatalogue& cat) // copy constructor
{

	numcds = cat.numcds; //  copy of the cat parameter's fields
	maxsize = cat.maxsize; //  copy of the cat parameter's fields

	cds = new CD[maxsize]; // Creates a new CDCatalogue object,
	CopyArray(cat); // call to helper function to perform deep copy 
}

void CDCatalogue::CopyArray(const CDCatalogue& cat)
{
	for (int i = 0; i<numcds; i++)
	{
		cds[i] = cat.cds[i]; // Performs deep copy of dynamic array
	}
}

CDCatalogue ::~CDCatalogue()
{
	if (cds)
	{
		delete[] cds;// Releases all memory allocated to private pointer members
	}
}
// Insert - performs a set insertion with the CD catalogue
// Inserts CD and returns true if CD is not already in the catalogue
// Does not insert and returns false if a CD with a matching artist and album name
//   already exists in the registry
// If the array is already filled before the insertion occurs, then
//   first create a new dynamic array double the size of the old array,
//   copy all CD objects from old array to new array,
//   deallocate memory associated with the old array,
//   and insert the new CD and return true.
// POST:  catalogue contains CD
// PARAM: disc = item to be inserted, its fields should not be empty string
// NOTE:  since overloaded assignment operator has not been defined,
//          "insertion" will mean updating all fields of the CD at the appropriate index

bool CDCatalogue::Insert(CD disc)
{
	//need if stack is full because we cannot increase the size, make a new array
	// and copy the contents of the old one over

	if (numcds == maxsize) // if array full already -1
	{

		CD* old_list = cds; // creates a pointer to the original list
		maxsize = 2 * maxsize; // doubles the maxsize of the array
		cds = new CD[maxsize]; // creates a new array with new doubled max size

		for (int i = 0; i < numcds; i++) // for all elements in old array copy to new array  **MAXSIZE**
		{
			// copies from old list to new list one element at a time
			cds[i].UpdateAlbum(old_list[i].GetAlbum());
			cds[i].UpdateArtist(old_list[i].GetArtist());
		}
		delete[] old_list;//deallocate memory associated with the old array,
	}
	int exists = 0; // counter to count if element at index is already in the catalogue so if it is there don't add it
	for (int i = 0; i <= numcds; i++) // for every cd is cd catalogue
	{
		if (cds[i].GetAlbum() == disc.GetAlbum() && cds[i].GetArtist() == disc.GetArtist()) // if album and artist are the same as the disc objects being inserted
		{
			exists++; // increment the counter
		}
	}

	if (exists == 0) // if counter didn't increment then it wasn't already in the catalogue
	{
		cds[numcds].UpdateAlbum(disc.GetAlbum());
		cds[numcds].UpdateArtist(disc.GetArtist());
		numcds++; // number of cds have increased by one
		return true;
	}


	return false;

}

bool CDCatalogue::Remove(CD disc)
{

	if (numcds == 0) // just in case no disks in catalogue at the moment
	{
		return false;
	}
	int total = numcds; // variable to be the number of cds in catalogue currently
	numcds = 0; // so that the correct number of cds can be displayed in find function
	int removed = 0; // flag for if item that user want to be removed exists in the array/ catalogue

	CD* old_list = cds; // creates a pointer to the original list
	cds = new CD[maxsize]; // creates a new array with new doubled max size

	for (int i = 0; i < total; i++) // for every cd is cd catalogue
	{

		if (old_list[i].GetAlbum() == disc.GetAlbum() && old_list[i].GetArtist() == disc.GetArtist()) // if album and artist are the same as the object being removed
		{
			removed++; // increment flag
		}
		else
		{
			Insert(old_list[i]); // else it isn't the element to be removed so place it in the catalogue again
		}
	}

	delete[] old_list; //deallocate memory associated with the old array,

	if (removed > 0) // if flag is incremented
	{
		return true; // then it is true that the item wanting to be removed is in array
	}

	return false; // else wasn't in array




}


int CDCatalogue::Find(CD disc) const
{
	if (numcds == 0) // just in case no disks in catalogue at the moment
	{
		return -1;
	}
	for (int i = 0; i < numcds; i++) // for every cd is cd catalogue
	{
		if (cds[i].GetAlbum() == disc.GetAlbum() && cds[i].GetArtist() == disc.GetArtist()) // if album and artist are  the same as the disc objects being removed
		{
			return i;//return index number
		}

	}
	return -1;
}

bool CDCatalogue::Boycott(string dontlikeanymore)
{
	if (numcds == 0) // just in case no disks in catalogue at the moment
	{
		return false;
	}
	int total = numcds;// variable to be the number of cds in catalogue currently
	numcds = 0;// so that the correct number of cds can be displayed in find function
	int removed = 0;// flag for if item that user want to be removed exists in the array/ catalogue

	CD* old_list = cds; // creates a pointer to the original list
	cds = new CD[maxsize]; // creates a new array with new doubled max size

	for (int i = 0; i < total; i++) // for every cd is cd catalogue
	{
		if (old_list[i].GetArtist() != dontlikeanymore) // if artist doesn't matche the one you are boycotting
		{
			Insert(old_list[i]); //reinsert it into the list
		}
		else
		{
			removed++; // it is the one you're boycotting so falg is incremented
		}
	}

	delete[] old_list;//deallocate memory associated with the old array,


	if (removed > 0) //if flag incremented
	{
		return true; // then artist being boycotted was in catalogue at least once
	}

	return false; // artist being boycotted wasn't in catalogue
}

int CDCatalogue::Count() const
{
	return numcds; // returns the number of cds in the catlaogue at that time
}

CDCatalogue CDCatalogue::Join(const CDCatalogue& cat) const
{

	CDCatalogue joint; // catalogue that will return the CDs that are in the users catalogue and the new catalogue but not in both 
	int i = 0; // counter for indexing purposes of joint 

	for (i = 0; i< numcds; i++) // for every cd is cd catalogue
	{
		joint.Insert((cds[i])); // insert into joint, joint should also take care of doubles in the catalogue as well as it is built into insert function
	}

	for (int j = 0; j< cat.numcds; j++) // for every cd is cat catalogue
	{
		joint.Insert(CD(cat.cds[j]));  // insert into joint, joint should also take care of doubles in the catalogue as well as it is built into insert function
	}
	////**************PRINTING OUT PURPOSES**************************************//
	//		cout<<endl<<"This is joint"<<endl;
	//			for(int i =0; i< joint.numcds; i++)
	//			    {
	//					 cout<< joint.cds[i].GetArtist()<< "  "<<joint.cds[i].GetAlbum()<< endl;
	//				}  
	//
	return joint;

}
CDCatalogue CDCatalogue::Common(const CDCatalogue& cat) const
{
	CDCatalogue common;// catalogue that will return the doubles of CDs that are in the users catalogue and the new catalogue  
					   //if any of them is empty there is no commons
	if (numcds == 0 || cat.numcds == 0) // if either catalogue are empty there will be no doubles between them to return
	{
		return common; // empty catalogue
	}

	int isCommon = 0; // counter to count how many are in common between the two catalogues
	for (int i = 0; i< numcds; i++)// for every cd is cd catalogue
	{
		isCommon = 0; // reinitialize to 0 each time through
		for (int j = 0; j< cat.numcds; j++)// for every cd is cat catalogue
		{

			if (cds[i].GetAlbum() == cat.cds[j].GetAlbum() && cds[i].GetArtist() == cat.cds[j].GetArtist())// if album and artist are  the same as the disc catalogues
			{
				isCommon++; // is common becomes greater than 0
			}
		}

		if (isCommon > 0) // if it is a common occurance
		{
			common.Insert(cds[i]); // insert that cd in the common catalogue

		}
	}
	//**************PRINTING OUT PURPOSES**************************************//
	/*  cout<<endl<<"This is common"<<endl;
	for(int i =0; i < common.numcds; i++)


	{
	cout<< common.cds[i].GetAlbum()<< "  "<<common.cds[i].GetArtist()<< endl;

	}*/

	return common;
}



CDCatalogue CDCatalogue::Split(const CDCatalogue& cat) const
{
	CDCatalogue difference; // catalogue that will return the CDs that are in the users catalogue but not in the new catalogue equivalent to macms A-B 
	int count = 0;// counter for indexing initialized here so that the indexing for when cds are put in the catalogue are correct and are not trying to be put in a index that already has a CD


	if (numcds == 0) //if left hand side is empty there is no difference
	{
		return difference; // return the empty difference catalogue
	}

	else if (cat.numcds == 0) // if right catalogue side is empty then the answer is the whole left side catalogue
	{
		for (int i = 0; i < numcds; i++)
		{
			difference.Insert(cds[i]);  // insert left catalogue cds into difference catalogue    
		}

		return difference;
	}
	else // General case
	{
		int diff = 0; // counter to tell when to insert flag
		for (int i = 0; i< numcds; i++)// for every cd is cd catalogue
		{
			diff = 0;// reinitialize to 0 each time through
			for (int j = 0; j< cat.numcds; j++)// for every cd is cd catalogue
			{

				if (cds[i].GetAlbum() == cat.cds[j].GetAlbum() && cds[i].GetArtist() == cat.cds[j].GetArtist()) // if cd is in both catalogues
				{
					diff++; // then they are not different as they are in both 
				}
			}

			if (diff == 0) // if they are different 
			{
				difference.Insert(cds[i]); // insert them into difference catalogue

			}
		}
	}
	//**************PRINTING OUT PURPOSES**************************************//
	/*cout<<endl<<"This is split"<<endl;
	for(int i =0; i < difference.numcds; i++)
	{
	cout<< difference.cds[i].GetAlbum()<< "  "<< difference.cds[i].GetArtist()<< endl;

	}*/

	return difference;
}
