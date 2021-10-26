#ifndef CSLIDINGFLOOR_H
#define CSLIDINGFLOOR_H

#include "CRectangle.h"

extern CTexture Texture;

class CSlidingfloor :public CRectangle {
public:
	int inertia;

	CSlidingfloor();

	void Render() {
		if (mEnabled) {
			CRectangle::Render(Texture, 100, 100, 0, 0);
		}
	}
};

#endif