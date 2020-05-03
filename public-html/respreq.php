<!DOCTYPE HTML>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=encoding">
<title>Résultat de requête</title>
</head>
<body>

<?php
$qry = stripslashes ( $_POST ['txreq'] );
echo $qry . "\n<br /><br />\n";
include 'defdb.php';

$link = mysqli_connect($host, $user, $mp, $db ) or exit ( 'Echec connexion' );
mysqli_select_db($link, $db) or exit ( 'Echec sélection base' );
$res = mysqli_query($link, $qry) or exit ( 'Echec requête' );
$nr = mysqli_num_rows($res);
if ($nr == NULL) {
    echo 'Requête effectuée';
} else {
    echo '<table border="1"><thead><tr>' . "\n";
    for($k = 0; $k < mysqli_num_fields($res); $k ++) {
        echo '<th>' . mysqli_fetch_field_direct($res, $k)->name . '</th>';
    }
    echo "</tr></thead>\n<tbody>";
    for($i = 0; $i < $nr; $i ++) {
        echo "\n<tr>";
        $ligne = mysqli_fetch_row($res);
        for($k = 0; $k < mysqli_num_fields($res); $k ++) {
            echo '<td>' . $ligne [$k] . '</td>';
        }
        echo '</tr>';
    }
    echo "\n</tbody></table>";
}
mysqli_close($link);
?>
</body>
</html>
