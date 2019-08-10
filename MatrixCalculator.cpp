#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>

struct HISTORY        
//Structure that will be written into the binary file
{
    int x;
    int y;
    int z;
    float A[20][20];
    float B[20][20];
    char Operation[25];
    float C[20][20];
    char type[10];//unary or binary
    char defined;
}HIS;

void INPUT(float M[20][20], int &m, int &n)
//to get the matrices' details from the user
{
    cout<<"Enter the number of rows:-";
    cin>>m;
    cout<<"Enter the number of columns:-";
    cin>>n;

    for(int i = 0; i < m; i++)
    {
	for(int j = 0; j < n; j++)
	{
	    cout<<"Enter the element for row "<<i + 1<<" and column "<<j + 1<<":-";
	    cin>>M[i][j];
	}
     }

}

void DISPLAY(float M[20][20], int x, int y)
//To display the matrix
//M - matrix to be displayed, x - no. of rows, y - no. of columns
{
    int i, j;

    for(i = 0; i < x; i++)
    {
	for(j = 0; j < y; j++)
	{
	    cout<<M[i][j]<<'\t';
	}
	cout<<endl;
    }
}

void SaveHistory(HISTORY X)
//This function will save the operations history.
{
    ofstream H("HISTORY.DAT", ios::app | ios::binary);

    H.write((char*)&X, sizeof(X));
    H.close();
}

void DisplayHistory()
//This function will display the history.
{
    ifstream I("HISTORY.DAT", ios::in | ios::binary);

    HISTORY Y;

    int Count = 0;

    while(I.read((char*)&Y, sizeof(Y)))
    {
	clrscr();
	Count++;
	cout<<"\tOPERATION #"<<Count<<":\n\n";
	cout<<"Matrix #1:"<<endl;
	DISPLAY(Y.A, Y.x, Y.y);

	if(strcmpi(Y.type, "binary") == 0)
	{
	    cout<<"\n\nMatrix #2:"<<endl;

	    if(strcmpi(Y.Operation, "multiplication") == 0)
		DISPLAY(Y.B, Y.y, Y.z);

	    else
		DISPLAY(Y.B, Y.x, Y.y);
	}
	cout<<"\n\nOperation: "<<Y.Operation;
	if(Y.defined != 'N')
	{
	    if(strcmpi(Y.Operation, "multiplication") == 0)
	    {
		cout<<"\n\nResult:"<<endl;
		DISPLAY(Y.C, Y.x, Y.z);
	    }

	    else if(strcmpi(Y.Operation, "transpose") == 0)
	    {
		cout<<"\n\nResult:"<<endl;
		DISPLAY(Y.C, Y.y, Y.x);
	    }

	    else
	    {
		cout<<"\n\nResult:"<<endl;
		DISPLAY(Y.C, Y.x, Y.y);
	    }
	}
	else
	    cout<<"\n\nNot defined."<<endl;
	if(strcmpi(Y.Operation, "ScalarMultiplication") == 0)
	{
	    cout<<"The scalar constant is = "<<Y.z<<endl;
	}
	getch();
	cout<<"\n\n-----------------------------------------------------------------------------\n\n";
    }
    I.close();
}

void ClearHistory()
//This function clears the history.
{
    remove("HISTORY.DAT");
    rename("TEMP.DAT", "HISTORY.DAT");
}

void ADD(float A[20][20],float B[20][20],float C[20][20],int m, int n)
//addition of matrices
{
    strcpy(HIS.type, "binary");
    HIS.defined = 'Y';
    for(int i = 0; i < m; i++)
    {
	for(int j = 0; j < n; j++)
	{
	    C[i][j] = A[i][j] + B[i][j];
	}
    }
}

void SUBTRACT(float A[20][20],float B[20][20],float C[20][20],int m, int n)
//subtraction of matrices
{
    strcpy(HIS.type, "binary");
    HIS.defined = 'Y';
    for(int i = 0; i < m; i++)
    {
	for(int j = 0; j < n; j++)
	{
	    C[i][j] = A[i][j] - B[i][j];
	}
    }
}

