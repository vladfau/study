#pragma once
#include "stdafx.h"

#include "Transform.h"

using namespace std;

polygon^ Pclip (polygon^ P, point min, point max) {
	polygon^ P1 = gcnew polygon(0);

	int k = 0;

	point p1 = P[P->Count - 1];
	point p2;

	point in, out, tin, tout;
	float t1in, t1out, t2in, t2out;

	while (k < P->Count) {
		p2 = P[k];

		float dx = p2.x - p1.x,
			dy = p2.y - p1.y;

		if (dx > 0 || dx == 0 && p1.x > max.x) {
			in.x = min.x;
			out.x = max.x;
		} else {
			in.x = max.x;
			out.x = min.x;
		}

		if (dy > 0 || dy == 0 && p1.y > max.y) {
			in.y = min.y;
			out.y = max.y;
		} else {
			in.y = max.y;
			out.y = min.y;
		}

		if (dx != 0) {
			tout.x = (out.x - p1.x) / dx;
		} else if (p1.x >= min.x && p1.x <= max.x) {
			tout.x = float::MaxValue;
		} else {
			tout.x = float::MinValue;
		}

		if (dy != 0) {
			tout.y = (out.y - p1.y) / dy;
		} else if (p1.y >= min.y && p1.y <= max.y) {
			tout.y = float::MaxValue;
		} else {
			tout.y = float::MinValue;
		}


		if (tout.x < tout.y) {
			t1out = tout.x;
			t2out = tout.y;
		} else {
			t1out = tout.y;
			t2out = tout.x;
		}

		if (t2out > 0) {

			if (dx != 0) {
				tin.x = (in.x - p1.x) / dx;
			} else {
				tin.x = float::MinValue;
			}

			if (dy != 0) {
				tin.y = (in.y - p1.y) / dy;
			} else {
				tin.y = float::MinValue;
			}

			if (tin.x < tin.y) {
				t2in = tin.y;
			} else {
				t2in = tin.x;
			}

			if (t1out < t2in) {

				if (t1out > 0 && t1out <= 1) {
					if (tin.x < tin.y) {
						P1->Add(point(out.x, in.y));
					} else {
						P1->Add(point(in.x, out.y));
					}
				}

			} else if (t1out > 0 && t2in <= 1) {

				if (t2in >= 0) {
					if (tin.x > tin.y) {
						P1->Add(point(in.x, p1.y + tin.x * dy));
					} else {
						P1->Add(point(p1.x + tin.y * dx, in.y));
					}
				}

				if (t1out <= 1) {
					if (tout.x < tout.y) {
						P1->Add(point(out.x, p1.y + tout.x * dy));
					} else {
						P1->Add(point(p1.x + tout.y * dx, out.y));
					}
				} else {
					P1->Add(p2);
				}
			}

			if (t2out > 0 && t2out <= 1) {
				P1->Add(out);
			}
		}

		k = k + 1;
		p1 = p2;
	}

	return P1;
}

void Pfill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C) {

	System::Collections::Generic::List<line> S;
	System::Collections::Generic::List<array<float>^> AEL;

	int yAELNext = float::MaxValue;

	// Формируем список S
	point p1 = P[P->Count - 1];
	for (int i = 0; i < P->Count; i++) {

		if (p1.y <= P[i].y) {
			S.Add(line(p1, P[i]));
		} else {
			S.Add(line(P[i], p1));
		}

		p1 = P[i];
	}

	// Сортируем список S по y1
	for (int i = 0; i < S.Count; i++) {
		for (int j = 0; j < S.Count - i - 1; j++) {
			if (S[j].start.y > S[j + 1].start.y) {
				line temp = S[j];
				S[j] = S[j + 1];
				S[j + 1] = temp;
			}
		}
	}

	int ymin = S[0].start.y;
	int ySNext = ymin;
	int yt = ymin;
	int ymax = ymin;

	for (int i = 0; i < P->Count; i++) {
		if (P[i].y > ymax)
			ymax = P[i].y;
	}

	while (yt <= ymax) {
		if (yt == ySNext) {
			for (int i = 0; i < S.Count; i++) {
				if ((int)S[i].start.y == yt && S[i].start.y != S[i].end.y) {
					float dx = S[i].end.x - S[i].start.x;
					float dy = S[i].end.y - S[i].start.y;
					array<float>^ trio = { S[i].start.x, S[i].end.y, dx / dy };

					AEL.Add(trio);
				}

				if ((int)S[i].start.y == yt && S[i].start.y == S[i].end.y) {
					for (float j = S[i].start.x; j <= S[i].end.x; j++) {
						image->SetPixel(j, S[i].start.y, C);
					}
				}

				if ((int)S[i].start.y == yt) {
					S.RemoveAt(i);
					i--;
				}
			}

			if (S.Count != 0)
				ySNext = S[0].start.y;

			// Сортировка AEL
			for (int i = 0; i < AEL.Count; i++) {
				for (int j = 0; j < AEL.Count - i - 1; j++) {
					if (AEL[j][0] > AEL[j + 1][0] ||
					   (AEL[j][0] == AEL[j + 1][0] && AEL[j][2] > AEL[j + 1][2])) {

						array<float>^ temp = AEL[j];
						AEL[j] = AEL[j + 1];
						AEL[j + 1] = temp;
					} 
				}
			}

			for (int i = 0; i < AEL.Count; i++) {
				if ((int)AEL[i][1] < yAELNext && (int)AEL[i][1] != yt) {
					yAELNext = AEL[i][1];
				}
			}
		}

		for (int i = 0; i < AEL.Count - 1; i += 2) {
			for (int j = AEL[i][0]; j <= AEL[i + 1][0]; j++) {
				image->SetPixel(j, yt, C);
			}
		}

		for (int i = 0; i < AEL.Count; i++) {
			AEL[i][0] = AEL[i][0] + AEL[i][2];
		}

		yt = yt + 1;

		if (yt >= yAELNext) {
			for (int i = 0; i < AEL.Count; i++) {
				if ((int)AEL[i][1] <= yt) {
					AEL.RemoveAt(i);
					i--;
				}
			}

			for (int i = 0; i < AEL.Count; i++) {
				if ((int)AEL[i][1] < yAELNext && (int)AEL[i][1] != yt) {
					yAELNext = AEL[i][1];
				}
			}
		}
	}
}