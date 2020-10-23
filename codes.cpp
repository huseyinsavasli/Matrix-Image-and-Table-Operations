/*  Name and Surname:Hüseyin SAVAŞLI
 A "Matrix, Image and Table Operations" */
/*
For Linux-On Terminal--To compile my c++ code,use 
$g++ codes.cpp
$./a. out
OR
$chmod +x ./a. out
OR for Nameless
$g++ -o output codes.cpp                                 
*/

#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <sstream>
#include <fstream>

using namespace std;
/*try - catch icinde yaz yanlıs varsa error verecektir.
	hatalar const char* exception turunde olur.
	catch blogunda bu sekilde yakalar.
	"Error : Matrix::fillToUnitMatrix() matris kare degil" hatasi verir mesela.
	Hatalar genellikle hangi siniftan kaynakli,hangi methodun icerisinde ve hatanin sebebi hakkinda bilgiler icerir.*/
template <class A>
class Row{
		A* data;
		int length;
	public:
		Row();//default yapici dataya yer almaz. length = 0 atar.
		Row(int length);//Satiri istenilen uzunlukta baslatir. Deger doldurmaz.
		Row(int length,const A& value);//satir istenilen uzunlukla baslar ve eleman degerlerini value ile doldurur.
		Row(const Row<A>& rhs); ~Row();//kopyalama yapicisi ve yikicisi
		void memAllocation(int length);// bellek tahsisi yaparak satiri baslatir.
    void charge(int starting,int finishing,const A& value);//satiri doldur 
		//starting = baslangic, finishing = bitis indeksleridir.
		void kill();//tahsis edilmis bellek varsa sisteme iade et satiri kaldir.
		int size()const;// eleman sayisini döndürür.
		bool sizeChecking(const Row<A>& rhs)const;//Satir boyutunu kontrolet.Ayniysa true don.
		Row<A>& operator=(const Row<A>& rhs); //degerleri kopyala yeniden bellek tahsisi yap!
    bool areTheyAllZero()const;
		A& operator[](int index);//indeksinci elemana ulasir.
		Row<A>& resize(int length);// yeniden boyutlandır ve daha büyük boyuta gecerken alanları 0 ile doldur
		Row<A>& copy(const Row<A>& rhs);//satır degerlerini kopyala,bellek tahsisi yapma!
	
		// Skaler operator islemlerim
    Row<A> operator%(const A& scaler)const;
		Row<A> operator+(const A& scaler)const;
		Row<A> operator-(const A& scaler)const;
    Row<A> operator/(const A& scaler)const;
		Row<A> operator*(const A& scaler)const;
		//Satir operator islemlerim
    Row<A> operator*(const Row<A>& rhs)const;
		Row<A> operator+(const Row<A>& rhs)const;
		Row<A> operator-(const Row<A>& rhs)const;

		A summation()const;   // satirdaki elemanlarin toplamini bulur.
		string toString(bool isSpace = false)const; //satiri stringe cevir,bosluk icin isSpace=true yap.
};

template<class A>
class Matrix{
	protected:
		Row<A>* data;
		int length;
	public:
		Matrix(int row = 10,int column = 10,const A& value = A()); // default yapici
		Matrix(int row,int column,char ch);//ch=e için birim matris, r için random deger doldur
		Matrix(const Matrix<A>& rhs); ~Matrix();// kopyalama yapicisi ve yikici	
		Matrix<A>& 
    copy(const Matrix<A>& rhs);//matris degerlerini kopyala,bellek tahsisi yapma,boyut ayni olmali!
		Matrix<A>& 
    set(const Matrix<A>& rhs,int sRow = 0,int sColumn = 0);//matris degerlerini setle
	  //Yeniden bellek tahsisi yapmaz.sRow baslangic satiri,sColumn baslangic kolunu indeksleridir. 
		Matrix<A> 
    get(int sRow,int fRow,int sColumn,int fColumn);
		/*bir Matrisden alt matris cikartir ve sRow baslangic,fRow bitis satir indeksi
		 sColumn baslangic,fColumn bitis kolunu indeksleridir.*/	
		void resize(int row, int column);
		//yeniden boyutlandirma.Daha buyuk bir boyuta gecerken yeni alanlari 0 ile doldurur.
		Matrix<A>& operator=(const Matrix<A>& rhs);
		//bir satirin degerlerini kopyalar.Yeniden bellek tahsisi yapar.
		Row<A>& operator[](int index);
		//indeksinci satir referansi doner.Satir duzeyinde islemlerde kullanmak icin.
		void memAllocation(int row,int column);// bellek tahsisi yaparak Matrisi baslatir.
		void charge(int starting,int finishing,const A& value);
		//Matrisi doldurur. starting = baslangic,finishing = bitis satir indeksleridir.
		void charge(int sRow,int fRow,int sColumn,int fColumn,const A& value);
		//Matrisi doldurur. sRow = baslangic satiri, fRow = bitis satiri, sColumn = baslangic sutunu,
		//fColumn = bitis satir indeksleridir.
		void charge(char ch);//Matrisi doldurur. ch = 'e' ise birim matris olarak,
		//ch = 'r' 0-255 arasinda degerler olacak sekilde doldurur.
		//Birim matris olustururken kare olmasi gerekir yoksa hata verir.
		void kill();//tahsis edilmis bellek varsa sisteme geri iade ederek matrisi kaldirir.
		int columnSize()const;// Sutun uzunlugunu dondurur.Tahsis edilmemis matrisde 0 doner.
		int rowSize()const;// Satir uzunlugunu dondurur.Tahsis edilmemis matrisde 0 doner.
		bool isSquareMatrix()const;// Kare matris mi degil mi?check
		bool sizeControl(const Matrix<A>& rhs)const;
		//Parametre matris ile satir sutun uzunluklarinin ayni olup olmadigini kontrol eder. Ayni ise true doner.
    void random();// 0-255 arasinda rastgele degerler ile doldurur.
		void fillToUnitMatrix();//Birim matris olacak sekilde elemanlari doldurur.
		string toString(bool hasSpace = false)const;//Matrisi stringe cevirir,her satirin toString kullanir.
		//elemanlar arasinda bosluk istenirse hasSpace = true olmalidir.
		void print(bool hasSpace = true)const;//Matrisi ekrana yazar.
		//Elemanlar arasinda bosluk istenirse hasSpace = true olmalidir.
		void print(string filename,bool hasSpace = false)const;//matrisi dosyaya yaz,elemanlar arasi bosluk icin hasSpace= true olmali!
		Row<A> nthRow(int index)const;//indeksinci satiri nesne olarak dondurur.
		Row<A> nthColumn(int index)const;//indeksinci sutunu nesne olarak dondurur.		
		// Matrix operation
		Matrix<A> operator+(const Matrix<A>& rhs)const;
		Matrix<A> operator-(const Matrix<A>& rhs)const;
		Matrix<A> operator*(const Matrix<A>& rhs)const;
   //Matrix<A> operator/(const Matrix<A>& rhs)const;
		Matrix<A> T()const;
		Matrix<A> emul(const Matrix<A>& rhs)const;
		Matrix<A> inv()const;
		/*kendi matrisimizin bir kopyasi solda,sagdaysa birim matris olacak sekilde islemler baslar.
			Gauss-Jordan alg. ile sol taraf birim
			matris olacak sekilde islemler yapilir.
			islemlerin sonunda sag tarafta kalan matris 
			orjinal matrisin tersidir.
		 Eğer matris kare degilseveyadeterminant sifirsa hata verir.*/	
		A det()const;//Laplace alg. ile rekursif olarak hesaplanir.
		//kare matrislerin ve n*nlik tum matrislerin determinanti hesaplanir.	
  	// Scalar operation
    Matrix<A> operator%(const A& scalar)const;
    Matrix<A> operator+(const A& scalar)const;
    Matrix<A> operator-(const A& scalar)const;
		Matrix<A> operator^(const A& scalar)const;
    Matrix<A> operator/(const A& scalar)const;	
		Matrix<A> operator*(const A& scalar)const;
		A summation()const;		
};
enum Type{BINARY,GRAY,RGB};
template<class A>
class Image:public Matrix<A>{
		Type type;
		void readFromBin(ifstream &f); // Gri olarak .bin dosyasi okur
		void readFromBin(ifstream &f,bool);//renkli olarak .bin dosyasi okur
		void readFromBMP(ifstream &f);//Gri olarak .BMP dosyasi okur
		void readFromBMP(ifstream &f,bool);//renkli olarak .BMP dosyasi okur
	public:
		Image(int width = 255,int height = 255,const A& value = A(),Type type = RGB);
		/*Matrix sifindan miras alir.
			height -> Matrix sinifina satir sayisi width -> Matrix sinifina sutun sayisi olarak gonderilir.
			Extra Type degiskeni goruntunun BINARY - GRAY - RGB oldugunu takip eder.
			Varsayilan olarak deger RGB dir.*/
		Image(string filename,string format);
		Type getType()const; //Resim tipini dondurur. BINARY - GRAY - RGB
		int getWidth()const; //genislik dondurur
		int getHeight()const;//yukseklik dondurur
		bool sizeControlOdd()const; //boyutlar tek sayimi kontrol eder.
		void imagereader(string filename,string format); //dosyadan okur
		void imagewriter(string filename,string format);
		void color2gray();//RGB ise GRAY'e donustur!bir piksel icin(red+green+blue)/3 ortalama al GRAY'e cevir!
		void gray2binary(int threshold);//GRAY ise esik degere gore BINARY'e donustur!
		//Eger goruntu GRAY ise esik degerine gore BINARY donusum yapar.
		//Bir Pixelin degeri esikten buyuk ise 1 olarak kucukse 0 olarak deger alir.
	
