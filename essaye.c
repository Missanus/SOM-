#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "file.h"



 void initialize_var()
{
     t_dim.largeur=4;
     t_dim.longueur=150;
     t_dim.map_larg=9;
     t_dim.map_long=7;
}

int Bmu_size=1;
t_bmu *Bmu = NULL;

/// Fonction aléatoire pour générer des valeurs aléatoires comprisent entre 0 et 1 
double _random(){
    double number = 0 ;
    srand(time(NULL));
    number=(double) rand()/RAND_MAX;
    return number ;
}
/// renvoie le carré d'un nombre
double CARRE(double X){
  return X*X ;
}		    


void alloc_vec(int taille)
{
    int i ;
    array_vec = NULL;
    array_vec = malloc(taille * sizeof(t_vec));
    if( array_vec == NULL) // si l'alloc  aéchoué 
      {
	exit(0); //  on arrete iméd
      }else 
      
    for(i=0;i<taille;i++)
    {
       array_vec[i].name= malloc(18 * sizeof(char));
       array_vec[i].arr=  malloc( 4 * sizeof(double));
       
    }
}
    



double *  moyenne ;
void moyenne_vec(int taille )
{
   // moyenne = NULL;
  moyenne = malloc( 4 * sizeof( double));
  int i,j;
  for(j =0; j<4; j++){
      for(i=0 ; i< taille; i++){
            moyenne[j] += array_vec[i].arr[j];
            moyenne[j]/=taille;
	    // printf("%f \n", moyenne[j] ); 
    }
   }
}

double * min;
double*  min_vec(double val)
{
    min = NULL;
    min = malloc(4 * sizeof(double));
    int i;
    for(i = 0;i<4 ;i++)
      {
    min[i] = moyenne[i] - val;
    }
return min ;
}

double * max ;
double * max_vec(double val)
{
   
    max = NULL;
    max = malloc(4 * sizeof(double));
    int i;
    for(i=0 ;i<4 ;i++){
        max[i] = moyenne[i] + val;
}
return max ;
}

void norm_array_vec(int index)
{   
	double somme=0.0;
    int i;
    for(i=0; i<4;i++)
      
    somme = somme +  CARRE(array_vec[index].arr[i]);
    array_vec[index].norm = sqrt(somme);
   //printf("%f \n", array_vec[index].norm);
      
}



int * vec_index;
void init_shuffle(int n)
{  
  int i, temp, index;
vec_index = NULL;
 vec_index = malloc (n * sizeof(int));
  
  for(i=0;i<n;i++)
    {
   vec_index[i]=i; // initialser le tableau 
    }
    srand(time(NULL));
    for(i=0;i<n;i++)
      {
            temp = rand() % n;
            index= vec_index[i];
            vec_index[i]=vec_index[temp];
            vec_index[temp]=index;
       }
}

double euc_distance(double t1[], double t2[], int n)
{       int i ; 
	double somme=0.0;
	for(i=0;i<n;i++){
	       somme = somme +(CARRE(t1[i] - t2[i]));
	}
	return sqrt(somme);
}





void update(t_bmu* b_mu)
{
    int nr = Net.nhd_r;
    int k,i,j,x1,x2,y1,y2;
      while ( nr >=0)
    
    {
        if(b_mu->r - nr<0)
            x1 = 0;
        else
            x1=b_mu->r - nr;
//////////////////////////////////////////
        if(b_mu->c - nr<0)
            y1 = 0;
        else
            y1=b_mu->c - nr;
///////////////////////////////////////////
        if(b_mu->r + nr > t_dim.map_long - 1)
            x2 = t_dim.map_long- 1 ;
        else
            x2=b_mu->r+nr;
/////////////////////////////////////////////
        if(b_mu->c + nr >  t_dim.map_larg - 1)
            y2=t_dim.map_larg - 1;
        else
            y2=b_mu->c + nr;
			
        for(i=x1;i<=x2;i++)
            for(j=y1;j<=y2;j++)
            {             

   for(k=0;k<t_dim.largeur;k++)
                    {
           Net.map[i][j].w[k] +=  Net.alpha*(Net.captors[k]-Net.map[i][j].w[k]);
            }
                                   
             }
nr-- ;
 }
}

