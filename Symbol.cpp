#include  <cstdlib>
#include "Cell.h"
#include "Point.h"
#include "Shape.h"
#include "Symbol.h"

namespace Netlist {
	using namespace std;

	Symbol::Symbol(Cell* cell) :
		owner_(cell){
	}

	Symbol::~Symbol(){}

	Cell* Symbol::getCell() const{
		return owner_;
	}

	Box Symbol::getBoundingBox() const{
		return Box();
	}

	Point Symbol::getTermPosition(Term* term) const{
		for(vector<Shape*>::const_iterator iS = shapes_.begin(); iS != shapes_.end(); ++iS){
			if((dynamic_cast<TermShape*>(*iS))->getTerm() == term) //need a cast
				return (dynamic_cast<TermShape*>(*iS))->getTerm()->getPosition();
		}
		return Point();
	}

	TermShape* Symbol::getTermShape(Term* term) const{
		for(vector<Shape*>::const_iterator iS = shapes_.begin(); iS != shapes_.end(); ++iS){
			if((dynamic_cast<TermShape*>(*iS))->getTerm() == term) //need a cast
				return dynamic_cast<TermShape*>(*iS);
		}
		return NULL;
	}

	void Symbol::add (Shape* shape){
		if(shape != NULL)
			shapes_.push_back(shape);
	}

	void Symbol::remove(Shape* shape){
		if(shape)
			for(vector<Shape*>::iterator iS = shapes_.begin(); iS != shapes_.end() ; ++iS)
				if(*iS == shape)
					shapes_.erase(iS);
	}

	void Symbol::toXml(ostream& stream) const{
		stream << indent++ << "<symbol>\n";

		for(vector<Shape*>::const_iterator iS = shapes_.begin(); iS != shapes_.end() ; ++iS)
			(*iS)->toXml(stream);

		stream << --indent << "</symbol>\n";
	}

	Symbol* Symbol::fromXml(Cell* owner, xmlTextReaderPtr reader){
		const xmlChar* symbolTag = xmlTextReaderConstString(reader, (const xmlChar*)"symbol");

		Symbol* symbol = new Symbol(owner);

		do{
			if(xmlTextReaderRead(reader) != 1)
				return NULL;

			Shape::fromXml(owner->getSymbol(), reader);
		} while (xmlTextReaderConstLocalName(reader) != symbolTag and xmlTextReaderNodeType(reader) != XML_READER_TYPE_END_ELEMENT);

		return symbol;
	}
}  // Netlist namespace.