		/*Buradaki bicimsel islemler sadece BINARY goruntulerde calisir.
			Param.olarak bir Image turunden bir yapisal element bekler.
			yapisal element BINARY formda olmalidir. Ayrica boyutlaritek sayilar olmalidir.
			Ornegin Height = 3, Width = 3 veya Height = 5,Width 3 gibi	*/
		//!!Yapisal Element goruntu uzerinde gezdirilir.!!
		void erosion(const Image<A>& structElement); 
		//yapisal elemandaki tum elemanlar goruntunun o bolgesine FIT oluyorsa
		/*	yani noktasal carpimi yine yapisal elemanin eleman toplamina esitse
			o pixel degerine dokunmaz. Eger ki FIT olmuyorsa o pixel degerini
			0 yapar yani siler.*/
		void dilation(const Image<A>& structElement);
			/*Yapisal elemandaki tum elemanlar goruntunun o bolgesine Hit oluyorsa
			yani noktasal carpim degeri sifir degilse en az bir eleman eslesiyor
			demektir.Bu durumda o pixel degeri 1 olur.
			Hicbir eslesme yok ise o pixel degerine dokunmaz.*/
		void opening(const Image<A>& structElement); 
		/*Bu islemde erosion ve dilation islemleri arka arka sirasi ile ayni goruntuye uygulanir.*/
			//asindirma + genisletme
		void closing(const Image<A>& structElement); //genisletme + asindirma
		/*Bu islemde dilation ve erosion islemleri arka arka sirasi ile ayni goruntuye uygulanir.*/
		//yani genisletme + asindirma	
};
template<class A>
class Table : public Matrix<A>{
		string* rowNames;
		string* columnNames;
	public:
		Table(int r = 10,int c = 10,const A& value = A());
		/*r satirlik,c sutunluk table olusturur.
			Background'da matrix sinifi kullanir.
			Value matrisin varsayilan degerleridir.*/
		Table(int r,int c,char ch);
		/*r satirlik,c sutunluk table olusturur.
			Background'da matrix sinifi kullanir.
			ch = 'r' ise 0-255 arasinda degerler alir.
			ch != 'r' ise 0 degerini alir.*/
		Table(const Table<A>& rhs); ~Table();// kopyalama yapicisi ve yikicisi
		void memAllocation(int row,int column);
		/*Tableyi baslatir. satir ve sutun stringleri icin yer ayrimi yapar.
			Datalari saklamak icin Matrix sinifini kullanir.*/
		void kill();//satir ve sutun isimleri yer ayrilmissa kaldirir.
		void setDefaultNames(int row,int column);
		/*  default satir ve sutun isimleri hesaplar
			kolon isimleri icin kac harfli olmasi gerektigini bulur ve
			oruntusel olarak harf atamalari yapar.
			ornegin sutun = 27 icin AA,AB,...,AZ,BA olarak
			ornegin sutun 677 icin AAA,AAB,AAC...AAZ,ABA,ABB,ABA,...,AZZ,BAA olarak atama yapar.
			Yani her kelimenin en sagindaki harf bittiginde hemen solundaki
			bir sonraki harf olarak atayarak tekrar A dan baslar.*/
		Table<A>& operator=(const Table<A>& rhs);
		
