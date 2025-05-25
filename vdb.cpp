#include <openvdb/openvdb.h>
// #include <openvdb/tools/ChangeBackground.h>
#include <iostream>

int main()
{
    openvdb::initialize();
    // Create a VDB file object.
     openvdb::io::File file("fluid_data_0030.vdb");
    //openvdb::io::File file("HoudiniSimulation.filecache1.30.vdb");

    // Open the file.  This reads the file header, but not any grids.
    file.open();

    std::cout << std::setprecision(2)  << "bako reading " << file.filename() << std::endl;
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
            //std::cout << "skipping grid " << nameIter.gridName() << std::endl;
        }
    }
    file.close();
    openvdb::FloatGrid::Ptr grid = openvdb::gridPtrCast<openvdb::FloatGrid>(baseGrid);

    //std::cout << std::setprecision(2)  << "bako kloniec " << std::endl;
    //long i = 1;
    // Print all active ("on") voxels by means of an iterator.
    // for (openvdb::FloatGrid::ValueOnCIter iter = grid->cbeginValueOn(); iter; ++iter) {
    //     std::cout << i <<" Grid" << iter.getCoord() << " = " << *iter << std::endl;
    //     i++;
    // }

    for (openvdb::MetaMap::MetaIterator iter = grid->beginMeta(); iter != grid->endMeta(); ++iter)
    {
        const std::string& name = iter->first;
        openvdb::Metadata::Ptr value = iter->second;
        std::string valueAsString = value->str();
        std::cout << name << " = " << valueAsString << std::endl;
    }
}