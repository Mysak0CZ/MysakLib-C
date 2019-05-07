#include "doubleBuffer.h"
#include "internals.h"
#include "misc.h"

DoubleBuffer_t* DoubleBuffer_new(long size_x, long size_y)
{
	DoubleBuffer_t* self = malloc(sizeof(DoubleBuffer_t));
	long i;
	if (self == NULL) {
		MysakLib_internals_logError("Failed to allocate memory for DoubleBuffer struct");
		return NULL;
	}
	self->anchor.x = 0;
	self->anchor.y = 0;
	self->buffer_1.x = 0;
	self->buffer_1.y = 0;
	self->size.x = size_x;
	self->size.y = size_y;
	self->buffer_2.x = size_x - 1;
	self->buffer_2.y = size_y - 1;
	self->frame = malloc(size_x * size_y * sizeof(char));
	if (self->frame == NULL) {
		MysakLib_internals_logError("DoubleBuffer: Failed to allocate memory for frame");
		free(self);
		return NULL;
	}
	for (i = 0; i < size_x * size_y; i++) {
		self->frame[i] = '\0';
	}
	self->nxframe = malloc(size_x * size_y * sizeof(char));
	if (self->nxframe == NULL) {
		MysakLib_internals_logError("DoubleBuffer: Failed to allocate memory for nxframe");
		free(self->frame);
		free(self);
		return NULL;
	}
	for (i = 0; i < size_x * size_y; i++) {
		self->nxframe[i] = ' ';
	}
	for (i = 1; i < size_x - 1; i++) {
		self->nxframe[i] = '-';
		self->nxframe[((size_y - 1) * size_x) + i] = '-';
	}
	for (i = 1; i < size_y - 1; i++) {
		self->nxframe[i * size_x] = '|';
		self->nxframe[i * size_x + (size_x - 1)] = '|';
	}
	self->nxframe[0] = '+';
	self->nxframe[size_x - 1] = '+';
	self->nxframe[size_x * (size_y - 1)] = '+';
	self->nxframe[size_x * size_y - 1] = '+';
	self->needUpdate = TRUE;
	MysakLib_internals_logDebug("DoubleBuffer: new %p %ldx%ld", self, size_x, size_y);
	return self;
}

/* ~DoubleBuffer */
void DoubleBuffer_delete(DoubleBuffer_t* self)
{
	if (self == NULL)
		return;
	MysakLib_internals_logDebug("DoubleBuffer: delete %p", self);
	if (self->frame != NULL)
		free(self->frame);
	if (self->nxframe != NULL)
		free(self->nxframe);
	free(self);
}

void DoubleBuffer_draw(DoubleBuffer_t* self)
{
	if (!self->needUpdate)
		return;
	bool_t lastPos = FALSE;
	long x, y, pos;
	long sizeY = self->buffer_2.y - self->buffer_1.y + 1;
	long sizeX = self->buffer_2.x - self->buffer_1.x + 1;
	for (y = 0; y < sizeY; y++) {
		lastPos = FALSE;
		for (x = 0; x < sizeX; x++) {
			pos = (y + self->buffer_1.y) * self->size.x + (x + self->buffer_1.x);
			if (self->frame[pos] != self->nxframe[pos]) {
				if (!lastPos) {
					m_setConsolePos(self->anchor.x + x, self->anchor.y + y);
				}
				putchar(self->nxframe[pos]);
				self->frame[pos] = self->nxframe[pos];
				lastPos = TRUE;
			} else {
				lastPos = FALSE;
			}
		}
	}
	m_setConsolePos(self->anchor.x, self->anchor.y + sizeY);
	fflush(stdout);
	self->needUpdate = FALSE;
}

void DoubleBuffer_redraw(DoubleBuffer_t* self)
{
	long i;
	for (i = 0; i < self->size.x * self->size.y; i++) {
		self->frame[i] = '\0';
	}
	self->needUpdate = TRUE;
	DoubleBuffer_draw(self);
}

void DoubleBuffer_setCharAtXY(DoubleBuffer_t* self, long x, long y, char c)
{
	if (c < ' ') {
		MysakLib_internals_logWarning("DoubleBuffer::setChatAt character is out of bounds %2x", c);
		return;
	}
	if (x < 0 || x >= self->size.x || y < 0 || y >= self->size.y) {
		MysakLib_internals_logWarning("DoubleBuffer::setChatAt coordinates out of bounds %ld:%ld (size %ld:%ld)", x, y, self->size.x, self->size.y);
		return;
	}
	self->nxframe[(self->size.x * y) + x] = c;
	self->needUpdate = TRUE;
}

void DoubleBuffer_setCharAt(DoubleBuffer_t* self, vector2_t pos, char c)
{
	DoubleBuffer_setCharAtXY(self, pos.x, pos.y, c);
}

void DoubleBuffer_fillRectXY(DoubleBuffer_t* self, long x1, long y1, long x2, long y2, char c)
{
	if (c < ' ') {
		MysakLib_internals_logWarning("DoubleBuffer::fillRect character is out of bounds %2x", c);
		return;
	}
	if (x1 < 0 || y1 < 0 || x2 >= self->size.x || y2 >= self->size.y) {
		MysakLib_internals_logWarning("DoubleBuffer::fillRect coordinates out of bounds %ld:%ld => %ld:%ld (size %ld:%ld)", x1, y1, x2, y2, self->size.x, self->size.y);
		return;
	}
	long x, y;
	for (y = y1; y <= y2; y++) {
		for (x = x1; x <= x2; x++) {
			self->nxframe[(self->size.x * y) + x] = c;
		}
	}
	self->needUpdate = TRUE;
}

void DoubleBuffer_fillRect(DoubleBuffer_t* self, vector2_t start, vector2_t size, char c)
{
	DoubleBuffer_fillRectXY(self, start.x, start.y, start.x + size.x - 1, start.y + size.y - 1, c);
}

void DoubleBuffer_loadFromBuffer(DoubleBuffer_t* self, char* buffer, long sizex, long sizey, long anchorx, long anchory)
{
	if (buffer == NULL) {
		MysakLib_internals_logWarning("DoubleBuffer::loadFromBuffer received null buffer");
		return;
	}
	long x, y;
	for (y = 0; y < sizey; y++) {
		if (anchory + y > self->size.y)
			continue;
		for (x = 0; x < sizex; x++) {
			if (anchorx + x > self->size.x)
				continue;
			self->nxframe[(anchory + y) * self->size.x + anchorx + x] = buffer[y * sizex + x];
		}
	}
	self->needUpdate = TRUE;
}

void DoubleBuffer_loadFromString(DoubleBuffer_t* self, char* str, long anchorx, long anchory)
{
	long x = anchorx;
	long y = anchory;
	long i;
	for (i = 0; str[i] != '\0'; i++) {
		switch (str[i]) {
			case '\n':
				x = anchorx;
				y++;
				break;
			default:
				self->nxframe[y * self->size.x + x] = str[i];
				x++;
				break;
		}
		if (x >= self->size.x) {
			x = anchorx;
			y++;
		}
		if (y >= self->size.y) {
			break;
		}
	}
	self->needUpdate = TRUE;
}
