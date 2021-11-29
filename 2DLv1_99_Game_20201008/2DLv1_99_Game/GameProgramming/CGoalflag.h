#ifndef CGOALFLAG_H
#define CGOALFLAG_H

#include "CGoalflag.h"

extern CTexture Texture;

class CGoalflag : public CRectangle {
public:
	void Render() {
		if (mEnabled) {
			CRectangle::Render(Texture, 0, 0, 0, 0);
		}
	}
};



#endif
