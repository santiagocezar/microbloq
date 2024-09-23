#include <iostream>
#include <lager/event_loop/manual.hpp>
#include <lager/store.hpp>

#include "block/library.hpp"
#include "workspace/actions.hpp"
#include "workspace/model.hpp"

#include <QApplication>
#include "ui/mainwindow.h"
#include "ui/blockparts.h"
#include "ui/blockwrapper.h"

int main(int argc, char **argv) {
	QApplication app (argc, argv);
	MainWindow win;
	BlockWrapper bw;
	BlockParts bw1(BlockParts::Notch, BlockParts::Offset);
	BlockParts bw2(BlockParts::Offset, BlockParts::Notch);

	bw.layout.addWidget(&bw1);
	bw.layout.addWidget(&bw2);

	win.layout()->addWidget(&bw);

	win.show();

	return app.exec();

	/*
	auto store = lager::make_store<workspace::Action>(
		workspace::Model{}, lager::with_manual_event_loop{});

	watch(store, [](auto m) { m.print(); });

	auto lib = BlockLibrary::fromFile("example_collection.json");

	store.dispatch(workspace::AddAction{.block = lib.blocks[1]});
	/*
	auto root1 = w1.add({});
	auto item = w1.add({}, w1.add({}, root1));

	auto w2 = w1;

	w2.link(item, root1);

	w1.sanityCheck();
	w2.sanityCheck();

	w1.print();
	w2.print();*/
	/*
	auto col1 = w.add({});
	col1 = w.add({}, col1);
	col1 = w.add({}, col1);
	auto after = col1;
	col1 = w.add({}, col1);
	col1 = w.add({}, col1);

	auto col2 = w.add({});
	auto root2 = col2;
	col2 = w.add({}, col2);
	col2 = w.add({}, col2);
	col2 = w.add({}, col2);

	w.link(root2, after);
	w.link(col2, after);*/

	/*
		BlockCollection blocks ({
			BlockBuilder("WHILE_LOOP", "Repite cierta acción mientras que la
	   condición resulte verdadera") .withLabel("repetir mientras %1")
				.addInput({"COND", "bool", "true"})
				.allowsChildren(),
			BlockBuilder("  FOR_LOOP", "Repite cierta acción un número definido
	   de veces") .withLabel("repetir %1 veces") .addInput({"COUNT", "number",
	   "10"}) .allowsChildren(), BlockBuilder("MOVE_UNITS", "Mover el cierta
	   cantidad de unidades") .withLabel("mover %1 unidades")
				.addInput({"AMOUNT", "number", "10"}),
			BlockBuilder("ROTATE_DEGREES", "Rotar en sentido antihorario cierto
	   ángulo") .withLabel("rotar %1 grados") .addInput({"AMOUNT", "number",
	   "15"})
		});*/

	// std::cout << lib.blocks[1] << std::endl;
}
