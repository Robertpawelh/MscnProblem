#include "pch.h"
#include "CMscnProblem.h"
#include "CRandomSearch.h"

int main() {
	bool b_is_success;
	string s_error_code;
	CMscnProblem *pc_problem_object = new CMscnProblem();
	pc_problem_object->bSetD(3);
	pc_problem_object->bSetF(3);
	pc_problem_object->bSetM(3);
	pc_problem_object->bSetS(2);
	pc_problem_object->vGenerateInstance(10);
	//pc_problem_object->vPrintInstance();
	CRandomSearch c_search(pc_problem_object);
	for (int i = 0; i < 3; i++) {
		cout << "PROBA NR " << i << ": " << endl;
		double * pd_best = c_search.pd_findBestSolution(i);
		if (pc_problem_object->bConstraintsSatisfied(pd_best, s_error_code)) {
			cout << pc_problem_object->dGetQuality(pd_best, b_is_success) << endl;
		}
		else {
			cout << s_error_code << endl;
		}
	}

	/* Parametry do generowania instancji zostaly dobrane tak, aby byly w stanie generowac sie dosc rozsadne instancje problemu.
	Zastosowane zostaly stale. Ich wartosc ustalono tak, aby zysk ze sklepow na ogol byl wiekszy niz suma kosztow transportu na wszystkich etapach.
	Popyt rowniez powinien byc na ogol nizszy, niz mozliwosci magazynowania, tak samo pojemnosc magazynow nizsza niz wydajnosc fabryk,
	a wydajnosc fabryk nizsza niz mozliwosci dostawcze.

	Pomiedzy klasami CRandomSearch i CMscnProblem zachodzi agregacja slaba, gdyz CMscnProblem moze istniec bez klasy
	szukajacej rozwiazania.
	Takich klas mozna utworzyc wiele, wiec nie powinien byc zalezny od odpowiedniej implementacji. Nie mozemy natomiast utworzyc
	obiektu klasy CRandomSearch bez obiektu problemu, gdyz w zamysle ma byc to klasa szukajaca rozwiazania dla konkretnego problemu
	mscn.
	Dziedziczenie w tym zadaniu rowniez mija sie z celem, gdyz obiekt klasy CRandomSearch powinien skupiac sie jedynie na
	operacjach zwiazanych z rozwiazywaniem problemu, nie powinien m.in. moc go zmieniac.
	*/
}