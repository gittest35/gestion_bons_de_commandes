<?php
define(SRV_BDD, "srvmysql");
define(USER_BDD, "root");
define(PWD_BDD, "root");
define(BDD, "Bd_rpi");

define(MYSQLI_NUM, 'MYSQLI_NUM');
define(MYSQLI_ASSOC, 'MYSQLI_ASSOC');


//Les requêtes

define(REQ_VERIF, "SELECT CLIENT.NCLI, COMMANDE.NCOM  FROM CLIENT, COMMANDE  
                  WHERE COMMANDE.NCOM = '$_POST[fNCOM]'  
                  AND CLIENT.NCLI = '$_POST[fNCLI]' AND CLIENT.NCLI = COMMANDE.NCLI;");

// Donne la date et le total d'une commande.
define(REQ_COM, "SELECT COMMANDE.NCOM, DATE_FORMAT(DATE(COMMANDE.DATECOM), '%d/%m/%Y') AS DATE, SUM(DETAIL.QCOM*PRODUIT.PRIX) AS 'TOTCOM' 
                    FROM CLIENT, COMMANDE, DETAIL, PRODUIT  
                    WHERE COMMANDE.NCOM = '$_POST[fNCOM]' AND CLIENT.NCLI = '$_POST[fNCLI]' 
                    AND CLIENT.NCLI = COMMANDE.NCLI AND COMMANDE.NCOM = DETAIL.NCOM AND DETAIL.NPRO = PRODUIT.NPRO;");

//Retrouve les informtaions sur un client.                    
define(REQ_CLI, "SELECT NCLI, NOM, ADRESSE, LOCALITE 
                        FROM CLIENT
                        WHERE NCLI = '$_POST[fNCLI]';");

//Donne les détails d'une commande                
define(REQ_PROD, "SELECT PRODUIT.NPRO, PRODUIT.LIBELLE, PRODUIT.PRIX,
                         DETAIL.QCOM,
                         DETAIL.QCOM*PRODUIT.PRIX AS 'SOUSTOT' 
                         FROM COMMANDE, DETAIL, PRODUIT  
                         WHERE COMMANDE.NCOM = '$_POST[fNCOM]' AND COMMANDE.NCOM = DETAIL.NCOM AND DETAIL.NPRO = PRODUIT.NPRO;");                                            

function connexion($srv_bdd, $user_bdd, $pwd_bdd, $bdd, &$erreur=array(0,'')){
    /*
     * Description : Connexion au SGBD et à la base de données $bdd.
     *  Entrées : 
     *              - $srv_bdd : Serveur de base de données
     *              - $user_bdd : Identifiant de l'utilisateur ayant droit sur la base
     *              - $pwd_bdd : Mot de passe de l'utilisateur
     *              - $bdd : La base de donnée concernée
     *              - &$erreur : tableau pour récupérer le numéro d'erreur (o par défaut 
     *                              et le message d'erreur (vide par défaut)
     *  Sorties :
     *              - $con : L'identiifant de connexion si pas d'erreurs
     *              - False sinon
     */
 
    //Connexion au SGBD
    $ok = ($con = mysqli_connect($srv_bdd, $user_bdd, $pwd_bdd));
 
    //Si connexion au SGBD ok, tentative de connexion à la base
    if ($ok) $ok = mysqli_select_db($con, $bdd);
 
    if (! $ok) { // erreur quelque part
        // Récupérer les informations  sur l’erreur.
        if (! $con) { // erreur de connexion
            $erreur = [mysqli_connect_errno(), mysqli_connect_error()];
        } else { // autre erreur
            $erreur = [mysqli_errno($con),mysqli_error($con)];
        }
    }
 
    // Retourner l'identifiant de la connexion $con ou FALSE en cas d’erreur.
    return ($ok)?$con:FALSE;
}

 
function komo_fetch_all($result, $typeTab){
    /* Description : récupére le résultat d'une requête dans un tableau à deux dimensions : 
     *      Avec $typeTab = MYSQLI_ASSOC : [[identifiant => 1, libelle => Abricots, prix => 35.5], [], [],...]
     *      Avec $typeTab = MYSQLI_NUM : [[0 => 1, 1 => Abricots, 2 => 35.5], [], [],...]   
     * Entrées :
     *          $result : type mysqli_result, objet resultat d'une requête
     *          $typeTab : 
     *                      MYSQLI_NUM : Tableau à indices entiers
     *                      MYSQLI_ASSOC : Tableau associatif
     * Sorties : 
     *          Soit un tableau à deux dimensions à indice entier.  
     * */
  //$tab = array();
  $data = [];
 
  if ($typeTab == MYSQLI_NUM) $fetch  = 'mysqli_fetch_row';
  elseif ($typeTab == MYSQLI_ASSOC) $fetch  = 'mysqli_fetch_assoc';
  else return false;
 
   while (($ligne = $fetch($result)) != null){
    //array_push($tab,$ligne);     
    $data[] = $ligne;   
   }
   return $data;
}

function komo_mysql_db_lire_lignes_dans_tableau_avec_erreur($connexion, $requête, &$erreur=array(0,'')) {
 
  // La variable $ok est utilisée pour savoir
  // si tout se passe bien.
 
  // Exécuter la requête et tester le résultat pour
  // affecter la variable $ok.
 
    $ok = ( ($résultat = mysqli_query($connexion,$requête)) != FALSE );
 
  // Initialiser le tableau.
  $tableau = array();
 
  // Lire les lignes dans le tableau.
  if ($ok) {
    $tableau = komo_fetch_all($résultat,MYSQLI_ASSOC);
  }else { // erreur exécution de la requête
        $erreur = [ 
                mysqli_errno ($connexion), mysqli_error ($connexion) 
        ];
    }
 
  // Retourner $tableau ou FALSE en cas d’erreur
  return ($ok)?$tableau:FALSE;
}



function komo_mysql_db_lire_ligne_avec_erreur($connexion, $requête, &$erreur=array(0,'')) {
 
    /*
     * La fonction retourne un tableau associatif $ligne : 
     *                      cle = nom de la colonne => valeur = valeur de l'attribut
     * Entrées : 
     *              - $connexion : Identifiant de connexion au SGBD
     *              - $requête : objet de type mysqli_result
     *              - &$erreur : tableau pour récupérer le numéro d'erreur (o par défaut 
     *                              et le message d'erreur (vide par défaut)
     *  Sorties : 
     *              - $ligne : tableau associatif (nom de la colonne => Valeur de l'attribut pour la colonne)
     *                         si pas d'erreur.
     *              - False sinon.              
     */
 
    // La variable $ok est utilisée pour savoir
    // si tout se passe bien.
 
    // Exécuter la requête et tester le résultat pour
    // affecter la variable $ok.
    $ok = (($résultat = mysqli_query ( $connexion, $requête )) != FALSE);
 
    if ($ok) { // exécution OK
               // Lire le résultat.
        $ligne = mysqli_fetch_assoc ( $résultat );
    } else { // erreur exécution de la requête
        $erreur = [ 
                mysqli_errno ( $connexion ),
                mysqli_error ( $connexion ) 
        ];
    }
 
    // Retourner $ligne ou FALSE en cas d’erreur.
    return ($ok) ? $ligne : FALSE;
}

function requeter($con, $requete, &$erreur = array(0,'')) {
    $ok = (($résultat = mysqli_query ( $con, $requete )) != FALSE);
    if (! $ok)
        $erreur = [ 
                mysqli_errno ( $con ),
                mysqli_error ( $con ) 
        ];
 
    return ($ok) ? $resultat : FALSE;
}
     
function construire_requete($sql) { 
  // Récupérer le nombre de paramètres. 
  $nombre_param = func_num_args(); 
  // Boucler sur tous les paramètres à partir du deuxième 
  // (le premier contient la requête de base). 
  for($i=1;$i<$nombre_param;$i++) { 
    // Récupérer la valeur du paramètre. 
    $valeur = func_get_arg($i); 
    // Si c’est une chaîne, l’échapper. 
    if (is_string($valeur)) { 
      $valeur = str_replace("’","’’",$valeur); 
    } 
    // Mettre la valeur à son emplacement %n (n = $i). 
    $sql = str_replace("%$i",$valeur,$sql); 
  } 
  // Retourner la requête. 
  return $sql; 
}       


function bddTOtab($connexion_bdd, $req_cli, $req_com, $req_prod){
    /*-------------------------------------------------COMMANDE---------------------------------------*/
            //Récupération de la  ligne résultat de la requête sur la commande
            if (!($tab_com = komo_mysql_db_lire_lignes_dans_tableau_avec_erreur($connexion_bdd, $req_com, $erreur))) {
                exit("$erreur[0] - $erreur[1]");
            }
            /*------------------------------------------------- FIN COMMANDE---------------------------------------*/

            /*-------------------------------------------------CLIENT---------------------------------------*/
            //Récupération de la  ligne résultat de la requête sur le client
            if (!($tab_cli = komo_mysql_db_lire_lignes_dans_tableau_avec_erreur($connexion_bdd, $req_cli, $erreur))) {
                exit("$erreur[0] - $erreur[1]");
            }
            /*-------------------------------------------------FIN CLIENT---------------------------------------*/

            /*-------------------------------------------------PRODUIT---------------------------------------*/
            //Récupération des lignes résultats de la requête sur les details de la commande
            if (!($tab_prod = komo_mysql_db_lire_lignes_dans_tableau_avec_erreur($connexion_bdd, $req_prod, $erreur))) {
                exit("$erreur[0] - $erreur[1]");
            }
            /*-------------------------------------------------FIN PRODUIT---------------------------------------*/
            return array($tab_cli, $tab_com, $tab_prod);
}

function verif_ncom_ncli($connexion_bdd, $req_verif, $ncom, $ncli){
    if (!(komo_mysql_db_lire_lignes_dans_tableau_avec_erreur($connexion_bdd, $req_verif, $erreur))){
     if ($erreur[0]){
      exit("$erreur[0] - $erreur[1]");
     }
     $tab_cli[0]['NCLI'] = $ncli;
     $tab_com[0]['NCOM'] = $ncom;
     return FALSE;
    }else return TRUE;
}
    
?>