		A& itemAt(int r,int c);
		A& itemAt(string s);
		A& itemAt(string rs,string cs);
		void setRowNames(string* newRowNames,int n);
		void setColumnNames(string* newColumnNames,int n);
		string toString(int space = 5)const;
		//stringe cevirir. Elemanlar arasinda space kadar bosluk koyar
		void print()const;
};
struct rgb{
	int red;
	int green;
	int blue;
	rgb(int red = 0,int green = 0,int blue = 0)
	: red(red),green(green),blue(blue)
	{	}
};

// create pixel level
rgb createPixelRGB(int red,int green,int blue);
rgb createPixelGray(int gray);

// convert pixel before to(2) after
rgb convertBGR2RGB(const rgb& pixel);
rgb convertRGB2Gray(const rgb& pixel);
rgb convertBGR2Gray(const rgb& pixel);
rgb convertGray2Binary(const rgb& pixel,int threshold);

// RGB struct operations 
rgb operator*(const rgb& lhs,const rgb& rhs);
rgb operator+(const rgb& lhs,const rgb& rhs);
rgb operator-(const rgb& lhs,const rgb& rhs);

// RGB scalar operations 
template<typename A> rgb operator%(const rgb& lhs,A scalar);
template<typename A> rgb operator+(const rgb& lhs,A scalar);
template<typename A> rgb operator-(const rgb& lhs,A scalar);
template<typename A> rgb operator/(const rgb& lhs,A scalar);
template<typename A> rgb operator*(const rgb& lhs,A scalar);


bool operator<(const rgb& lhs, const rgb& rhs)
{	return	lhs.green < rhs.green;	}
bool operator==(const rgb& lhs, const rgb& rhs)
{	return	lhs.green == rhs.green;	}
bool operator>(const rgb& lhs, const rgb& rhs)
{	return	lhs.green > rhs.green;	}


ostream& operator<<(ostream& out,const rgb& r);

rgb createPixelRGB(int red,int green,int blue)
{	return rgb(red,green,blue);	}

rgb createPixelGray(int gray)
{	return rgb(0,gray,0);	}

//convert pixel before to(2) after
rgb convertBGR2RGB(const rgb& pixel)
{	return rgb(pixel.blue,pixel.green,pixel.red);	}

rgb convertRGB2Gray(const rgb& pixel)
{	return createPixelGray((pixel.red + pixel.green + pixel.blue) / 3); }

rgb convertBGR2Gray(const rgb& pixel)
{	return convertBGR2Gray(convertBGR2RGB(pixel));	}

rgb convertGray2Binary(const rgb& pixel,int threshold)
{	
	return 	pixel.green > threshold 
			? createPixelGray(0)
			: createPixelGray(1);
}
rgb operator*(const rgb& lhs,const rgb& rhs)
{
	int red = lhs.red * rhs.red;
	int green = lhs.green * rhs.green;
	int blue = lhs.blue * rhs.blue;
	return rgb(red,green,blue);
}
rgb operator+(const rgb& lhs,const rgb& rhs)
{
	int red = lhs.red + rhs.red;
	int green = lhs.green + rhs.green;
	int blue = lhs.blue + rhs.blue;
	return rgb(red,green,blue);
}
rgb operator-(const rgb& lhs,const rgb& rhs)
{	return lhs + (rhs * -1.0);	}

template<typename A> rgb operator%(const rgb& lhs,A scalar)
{
	int red = lhs.red % scalar;
	int green = lhs.green % scalar;
	int blue = lhs.blue % scalar;
	return rgb(red,green,blue);
}
template<typename A> rgb operator+(const rgb& lhs,A scalar)
{	return lhs + rgb(scalar,scalar,scalar);	}

template<typename A> rgb operator-(const rgb& lhs,A scalar)
{	return lhs - rgb(scalar,scalar,scalar);	}

template<typename A> rgb operator/(const rgb& lhs,A scalar)
{
	int red = lhs.red / scalar;
	int green = lhs.green / scalar;
	int blue = lhs.blue / scalar;
	return rgb(red,green,blue);
}
template<typename A> rgb operator*(const rgb& lhs,A scalar)
{	return lhs * rgb(scalar,scalar,scalar);	}


ostream& operator<<(ostream& out,const rgb& r)
{	
    out<<r.green<<"";// bozuk paralar belli bir sekilde gorunur...
	//out << r.green<<","<<r.blue<<","<<r.red;
	return out;
}

template<class A>
Row<A>::Row()
: data(NULL),length(0)
{	}
		
template<class A>
Row<A>::Row(int length)
: Row<A>()
{	memAllocation(length); } 

template<class A>
Row<A>::Row(int length,const A& value)
: Row<A>(length)
{	
	charge(0,length,value);
}

template<class A>
Row<A>::Row(const Row<A>& rhs)
: data(NULL)
{	*this = rhs;	}

template<class A>
Row<A>::~Row()
{	kill();	}

template<class A>
Row<A>& Row<A>::operator=(const Row<A>& rhs)
{
	if(this != &rhs){
		memAllocation(rhs.length);
		copy(rhs);
	}
	return *this;	
}

template<class A>
void Row<A>::memAllocation(int length)
{
	kill();
	this->length = length;
	data = new A[length];
}	

template<class A>
void Row<A>::charge(int starting,int finishing,const A& value)
{
	if(data){
		for(int i = starting;i < finishing;i++)
			data[i] = value;
	}
	else
		throw "Error Row::charge(starting,finishing,value) dataya yer ayrilmamis";
}

template<class A>
void Row<A>::kill()
{
	if(data){
		delete[] data;
		data = NULL;
	}
}

template<class A>
int Row<A>::size()const
{	return length;	}

template<class A>
bool Row<A>::sizeChecking(const Row<A>& rhs)const
{	return length == rhs.length;	}

template<class A>
bool Row<A>::areTheyAllZero()const
{	
	for(int i = 0;i<length;i++)
		if(data[i] != 0)
			return false;
	return true;
}

template<class A> Row<A>& Row<A>::copy(const Row<A>& rhs)
{
	if(!sizeChecking(rhs))
		throw "Error Row::copy(rhs) boyutlar ayni degil";
	for(int i = 0 ; i < length;i++)
		data[i] = rhs.data[i];
	return *this;
}

template<class A> Row<A>& Row<A>::resize(int length)
{
	if(this->length != length){
		Row<A> tmp(length);
		int availableLength = this->length < length ? this->length : length;
		for(int i=0;i<availableLength;i++)
			tmp[i] = data[i];
		*this = tmp;
	}
	return *this;
}

