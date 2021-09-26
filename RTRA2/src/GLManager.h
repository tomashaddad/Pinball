#pragma once

#include <GLAD/glad.h>

class GLManager {
public:
	GLManager();
	void toggleDepthTesting();
	void toggleBackFaceCulling();

	const bool isDepthTesting() const;
	const bool isCullingBackFaces() const;

private:
	bool m_depthTesting;
	bool m_cullBackFace;
};