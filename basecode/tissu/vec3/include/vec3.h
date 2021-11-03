#ifndef _VEC3_
#define _VEC3_

#ifdef _VEC3_C_
#define VEC3_API __declspec(dllexport)
#else
#define VEC3_API __declspec(dllimport)
#endif

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/*!
	\file vec3.h
	\brief Bibliotheque manipulation vecteurs.
	Bibliotheque comprenant plusieurs fonctions de calculs de vecteurs.
*/

/*!
	Union vec3 contenant ses coordonees.
*/
typedef union
{
	float data[3]; /*!< Tableau des coordonnes de vec3. */
	struct
	{
		float x; /*!< coordonne x de vec3 */
		float y; /*!< coordonne y de vec3 */
		float z; /*!< coordonne z de vec3 */
	};
}vec3;

/*! \brief Addition vecteurs.
Additionne deux vecteurs.
\param[in] a vecteur a
\param[in] b vecteur b
\return c le vecteur additionne
*/
VEC3_API vec3 add3(vec3 a, vec3 b);

/*! \brief soustraction vecteurs.
Soustrait deux vecteurs.
\param[in] a vecteur a
\param[in] b vecteur b
\return c le vecteur différence
*/
VEC3_API vec3 sub3(vec3 a, vec3 b);

/*! \brief multiplication vecteurs.
multiplie deux vecteurs.
\param[in] a vecteur a.
\param[in] b float b.
\return c le vecteur multiplie
*/
VEC3_API vec3 mul3(vec3 a, float b);

/*! \brief division vecteurs.
divise deux vecteurs.
\param[in] a vecteur a.
\param[in] b float b.
\return c le vecteur divise
*/
VEC3_API vec3 div3(vec3 a, float b);

/*! \brief norme vecteurs.
 calcul de la norme du vecteur.
\param[in] a vecteur a.
\param[in] b float b.
\return float c norme de a
*/
VEC3_API float norm3(vec3 a);

/*! \brief normalisation vecteurs.
normalise deux vecteurs.
\param[in] a vecteur a.
\param[in] b float b.
\return c la valeur de la norme
*/
VEC3_API vec3 normalize3(vec3 a);

/*! \brief Distance.
Calcul distance entre deux vecteurs a et b.
\param[in] a vecteur a
\param[in] b vecteur b
\return float c distance entre les deux vecteurs
*/
VEC3_API float distance3(vec3 a, vec3 b);

/*! \brief produit scalaire.
Produit scalaire entre deux vecteurs a et b.
\param[in] a vecteur a
\param[in] b vecteur b
\return vecteur c résultat du produit scalaire
*/
VEC3_API float dot3(vec3 a, vec3 b);

/*! \brief Produit vectoriel.
produit vectoriel entre deux vecteurs a et b.
\param[in] a vecteur a
\param[in] b vecteur b
\return vecteur c resultat du produit vectoriel
*/
VEC3_API vec3 cross3(vec3 a, vec3 b);

/*! \brief Reflexion vecteur.
Réfléchit le vecteur a par rapport a la normale en b.
\param[in] a vecteur a
\param[in] b vecteur b
\return vecteur c reflexion du vecteur a
*/
VEC3_API vec3 reflect3(vec3 a, vec3 b);

/*! \brief Initialisation vecteur.
Initialiser coordonnees x, y, z du vecteur avec respectivement a, b, c en parametres.
\param[in] a float a
\param[in] b float b
\param[in] c float c
\return vecteur d cree avec (a,b,c)=>(x, y, z)
*/
VEC3_API vec3 set3(float a, float b, float c);

/*! \brief Copie vecteur.
Copie x, y, z du vecteur a et cree un vecteur b avec ces memes parametres.
\param[in] a vecteur a
\return vecteur b copie de a
*/
VEC3_API vec3 copy3(vec3 a);

#endif