template<class A> A& Row<A>::operator[](int index)
{
	if(index < 0 || index >= length)
		throw "Error : Row::operator[](index) index hatali";
	return data[index];
}

template<class A> Row<A> Row<A>::operator+(const Row<A>& rhs)const
{
	if(!sizeChecking(rhs))
		throw "Error Row::operator+(rhs) boyutlar ayni degil";
	Row<A> tmp(length);
	for(int i=0;i<length;i++)
		tmp[i] = data[i] + rhs.data[i];
	return tmp;
}

template<class A> Row<A> Row<A>::operator-(const Row<A>& rhs)const
{
	if(!sizeChecking(rhs))
		throw "Error Row::operator-(rhs) boyutlar ayni degil";
	return *this + Row<A>(length,-1) * rhs;
}
template<class A> Row<A> Row<A>::operator*(const Row<A>& rhs)const
{
	if(!sizeChecking(rhs))
		throw "Error Row::operator*(rhs) boyutlar ayni degil";
	Row<A> tmp(length);
	for(int i=0;i<length;i++)
		tmp[i] = data[i] * rhs.data[i];
	return tmp;
}


template<class A> Row<A> Row<A>::operator%(const A& scaler)const
{
	Row<A> tmp(length);
	for(int i=0;i<length;i++)
		tmp[i] = data[i] % scaler;
	return tmp;
}
template<class A> Row<A> Row<A>::operator+(const A& scaler)const
{	return *this + Row<A>(length,scaler);	}

template<class A> Row<A> Row<A>::operator-(const A& scaler)const
{	return *this - Row<A>(length,scaler);	}

template<class A> Row<A> Row<A>::operator/(const A& scaler)const
{
	Row<A> tmp(length);
	for(int i=0;i<length;i++)
		tmp[i] = data[i] / scaler;
	return tmp;
}
template<class A> Row<A> Row<A>::operator*(const A& scaler)const
{	return *this * Row<A>(length,scaler);	}


template<class A> A Row<A>::summation()const
{
	A result = A();
	if(data){
		for(int i=0;i<length;i++)
			result = result + data[i];
	}
	return result;
}

template<class A> 
string Row<A>::toString(bool isSpace)const
{
	stringstream ss;
	string space = (isSpace ? " ":"");
	if(data){
		for(int i = 0 ; i < length;i++)
			ss << data[i] << space;
	}
	return ss.str();
}

template<class A>
Matrix<A>::Matrix(int row,int column,const A& value)
: data(NULL)
{
	memAllocation(row,column);
	charge(0,row,0,column,value);
}

template<class A>
Matrix<A>::Matrix(int row,int column,char ch)
: data(NULL)
{	
	memAllocation(row,column);
	charge(ch);
}

template<class A>
Matrix<A>::Matrix(const Matrix<A>& rhs) : data(NULL)
{	*this = rhs;	}

template<class A>
Matrix<A>::~Matrix()
{	kill();	}

template<class A>
Matrix<A>& Matrix<A>::copy(const Matrix<A>& rhs){
	if(!sizeControl(rhs))
		throw "Error Matrix::copy(rhs) boyutlar ayni degil";
	return set(rhs);
}
template<class A>
Matrix<A>& Matrix<A>::set(const Matrix<A>& rhs,int sRow,int sColumn){
	int rowlength = rowSize();
	int columnlength = columnSize();
	int rhs_rowlength = rhs.rowSize();
	int rhs_columnlength = rhs.columnSize();
	if(sRow < 0 || rhs_rowlength + sRow > rowlength)
		throw "Error Matrix::set(rhs,sRow,sColumn) sRow hatali";
	if(sColumn < 0 || rhs_columnlength + sColumn > columnlength)
		throw "Error Matrix::set(rhs,sRow,sColumn) sColumn hatali";
	for(int i = 0 ;i < rhs_rowlength;i++){
		for(int j=0;j< rhs_columnlength;j++)
			data[sRow + i][sColumn + j] = rhs.data[i][j];
	}
	return *this;
}

template<class A>
Matrix<A> Matrix<A>::get(int sRow,int fRow,int sColumn,int fColumn)
{
	int rowlength = rowSize();
	int columnlength = columnSize();
		
	if(sRow < 0 || sRow >= rowlength || sRow > fRow)
		throw "Error Matrix::get(sRow,fRow,sColumn,fColumn) sRow hatali";
	if(fRow < 0 || fRow > rowlength)
		throw "Error Matrix::get(sRow,fRow,sColumn,fColumn) fRow hatali";
	if(sColumn < 0 || sColumn >= columnlength || sColumn > fColumn)
		throw "Error Matrix::get(sRow,fRow,sColumn,fColumn) sColumn hatali";
	if(fColumn < 0 || fColumn > columnlength)
		throw "Error Matrix::get(sRow,fRow,sColumn,fColumn) fColumn hatali";
	Matrix<A> tmp(fRow-sRow,fColumn-sColumn);
	for(int i=sRow;i < fRow;i++){
		int new_i = i-sRow;
		for(int j = sColumn;j<fColumn;j++)
		{
			tmp[new_i][j-sColumn] = data[i][j];
		}
	}
	return tmp;
}

template<class A>
void Matrix<A>::resize(int row, int column)
{
	Matrix<A> tmp(row,column);
	int forrow = row < rowSize() ? row : rowSize();
	int forcolumn = column < columnSize() ? column : columnSize();
	for(int i=0;i<forrow;i++)
		for(int j = 0;j < forcolumn;j++)
			tmp[i][j] = data[i][j];
	*this = tmp;
}

template<class A>
Matrix<A>& Matrix<A>::operator=(const Matrix<A>& rhs)
{
	if(this != &rhs){
		memAllocation(rhs.rowSize(),rhs.columnSize());
		copy(rhs);
	}
	return *this;
}

template<class A>
Row<A>& Matrix<A>::operator[](int index)
{
	if(index < 0 || index >= length)
		throw "Error : Matrix::operator[](index) index hatali";
	return data[index];
}

template<class A>
void Matrix<A>::memAllocation(int row,int column)
{
	kill();
	length = row;
	data = new Row<A>[length];
	for(int i=0;i<length;i++)
		data[i].memAllocation(column);
}

template<class A>
void Matrix<A>::kill()
{
	if(data){
		for(int i = 0; i < length;i++)
			data[i].kill();
		delete [] data;
		data = NULL;
	}
}

template<class A>
int Matrix<A>::rowSize()const
{	return data ? length : 0;	}