void MULTIPLY(float A[20][20],float B[20][20],float C[20][20],int a, int b, int c)
//for multiplying the matrices
{
    strcpy(HIS.type, "binary");
    HIS.defined = 'Y';
    for(int i = 0; i < a; i++)
    {
	for(int j = 0; j < c; j++)
	{
	    C[i][j] = 0;
	    for(int k = 0; k < b; k++)
	    C[i][j] = C[i][j] +(A[i][k] * B[k][j]);
	}
    }
}

void INVERSE()
{
    strcpy(HIS.type, "unary");

    int option3;
    float temp1, temp2, det, det_rec;

    beg_inverse:
    cout<<"This operation can calculate the inverse of only 1x1, 2x2 or 3x3 matrix."<<endl;
    cout<<"\nWhich one would you like?"<<endl;
    cout<<"1. 1x1"<<endl;
    cout<<"2. 2x2"<<endl;
    cout<<"3. 3x3"<<endl;
    cout<<"4. Go back?"<<endl;
    cout<<"\nEnter 1/2/3/4."<<endl;
    cin>>option3;

    switch(option3)
    {
    case 1:
	HIS.x = HIS.y = 1;

	cout<<"Enter the matrix. In this case, it has only one element."<<endl;
	cin>>HIS.A[0][0];

	if (HIS.A[0][0] == 0)
	{
	    HIS.defined = 'N';
	    cout<<"The inverse doesn't exist, it's not defined."<<endl;
	}

	else
	{
	    HIS.defined = 'Y';
	    HIS.C[0][0] = 1/HIS.A[0][0];
	    cout<<"The inverse is:\n\n";
	    cout<<HIS.C[0][0]<<endl;
	}
	SaveHistory(HIS);
	getch();
	break;

    case 2:
	HIS.x = HIS.y = 2;

	cout<<"Enter the matrix. In this case, it has four elements."<<endl;

	for(int i = 0; i < 2; i++)
	{
	    for(int j = 0; j < 2; j++)
	    {
		cout<<"Enter the element for row "<<i + 1<<" and column "<<j + 1<<":-";
		cin>>HIS.A[i][j];
	    }
	}

	det = ((HIS.A[0][0] * HIS.A[1][1]) - (HIS.A[1][0] * HIS.A[0][1]));

	if(det == 0)
	{
	    HIS.defined = 'N';
	    cout<<"The inverse doesn't exist, it's not defined."<<endl;
	}

	else
	{
	    HIS.defined = 'Y';

	    det_rec = 1/det;
	    temp1 = HIS.C[1][1];
	    HIS.C[1][1] = det_rec * HIS.C[0][0];
	    HIS.C[0][0] = det_rec * temp1;
	    temp2 = -1 * HIS.C[1][0];
	    HIS.C[1][0] = -1 * HIS.C[0][1] * det_rec;
	    HIS.C[0][1] = temp2 * det_rec;

	    clrscr();

	    cout<<"The Inverse is:\n\n";
	    DISPLAY(HIS.C, 2, 2);

	}
	SaveHistory(HIS);
	getch();
	break;

    case 3:
	HIS.x = HIS.y = 3;

	cout<<"Enter the matrix. In this case it has 9 elements."<<endl;
	for(i = 0; i < 3; i++)
	{
	    for(int j = 0; j < 3; j++)
	    {
		cout<<"Enter the element for row "<<i + 1<<" and column "<<j + 1<<":-";
		cin>>HIS.A[i][j];
	    }
	}
	det = (HIS.A[0][0] * ((HIS.A[1][1] * HIS.A[2][2]) - (HIS.A[1][2] * HIS.A[2][1])));

	if(det == 0)
	{
	    HIS.defined = 'N';
	    cout<<"The inverse doesn't exist, it's not defined."<<endl;
	}

	else
	{
	    det_rec = 1/det;
	    float a, b, c, d, e, f, g, h, i;
	    HIS.defined = 'Y';

	    a = HIS.A[0][0];
	    b = HIS.A[0][1];
	    c = HIS.A[0][2];
	    d = HIS.A[1][0];
	    e = HIS.A[1][1];
	    f = HIS.A[1][2];
	    g = HIS.A[2][0];
	    h = HIS.A[2][1];
	    i = HIS.A[2][2];


	    HIS.C[0][0] = det_rec * ((e * i) - (h * f));
	    HIS.C[0][1] = det_rec * -1 * ((b * i) - (c * h));
	    HIS.C[0][2] = det_rec * ((b * f) - (c * e));
	    HIS.C[1][0] = det_rec * -1 * ((d * i) - (f * g));
	    HIS.C[1][1] = det_rec * ((a * i) - (c * g));
	    HIS.C[1][2] = det_rec * -1 * ((a * f) - (c * d));
	    HIS.C[2][0] = det_rec * ((h * d) - (g * e));
	    HIS.C[2][1] = det_rec * -1 * ((a * h) - (b * g));
	    HIS.C[2][2] = det_rec * ((b * e) - (b * d));
	    cout<<"The inverse is:\n"<<endl;
	    clrscr();
	    DISPLAY(HIS.C, 3, 3);
	}
	SaveHistory(HIS);
	getch();
	break;

    case 4:
	break;

    default:
	cout<<"\nERROR! Invalid input! Please enter only 1/2/3/4."<<endl;
	getch();
	clrscr();
	goto beg_inverse;
    };
    clrscr();
}

