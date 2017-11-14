
/* Interaction avec l'utilisateur */

/* -------------------------------------------------------------------
 * CodeCommande   : le type [SIMULQLL, ANALYSEQLL, FIN]
 * -------------------------------------------------------------------
*/

typedef enum {SIMULQLL, ANALYSEQLL, FIN}     CodeCommande ;

void SaisirCommande (CodeCommande *);
