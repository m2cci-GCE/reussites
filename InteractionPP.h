
/* Interaction avec l'utilisateur */

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULPP, ANALYSEPP, FIN]
 * -------------------------------------------------------------------
*/

typedef enum {SIMULPP, ANALYSEPP, FIN}     CodeCommande ;

void SaisirCommande (CodeCommande *);
