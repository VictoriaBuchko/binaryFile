#include <fstream>
#include <iostream>
using namespace std;

class Fraction
{
	int Numerator;   // числитель
	int Denominator; // знаменатель
public:

	Fraction() {
		Numerator = 0;
		Denominator = 1;
	}

	Fraction(int numerator, int denominator) {
		Numerator = numerator;
		Denominator = denominator;
	}

	void SetNumeratorFirst() {
		do
		{
			cout << "Enter the numerator for the first fraction: \n";
			cin >> Numerator;

		} while (Numerator == 0);

	}
	void SetDenominatorFirst() {

		do
		{
			cout << "Enter the denominator for the first fraction: \n";
			cin >> Denominator;

		} while (Denominator == 0);
	}
	void SetNumeratorSecond() {

		do
		{
			cout << "Enter the numerator for the second fraction: \n";
			cin >> Numerator;

		} while (Numerator == 0);
	}

	void SetDenominatorSecond() {
		do
		{
			cout << "Enter the denominator for the second fraction: \n";
			cin >> Denominator;

		} while (Denominator == 0);
	}
	void SetNumerator(double result) {

		Numerator = result;
	}

	void SetDenominator(double result) {

		Denominator = result;
	}

	int GetNumerator() const {
		return Numerator;
	}

	int GetDenominator() const {
		return Denominator;
	}

	Fraction operator + (const Fraction& fraction2) const {
		Fraction sum;

		sum.Numerator = (Numerator) * (fraction2.Denominator) + (fraction2.Numerator) * (Denominator);
		sum.Denominator = Denominator * fraction2.Denominator;

		return sum;
	}

	Fraction operator - (const Fraction& fraction2) const {
		Fraction difference;

		difference.Numerator = Numerator * (fraction2.Denominator) - (fraction2.Numerator) * Denominator;
		difference.Denominator = Denominator * fraction2.Denominator;

		return difference;
	}

	Fraction operator *(const Fraction& fraction2) const {
		Fraction product;

		product.Numerator = Numerator * fraction2.Numerator;
		product.Denominator = Denominator * fraction2.Denominator;

		return product;
	}

	Fraction operator*(int value) const
	{
		Fraction product;
		product.Numerator = Numerator * value;
		product.Denominator = Denominator;
		return product;
	}



	Fraction operator /(const Fraction& fraction2) const {
		Fraction fraction;

		fraction.Numerator = Numerator * fraction2.Denominator;
		fraction.Denominator = Denominator * fraction2.Numerator;

		return fraction;
	}

	Fraction operator++() {

		Numerator++;
		Denominator++;

		return *this;
	}

	Fraction operator++(int) {

		Fraction temp = *this;

		Numerator++;
		Denominator++;

		return temp;
	}

	operator double() {
		return double(Numerator) / double(Denominator);
	}
};

void printResult(const Fraction& result) {

	if ((result.GetNumerator() == result.GetDenominator()) || result.GetNumerator() == 0)
		cout << result.GetNumerator() / result.GetDenominator();
	else
		cout << result.GetNumerator() << "/" << result.GetDenominator();
}

Fraction& operator*(int value, const Fraction& fraction)
{
	Fraction product;
	product.SetNumerator(value * fraction.GetNumerator());
	product.SetDenominator(fraction.GetDenominator());
	return product;
}

int main()
{
	//1) Создать и инициализировать массив из 4-х объектов типа Дробь (Fraction)
	//  и записать этот массив в файл в бинарном режиме.
	//  Затем создать другой массив из 4-х объектов типа Дробь и считать в этот массив объекты из этого файла.
	Fraction fractions[4] = {
		Fraction(1, 2),
		Fraction(3, 4),
		Fraction(5, 6),
		Fraction(7, 8)
	};

	ofstream Fractions("Fractions.dat", ios::binary);
	if (!fractions) {
		cerr << "Error" << endl;
		exit(1);
	}
	for (const Fraction& fraction : fractions) {
		Fractions.write((char*)&fraction, sizeof(Fraction));
	}
	Fractions.close();


	Fraction fractions2[4];
	ifstream Fraction2("Fractions.dat", ios::binary);
	if (!Fraction2) {
		cerr << "Error" << endl;
		exit(1);
	}

	for (int i = 0; i < 4; ++i) {
		Fraction2.read((char*)&fractions2[i], sizeof(Fraction));
	}

	for (const Fraction& fraction : fractions2) {
		cout << "Numerator: " << fraction.GetNumerator()<< ", Denominator: " << fraction.GetDenominator() << endl;
	}

	//2 заданиеСоздать и инициализировать массив из 4-х объектов типа Дробь (Fraction)
	//  и записать этот массив в файл в бинарном режиме.
	//  Затем создать объект типа Дробь и считать из этого файла в этот объект данные предпоследнего объекта массива.
	//  Использовать позиционирование по файлу.

	Fraction2.seekg(-2 * sizeof(Fraction), ios::end);//-2*8=-16 байт от конца
	Fraction fraction;
	Fraction2.read((char* ) &fraction, sizeof(Fraction));
	cout << "Numerator: " << fraction.GetNumerator() << ", Denominator: " << fraction.GetDenominator() << endl;

	Fraction2.close();

	return 0;
}

