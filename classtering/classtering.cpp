#include<stdio.h>
#include<math.h>
#include<iostream>
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
	int* kol;
	pointf** w;
	pointf* mas;
	pointf* new_mas;
	pointf* vvod_p(int n) {                                 //Ввод исходного массива точек
		int i;
		z = new pointf[n];
		for (i = 0; i < n; i++)
			cin >> z[i].x >> z[i].y;
		return z;
	}
	void vivod(int n) {                                     //Вывод исходного масива точек
		int i;
		for (i = 0; i < n; i++)
			cout << z[i].x << ' ' << z[i].y << endl;
	}
	pointf* form_mas_centr(int n, int& m) {                 //Ввод массива центров
		int i, j, nom;
		j = 0;
		cout << "vvedite kolichestvo tochek-centrov" << endl;
		cin >> m;
		mas = new pointf[m];
		cout << "vvedite nomera tochek-centrov" << endl;
		for (i = 0; i < m; i++) {
			cin >> nom;
			mas[j] = z[nom];
			j++;
		}
		return mas;
	}
	pointf** form_klaster(int n, int m) {          //Формирование класстера по массиву центров (mas1)
		int i, j, k;
		kol = new int[m];
		//выделяем память
		w = new pointf * [m];
		for (j = 0; j < m; j++) {
			kol[j] = 0;
			for (i = 0; i < n; i++) {
				if (z[i].index(mas, m) == j)
					kol[j]++;
			}
			w[j] = new pointf[kol[j]];
		}
		//записываем в массив
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
	void vivod_matrix(int m) {
		int i, j;
		//выведем полученную рваную матрицу
		for (j = 0; j < m; j++) {
			for (i = 0; i < kol[j]; i++)
				//cout <<"( " << w[j][i].x << " ; " << w[j][i].y << ")  ";
				printf_s("( % f ;  % f)", w[j][i].x, w[j][i].y);
			cout << endl;
		}
	}
	pointf* new_centr(int m) {                            //метод пересчёта центровых точек (вычисление среднего арифемтического в класстерах)
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
	float modul_vector(int m, pointf* mas, pointf* new_mas) {             //Вычисление суммы расстояний между соотвтетствующими центровыми точками
		int j;
		float s = 0;
		for (j = 0; j < m; j++)
			s += sqrt((mas[j].x - new_mas[j].x) * (mas[j].x - new_mas[j].x) + (mas[j].y - new_mas[j].y) * (mas[j].y - new_mas[j].y));
		return s;
	}
	pointf** clustering_of_points(int m, int n) {                      //КЛАССТЕРИЗАЦИЯ ДО ТЕХ ПОР,ПОКА ЦЕНТРОВЫЕ ТОЧКИ НЕ СТАНУТ "ИДЕАЛЬНЫМИ"
		int k = 0;
		float eps;
		cout << "vvedite epsilon" << endl;
		cin >> eps;
		w = form_klaster(n, m);
		new_mas = new_centr(m);
		while (modul_vector(m, mas, new_mas) > eps)
		{
			mas = new_mas;
			w = form_klaster(n, m);
			new_mas = new_centr(m);
			k++;
		}
		cout << "kolichestvo iteracii=" << k << endl;
		return w;
	}
	void vivod_new_centr(int m) {                                              //Вывод массива центров
		int i;
		cout << "new masiv zentrov:" << endl;
		for (i = 0; i < m; i++)
			printf_s("( % f ;  % f)", new_mas[i].x, new_mas[i].y);
	}

};
void main() {
	classter klas;
	int d;
	int n, m;
	pointf* mas_centr;
	cout << "vvedite kolichestvo tochek" << endl;
	cin >> n;
	cout << "vvedite koordinaty tochek" << endl;
	klas.vvod_p(n);
	printf("vivod massiva tochek\n");
	klas.vivod(n);
	cout << endl;
	klas.form_mas_centr(n, m);
	//cout << "vivod mas centrov" << endl;
	//klas.form_klaster(n, m, mas_centr);
	klas.clustering_of_points(m, n);
	klas.vivod_matrix(m);
	klas.vivod_new_centr(m);
	cin >> d;
}