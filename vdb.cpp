#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string_view>

#include <openvdb/openvdb.h>
#include <iostream>

//Build: clear && g++ -I/usr/include vdb.cpp -o vdb -lopenvdb -ltbb -lImath && ./vdb

int main( int argc, char* argv[] )
{
    openvdb::initialize();
    // if (argc < 2) {
    //     std::cout << "Missing argument. Number of arguments: " << argc;
    //     exit;
    // }
    // openvdb::io::File file(argv[1]); 

    // openvdb::io::File file("sim/NonMantaflowBlenderCache_000005.vdb"); // no mantaflow
    openvdb::io::File file("sim/fluid_data_0005.vdb"); // mantaflow
    // openvdb::io::File file("sim/HoudiniSimulation.filecache1.5.vdb");
    // openvdb::io::File file("fluid_data_0008.vdb");
    
    // openvdb::io::File file("sim/HoudiniSimulation.filecache1.2.vdb");

    file.open();

    openvdb::GridBase::Ptr baseGrid;
    for (openvdb::io::File::NameIterator nameIter = file.beginName();
        nameIter != file.endName(); ++nameIter)
    {
        if (nameIter.gridName() == "density") {
        // if (nameIter.gridName() == "temperature") {
            baseGrid = file.readGrid(nameIter.gridName());
            // std::cout << std::endl << std::setprecision(2)  << " >> " << file.filename() << "  >> " <<  nameIter.gridName() << std::endl;
        } else {
            // std::cout << "\tskip: " << nameIter.gridName();
        }
    }
    file.close();
    openvdb::FloatGrid::Ptr grid = openvdb::gridPtrCast<openvdb::FloatGrid>(baseGrid);

    //Min and max (it is already calculated)
    long i = 1;
    long minx =100000; long miny =100000; long minz =100000;
    long maxx =0; long maxy =0; long maxz =0;
    for (openvdb::FloatGrid::ValueOnCIter iter = grid->cbeginValueOn(); iter; ++iter) {
        minx = std::min(long(iter.getCoord().x()), minx);
        miny = std::min(long(iter.getCoord().y()), miny);
        minz = std::min(long(iter.getCoord().z()), minz);
        maxx = std::max(long(iter.getCoord().x()), maxx);
        maxy = std::max(long(iter.getCoord().y()), maxy);
        maxz = std::max(long(iter.getCoord().z()), maxz);
        i++;
    }
    // std::cout << "\t Max X: " << maxx << "\t Max Y: " << maxy << "\t Max Z: " << maxz << std::endl;
    // std::cout << "\t Min X: " << minx << "\t Min Y: " << miny << "\t Min Z: " << minz << std::endl;

    // Meta properties
    for (openvdb::MetaMap::MetaIterator iter = grid->beginMeta(); iter != grid->endMeta(); ++iter)
        std::cout << iter->first << " = " << iter->second->str() << std::endl;

    //Transform (Brakuje w eksporcie Transform::Ptr )
    std::cout << file.filename() << "  >> " << grid->transform();
}

/*
template <typename GridType, typename T>
GridType *OpenVDB_export_grid( // tutaj zapisywane jest
        OpenVDBWriter *writer,
        const openvdb::Name &name,
        const T *data,
        const int res[3],
        float fluid_mat[4][4],
        const openvdb::FloatGrid *mask)
{
	using namespace openvdb;

	math::CoordBBox bbox(Coord(0), Coord(res[0] - 1, res[1] - 1, res[2] - 1));
	Mat4R mat = convertMatrix(fluid_mat); // bako konwersja
	math::Transform::Ptr transform = math::Transform::createLinearTransform(mat);

	typename GridType::Ptr grid = GridType::create(T(0));

	tools::Dense<const T, openvdb::tools::LayoutXYZ> dense_grid(bbox, data);
	tools::copyFromDense(dense_grid, grid->tree(), (T)TOLERANCE);

	grid->setTransform(transform);

	if (mask && !mask->tree().empty()) {
		grid = tools::clip(*grid, *mask);
	}

	grid->setName(name);
	grid->setIsInWorldSpace(false);
	grid->setVectorType(openvdb::VEC_INVARIANT);

	writer->insert(grid);

	return grid.get();
}
*/