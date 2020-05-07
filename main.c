#include "file.h"
//#include "globals.h"


int main( void )
{
    initialize_var();
    alloc_vec(150);
    Lecture_data();
    moyenne_vec(150);
    min=     min_vec(0.005); 
    max =     max_vec(0.005);
    bound=  bounded(max , min);
    init_shuffle(150);
    create_neuron_map();
    printf("Affichage de la carte :\n");
    print_map();
    printf("\n");
    Net.nhd_r=5;
    Net.alpha=0;
    training();
    printf("****Resultat****:\n");
    print_map();
    free(aver);
    free(min);
    free(max);

	return 0;
}


