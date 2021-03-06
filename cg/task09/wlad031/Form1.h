#pragma once

#define TEXT_SIZE 7
#define BORDER 3
#define RAD 0.0175
#define CLIENT_HEIGHT Form::ClientRectangle.Height
#define CLIENT_WIDTH Form::ClientRectangle.Width
#define FRAME_WIDTH_MIDDLE (Form::ClientRectangle.Width - left - right) / 2 + left;
#define FRAME_HEIGHT_MIDDLE (Form::ClientRectangle.Height - bottom - top) / 2 + top;

namespace CG_task9 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;

	private: System::Collections::Generic::List<polygon3D^> polygons;
	private: System::Collections::Generic::List<System::Drawing::Color> colors;

	private: point3D eye, center, up, eyeOld, centerOld, upOld;

	private: System::Drawing::Color currentColor;

	private: bool prOrtho;

	private: float near, nearOld, far, fovy, fovyOld, aspect, alpha;

	private: float left, right, top, bottom;
	private: float Wcx, Wcy, Wx, Wy;
	private: float Vcx, Vcy, Vx, Vy;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txt_eye;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  txt_center;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  txt_up;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  txt_fovy;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  txt_near;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  txt_mode;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  txt_triangles;
	private: System::Windows::Forms::TextBox^  txt_far;


