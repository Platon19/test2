#include<stdio.h>
#include<math.h>
#include<iostream>
#include<fstream>
using namespace std;
class pointf {
public:
	float x, y;
	float rast(pointf t) {
		return sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y));
	}
	int index(pointf* mas, int m) {
		int i, imin;
		float min;
		imin = 0;
		min = rast(mas[0]);
		for (i = 0; i < m; i++)
			if (min > rast(mas[i])) {
				min = rast(mas[i]);
				imin = i;
			}
		return imin;
	}
};
class classter {
public:
	pointf* z;
	int n;
	int m;
	int* kol;
	pointf** w;
	pointf* mas;
	pointf* new_mas;
	pointf* vvod_p() {                                 //Ввод исходного массива точек
		int i;
		cout << "vvedite kolichestvo tochek" << endl;
		cin >> n;
		z = new pointf[n];
		cout << "vvedite koordinaty tochek" << endl;
		for (i = 0; i < n; i++)
			cin >> z[i].x >> z[i].y;
		return z;
	}
	//*classter(){}
	pointf* vvod_p_in_file(){
		int i;
		ifstream f;
		f=ifstream("massiv_point.txt");	
		n = 10;
		z = new pointf[n];
		for (i = 0; i < n; i++)
			f>> z[i].x >> z[i].y;
		f.close();
		return z;
	}
	 /*~classter() {
	 if (n>0){
	 for(i=0; i<n; i++)
	 delete z[i];
	 }
	 }
	 */
	void vivod() {                                     //Вывод исходного масива точек
		int i;
		for (i = 0; i < n; i++)
			cout << z[i].x << ' ' << z[i].y << endl;
	}
	pointf* form_mas_centr() {                 //Ввод массива центров
		int i, j, nom;
		j = 0;
		cout << "vvedite kolichestvo tochek-centrov" << endl;
		cin >> m;
		mas = new pointf[m];

		cout << "vvedite nomera tochek-centrov" << endl;
		for (i = 0; i < m; i++) {
			cin >> nom;
			mas[i] = z[nom];

		}
		return mas;
	}
	pointf** form_klaster() {          //Формирование класстера по массиву центров
		int i, j, k;
		kol = new int[m];
		w = new pointf * [m];
		for (j = 0; j < m; j++) {
			kol[j] = 0;
			for (i = 0; i < n; i++) {
				if (z[i].index(mas, m) == j)
					kol[j]++;
			}
			w[j] = new pointf[kol[j]];
		}
		for (j = 0; j < m; j++) {
			k = 0;
			for (i = 0; i < n; i++)
				if (z[i].index(mas, m) == j) {
					w[j][k] = z[i];
					k++;
				};
		}
		return w;
	}
	void vivod_matrix() {
		int i, j;
		for (j = 0; j < m; j++) {
			for (i = 0; i < kol[j]; i++)
				//cout <<"( " << w[j][i].x << " ; " << w[j][i].y << ")  ";
				printf_s("( % f ;  % f)", w[j][i].x, w[j][i].y);
			cout << endl;
		}
	}
	pointf* new_centr() {                            //метод пересчёта центровых точек (вычисление среднего арифемтического в класстерах)
		int i, j;
		new_mas = new pointf[m];
		for (j = 0; j < m; j++) {
			new_mas[j].x = 0;
			new_mas[j].y = 0;
		}
		for (j = 0; j < m; j++) {
			for (i = 0; i < kol[j]; i++) {
				new_mas[j].x += w[j][i].x;
				new_mas[j].y += w[j][i].y;
			}
			new_mas[j].x = new_mas[j].x / kol[j];
			new_mas[j].y = new_mas[j].y / kol[j];
		}
		return new_mas;
	}
	float modul_vector() {             //Вычисление суммы расстояний между соотвтетствующими центровыми точками
		int j;
		float s = 0;
		for (j = 0; j < m; j++)
			s += mas[j].rast(new_mas[j]);
		return s;
	}
	pointf** clustering_of_points() {                      //КЛАССТЕРИЗАЦИЯ ДО ТЕХ ПОР,ПОКА ЦЕНТРОВЫЕ ТОЧКИ НЕ СТАНУТ "ИДЕАЛЬНЫМИ"
		int k = 0;
		float eps;
		cout << "vvedite epsilon" << endl;
		cin >> eps;
		w = form_klaster();
		new_mas = new_centr();
		while (modul_vector() > eps)
		{
			mas = new_mas;
			w = form_klaster();
			new_mas = new_centr();
			k++;
		}
		cout << "kolichestvo iteracii=" << k << endl;
		return w;
	}
	void vivod_new_centr() {                                              //Вывод массива центров
		int i;
		cout << "new masiv zentrov:" << endl;
		for (i = 0; i < m; i++)
			printf_s("( % f ;  % f)", new_mas[i].x, new_mas[i].y);
	}

};
void main() {
	classter klas;
	int d;
	//int n, m;
	//pointf* mas_centr;
	//klas.vvod_p();
	klas.vvod_p_in_file();
	//cin >> n;
	printf("vivod massiva tochek\n");
	klas.vivod();
	cout << endl;
	klas.form_mas_centr();
	//cout << "vivod mas centrov" << endl;
	//klas.form_klaster(n, m, mas_centr);
	klas.clustering_of_points();
	klas.vivod_matrix();
	klas.vivod_new_centr();
	cin >> d;
}