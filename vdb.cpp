#include <openvdb/openvdb.h>
// #include <openvdb/tools/ChangeBackground.h>
#include <iostream>

int main()
{
    openvdb::initialize();
    // Create a VDB file object.
    openvdb::io::File file("fluid_data_0030.vdb");
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
        if (nameIter.gridName() == "density") {
            baseGrid = file.readGrid(nameIter.gridName());

            std::cout << "reading grid " << nameIter.gridName() << std::endl;
        } else {
            std::cout << "skipping grid " << nameIter.gridName() << std::endl;
        }
    }
    file.close();
    openvdb::FloatGrid::Ptr grid = openvdb::gridPtrCast<openvdb::FloatGrid>(baseGrid);

    std::cout << "bako kloniec " << std::endl;
}