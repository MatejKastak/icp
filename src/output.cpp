/**
 * @file output.cpp
 * @author Matej Kastak <xkasta02>
 * @author Adam  Venger <xvenge00>
 */

#include <QGraphicsScene>
#include <algorithm>
#include <iostream>

#include "block.h"
#include "block_graphics_object.h"
#include "connection.h"
#include "connection_graphics_object.h"
#include "debug.h"
#include "schema.h"
#include "schema_area.h"

std::ostream &operator<<(std::ostream &s, const Block &b) {
    s << "\tID: " << b.ID << "\n"
      << "\ttype: " << b.block_type;
    switch (b.block_type) {
    case DIV:
    case SUB:
    case POW:
    case NEG:
        return s;
    case ADD:
    case MUL:
        return s << "\n\tin_size: " << b.input_size;
    case OUT:
        return s << "\n\toutput: " << b.output;
    default:
        return s << "\n\tin_size: " << b.input_size << "\n"
                 << "\toutput: " << b.output;
    }
}

std::ostream &operator<<(std::ostream &s, const BlockGraphicsObject &b) {
    return s << "Block {\n"
             << "\twidth: " << b.width << "\n"
             << "\theight: " << b.height << "\n"
             << "\tx: " << b.pos().x() << "\n"
             << "\ty: " << b.pos().y() << "\n"
             << *b._block << "\n"
             << "}\n";
}

/*
 * Used in Schema output.
 * out example:
 * Connection: {
 *      in: 0
 *      out: 1
 *      index: 2
 * }
 */
std::ostream &operator<<(std::ostream &s, const Connection &c) {
    s << "Connection: {\n"
      << "\tID: " << c.ID << "\n"
      << "\tin: " << c.input->getID() << "\n"
      << "\tout: " << c.output->getID() << "\n"
      << "\tindex: " << c.index << "\n"
      << "}\n";
    return s;
}

std::ostream &operator<<(std::ostream &s, const ConnectionGraphicsObject &c) { return s << *c._connection; }

std::ostream &operator<<(std::ostream &s, const SchemaArea &a) {
    for (const auto &i : a.items(Qt::DescendingOrder)) {
        BlockGraphicsObject *casted_b = dynamic_cast<BlockGraphicsObject *>(i);
        if (casted_b != nullptr) {
            s << *casted_b;
        } else {
            ConnectionGraphicsObject *casted_c = dynamic_cast<ConnectionGraphicsObject *>(i);
            if (casted_c != nullptr) {
                s << *casted_c;
            }
        }
    }
    return s;
}