template<class A>
int Matrix<A>::columnSize()const
{	return data ? data[0].size() : 0;	}

template<class A>
void Matrix<A>::charge(int sRow,int fRow,int sColumn,int fColumn,const A& value)
{
	for(int i=sRow;i<fRow;i++)
		data[i].charge(sColumn,fColumn,value);	
}

template<class A>
void Matrix<A>::charge(char ch)
{
	switch(ch){
		case 'e':
		case 'E':
			fillToUnitMatrix();
			break;
		case 'r':
		case 'R':
			random();
			break;
	}
}

template<class A>
bool Matrix<A>::sizeControl(const Matrix<A>& rhs)const
{	
	return 	rowSize() == rhs.rowSize() &&
			columnSize() == rhs.columnSize();
}
		
template<class A>
bool Matrix<A>::isSquareMatrix()const
{	return data && rowSize() == columnSize();	}

template<class A>
void Matrix<A>::fillToUnitMatrix()
{
	if(data){
		if(!isSquareMatrix())
			throw "Error : Matrix::fillToUnitMatrix() matris kare degil";
		int columnlength = columnSize();
		int rowlength = rowSize();
		
		for(int i = 0 ; i < rowlength;i++){
			for(int j = 0 ; j < columnlength;j++)
				if(i == j)
        data[i][j] =1.0;
        else{
        data[i][j] =0.0;
        }
        //data[i][j] = i == j ? 1.0 : 0.0;
		}
	}
}

template<class A>
void Matrix<A>::random()
{
	if(data){
		int column = data[0].size();
		for(int i = 0 ; i < length;i++){
			for(int j = 0 ; j < column;j++)
				data[i][j] = rand() % 256;
		}
	}
}

template<class A>
string Matrix<A>::toString(bool isSpace)const
{
	string tmp;
	for(int i = 0 ; i < length;i++)
		tmp += data[i].toString(isSpace) + "\n";
	return tmp;
}

template<class A>
void Matrix<A>::print(bool hasSpace)const
{
	cout << toString(hasSpace);	
}

template<class A>
void Matrix<A>::print(string filename,bool hasSpace)const
{
	ofstream f(filename.c_str());
	if(f.is_open()){
		f << toString(hasSpace);
		f.close();
	}
}

template<class A> 
Row<A> Matrix<A>::nthRow(int index)const
{
	if(index < 0 || index >=length)
		throw "Error Matrix::getRow(index) index hatali";			
	return data[index];
}

template<class A> 
Row<A> Matrix<A>::nthColumn(int index)const
{
	try{
		int rowlength = rowSize();
		Row<A> tmp(rowlength);
		for(int i = 0 ; i < rowlength;i++)
			tmp[i] = nthRow(i)[index];
		return tmp;
	}
	catch(...){	
		throw "Error Matrix::nthColumn(index) index hatali";			
	}	
}


template<class A> Matrix<A> Matrix<A>::operator+(const Matrix<A>& rhs)const
{
	if(!sizeControl(rhs))
		throw "Error Matrix::operator+(rhs) boyutlar ayni degil";
	int rowlength = rowSize();
	Matrix<A> tmp(rowlength,columnSize());
	for(int i = 0 ; i < rowlength;i++)
		tmp[i] = nthRow(i) + rhs.nthRow(i);
	return tmp;
}

template<class A> Matrix<A> Matrix<A>::operator-(const Matrix<A>& rhs)const
{
	try{
		return *this + rhs * -1;
	}
	catch(...){	
		throw "Error Matrix::operator-(rhs) boyutlar ayni degil";
	}
}

template<class A> Matrix<A> Matrix<A>::operator*(const Matrix<A>& rhs)const
{
	if(columnSize() != rhs.rowSize())
		throw "Error Matrix::operator* boyutlar uygun degil";
	int rowlength = rowSize();
	int columnlength = rhs.columnSize();
	Matrix<A> tmp(rowlength,columnlength);
	for(int i = 0; i < rowlength ; i++){
		Row<A> row = nthRow(i);
		for(int j = 0 ; j < columnlength ; j++)
			tmp[i][j] = (row * rhs.nthColumn(j)).summation();
	}
	return tmp;
}


template<class A> Matrix<A> Matrix<A>::T()const
{
	int columnlength = columnSize();
	Matrix<A> tmp(columnlength,rowSize());
	for(int i = 0 ; i < columnlength; i++)
		tmp[i] = nthColumn(i);
	return tmp;
}

template<class A> Matrix<A> Matrix<A>::emul(const Matrix<A>& rhs)const
{
	if(!sizeControl(rhs))
		throw "Error Matrix::emul(rhs) boyutlar ayni degil";
	int rowlength = rowSize();
	Matrix<A> tmp(rowlength,rowlength);
	for(int i = 0 ; i < rowlength;i++)
		tmp[i] = nthRow(i) * rhs.nthRow(i);
	return tmp;
}

template<class A> Matrix<A> Matrix<A>::inv()const
{
	if(!isSquareMatrix())
		throw "Error :  Matrix::inv() matrix kare degil";
	if(det() == A())
		throw "Error :  Matrix::inv() matrixin determinanti sifir";
	int rowlength = rowSize();
	Matrix<A> copyMatrix = *this;
	Matrix<A> inverse(rowlength,rowlength,'e');
	int i = 0;
	//ust ucgen matris olusturma
	while(i < rowlength){
		A pivotCoeffient = copyMatrix[i][i];
		if(pivotCoeffient == A()){
			for(int j = i ; j < rowlength ; j++)
			{
				if(copyMatrix[j][i] != A()){
					Row<A>  row = copyMatrix[i];
					copyMatrix[i] = copyMatrix[j];
					copyMatrix[j] = row;
					 
					row = inverse[i];
					inverse[i] = inverse[j];
					inverse[j] = row;
					pivotCoeffient = copyMatrix[i][i];
					break;
				}
			}
		}
		copyMatrix[i] = copyMatrix[i] / pivotCoeffient;
		inverse[i] = inverse[i] / pivotCoeffient;
		for(int j = i + 1;j< rowlength;j++){
			A coeffient = copyMatrix[j][i];
			copyMatrix[j] = copyMatrix[j] -  copyMatrix[i] * coeffient;
			inverse[j] = inverse[j] - inverse[i] * coeffient;
		}
		i++;
	}
	
	//alt ucgen matris olusturma
	while(--i > 0){
		for(int j = i - 1;j >= 0;j--){
			A coeffient = copyMatrix[j][i];
			copyMatrix[j] = copyMatrix[j] -  copyMatrix[i] * coeffient;
			inverse[j] = inverse[j] - inverse[i] * coeffient;
		}
	}
	/*
		tum islemlerden orjinal matris birim matrise dondu.
		inverse ilk basta birim matris olarak baslamisti.
		fakat orjinal matris birim matrise donusturulurken
		ayni islemler inverse uzerinde de yapildiginden
		inverse artik bu matrisin tersidir.
	*/
	return inverse;
}

