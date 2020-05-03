<?php
function createTable($donnees, $entete = FALSE, $style = FALSE) {
    /*
     * Description : la fonction crée un tableau avec  éventuellement 
     * un entête et des styles pour la mise en forme. 
     * Entrées : les données pour remplir le tableau, la variable $donnee est un tableau
     * Sorties : affichage du tableau
     */

    $id = ($style) ? "id=\"$style\"" : "";

    echo "<table " . $id . ">\n";

    if ($entete) {
        echo "<thead>\n
            <tr>\n";
        foreach ($entete as $value) {
            echo "<th>$value</th>\n";
        }
        echo "  </tr>\n
            </thead>\n";
    }

    echo "<tbody>\n";

    for ($i = 1; $i < count($donnees); $i++) {
        echo "<tr>\n";
        for ($j = 0; $j < count($donnees[$i]); $j++) {
            echo "  <td>" . $donnees[$i][$j] . "</td>\n";
        }
        echo "</tr>\n";
    }
    echo "</tbody>\n
 
        </table>\n";
}

function vers_formulaire($valeur) {
 
  // affichage dans un formulaire
 
  // encoder tous les caractères HTML spéciaux
  //  - ENT_QUOTES : dont " et '
  //return htmlentities($valeur,ENT_QUOTES|ENT_XHTML,'UTF-8');
  return htmlentities($valeur,ENT_QUOTES|ENT_HTML5, 'ISO8859-1'); 
}

function vers_page($valeur) { 
  return nl2br(htmlentities($valeur,ENT_QUOTES|ENT_HTML5, 'ISO8859-1')); 
} 

function vers_base($valeur) { 
  // Le seul caractère qui pose vraiment problème est l’apostrophe (’) ; 
  // c’est donc le seul qui est échappé par cette fonction. 
  // Une solution valable pour toutes les bases consiste à 
  // l’échapper par lui-même => remplacement de ’ par ’’. 
  return str_replace("’","’’",$valeur); 
} 

function afficher_tableau($tableau,$titre="",$niveau=0) {

  // Paramètres
  //    - $tableau = tableau dont il faut afficher le contenu
  //    - $titre = titre à afficher au dessus du contenu
  //    - $niveau = niveau d'affichage

  // s'il y a un titre, l'afficher
  if ($titre != "") {
    echo "<P><B>$titre</B><BR>\n";
  }

  // tester s'il y des données
  if (isset($tableau)) { // il y a des données

    // parcourir le tableau passé en paramètre
    reset ($tableau);
    while (list ($cle, $valeur) = each ($tableau)) {

      // afficher la clé (avec indentation fonction 
      // du niveau)
      echo
        str_pad("",12*$niveau, "&nbsp;").
            htmlentities($cle,ENT_QUOTES|ENT_HTML5,'ISO8859-1')." = ";

      // afficher la valeur
      if (is_array($valeur)) { // c'est un tableau ...

        // mettre une balise <BR>
        echo "<BR>";
        // et appeler récursivement afficher_tableau pour 
        // afficher le tableau en question (sans titre et au
        // niveau supérieur pour l'indentation)
        afficher_tableau($valeur,"",$niveau+1);

      } else { // c'est une valeur scalaire

        // afficher la valeur
        echo htmlentities($valeur,ENT_QUOTES|ENT_HTML5,'ISO8859-1')."<BR>";

      }
      
    }

  } else { // pas de données

    // mettre une simple balise <BR>
    echo "<BR>\n";

  }

}
?>