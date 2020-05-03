-- MySQL dump 10.13  Distrib 5.5.41, for debian-linux-gnu (x86_64)
--
-- Host: srvmysql    Database: Bd_rpi
-- ------------------------------------------------------
-- Server version	5.5.41-0+wheezy1-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `CLIENT`
--
CREATE DATABASE Bd_rpi;
USE Bd_rpi;
DROP TABLE IF EXISTS `CLIENT`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `CLIENT` (
  `NCLI` char(10) NOT NULL,
  `NOM` char(32) NOT NULL,
  `ADRESSE` char(60) NOT NULL,
  `LOCALITE` char(30) NOT NULL,
  `CAT` enum('A1','A2','B1','B2','C1','C2') DEFAULT NULL,
  `COMPTE` decimal(9,2) NOT NULL,
  PRIMARY KEY (`NCLI`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CLIENT`
--

LOCK TABLES `CLIENT` WRITE;
/*!40000 ALTER TABLE `CLIENT` DISABLE KEYS */;
INSERT INTO `CLIENT` VALUES ('B062','GOFFIN','72, r. de la Gare','Namur','B2',-3200.00),('B112','HANSENNE','23, a. Dumont','Poitiers','C1',1250.00),('B332','MONTI','112, r. Neuve','Geneve','B2',0.00),('B512','GILLET','14, r. de l\'Ete','Toulouse','B1',-8700.00),('C003','AVRON','8, ch. de la Cure','Toulouse','B1',-1700.00),('C123','MERCIER','25, r. Lemaitre','Namur','C1',-2300.00),('C400','FERARD','65, r. du Tertre','Poitiers','B2',350.00),('D063','MERCIER','201, bvd du Nord','Toulouse',NULL,-2250.00),('F010','TOUSSAINT','5, r. Godefroid','Poitiers','C1',0.00),('F011','PONCELET','17, Clos des Erables','Toulouse','B2',0.00),('F400','JACOB','78, ch. du Moulin','Bruxelles','C2',0.00),('K111','VANBIST','180, r. Florimont','Lille','B1',720.00),('K729','NEUMAN','40, r. Bransart','Toulouse','A1',0.00),('L422','FRANCK','60, r. de Wepion','Namur','C1',0.00),('S127','VANDERKA','3, av. des Roses','Namur','C1',-4580.00),('S712','GUILLAUME','14a, ch. des Roses','Paris','B1',0.00);
/*!40000 ALTER TABLE `CLIENT` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `COMMANDE`
--

DROP TABLE IF EXISTS `COMMANDE`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `COMMANDE` (
  `NCOM` char(12) NOT NULL,
  `NCLI` char(10) NOT NULL,
  `DATECOM` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`NCOM`),
  KEY `fk_COMMANDE_CLIENT` (`NCLI`),
  CONSTRAINT `fk_COMMANDE_CLIENT` FOREIGN KEY (`NCLI`) REFERENCES `CLIENT` (`NCLI`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `COMMANDE`
--

LOCK TABLES `COMMANDE` WRITE;
/*!40000 ALTER TABLE `COMMANDE` DISABLE KEYS */;
INSERT INTO `COMMANDE` VALUES ('30178','K111','2008-12-21 23:00:00'),('30179','C400','2008-12-21 23:00:00'),('30182','S127','2008-12-22 23:00:00'),('30184','C400','2008-12-22 23:00:00'),('30185','F011','2009-12-01 23:00:00'),('30186','C400','2009-01-01 23:00:00'),('30188','B512','2009-01-02 23:00:00');
/*!40000 ALTER TABLE `COMMANDE` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `DETAIL`
--

DROP TABLE IF EXISTS `DETAIL`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `DETAIL` (
  `NCOM` char(12) NOT NULL,
  `NPRO` char(15) NOT NULL,
  `QCOM` decimal(8,0) NOT NULL,
  PRIMARY KEY (`NCOM`,`NPRO`),
  KEY `fk_DETAIL_PRODUIT` (`NPRO`),
  CONSTRAINT `fk_DETAIL_COMMANDE` FOREIGN KEY (`NCOM`) REFERENCES `COMMANDE` (`NCOM`),
  CONSTRAINT `fk_DETAIL_PRODUIT` FOREIGN KEY (`NPRO`) REFERENCES `PRODUIT` (`NPRO`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `DETAIL`
--

LOCK TABLES `DETAIL` WRITE;
/*!40000 ALTER TABLE `DETAIL` DISABLE KEYS */;
INSERT INTO `DETAIL` VALUES ('30178','CS464',25),('30179','CS262',60),('30179','PA60',20),('30182','PA60',30),('30184','CS464',120),('30184','PA45',20),('30185','CS464',260),('30185','PA60',15),('30185','PS222',600),('30186','PA45',3),('30188','CS464',180),('30188','PA45',22),('30188','PA60',70),('30188','PH222',92);
/*!40000 ALTER TABLE `DETAIL` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PRODUIT`
--

DROP TABLE IF EXISTS `PRODUIT`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `PRODUIT` (
  `NPRO` char(15) NOT NULL,
  `LIBELLE` char(60) NOT NULL,
  `PRIX` float NOT NULL,
  `QSTOCK` decimal(6,0) NOT NULL,
  PRIMARY KEY (`NPRO`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PRODUIT`
--

LOCK TABLES `PRODUIT` WRITE;
/*!40000 ALTER TABLE `PRODUIT` DISABLE KEYS */;
INSERT INTO `PRODUIT` VALUES ('CS262','CHEV. SAPIN 200x6x2',75,45),('CS264','CHEV. SAPIN 200x6x4',120,2690),('CS464','CHEV. SAPIN 400x6x4',220,450),('PA45','POINTE ACIER 45 (1K)',105,580),('PA60','POINTE ACIER 60 (1K)',95,134),('PH222','PL. HETRE 200x20x2',230,782),('PS222','PL. SAPIN 200x20x2',185,1220);
/*!40000 ALTER TABLE `PRODUIT` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-04-29 16:04:59