template<class A> A Matrix<A>::det()const
{
	if(!isSquareMatrix())
		throw "Error : Matrix::det() matrix kare degil";
	if(rowSize() == 1)
		return data[0][0];
	int rowlength = rowSize();
	A result = A();
	for(int i = 0 ; i < rowlength ; i++){
		if(data[0][i] != 0){
			Matrix<A> tmp(rowlength - 1,rowlength - 1);
			for(int j = 1 ; j < rowlength ; j++)
			{
				for(int k = 0; k < rowlength;k++){
					if(k < i)
						tmp[j-1][k] = data[j][k];
					else if(k > i)
						tmp[j-1][k - 1] = data[j][k];
				}
			}
			result += pow(-1,i) * data[0][i] * tmp.det();
		}
	}
	/*  ilk satiri sabit tutarak alt matrisleri yinelemeli(rekursif)olarak gider.
		matrisin kofaktor,minor ve alt matrisin determinant degeri 
		carpma islemleri yapilir ve orjinal matrisin determinantı elde edilir.
		Matrisin satir sayisi = 1 esit olasiga kadar alt matris olusur.
		satir sayisi 1 olan matrisin determinanti kendisine esittir.*/	
	return result;
}
 /*                         Scalar islemler*/
template<class A> Matrix<A> Matrix<A>::operator%(const A& scalar)const
{
	Matrix<A> tmp = *this;
	int rowlength = rowSize();
	for(int i = 0;i < rowlength;i++)
		tmp[i] = tmp[i] % scalar;
	return tmp;
}
template<class A> Matrix<A> Matrix<A>::operator+(const A& scalar)const
{	return *this + Matrix<A>(rowSize(),columnSize(),scalar);	}

template<class A> Matrix<A> Matrix<A>::operator-(const A& scalar)const
{	return *this - Matrix<A>(rowSize(),columnSize(),scalar);	}

template<class A> Matrix<A> Matrix<A>::operator^(const A& scalar)const
{
	Matrix<A> tmp(rowSize(),columnSize(),'e');
	for(int i = 0;i<scalar;i++)
		tmp = tmp * *this;
	return tmp;
}
template<class A> Matrix<A> Matrix<A>::operator/(const A& scalar)const
{
	Matrix<A> tmp = *this;
	int rowlength = rowSize();
	for(int i = 0;i < rowlength;i++)
		tmp[i] = tmp[i] / scalar;
	return tmp;
}

template<class A> Matrix<A> Matrix<A>::operator*(const A& scalar)const
{
	int rowlength = rowSize();
	Matrix<A> tmp(rowlength,columnSize());
	for(int i = 0 ; i < rowlength ;i++)
		tmp[i] = nthRow(i) * scalar;
	return tmp;
}


template<class A>
A Matrix<A>::summation()const
{
	A result = A();
	int rowlength = rowSize();
	for(int i=0;i<rowlength;i++)
		result = result + nthRow(i).summation();
	return result;
}

//Table tanımlamalarim
template<class A>
Table<A>::Table(int r,int c,const A& value)
: Matrix<A>(r,c,value), rowNames(NULL),columnNames(NULL)
{	
	memAllocation(r,c);
	setDefaultNames(r,c);
}

template<class A>
Table<A>::Table(int r,int c,char ch)
: Matrix<A>(r,c) , rowNames(NULL),columnNames(NULL)
{	
	switch(ch){
		case 'r':
		case 'R':
			Matrix<A>::random();
			break;
	}
	memAllocation(r,c);
	setDefaultNames(r,c);
}

template<class A>
Table<A>::Table(const Table<A>& rhs)
: rowNames(NULL),columnNames(NULL)
{	*this = rhs;	}

template<class A>
Table<A>::~Table()
{	kill();	}

template<class A>
void Table<A>::memAllocation(int row,int column)
{
	kill();
	rowNames = new string[row];
	columnNames = new string[column];
}

template<class A>
void Table<A>::setDefaultNames(int row,int column)
{
	//kod prototipinde aciklanmistir!
	string tmpRowNames[row];
	string tmpColumnNames[column];
	stringstream ss;
	
	for(int i = 0 ; i < row;i++)
	{
		ss << i;
		getline(ss,tmpRowNames[i]);
		ss.clear();
	}
	
	int letterCount = 26;
	int entropy = column == 1 ? 1 : ceil(log(column) / log(letterCount));
	for(int i = 0 ; i < column ; i++){
		int value = i;
		for(int e = entropy - 1 ; e >= 0 ; e--){
			int energy = value / pow(letterCount,e);
			tmpColumnNames[i] += (char)(energy + 65);
			value -= energy * pow(letterCount,e);
		}
	}
	setRowNames(tmpRowNames,row);
	setColumnNames(tmpColumnNames,column);
}

template<class A>
void Table<A>::kill()
{
	if(rowNames)
		delete [] rowNames;
	if(columnNames)
		delete [] columnNames;
	rowNames = NULL;
	columnNames = NULL;
}

template<class A>
Table<A>& Table<A>::operator=(const Table<A>& rhs)
{
	if(this != &rhs){
		Matrix<A>::operator=(rhs);
		int rowlength = rhs.rowSize();
		int columnlength = rhs.columnSize();
		memAllocation(rowlength,columnlength);
		setRowNames(rhs.rowNames,rowlength);
		setColumnNames(rhs.columnNames,columnlength);
	}
	return *this;
}

template<class A>
A& Table<A>::itemAt(int r,int c)
{
	if(r < 0 || r >= Matrix<A>::rowSize())
		throw "Error : Table::itemAt(r,c) r parametresi hatali";
	if(c < 0 || c >= Matrix<A>::columnSize())
		throw "Error : Table::itemAt(r,c) c parametresi hatali";
	return Matrix<A>::data[r][c];
}

