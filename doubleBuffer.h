#include "types.h"

/* Class DoubleBuffer */
typedef struct
{
	vector2_t size;
	vector2_t buffer_1;
	vector2_t buffer_2;
	vector2_t anchor;
	bool_t needUpdate;
	char* frame;
	char* nxframe;
} DoubleBuffer_t;

/* Create new DoubleBuffer instance */
DoubleBuffer_t* DoubleBuffer_new(long size_x, long size_y);

/* ~DoubleBuffer */
void DoubleBuffer_delete(DoubleBuffer_t* self);

/* Draw the buffer (update) */
void DoubleBuffer_draw(DoubleBuffer_t* self);

/* Redraw the buffer (forced update) */
void DoubleBuffer_redraw(DoubleBuffer_t* self);

/* Set char at x:y (Checks for valid characters) */
void DoubleBuffer_setCharAtXY(DoubleBuffer_t* self, long x, long y, char c);

/* Set char at x:y (Checks for valid characters) */
void DoubleBuffer_setCharAt(DoubleBuffer_t* self, vector2_t pos, char c);

void DoubleBuffer_fillRectXY(DoubleBuffer_t* self, long x1, long y1, long x2, long y2, char c);
void DoubleBuffer_fillRect(DoubleBuffer_t* self, vector2_t start, vector2_t size, char c);

void DoubleBuffer_loadFromBuffer(DoubleBuffer_t* self, char* buffer, long sizex, long sizey, long anchorx, long anchory);

void DoubleBuffer_loadFromString(DoubleBuffer_t* self, char* str, long anchorx, long anchory);
