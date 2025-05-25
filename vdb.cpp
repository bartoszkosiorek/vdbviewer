#include <openvdb/openvdb.h>
#include <openvdb/tools/ChangeBackground.h>
#include <iostream>

openvdb::initialize();
// Create a VDB file object.
openvdb::io::File file("mygrids.vdb");
// Open the file.  This reads the file header, but not any grids.
file.open();
// Loop over all grids in the file and retrieve a shared pointer
// to the one named "LevelSetSphere".  (This can also be done
// more simply by calling file.readGrid("LevelSetSphere").)
openvdb::GridBase::Ptr baseGrid;
for (openvdb::io::File::NameIterator nameIter = file.beginName();
    nameIter != file.endName(); ++nameIter)
{
    // Read in only the grid we are interested in.
    if (nameIter.gridName() == "LevelSetSphere") {
        baseGrid = file.readGrid(nameIter.gridName());
    } else {
        std::cout << "skipping grid " << nameIter.gridName() << std::endl;
    }
}
file.close();
// From the example above, "LevelSetSphere" is known to be a FloatGrid,
// so cast the generic grid pointer to a FloatGrid pointer.
openvdb::FloatGrid::Ptr grid = openvdb::gridPtrCast<openvdb::FloatGrid>(baseGrid);

std::cout << "bako kloniec " << std::endl;