template<class A>
A& Table<A>::itemAt(string s)
{
	if(s.empty())
		throw "Error : Table::itemAt(s) s stringi bos";
	int rowlength = Matrix<A>::rowSize();
	int columnlength = Matrix<A>::columnSize();
	for(int x = 0 ; x < columnlength;x++)
	{
		for(int j = 0;j< rowlength;j++)
			if(s == columnNames[x] + rowNames[j])
				return itemAt(j,x);
	}
	throw "Error : Table::itemAt(s) aranan indeksler bulunamadi";
}

template<class A>
A& Table<A>::itemAt(string rs,string cs)
{
	try{
		return itemAt(cs + rs);
	}
	catch(...){
		throw "Error : Table::itemAt(rs,cs) aranan indeksler bulunamadi";
	}
}

template<class A>
void Table<A>::setRowNames(string* newRowNames,int n)
{
	if(rowNames){
		for(int i = 0;i<n;i++)
			rowNames[i] = newRowNames[i];
	}
}

template<class A>
void Table<A>::setColumnNames(string* newColumnNames,int n)
{
	if(columnNames){
		for(int i = 0;i<n;i++)
			columnNames[i] = newColumnNames[i];
	}
}

template<class A>
string Table<A>::toString(int space)const
{
	stringstream matSS,ss;
	matSS << Matrix<A>::toString(true);
	int column = Matrix<int>::columnSize();
	ss << left << setw(space * 2) << "";
	for(int i = 0 ; i < column;i++)
		ss  << setw(space) << columnNames[i];
	ss << endl;
	int row = 0;
	string line;
	while(getline(matSS,line)){
		ss << setw(space * 2) << rowNames[row];
		stringstream lineSS;
		lineSS << line;
		string lineReader;
		while(lineSS >>lineReader)
			ss << setw(space) << lineReader;
		ss << endl;
		row++;
	}
	return ss.str();
}

template<class A>
void Table<A>::print()const{
	cout << toString();//bosluklar icin varsayilan degeri baz alir.
}


template<class A>
Image<A>::Image(int width,int height,const A& value,Type type)
: Matrix<A>(height,width,value), type(type)
{		}

template<class A>
Image<A>::Image(string filename,string format)
{	imagereader(filename,format);	}

template<class A>
Type Image<A>::getType()const
{	return type;	}

template<class A>
int Image<A>::getWidth()const
{	return Matrix<A>::columnSize();	}

template<class A>
int Image<A>::getHeight()const
{	return Matrix<A>::rowSize();	}

template<class A>
bool Image<A>::sizeControlOdd()const
{	return getWidth() % 2 && getHeight() % 2;	}

template<class A>
void Image<A>::readFromBin(ifstream &f)
{
	unsigned char size[2];
	unsigned char reader;
	f.read((char*)size,sizeof(size));
	int height = (int)size[0];
	int width = (int)size[1];
	Matrix<A>::resize(height,width);
	for(int i=0;i<height;i++){
		for(int j = 0 ; j < width;j++){
			f.read((char*)&reader,sizeof(reader));
			Matrix<A>::data[i][j] = createPixelGray(reader);
		}
	}
	
}
template<class A>
void Image<A>::readFromBin(ifstream &f,bool)
{
	unsigned char size[2];
	unsigned char reader[3];
	f.read((char*)size,sizeof(size));
	int height = (int)size[0];
	int width = (int)size[1];
	Matrix<A>::resize(height,width);
	for(int i=0;i<height;i++){
		for(int j = 0 ; j < width;j++){
			f.read((char*)&reader,sizeof(reader));
			rgb pixel = createPixelRGB(reader[0],reader[1],reader[2]);
			Matrix<A>::data[i][j] = convertBGR2RGB(pixel);
			/*BMP dosyalar BGR desenine sahiptir.pixeli RGB gibi okuduk. Ancak pixel icerisinde BGR var
			 convert islemi ile B ile R yer degismesi gerekir.
			 convertBGR2RGB islemi sadece B ile R nin yerini degistirir, G sabit kalir.
		   Artik pixel icerisinde RGB degerler vardir.*/
		}
	}
	
}
template<class A>
void Image<A>::readFromBMP(ifstream &f)
{	
	unsigned char info[54];
	f.read((char*)info,sizeof(info));
	int height = (int)info[22];
	int width = (int)info[18];
	unsigned char reader;
	Matrix<A>::resize(height,width);
	f.seekg((int)info[10],ios::beg);
	for(int i=0;i<height;i++){
		for(int j = 0 ; j < width;j++){
			f.read((char*)&reader,sizeof(reader));
			Matrix<A>::data[i][j] = createPixelGray(reader);
		}
	}
}

template<class A>
void Image<A>::readFromBMP(ifstream &f,bool)
{	
	unsigned char info[54];
	f.read((char*)info,sizeof(info));
	int height = (int)info[22];
	int width = (int)info[18];
	Matrix<A>::resize(height,width);
	unsigned char reader[3];
	f.seekg((int)info[10],ios::beg);
	for(int i=0;i<height;i++){
		for(int j = 0 ; j < width;j++){
			f.read((char*)&reader,sizeof(reader));
			rgb pixel = createPixelRGB(reader[0],reader[1],reader[2]);
			Matrix<A>::data[i][j] = convertBGR2RGB(pixel);
			/*	BMP dosyalar BGR desenine sahiptir.
				pixeli RGB gibi okuduk. Ancak pixel icerisinde BGR var
				convert islemi ile B ile R yer degismesi gerekir.
				convertBGR2RGB islemi sadece B ile R nin yerini degistirir, G sabit kalir.
				Artik pixel icerisinde RGB degerler vardir.
			*/
		}
	}
}

template<class A>
void Image<A>::imagereader(string filename,string format){
	ifstream f(filename.c_str(),ios::binary);
	if(!f.is_open())
		throw "Image::imagereader(filename,format) dosya acilamadi";
	string postFix = filename.substr(filename.rfind(".") + 1);
	if(format == "color"){
		type = RGB;
		if(postFix == "bin")
			readFromBin(f,true);
		else if(postFix == "bmp")
			readFromBMP(f,true);
		else
			throw "Error : Image::imagereader(filename,format) filename uzantisi hatali";
	}
	else if(format == "gray"){
		type = GRAY;
		if(postFix == "bin")
			readFromBin(f);
		else if(postFix == "bmp")
			readFromBMP(f);
		else
			throw "Error : Image::imagereader(filename,format) filename uzantisi hatali";
	}
	else
		throw "Error : Image::imagereader(filename,format) dosya format hatasi var";
	
}

template<class A>
void Image<A>::imagewriter(string filename,string format){
	if(format == "color"){
		
	}else if("gray"){
		
	}
}

