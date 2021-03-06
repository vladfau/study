#pragma once

#define forn(i, n) for(int i=0; i < (int) n; ++i)

namespace task4_5 {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;

	private: System::Windows::Forms::Button^  btnOpen;
			 int CELL_SIZE;
			 int PEN_WIDTH;
			 float left, right, top, bottom;
			 float Wcx, Wcy, Wx, Wy;
			 float Vcx, Vcy, Vx, Vy;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->btnOpen = (gcnew System::Windows::Forms::Button());
				 this->SuspendLayout();
				 // 
				 // openFileDialog
				 // 
				 this->openFileDialog->DefaultExt = L"txt";
				 this->openFileDialog->FileName = L"openFileDialog";
				 this->openFileDialog->Filter = L"ÒåêCòîâûå ôàéëû (*.txt)|*.txt|ÂCå ôàéëû (*.*)|*.*";
				 this->openFileDialog->Title = L"Îòêðûòü ôàéë";
				 // 
				 // btnOpen
				 // 
				 this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->btnOpen->Location = System::Drawing::Point(672, 16);
				 this->btnOpen->Name = L"btnOpen";
				 this->btnOpen->Size = System::Drawing::Size(99, 32);
				 this->btnOpen->TabIndex = 0;
				 this->btnOpen->Text = L"Открыть";
				 this->btnOpen->UseVisualStyleBackColor = true;
				 this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(784, 562);
				 this->Controls->Add(this->btnOpen);
				 this->DoubleBuffered = true;
				 this->KeyPreview = true;
				 this->MinimumSize = System::Drawing::Size(300, 300);
				 this->Name = L"Form1";
				 this->Text = L"Form1";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
				 this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
				 this->ResumeLayout(false);

			 }
