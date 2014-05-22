#ifndef ITEM_H_
#define ITEM_H_

typedef struct {
	int number;
	enum {UNDEF, DEFINITELY, MABY} state;
} Item;


#endif /* ITEM_H_ */
