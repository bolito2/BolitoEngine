#pragma once

namespace BolitoEngine {

	struct Color {
		GLubyte R;
		GLubyte G;
		GLubyte B;
		GLubyte A;
	};

	struct Position {
		float x;
		float y;
	};

	struct UV {
		float U;
		float V;
	};

	struct Vertex
	{
		Position position;
		Color color;
		UV uv;

		void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.R = r;
			color.G = g;
			color.B = b;
			color.A = a;
		}
		void setUV(float u, float v) {
			uv.U = u;
			uv.V = v;
		}

		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}
	};
}