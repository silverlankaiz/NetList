// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_INSTANCES_MODEL_H
#define NETLIST_INSTANCES_MODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

namespace Netlist {

	class Cell;

	class InstancesModel : public QAbstractTableModel{
		Q_OBJECT;
	public:
		InstancesModel(QObject* parent=NULL);

		void setCell(Cell* cell);
		Cell* getModel(int);

		int rowCount(const QModelIndex& parent = QModelIndex()) const;
		int columnCount(const QModelIndex& parent = QModelIndex()) const;

		QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const;
		QVariant headerData(int, Qt::Orientation, int role = Qt::DisplayRole) const;

	private :
		Cell* cell_;
	};
}  // Netlist namespace.

#endif  // NETLIST_INSTANCES_MODEL_H