template<class A>
void Image<A>::color2gray(){
	if(getType() == RGB){
		int width = Matrix<A>::columnSize();
		int height = Matrix<A>::rowSize();
		for(int i = 0;i< height;i++){
			for(int j=0;j<width;j++)
				Matrix<A>::data[i][j] = convertRGB2Gray(Matrix<A>::data[i][j]);
		}
		type = GRAY;
	}
}

template<class A>
void Image<A>::gray2binary(int threshold){
	if(getType() == GRAY){
		int width = Matrix<A>::columnSize();
		int height = Matrix<A>::rowSize();
		for(int i = 0;i< height;i++){
			for(int j=0;j<width;j++)
				Matrix<A>::data[i][j] = convertGray2Binary(Matrix<A>::data[i][j],threshold);
		}
		type = BINARY;
	}
	
}

template<class A>
void Image<A>::erosion(const Image<A>& structElement){
	if(getType() == BINARY){
		if(structElement.getType() != BINARY)
			throw "Error erosion(structElement) structElementin tipi BINARY degil";
		if(!structElement.sizeControlOdd())
			throw "Error erosion(structElement) structElementin boyutlari tek sayi degil";
		int elemWidth = structElement.getWidth();
		int elemHeight = structElement.getHeight();
		int width = getWidth();
		int height = getHeight();
		int centralX = elemWidth / 2;
		int centralY = elemHeight / 2;
		Image<A> result(width + 2 * centralX,height + 2 * centralY);
		Image<A> tmp(elemWidth,elemHeight);
		result.set(*this,centralY,centralX);
		A structElementTotal = structElement.summation();
		for(int i = 0 ; i < height;i++){
			for(int j = 0; j < width;j++){
				tmp.copy(result.get(i,elemHeight + i,j,elemWidth + j));
				if(!((structElement.emul(tmp)).summation() == structElementTotal))
						Matrix<A>::data[i][j] = A(0,0,0);
			}
		}	
	}
}

template<class A>
void Image<A>::dilation(const Image<A>& structElement){
	if(getType() == BINARY){
		if(structElement.getType() != BINARY)
			throw "Error dilation(structElement) structElementin tipi BINARY degil";
		if(!structElement.sizeControlOdd())
			throw "Error dilation(structElement) structElementin boyutlari tek sayi degil";
		int elemWidth = structElement.getWidth();
		int elemHeight = structElement.getHeight();
		int width = getWidth();
		int height = getHeight();
		int centralX = elemWidth / 2;
		int centralY = elemHeight / 2;
		Image<A> result(width + 2 * centralX,height + 2 * centralY);
		Image<A> tmp(elemWidth,elemHeight);
		result.set(*this,centralY,centralX);
		for(int i = 0 ; i < height;i++){
			for(int j = 0; j < width;j++){
				tmp.copy(result.get(i,elemHeight + i,j,elemWidth + j));
				if((structElement.emul(tmp)).summation() > A(0))
					Matrix<A>::data[i][j] = A(0,1,0);
			}
		}
	}
}

template<class A>
void Image<A>::opening(const Image<A>& structElement){
	if(getType() == BINARY){
		if(structElement.getType() != BINARY)
			throw "Error opening(structElement) structElementin tipi BINARY degil";
		if(!structElement.sizeControlOdd())
			throw "Error erosion(structElement) structElementin boyutlari tek sayi degil";
		erosion(structElement);
		dilation(structElement);
	}
}

template<class A>
void Image<A>::closing(const Image<A>& structElement){
	if(getType() == BINARY){
		if(structElement.getType() != BINARY)
			throw "Error opening(structElement) structElementin tipi BINARY degil";
		if(!structElement.sizeControlOdd())
			throw "Error erosion(structElement) structElementin boyutlari tek sayi degil";
		dilation(structElement);
		erosion(structElement);
	}
}
int main(){
	srand(time(0));
	
	try{

   /*
    Table<int> table(5,6,'r');
    table.print();
  */
  /*
    Matrix<int> m1(4,4);
	  m1.print();
	  cout << endl;
	  Matrix<int> m2(4,4,'e');
		m2.print();
		cout << endl;
		m1 = Matrix<int>(4,4,'r');
		m1.print();
		cout << endl;
		Matrix<int> m3;
		m3 = m1 + m2;
		m3.print();
		cout << endl;
		m3 = m1 - m2;
		m3.print();
		cout << endl;
		m3 = m1 + 4;
		m3.print();
		cout << endl;
		m3 = m1 * m2;
		m2.print();
		cout << endl;
		m3 = m1 + 4;
		m3.print();
		cout << endl;
		m3 = m1 - 4;
		m3.print();
		cout << endl;
		m3 = m1 * 4;
		m3.print();
		cout << endl;
		m3 = m1 / 4;
		m3.print();
		cout << endl;
		m3 = m1 % 4;
		m3.print();
		cout << endl;
		m3 = m1 ^ 4;
		m3.print();
		cout << endl;
		cout << m1.det() << endl;
		m1.inv().print();*/
  
  //kare birim matris yapma
  /*	Matrix<int> m(3,3,'e');
    m.print();*/
  
  //bozuk para tespiti icin 331.satiri aktif et!
    Image<rgb> image1("image1.bin", "gray");
    image1.print("gray.txt", true);
    image1.gray2binary(100);
    image1.print("binary.txt",true);
    Image<rgb> cigdem(3,3,1,BINARY);
    cout<<"dosyalar olusturuldu"<<endl; 
  /*
    Matrix<int> m(4,3,6);
	  m.print();
	  Matrix<int> m2(3,4,2);
	  m2.print();
	  Matrix<int> m3 = m * m2;
	  m3.print();
  */
  /*
    Table<int> t1;
		t1.print();
		cout << endl;
		Table<int> t2(2,3,10);
		t2.print();
		cout << endl;
		Table<int> t3(5,5,'r');
		t3.print();
		cout << endl;
		cout << t3.itemAt(3,4) << endl;
		cout << t3.itemAt("D4") << endl;
		cout << t3.itemAt("4","D") << endl;
		string rowNames[] = {"1.satir","2.satir","4.satir","5.satir","6.satir"};
		// 3. satırı atlıyorum;
		string columnNames[] = {"stn1","stn2","stn3","stn4","stn6"};
		//5. sütunu atlıyorum 
		t3.setRowNames(rowNames,5);
		t3.setColumnNames(columnNames,5);
		t3.print();
	*/
	}
	catch(const char* exception){
		cout << exception;
	}
	return 0;
}