#pragma region Windows Form Designer generated code

			 void InitializeComponent(void)
			 {
				 this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->btnOpen = (gcnew System::Windows::Forms::Button());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->txt_eye = (gcnew System::Windows::Forms::TextBox());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->txt_center = (gcnew System::Windows::Forms::TextBox());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->txt_up = (gcnew System::Windows::Forms::TextBox());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->txt_fovy = (gcnew System::Windows::Forms::TextBox());
				 this->label5 = (gcnew System::Windows::Forms::Label());
				 this->txt_near = (gcnew System::Windows::Forms::TextBox());
				 this->label6 = (gcnew System::Windows::Forms::Label());
				 this->txt_far = (gcnew System::Windows::Forms::TextBox());
				 this->label7 = (gcnew System::Windows::Forms::Label());
				 this->txt_mode = (gcnew System::Windows::Forms::TextBox());
				 this->label8 = (gcnew System::Windows::Forms::Label());
				 this->txt_triangles = (gcnew System::Windows::Forms::TextBox());
				 this->SuspendLayout();
				 // 
				 // openFileDialog
				 // 
				 this->openFileDialog->DefaultExt = L"txt";
				 this->openFileDialog->FileName = L"openFileDialog1";
				 this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
				 this->openFileDialog->Title = L"Open file";
				 // 
				 // btnOpen
				 // 
				 this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->btnOpen->Location = System::Drawing::Point(460, 12);
				 this->btnOpen->Name = L"btnOpen";
				 this->btnOpen->Size = System::Drawing::Size(75, 23);
				 this->btnOpen->TabIndex = 0;
				 this->btnOpen->Text = L"Open";
				 this->btnOpen->UseVisualStyleBackColor = true;
				 this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
				 // 
				 // label1
				 // 
				 this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(460, 91);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(24, 13);
				 this->label1->TabIndex = 1;
				 this->label1->Text = L"eye";
				 // 
				 // txt_eye
				 // 
				 this->txt_eye->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->txt_eye->Location = System::Drawing::Point(460, 108);
				 this->txt_eye->Name = L"txt_eye";
				 this->txt_eye->ReadOnly = true;
				 this->txt_eye->Size = System::Drawing::Size(78, 20);
				 this->txt_eye->TabIndex = 2;
				 // 
				 // label2
				 // 
				 this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(460, 136);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(37, 13);
				 this->label2->TabIndex = 3;
				 this->label2->Text = L"center";
				 // 
				 // txt_center
				 // 
				 this->txt_center->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->txt_center->Location = System::Drawing::Point(460, 152);
				 this->txt_center->Name = L"txt_center";
				 this->txt_center->ReadOnly = true;
				 this->txt_center->Size = System::Drawing::Size(78, 20);
				 this->txt_center->TabIndex = 4;
				 // 
				 // label3
				 // 
				 this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(460, 175);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(19, 13);
				 this->label3->TabIndex = 5;
				 this->label3->Text = L"up";
				 // 
				 // txt_up
				 // 
				 this->txt_up->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->txt_up->Location = System::Drawing::Point(460, 192);
				 this->txt_up->Name = L"txt_up";
				 this->txt_up->ReadOnly = true;
				 this->txt_up->Size = System::Drawing::Size(78, 20);
				 this->txt_up->TabIndex = 6;
				 // 
				 // label4
				 // 
				 this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(460, 219);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(27, 13);
				 this->label4->TabIndex = 7;
				 this->label4->Text = L"fovy";
				 // 
				 // txt_fovy
				 // 
				 this->txt_fovy->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->txt_fovy->Location = System::Drawing::Point(460, 236);
				 this->txt_fovy->Name = L"txt_fovy";
				 this->txt_fovy->ReadOnly = true;
				 this->txt_fovy->Size = System::Drawing::Size(78, 20);
				 this->txt_fovy->TabIndex = 8;
				 // 
				 // label5
				 // 
				 this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label5->AutoSize = true;
				 this->label5->Location = System::Drawing::Point(460, 263);
				 this->label5->Name = L"label5";
				 this->label5->Size = System::Drawing::Size(28, 13);
				 this->label5->TabIndex = 9;
				 this->label5->Text = L"near";
				 // 
				 // txt_near
				 // 
				 this->txt_near->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->txt_near->Location = System::Drawing::Point(460, 280);
				 this->txt_near->Name = L"txt_near";
				 this->txt_near->ReadOnly = true;
				 this->txt_near->Size = System::Drawing::Size(78, 20);
				 this->txt_near->TabIndex = 10;
				 // 
				 // label6
				 // 
				 this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label6->AutoSize = true;
				 this->label6->Location = System::Drawing::Point(460, 307);
				 this->label6->Name = L"label6";
				 this->label6->Size = System::Drawing::Size(19, 13);
				 this->label6->TabIndex = 11;
				 this->label6->Text = L"far";
				 // 
				 // txt_far
				 // 
				 this->txt_far->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->txt_far->Location = System::Drawing::Point(460, 324);
				 this->txt_far->Name = L"txt_far";
				 this->txt_far->ReadOnly = true;
				 this->txt_far->Size = System::Drawing::Size(78, 20);
				 this->txt_far->TabIndex = 12;
				 // 
				 // label7
				 // 
				 this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label7->AutoSize = true;
				 this->label7->Location = System::Drawing::Point(460, 365);
				 this->label7->Name = L"label7";
				 this->label7->Size = System::Drawing::Size(33, 13);
				 this->label7->TabIndex = 13;
				 this->label7->Text = L"mode";
				 // 
				 // txt_mode
				 // 
				 this->txt_mode->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->txt_mode->Location = System::Drawing::Point(460, 382);
				 this->txt_mode->Name = L"txt_mode";
				 this->txt_mode->ReadOnly = true;
				 this->txt_mode->Size = System::Drawing::Size(78, 20);
				 this->txt_mode->TabIndex = 14;
				 // 
				 // label8
				 // 
				 this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->label8->AutoSize = true;
				 this->label8->Location = System::Drawing::Point(457, 429);
				 this->label8->Name = L"label8";
				 this->label8->Size = System::Drawing::Size(46, 13);
				 this->label8->TabIndex = 15;
				 this->label8->Text = L"triangles";
				 // 
				 // txt_triangles
				 // 
				 this->txt_triangles->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->txt_triangles->Location = System::Drawing::Point(460, 445);
				 this->txt_triangles->Name = L"txt_triangles";
				 this->txt_triangles->ReadOnly = true;
				 this->txt_triangles->Size = System::Drawing::Size(78, 20);
				 this->txt_triangles->TabIndex = 16;
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(550, 500);
				 this->Controls->Add(this->txt_triangles);
				 this->Controls->Add(this->label8);
				 this->Controls->Add(this->txt_mode);
				 this->Controls->Add(this->label7);
				 this->Controls->Add(this->txt_far);
				 this->Controls->Add(this->label6);
				 this->Controls->Add(this->txt_near);
				 this->Controls->Add(this->label5);
				 this->Controls->Add(this->txt_fovy);
				 this->Controls->Add(this->label4);
				 this->Controls->Add(this->txt_up);
				 this->Controls->Add(this->label3);
				 this->Controls->Add(this->txt_center);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->txt_eye);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->btnOpen);
				 this->DoubleBuffered = true;
				 this->KeyPreview = true;
				 this->MinimumSize = System::Drawing::Size(558, 527);
				 this->Name = L"Form1";
				 this->Text = L"CG_task9";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
				 this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 unit(T);
				 
				 left   = 15;
				 right  = 110;
				 top    = 15;
				 bottom = 15;

				 Wcx = left;
				 Wcy = CLIENT_HEIGHT - bottom;
				 Wx  = CLIENT_WIDTH - left - right;
				 Wy  = CLIENT_HEIGHT - top - bottom;

				 aspect = Wx / Wy; 
			 }

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics;
				 g->Clear(Color::White);

				 Pen^ pen = gcnew Pen(Color::Black);
				 pen->Width = 1;

				 Pen^ rectPen = gcnew Pen(Color::Red);
				 rectPen->Width = BORDER;

				 Pen^ axesPen = gcnew Pen(Color::Gray);
				 axesPen->Width = 1;

				 System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", TEXT_SIZE);
				 SolidBrush^ brush = gcnew SolidBrush(Color::Black);

				 point Pmax = point(CLIENT_WIDTH - right, CLIENT_HEIGHT - bottom);
				 point Pmin = point(left, top);

				 mat3D V, U, R, T1;

				 LookAt(eye, center, up, V);

				 if (prOrtho == true) {
					 float Vy = 2 * near * tan(fovy / 2);
					 float Vx = Vy * aspect;
					 Ortho(Vx, Vy, near, far, U);
				 } else {
					 Perspective(fovy, aspect, near, far, U);
				 }

				 times(U, V, T1);
				 times(T1, T, R);

				 mat F;
				 frame(2, 2, -1, -1, Wx, Wy, Wcx, Wcy, F);

				 for (int i = 0; i < polygons.Count; i++) {
					 polygon3D^ p = polygons[i];
					 polygon^ p1 = gcnew polygon(0);

					 point a1, a2, c;
					 vec b1, b2;

					 point3D A;
					 vec3D B1, B2;

					 for (int j = 0; j < p->Count; j++) {
						 point2vec(p[j], B1);
						 timesMatVec(R, B1, B2);
						 vec2point(B2, A);
						 set(A, a1);

						 point2vec(a1, b1);
						 timesMatVec(F, b1, b2);
						 vec2point(b2, a1);
						 p1->Add(a1);
					 }

					 p1 = Pclip(p1, Pmin, Pmax);
					 if (p1->Count) {
						 pen->Color = colors[i];
						 c = p1[p1->Count - 1];
						 for (int j = 0; j < p1->Count; j++) {
							 g ->DrawLine(pen, c.x, c.y, p1[j].x, p1[j].y);
							 c = p1[j];
						 }
					 }
				 }

				 g->DrawLine(axesPen, left, 
					 (CLIENT_HEIGHT - bottom - top) / 2 + top, 
					 CLIENT_WIDTH - right, 
					 (CLIENT_HEIGHT - bottom - top) / 2 + top);
				 g->DrawLine(axesPen, (CLIENT_WIDTH - left - right) / 2 + left, 
					 top, 
					 (CLIENT_WIDTH - left - right) / 2 + left, 
					 CLIENT_HEIGHT - bottom);

				 g->DrawRectangle(rectPen, Wcx, top, Wx, Wy);

				 this->txt_eye->Text = "(" + round(eye.x, 1) + ", " + round(eye.y, 1) + ", " + round(eye.z, 1) + ")";
				 this->txt_center->Text = "(" + center.x + ", " + center.y + ", " + center.z + ")";
				 this->txt_up->Text = "(" + round(up.x, 1) + ", " + round(up.y, 1) + ", " + round(up.z, 1) + ")";
				 this->txt_fovy->Text = round(fovy, 1) + "";
				 this->txt_near->Text = round(near, 1) + "";
				 this->txt_far->Text = round(far, 1) + "";
				 if (prOrtho) this->txt_mode->Text = "Ortho";
				 else this->txt_mode->Text = "Perspective";
			 }

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {

				 if (this->openFileDialog->ShowDialog() ==
					 System::Windows::Forms::DialogResult::OK) {

						 wchar_t fileName[1024];
						 for (int i = 0; i < openFileDialog->FileName->Length; i++)
							 fileName[i] = openFileDialog->FileName[i];

						 fileName[openFileDialog->FileName->Length] = '\0';

						 polygons.Clear();
						 colors.Clear();

						 currentColor = Color::Black;

						 std::ifstream in;
						 in.open(fileName);
						 if (in.is_open()) {

							 std::string str;
							 getline(in, str);

							 while (in) {
								 if ((str.find_first_not_of(" \t\r\n") != std::string::npos)
									 && (str[0] != '#')) {

										 std::stringstream s(str);
										 std::string cmd;
										 s >> cmd;

										 if ( cmd == "lookat" ) {
											 float ex, ey, ez, cx, cy, cz, ux, uy, uz;
											 s >> ex >> ey >> ez >> 
												 cx >> cy >> cz >> 
												 ux >> uy >> uz;

											 eyeOld = point3D(ex, ey, ez);
											 centerOld = point3D(cx, cy, cz);
											 upOld = point3D(ux, uy, uz);
										 } 
										 else if ( cmd == "screen" ) {
											 float a, b, c;
											 s >> a >> b >> c;
											 fovyOld = a;
											 nearOld = b;
											 far = c;
										 } 
										 else if ( cmd == "triangle" ) {				
											 polygon3D^ P = gcnew polygon3D(0);
											 for (int i = 0; i < 3; i++) {
												 point3D p;
												 s >> p.x >> p.y >> p.z;
												 P->Add(p);
											 }

											 polygons.Add(P);
											 colors.Add(currentColor);
										 } 
										 else if ( cmd == "color" ) {
											 int r, g, b;
											 s >> r >> g >> b;

											 currentColor = Color::FromArgb(r, g, b);
										 }
								 }

								 getline(in, str);
							 }
						 }

						 center = centerOld;
                         near = nearOld;
                         fovy = fovyOld;

                         vec3D tmpVec, tmpVec1;
                         point3D tmpP;

						 LookAt(centerOld, eyeOld, upOld, T);

                         point2vec(eyeOld, tmpVec);
                         timesMatVec(T, tmpVec, tmpVec1);
                         vec2point(tmpVec1, tmpP);

                         eye = tmpP;
                         up  = point3D(0, 1, 0);
                         center = point3D(0, 0, 0);

						 alpha = RAD;
						 prOrtho = true;

						 this->txt_triangles->Text = polygons.Count + "";

						 this->Refresh();
				 }
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat3D R1, R2, R3, T1;

				 point3D xAxis = point3D(1, 0, 0);
				 point3D yAxis = point3D(0, 1, 0);
				 point3D zAxis = point3D(0, 0, 1);

				 switch(e->KeyCode) {
					 case Keys::W :
						 rotate(xAxis, alpha, R1);
						 times(R1, T, T1);
						 set(T1, T);
						 break;
					 case Keys::S :
						 rotate(xAxis, -alpha, R2);
						 times(R2, T, T1);
						 set(T1, T);
						 break;
					 case Keys::A :
						 rotate(yAxis, alpha, R1);
						 times(R1, T, T1);
						 set(T1, T);
						 break;
					 case Keys::D :
						 rotate(yAxis, -alpha, R1);
						 times(R1, T, T1);
						 set(T1, T);
						 break;
					 case Keys::Q :
						 rotate(zAxis, alpha, R3);
						 times(R3, T, T1);
						 set(T1, T);
						 break;
					 case Keys::E :
						 rotate(zAxis, -alpha, R3);
						 times(R3, T, T1);
						 set(T1, T);
						 break;
					 case Keys::O :
						 alpha *= 1.1;
						 break;
					 case Keys::L :
						 alpha *= 1 / 1.1;
						 break;
					 case Keys::Z :
						 near += 0.1;
						 break;
					 case Keys::X :
						 if (near >= 0.1) near -= 0.1;
						 break;
					 case Keys::C :
						 fovy += 0.1;
						 break;
					 case Keys::V :
						 fovy -= 0.1;
						 break;
					 case Keys::P :
						 prOrtho = !prOrtho;
						 break;
					 case Keys::Escape :
						 LookAt(centerOld, eyeOld, upOld, T);
						 near = nearOld;
						 fovy = fovyOld;
						 alpha = RAD;
						 prOrtho = true;
				 }

				 this->Refresh();
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx, oldWy = Wy;

				 Wcx = left;
				 Wcy = CLIENT_HEIGHT - bottom;
				 Wx  = CLIENT_WIDTH - left - right;
				 Wy  = CLIENT_HEIGHT - top - bottom;

				 mat R, T1;
				 move(-Wcx, -top, R);
				 times(R, resizeMat, T1);

				 scale(Wx / oldWx, Wy / oldWy, R);
				 times(R, T1, resizeMat);

				 move(Wcx, top, R);
				 times(R, resizeMat, T1);
				 set(T1, resizeMat);

				 aspect = Wx / Wy;

				 this->Refresh();
			 }
	};
}
