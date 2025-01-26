#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Date.h"
#include "Book.h"
#include "Patron.h"

struct Transaction {
	enum class Action {
		check_out, check_in
	};

	Book book;
	Patron patron;
	Date date;
	Action action;
};

#endif
