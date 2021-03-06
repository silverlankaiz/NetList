// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELLS_MODEL_H
#define NETLIST_CELLS_MODEL_H

#include <vector>
#include <QObject>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

namespace Netlist {

	class Cell;

	class CellsModel : public QAbstractTableModel{
		Q_OBJECT;
	public:
		CellsModel(QObject* parent=NULL);

		void setCells(std::vector<Cell*> cells);
		Cell* getModel(int);

		int rowCount(const QModelIndex& parent = QModelIndex()) const;
		int columnCount(const QModelIndex& parent = QModelIndex()) const;

		QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const;
		QVariant headerData(int, Qt::Orientation, int role = Qt::DisplayRole) const;

	public slots:
		void updateDatas();

	private :
		std::vector<Cell*> cells_; //le vector des (dura)cells déjà chargées
	};
}  // Netlist namespace.

#endif  // NETLIST_INSTANCES_MODEL_H