#include "pch.h"
#include "CMscnProblem.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"

int main() {
	bool b_is_success;
	string s_error_code;
	CMscnProblem *pc_problem_object = new CMscnProblem();
	pc_problem_object->bSetD(4);
	pc_problem_object->bSetF(3);
	pc_problem_object->bSetM(3);
	pc_problem_object->bSetS(2);
	pc_problem_object->vGenerateInstance(1);
//	pc_problem_object->vPrintInstance();

	CRandomSearch c_search(pc_problem_object);
	CDiffEvol c_diff_evol(pc_problem_object);
	for (int i = 0; i < 1; i++) {
		cout << "PROBA NR " << i << ": " << endl;
		cout << "BY RANDOM:\n";
		double * pd_best_by_random = c_search.pdFindBestSolution(i);
		if (pc_problem_object->bConstraintsSatisfied(pd_best_by_random, s_error_code)) {
			pc_problem_object->vPrintSolution(pd_best_by_random);
			cout << "\nPROFIT: " << pc_problem_object->dGetQuality(pd_best_by_random, b_is_success) << endl;
		}
		else {
			cout << "RANDOM SOL IS BAD: " << s_error_code << endl;
		}
		
		cout << "\nBY DIFF:\n";
		double * pd_best_by_diff = c_diff_evol.pdFindBestSolution(i);
		if (pc_problem_object->bConstraintsSatisfied(pd_best_by_diff, s_error_code)) {
			pc_problem_object->vPrintSolution(pd_best_by_diff);
			cout << "\nPROFIT: " << pc_problem_object->dGetQuality(pd_best_by_diff, b_is_success) << endl;
		}
		else {
			cout << "DIFF SOL IS BAD: " << s_error_code << endl;
		}
		delete pd_best_by_diff;
		//delete pd_best_by_random;
	}
	delete pc_problem_object;
}

/*Zastanow sie, ktory z obiektow powinien zliczac liczbe wywolan oceny przystosowania
i umiesc kod w odpowiednim miejscu.

Umiescilem licznik jako zmienna prywatna klasy CDiffEvol i inkrementuje go w metodzie, ktora odpowiada za ustawianie quality nowemu 
osobnikowi oraz w przypadku, gdy nie mozna bylo utworzyc nowego osobnika (jego rodzice sa tacy sami, wiec nie zmieniamy aktualnego osobnika,
jednak nalezy to potraktowac jako kolejna iteracje, w przeciwnym wypadku jesli populacja utracila swoja roznorodnosc mozemy dojsc do
nieskonczonej petli, gdyz nie mozna znalezc roznych od siebie rodzicow.
Licznik ten umiescilem w tej klasie, gdyz jest bezposrednio powiazany z logika wyszukiwania, czyli zakonczeniem iteracji
*/