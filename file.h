#ifndef _FILE_H
#define _FILE_H




#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
struct dimension
        {
	  int  largeur;
	  int  longueur;
	  int  map_larg;
	  int  map_long;
	  
         } t_dim;

struct node //neuron (node) struct
{
  double act; //euc. dist.
  char *etiq;
  double *w; //weight (memory) vector
};

typedef struct vec
	{
        double *arr;
        char *name;
        double norm;
	}t_vec;

t_vec * array_vec;

typedef struct node t_node;
struct net
{
  int nhd_r;  // neighbourhood radius
  t_node **map;
  double *captors; // current data vector
  double alpha; // learning coeficient
  char *etiq;
} Net;

struct bmu {
	double act; // euclidian distance
	int r;
	int c;
};
typedef struct bmu t_bmu;


////////////////////////////
double *aver,*min,*max , *bound;
///////////////////////////////////
extern void     init_n_conf();
extern  void    initialize_var();
extern void     alloc_vec(int taille );
extern void 	Lecture_data();

	// denorm_array_vec(150);
extern void     moyenne_vec(int a );
extern double * min_vec(double b);
extern double * max_vec(double b );
extern double * bounded(double * aa , double * bb);
extern void     init_shuffle(int a );
    //create neuron map with random neuron
extern void 	create_neuron_map();
extern void 	print_map();
extern void     training();

extern void     print_map();
#ifdef __cplusplus
}
#endif

#endif
