<?php 

function construire_form($tab_com, $tab_cli, $tab_prod, $message=""){
    
?>



<form action="main.php" method="post">
    <!-- Partie commande -->
	<div id="comForm">
		<label for="fNCOM">Commande N° &nbsp;:</label>
		<input type="text" name="fNCOM" value="<?php echo $tab_com[0]['NCOM']?>" id="fNCOM" />
		<p id="date">
			Date : <?php echo $tab_com[0]['DATE'] ?> 
		</p>
	</div>
	<!-- FIN comForm -->

	<div id="cliForm">	    
	    <!-- Partie client -->
		<label for="fNCLI">Numéro client&nbsp;&nbsp; :</label>
		<input type="text" name="fNCLI" value="<?php echo $tab_cli[0]['NCLI']?>" id="fNCLI" />
		<br />
		<br />
		<?php
        if ($message){
            echo "<p id=\"message\">$message</p>";
        }else{
        ?>
		
		<p>
			Nom&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; : &nbsp;<?php echo $tab_cli[0]['NOM']?>
		</p>
		<p>
			Adresse&nbsp; : &nbsp;<?php echo $tab_cli[0]['ADRESSE']?>
		</p>
		<p>
			Localité&nbsp; : &nbsp;<?php echo $tab_cli[0]['LOCALITE']?>
		</p>
		<?php
        }
        ?>

	</div>
	
	<!-- FIN cliForm -->

<!-- Partie detail de la commande -->
	<div id="prodForm">

		<table id="t01">
			<tr>
				<th>N° PRODUIT</th>
				<th>LIBELLE PRODUIT</th>
				<th>PRIX</th>
				<th>QUANTITE</th>
				<th>SOUS-TOTAL</th>
			</tr>
			<?php
			for ($ind = 0; $ind < count($tab_prod); $ind++){
			    echo "<tr>";
			    
			    foreach ($tab_prod[$ind] as $key => $value) {
			        echo "<td>$value </td>";		
				}			    
			    echo "</tr>";
			}
			 
			?>			
			
			<tr>
				<td id="totCom" colspan="4" >TOTAL COMMANDE</td>
				<td class="caseJaune"><?php echo $tab_com[0]['TOTCOM'] ?></td>
			</tr>
		</table>

	</div>
	
	<!-- FIN prodForm -->

	<input id="bouton_envoi" type="submit" name="ok" value="Envoi" />
</form>

<?php
}
?>