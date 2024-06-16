#include <iostream>


#include "block/library.hpp"



int main() {
    auto lib = BlockLibrary::fromFile("example_collection.json");

/*
    BlockCollection blocks ({
        BlockBuilder("WHILE_LOOP", "Repite cierta acción mientras que la condición resulte verdadera")
            .withLabel("repetir mientras %1")
            .addInput({"COND", "bool", "true"})
            .allowsChildren(),
        BlockBuilder("  FOR_LOOP", "Repite cierta acción un número definido de veces")
            .withLabel("repetir %1 veces")
            .addInput({"COUNT", "number", "10"})
            .allowsChildren(),
        BlockBuilder("MOVE_UNITS", "Mover el cierta cantidad de unidades")
            .withLabel("mover %1 unidades")
            .addInput({"AMOUNT", "number", "10"}),
        BlockBuilder("ROTATE_DEGREES", "Rotar en sentido antihorario cierto ángulo")
            .withLabel("rotar %1 grados")
            .addInput({"AMOUNT", "number", "15"})
    });*/

    std::cout << lib.blocks[1] << std::endl;
}
