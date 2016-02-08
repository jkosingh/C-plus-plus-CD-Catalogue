# C++-CD-Catalogue

implementation of a CDCatalogue class for your legally purchased musiccollection that stores a set of CD objects. The catalogue uses a dynamic array for its underlying data storage requirements.

Catalogue functionality includes:

- insert() to insert cds
- Remove() to remove cds
- Find() to find the index at where the cd you were looking for is at in your catalogue
- Boycott() to remove all cds from your catalogue by a certain artist name you pass in
- count() to return number of cds in the catalogue
- Join() to join two cd catalogues together excluding repeats
- Common() to return the number of common cds between two catalogues
- Split() to return the difference between two catalogues
