#include <iostream>
#include <vector>
//Calculadora que sólo usa sumas. Hay partes que se pueden optimizar, sobre todo sqrt(),
//puede que se pueda mejorar el rendimiento con simpificar() en algunos lados.
//El resto de operaciones se pueden añadir trivialmente teniendo las básicas.



//Operaciones para ints
int mult(int a, int b) {
	int ret = 0;
	for (int i = b; i > 0; i--)
	{
		ret += a;
	}
	return ret;
}
int resta(int a, int b) {
	return  a + (-b);
}
int divi(int a, int b) { //tiene que ser entera
	int cuenta = 0;
	while (a >= b)
	{
		cuenta++;
		a = resta(a,b);
	}
	return cuenta;
}


class Racional {
public:
	int num, den;
	Racional(int a, int b) {
		
		num = a;
		den = b;
		

	}
	void print() {
		simplificar(*this);
		printf("%d/%d\n",num,den);
	}
	
	Racional operator+(Racional a) {

		// a/b + c/d = (ad + cb)/bd
		return Racional(
			mult(a.num, this->den) + (mult(a.den, this->num)),
			mult(a.den, this->den));

	}
	Racional operator * (Racional a) {
		return Racional(
			mult(a.num, this->num),
			mult(a.den, this->den)
		);
	}
	Racional operator-(Racional a) {
		return( *this + (a * Racional(-1,1)));
	}
	Racional operator/(Racional a) {
		return Racional(
			mult(this->num, a.den),
			mult(this->den, a.num)
			);
	}
	 Racional operator%(Racional a) { //Optimizable
		 Racional temp = *this;
		 do
		 {
			 temp = *this;
			 *this = *this - a;
		 } while (this->num >= 0);
		 return temp;
	}	 
	 static std::vector<Racional> mcm(Racional a, Racional b) { //en verdad no es mcm pero me da igual, es ad/bd, cb/bd
		 int denominador = mult(a.den, b.den);
		 Racional x(mult(a.num, b.den), denominador);
		 Racional y(mult(b.num, a.den), denominador);
		 //Aquí es cuando lamento no estar usando python. Voy a usar un std::vector porque soy muy vago
		 std::vector<Racional> ret = { x,y};
		 return ret;
	 }
	 bool operator>(Racional a) { 
		 std::vector<Racional> foo = mcm(*this, a);
		 if (foo[0].num > foo[1].num)
			 return true;
		 else
			 return false;
	 }
	 bool operator<(Racional a) {
		 std::vector<Racional> foo = mcm(*this, a);
		 if (foo[0].num < foo[1].num)
			 return true;
		 else
			 return false;
	 }
	 bool operator==(Racional a) {
		 std::vector<Racional> foo = mcm(*this, a);
		 if (foo[0].num == foo[1].num)
			 return true;
		 else
			 return false;
	 }

	 static Racional sqrt(Racional a) {//Grande newton un crack. 
		 Racional raiz = a;
		 int cuenta = 0;
		 raiz = Racional(1, 2) * (raiz + (a / raiz));//4 iteraciones bastan porque se vuelven numeros muy grandes. quizas el rendimiento mejora con simplificar() tras cada iteracion pero no me apetece probarlo		 
		 raiz = Racional(1, 2) * (raiz + (a / raiz));
		 raiz = Racional(1, 2) * (raiz + (a / raiz));
		 raiz = Racional(1, 2) * (raiz + (a / raiz));
		
	 return raiz;
	 }
	 int coeficiente() {
		 int c = 0;
		 Racional x = *this;
		 while (x.num >= 0)
		 {
			 x.num = x.num - x.den;
			 c++;// :)

		 }
		 return c;
	 
	 }
	 static int mcd(Racional a){ //Euclides idolo genio maquina 
		 int x = a.num, y = a.den;
		 if (x == 0)
			 return y;
		 return mcd(Racional(y % x, x));
	 }

	 static Racional simplificar(Racional& x) { //Recursivo papi
		 int comun = mcd(x);   
		 x.den = divi(x.den, comun);
		 x.num = divi(x.num, comun);
		 if (comun == 1) {
			 return x;
		 }
		 
 		 return simplificar(x);

	 } 
		

};





int main() {
	Racional foo(20, 30);
	foo = foo * Racional(6, 1);
 	foo.print();
}