char * token ; 
void Lecture_data()

{
    FILE * Mon_file;
     char * chaine =malloc(600 * sizeof(char));
      Mon_file=fopen("iris.data","r");
       const char s[1] =",";
    int i,j;
    char *f1 = "Iris-setosa";
    char *f2 = "Iris-versicolor";
    char *f3 = "Iris-virginica";
	for(i=0 ;i<  t_dim.longueur; i++)
	{
        fscanf(Mon_file,"%s",chaine);
     
        token =strtok(chaine,s);
     
        for(j=0;j< 4 ;j++)
            {
                array_vec[i].arr[j]=atof(token);
                token = strtok(NULL,",");   
            }       
 
        
            if (strcmp(token, f1) == 0)
 strcpy(array_vec[i].name,"A");
        else if(strcmp(token,f2)==0)
            strcpy(array_vec[i].name,"B");
       else if (strcmp(token,f3)==0)
            strcpy(array_vec[i].name,"C");

norm_array_vec(i);
	}

	fclose(Mon_file);
    free(chaine);
}

double * bound ;
double * bounded(double * mx , double * mn)
 {
   double val= 0 ;
   int i  = 0;
   bound = malloc(4 * sizeof(double));
   for ( i =0; i< 4; i++)
     {
       val = _random();
       bound[i] = val * (mx[i] - mn[i]) + mn[i];
     } 
   double norme=0.;

    for(i=0;i<4;i++)
    {
        norme+=CARRE(bound[i]);
	
    }
    return bound ;
 }


void create_neuron_map()
{
    int i,j;
    Net.map=malloc(t_dim.map_long*sizeof(t_node * ));
	for(i=0;i<t_dim.map_long;i++)
	{
		Net.map[i]=malloc(t_dim.map_larg *sizeof(t_node));
	}
	for(i=0;i<t_dim.map_long;i++)
	{
		for (j=0;j<t_dim.map_larg;j++)
		{

            Net.map[i][j].w=(double*)malloc(sizeof(double) *t_dim.largeur);
			Net.map[i][j].w=bounded(max , min);
			Net.map[i][j].etiq=malloc(20 * sizeof(char));
			strcpy(Net.map[i][j].etiq, ".");
		}
	}
}
///////////////////

void print_map()
{
    int i,j;
    for(i=0;i<t_dim.map_long;i++)
    {
        for(j=0;j<t_dim.map_larg;j++)
            {
                printf("%s ",Net.map[i][j].etiq);
            }
        printf("\n");
    }
}

void calc_alpha(int it_n, int tot_it)
{
  double a_initial = 0.5 ;

	Net.alpha = a_initial * (1 - ((double)it_n/(double)tot_it));
}

void training()
{
 int i,j,p,u,it;
  int nb_it=30000;
  int ftrain=nb_it/5;
  int train = 3 ;
  double min_d,dist;
 Bmu = malloc( sizeof (t_bmu));
    for(p=0; p<train ; p++)
    {
        int cur_n_it;
             cur_n_it=ftrain;

        for(it=0; it<cur_n_it; it++)
        {
            calc_alpha(it,cur_n_it);
            init_shuffle(  t_dim.longueur);
	     for(u=0;u<t_dim.longueur;u++)
            {

              Net.captors=array_vec[vec_index[u]].arr;
              min_d=1000.;
              for(i=0;i<t_dim.map_long;i++)
              {
                for(j=0;j<t_dim.map_larg;j++)
                    {
                        dist=euc_distance(Net.captors,Net.map[i][j].w,t_dim.largeur);
                        Net.map[i][j].act=dist;
                        if(dist<min_d)
                        {
                            min_d=dist;
                         
                            Bmu[0].act=dist;
                            Bmu[0].r=i;
                            Bmu[0].c=j;
                        }
                        else if(dist==min_d)
                        {

                            Bmu_size = 2;
			    Bmu[Bmu_size-1].act=dist;
                            Bmu[Bmu_size-1].r=i;
                            Bmu[Bmu_size-1].c=j;

                        }
                     }
                }

                    strcpy(Net.map[Bmu[0].r][Bmu[0].c].etiq, array_vec[vec_index[u]].name);
                update(Bmu);
            }
        }
    }
}


