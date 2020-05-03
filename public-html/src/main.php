<?php
        //fichiers inclusions (bibliothèques)
        require_once '../include/fonctions.inc';
        require_once '../include/form.inc';
        require_once '../include/srvMySql.inc';
        
        //Traitement du formulaire
        if (!empty($_POST) and !empty($_POST['fNCOM']) and !empty($_POST['fNCLI'])) {            

            //Connexion au SGBD et à la base de données
            if (!($connexion_bdd = connexion(SRV_BDD, USER_BDD, PWD_BDD, BDD, $erreur))) {
                exit("$erreur[0] - $erreur[1]");
            }
            
            //Vérifier qu'il existe une commande fNCOM pour le client fNCLI     
            if (!verif_ncom_ncli($connexion_bdd, REQ_VERIF, $_POST['fNCOM'], $_POST['fNCLI'])){
             $message = " ERREUR : Vérifier les numéros de client et de commande";
            }else{
                // on récupére les résultats des trois requêtes dans trois tableaux de tableaux associatifs
                list($tab_cli, $tab_com, $tab_prod) = bddTOtab($connexion_bdd,REQ_CLI, REQ_COM, REQ_PROD);            
            }//FIN du else

        } // FIN if empty
        ?>


<!DOCTYPE html>
<html lang="en">
	<head>
		<meta charset="utf-8">
		<title>Bon de commande</title>
		<link rel="stylesheet" href="../css/styles.css">
	</head>

	<body> 		
		<div id="wrapper">
			<div id="main_content">
				<?php
                construire_form($tab_com, $tab_cli, $tab_prod, $message);                
				?>
			</div>
			<!-- FIN main_content -->
		</div>
		<!-- FIN wrapper -->

	</body>
</html>