void TRANSPOSE()
{
    strcpy(HIS.type, "unary");
    HIS.defined = 'Y';

    INPUT(HIS.A, HIS.x, HIS.y);

    int i, j;

    for(i = 0; i < HIS.x; i++)
    {
	for(j = 0; j < HIS.y; j++)
	HIS.C[j][i] = HIS.A[i][j];
    }
    clrscr();
    cout<<"The transpose is:\n\n";

    DISPLAY(HIS.C, HIS.y, HIS.x);
    getch();
}

void ScalarMultiplication()
{
    strcpy(HIS.type, "unary");
    HIS.defined = 'Y';
    INPUT(HIS.A, HIS.x, HIS.y);

    cout<<"Enter the scalar constant you want to multiply the matrix with."<<endl;

    cin>>HIS.z;

    for(int i = 0; i < HIS.x; i++)
    {
	for(int j = 0; j < HIS.y; j++)
	{
	    HIS.C[i][j] = HIS.z * HIS.A[i][j];
	}
    }

    clrscr();
    cout<<"Result:\n\n";
    DISPLAY(HIS.C, HIS.x, HIS.y);
}
void main()
{
    int option1, option2, option3;
    int a1, a2, b1, b2;

    while(1)
    {
	clrscr();
	HIS.x = HIS.y = HIS.z = 0;
	cout<<"---------------------------MENU-FOR-MATRIX-CALCULATOR---------------------------";
	cout<<"1. Find the Transpose of a Matrix."<<endl;
	cout<<"2. Calculate the Inverse of a Matrix."<<endl;
	cout<<"3. Addition of Two Matrices."<<endl;
	cout<<"4. Subtraction of a Matrix From Another."<<endl;
	cout<<"5. Multiplication of Two Matrices."<<endl;
	cout<<"6. Scalar Multiplication of a Matrix."<<endl;
	cout<<"7. See Calculator History."<<endl;
	cout<<"8. Clear History."<<endl;
	cout<<"9. Exit Program."<<endl;
	cout<<endl<<endl;

	cout<<"--------------------------------CHOOSE-AN-OPTION--------------------------------";
	cout<<endl<<"Option:-";
	cin>>option1;

	clrscr();

	switch(option1)
	{
	case 1:
	//TRANSPOSE
	    strcpy(HIS.type, "unary");
	    strcpy(HIS.Operation, "transpose");
	    cout<<"/////////////////////////////////////TRANSPOSE//////////////////////////////////";
	    TRANSPOSE();
	    SaveHistory(HIS);
	    break;

	case 2:
	//INVERSE
	    strcpy(HIS.Operation, "inverse");
	    strcpy(HIS.type, "unary");
	    cout<<"//////////////////////////////////////INVERSE///////////////////////////////////";
	    INVERSE();
	    break;

	case 3:
	//ADDITION
	    a:
	    clrscr();
	    cout<<"//////////////////////////////////////ADDITION//////////////////////////////////";
	    cout<<"The number of rows and columns for both matrices should be equal."<<endl;
	    cout<<"First Matrix:"<<endl;
	    INPUT(HIS.A, a1, a2);
	    cout<<endl;
	    cout<<"Second Matrix:"<<endl;
	    INPUT(HIS.B, b1, b2);
	    if(a1 == b1 && a2  == b2)
	    {
		cout<<endl;
		strcpy(HIS.Operation, "addition");
		strcpy(HIS.type, "binary");
		clrscr();
		HIS.x = a1;
		HIS.y = a2;
		ADD(HIS.A, HIS.B, HIS.C, HIS.x, HIS.y);
		cout<<endl<<"Addition successful!"<<endl;
		DISPLAY(HIS.C, HIS.x, HIS.y);
		getch();
		SaveHistory(HIS);
	    }
	    else
	    {
		cout<<"\nERROR! The number of rows or columns in both matrices are not equal. Please try again."<<endl;
		getch();
		goto a;
	    }
	    break;

	case 4:
	//SUBTRACTION
	    s:
	    clrscr();
	    cout<<"///////////////////////////////////SUBTRACTION//////////////////////////////////";
	    cout<<"The number of rows and columns for both matrices should be equal."<<endl;
	    cout<<"First Matrix:"<<endl;
	    INPUT(HIS.A, a1, a2);
	    cout<<endl;
	    cout<<"Second Matrix:"<<endl;
	    INPUT(HIS.B, b1, b2);
	    if(a1 == b1 && a2 == b2)
	    {
		cout<<endl;
		strcpy(HIS.type, "binary");
		strcpy(HIS.Operation, "subtraction");
		clrscr();
		HIS.x = a1;
		HIS.y = a2;
		SUBTRACT(HIS.A, HIS.B, HIS.C, HIS.x, HIS.y);
		cout<<endl<<"Subtraction successful!"<<endl;
		DISPLAY(HIS.C, HIS.x, HIS.y);
		getch();
		SaveHistory(HIS);
	    }
	    else
	    {
		cout<<"\nERROR! The number of rows or columns in both matrices are not equal. Please try again."<<endl;
		getch();
		goto s;
	    }
	    break;

	case 5:
	//MULTIPLICATION
	    m:
	    clrscr();
	    cout<<"//////////////////////////////////MULTIPLICATION////////////////////////////////";
	    cout<<"First Matrix:"<<endl;
	    INPUT(HIS.A, a1, a2);
	    cout<<endl;
	    cout<<"Second Matrix:"<<endl;
	    INPUT(HIS.B, b1, b2);
	    if(b1 != a2)
	    {
		cout<<"ERROR! Column of first matrix and row of second matrix should be equal. "<<endl;
		getch();
		goto m;
	    }
	    cout<<endl;
	    strcpy(HIS.Operation, "multiplication");
	    strcpy(HIS.type, "binary");
	    clrscr();
	    HIS.x = a1;
	    HIS.y = a2;
	    HIS.z = b2;
	    MULTIPLY(HIS.A, HIS.B, HIS.C, HIS.x, HIS.y, HIS.z);
	    cout<<endl<<"Multiplication successful!"<<endl;
	    DISPLAY(HIS.C, HIS.x, HIS.z);
	    getch();
	    SaveHistory(HIS);
	    break;

	case 6:
	   cout<<"////////////////////////////SCALAR_MULTIPLICATION///////////////////////////////";
	   strcpy(HIS.Operation, "ScalarMultiplication");
	   strcpy(HIS.type, "unary");
	   ScalarMultiplication();
	   SaveHistory(HIS);
	   getch();
	   break;

	case 7:
	   //DISPLAY HISTORY
	   DisplayHistory();
	   getch();
	   break;

	case 8:
	   //CLEAR HISTORY
	   ClearHistory();
	   clrscr();
	   cout<<"History successfully cleared."<<endl;
	   getch();
	   break;

	case 9:
	   clrscr();
	   cout<<"Thank you for using the Matrix Calculator! :)";
	   getch();
	   exit(0);

	default:
	   clrscr();
	   cout<<"\nERROR! Invalid Operation!\nPlease enter the index number of the funtion you want to use.";
	   getch();
	   break;
	};
    }
}