#pragma endregion
	private: Bitmap^ drawFigureBresenham(Bitmap^ bitmap, int x0, int y0, int R) {
				 int x = 0;
				 int y = R;
				 int delta = 1 - 2 * R;
				 int error = 0;

				 while (y >= 0) {
				     bitmap->SetPixel(x0 + x, y0 + y, Color::Black);
					 bitmap->SetPixel(x0 + x, y0 - y, Color::Black);
					 bitmap->SetPixel(x0 - x, y0 + y, Color::Black);
					 bitmap->SetPixel(x0 - x, y0 - y, Color::Black);

					 error = 2 * (delta + y) - 1;
					 if (delta < 0 && error <= 0) {
						 ++x;
						 delta += 1 + 2 * x;
						 continue;
					 }

					 error = 2 * (delta - x) - 1;
					 if (delta > 0 && error > 0) {
						 --y;
						 delta += 1 - 2 * y;
						 continue;
					 }

					 x++;
					 delta += 2 * (x - y);
					 y--;
				 }

				 return bitmap;
			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 unit(T);
				 matrices.clear();

				 CELL_SIZE = 20;
				 PEN_WIDTH = 0.1;
				 Rectangle rect = Form::ClientRectangle;

				 left = 100;
				 top = 100;
				 bottom = 100;
				 right = 100;

				 Vcx = 0;
				 Vcy = 0;
				 Vx = 800;
				 Vy = 400;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx;
				 float oldWy = Wy;

				 Wcx = left;
				 Wcy = Form::ClientRectangle.Height - bottom;
				 Wx = Form::ClientRectangle.Width - left - right;
				 Wy = Form::ClientRectangle.Height - top - bottom;

				 mat R, T1;
				 move(-Wcx, -top, R);
				 times(R, T, T1);

				 scale(Wx / oldWx, Wy / oldWy, R);
				 times(R, T1, T);

				 move(Wcx, top, R);
				 times(R, T, T1);
				 set(T1, T);

				 this->Refresh();
			 }

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Bitmap^ image1  = gcnew  Bitmap(this->ClientRectangle.Width, this->ClientRectangle.Height);
				 Graphics^ g = Graphics::FromImage(image1);

				 g->Clear(Color::White);
				 Rectangle rect = Form::ClientRectangle;

				 Pen^ pen = gcnew Pen(Color::Black);
				 pen->Width = PEN_WIDTH;

				 Pen^ red = gcnew Pen(Color::Red);
				 red->Width = PEN_WIDTH * 2;

				 Rectangle form = System::Drawing::Rectangle(Wcx, top, Wx, Wy);
				 g->DrawRectangle(red, form);
				 g->Clip = gcnew System::Drawing::Region(form);

				 System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 8);
				 SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);

				 g->Transform = gcnew System::Drawing::Drawing2D::Matrix(
					 T[0][0], T[1][0],
					 T[0][1], T[1][1],
					 T[0][2], T[1][2]);

				 int R = 20;
				 Bitmap^ circle = gcnew Bitmap(2 * (R + 1) + 1, 2 * (R + 1) + 1);
				 drawFigureBresenham(circle, R + 1, R + 1, R);

				 for (int i = 0; i < matrices.size(); i++) {
					 mat C;
					 times(T, matrices[i], C);
					 g->Transform = gcnew System::Drawing::Drawing2D::Matrix(
						 C[0][0], C[1][0],
						 C[0][1], C[1][1],
						 C[0][2], C[1][2]);

					 g->DrawImage(circle, -R, -R);
				 }

				 g = e->Graphics;
				 g->DrawImage(image1, 0, 0);
				 delete image1;
			 }

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					 wchar_t fileName[1024];
					 for (int i = 0; i < openFileDialog->FileName->Length; i++) {
						 fileName[i] = openFileDialog->FileName[i];
					 }

					 fileName[openFileDialog->FileName->Length] = '\0';
					 std::ifstream in;
					 in.open(fileName);

					 if (in.is_open()) {
						 matrices.clear();
						 std::stack<mat> matStack;
						 mat K; 
						 unit(K);
						 unit(T);

						 std::string str;
						 getline(in, str);

						 while (in) {
							 if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
								 std::stringstream s(str);
								 std::string cmd;
								 s >> cmd;

								 if (cmd == "frame") {
									 int a, b, c, d;
									 s >> a >> b >> c >> d;

									 Vcx = a;
									 Vcy = b;
									 Vx = c;
									 Vy = d;

									 frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
								 } else if (cmd == "figure") {
									 matrices.push_back(K);
								 } else if (cmd == "pushTransform") {
									 matStack.push(K);
								 } else if (cmd == "popTransform") {
									 K = matStack.top();
									 matStack.pop();
								 } else if (cmd == "translate") {
									 float x, y;
									 s >> x >> y;
									 mat C, C1;
									 move(x, y, C);
									 times(K, C, C1);
									 K = C1;
								 } else if (cmd == "scale") {
									 float x, y;
									 s >> x >> y;
									 mat C, C1;
									 scale(x, y, C);
									 times(K, C, C1);
									 K = C1;
								 } else if (cmd == "rotate") {
									 float Phi;
									 s >> Phi;
									 float pi = 3.1415926535;
									 float PhiR = Phi * (pi / 180);
									 mat C, C1;
									 rotate(PhiR, 0, 0, C);
									 times(K, C, C1);
									 K = C1;
								 }
							 }

							 getline(in, str);
						 }
					 }

					 this->Refresh();
				 }
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 Rectangle rect = Form::ClientRectangle;
				 mat R, T1;
				 unit(R);

				 float scaleCoeff = 1 / 1.1;
				 float centerX = left + (rect.Width - right - left) / 2;
				 float centerY = top + (rect.Height - bottom - top) / 2;

				 switch(e->KeyCode) {
					case Keys::W:
						move(0, -1, R);
						break;
					case Keys::S:
						move(0, 1, R);
						break;
					case Keys::A:
						move(-1, 0, R);
						break;
					case Keys::D:
						move(1, 0, R);
						break;
					case Keys::T:
						move(0, -CELL_SIZE, R);
						break;
					case Keys::G:
						move(0, CELL_SIZE, R);
						break;
					case Keys::F:
						move(-CELL_SIZE, 0, R);
						break;
					case Keys::H:
						move(CELL_SIZE, 0, R);
						break;
					case Keys::E:
						rotate(0.05, left, top, R);
						break;
					case Keys::Q:
						rotate(-0.05, left, top, R);
						break;
					case Keys::Y:
						rotate(0.05, centerX, centerY, R);
						break;
					case Keys::R:
						rotate(-0.05, centerX, centerY, R);
						break;
					case Keys::Z:
						scale(scaleCoeff, scaleCoeff, R);
						break;
					case Keys::X:
						scale(1.1, 1.1, R);
						break;
					case Keys::C:
						move(-centerX, -centerY, R);
						times(R, T, T1);

						scale(scaleCoeff, scaleCoeff, R);
						times(R, T1, T);

						move(centerX, centerY, R);
						break;
					case Keys::V:
						move(-centerX, -centerY, R);
						times(R, T, T1);

						scale(1.1, 1.1, R);
						times(R, T1, T);

						move(centerX, centerY, R);
						break;
					case Keys::L:
						move(-centerX, 0, R);
						times(R, T, T1);

						scale(1.1, 1, R);
						times(R, T1, T);

						move(centerX, 0, R);
						break;
					case Keys::K:
						move(-centerX, 0, R);
						times(R, T, T1);

						scale(scaleCoeff, 1, R);
						times(R, T1, T);

						move(centerX, 0, R);
						break;
					case Keys::O:
						move(0, -centerY, R);
						times(R, T, T1);

						scale(1, 1.1, R);
						times(R, T1, T);

						move(0, centerY, R);
						break;
					case Keys::I:
						move(0, -centerY, R);
						times(R, T, T1);

						scale(1, scaleCoeff, R);
						times(R, T1, T);

						move(0, centerY, R);
						break;
					case Keys::U:
						reflectVertical(R);
						times(R, T, T1);
						set(T1, T);
						move(rect.Width - right + left, 0, R);
						break;
					case Keys::J:
						reflectHorizontal(R);
						times(R, T, T1);
						set(T1, T);
						move(0, rect.Height - bottom + top, R);	
						break;
					case Keys::Escape:
						frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
				 }

				 times(R, T, T1);
				 set(T1, T);
				 this->Refresh();
			 }
	};
}
