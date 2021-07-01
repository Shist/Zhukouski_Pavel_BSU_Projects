-- MySQL dump 10.13  Distrib 8.0.23, for Win64 (x86_64)
--
-- Host: localhost    Database: projects_competition
-- ------------------------------------------------------
-- Server version	8.0.23

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `developers`
--

DROP TABLE IF EXISTS `developers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `developers` (
  `devID` int NOT NULL AUTO_INCREMENT,
  `devFIO` varchar(256) NOT NULL,
  `devBirthDate` date NOT NULL,
  `devSolvedPrCount` int unsigned NOT NULL,
  `devRating` float unsigned DEFAULT '0',
  `devDescript` longtext,
  PRIMARY KEY (`devID`),
  UNIQUE KEY `devID_UNIQUE` (`devID`),
  UNIQUE KEY `devFIO_UNIQUE` (`devFIO`)
) ENGINE=InnoDB AUTO_INCREMENT=59 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `developers`
--

LOCK TABLES `developers` WRITE;
/*!40000 ALTER TABLE `developers` DISABLE KEYS */;
INSERT INTO `developers` VALUES (1,'Zhukouskiy Pavel Sergeevich','2001-04-03',242,7.8,'DB owner'),(2,'Mikhailova Fatima Daniilovna','1971-01-17',178,5.6,'Old developer'),(3,'Kudryavtseva Lilia Ivanovna','1973-01-04',214,6.1,'No additional information'),(4,'Lobanova Valeria Demidovna','1973-10-19',87,4.3,'No additional information'),(5,'Titov Daniil Timofeevich','1974-04-15',314,7.9,'No additional information'),(6,'Potapova Anna Germanovna','1975-11-25',262,5.6,'No additional information'),(7,'Korneev Semyon Andreevich','1981-06-22',245,5.5,'No additional information'),(8,'Kirill Sidorov','1984-08-16',440,8.9,'The most experienced developer'),(9,'Rybakova Vera Ivanovna','1984-12-10',54,2.4,'No additional information'),(10,'Konovalova Yulia Markovna','1986-01-24',143,5.4,'No additional information'),(12,'Golubeva Anna Alievna','1990-03-31',98,7.2,'No additional information'),(13,'Efremov Kirill Dmitrievich','1989-03-30',179,7.7,'No additional information'),(14,'Sokolova Alexandra Daniilovna','1986-11-10',97,4.3,'No additional information'),(15,'Avdeeva Taisia Artyomovna','1993-11-19',76,3.7,'No additional information'),(16,'Kurochkina Sofia Davidovna','1986-11-28',78,3.6,'No additional information'),(17,'Titova Daria Petrovna','1997-08-20',82,3.8,'No additional information'),(18,'Fomichev Mikhail Davidovich','1994-06-11',155,5.8,'No additional information'),(19,'Sergeev Mark Bogdanovich','1997-03-12',169,6.2,'No additional information'),(20,'Nikulin Ivan Olegovich','2003-04-30',191,7.8,'Young developer'),(21,'Vlasov Timofey Leonidovich ','1992-11-25',287,9.4,'No additional information'),(22,'Bykova Taisiya Danilovna','2001-10-05',105,3.5,'No additional information'),(23,'Pavlova Amira Georgievna','1973-08-25',134,5.7,'No additional information'),(24,'Chebotareva Amelia Ruslanovna','1990-05-02',276,8.2,'No additional information'),(25,'Kuzina Maria Artyomovna','1974-04-28',396,9.4,'No additional information'),(26,'Chernykh Pavel Konstantinovich','1996-01-12',302,6.7,'No additional information'),(27,'Fadeeva Ekaterina Alexandrovna','1974-04-10',201,3.5,'No additional information'),(28,'Mironov Timur Matveevich','2001-03-27',267,8.2,'No additional information'),(29,'Nesterova Maria Vladimirovna','1982-08-29',143,4.7,'No additional information'),(30,'Shapovalova Ekaterina Arsentievna','1985-11-07',87,2.8,'No additional information'),(31,'Kosareva Ekaterina Andreevna ','1981-08-05',168,9.1,'No additional information'),(33,'Mikhailova Stefania Daniilovna','1981-06-20',147,6.3,'No additional information'),(34,'Korovin Vasily Anatolievich','1986-01-17',127,6.8,'No additional information'),(35,'Vasilyeva Maria Dmitrievna','1980-04-24',174,7.5,'No additional information'),(36,'Popova Ulyana Sergeevna','1990-08-01',157,6.9,'No additional information'),(37,'Nikiforov Leonid Dmitrievich','1979-07-30',195,7.6,'No additional information'),(38,'Ermilov Egor Vitalievich','1986-03-08',126,4.2,'No additional information'),(39,'Petrova Alina Alexandrovna','1978-12-16',119,3.8,'No additional information'),(40,'Vinogradov Mikhail Andreevich','2001-11-08',289,9,'No additional information'),(41,'Andrianov Mark Timofeevich ','1976-11-03',265,7.3,'No additional information'),(42,'Maslova Victoria Petrovna','2000-02-27',214,5.7,'No additional information'),(43,'Selivanova Yulia Yaroslavovna','1995-08-15',202,5,'No additional information'),(45,'Novikov Irakli Timurovich','1987-05-12',167,6.7,'One of new developers'),(46,'Nosov Apollon Vadimovich','1984-06-24',187,8.2,'One of new developers'),(47,'Matveeva Neva Feliksovna','1981-09-07',191,6.8,'One of new developers'),(48,'Abramova Genevieva Evseevna','2000-01-12',267,7.8,'One of new developers'),(49,'Zaitsev Ruben Yakovlevich','2001-03-27',243,7.2,'One of new developers'),(50,'Vishnyakov Samuil Kimovich','1989-08-14',314,8.6,'One of new developers'),(51,'Makarova Mila Yakunovna','1985-10-19',298,8,'One of new developers'),(52,'Kopylova Lali Alexandrovna','1994-11-13',286,7.9,'One of new developers'),(54,'Guryeva Natalia Ilyaovna ','1999-11-16',167,6.3,'One of new developers');
/*!40000 ALTER TABLE `developers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `projects`
--

DROP TABLE IF EXISTS `projects`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `projects` (
  `prID` int NOT NULL AUTO_INCREMENT,
  `prName` varchar(256) NOT NULL,
  `prLeaderID` int DEFAULT NULL,
  `prCreationDate` date NOT NULL,
  `prDevsAmount` int unsigned NOT NULL,
  `prInvests` float unsigned DEFAULT '0',
  `prDescript` longtext,
  `prOldLeaderFIO` varchar(256) NOT NULL,
  PRIMARY KEY (`prID`),
  UNIQUE KEY `prID_UNIQUE` (`prID`),
  UNIQUE KEY `prName_UNIQUE` (`prName`),
  KEY `devID_idx` (`prLeaderID`),
  CONSTRAINT `for_devID` FOREIGN KEY (`prLeaderID`) REFERENCES `developers` (`devID`) ON DELETE SET NULL ON UPDATE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `projects`
--

LOCK TABLES `projects` WRITE;
/*!40000 ALTER TABLE `projects` DISABLE KEYS */;
INSERT INTO `projects` VALUES (1,'Venom Rare',1,'2019-09-29',7,750.75,'The first project in general','Zhukouskiy Pavel Sergeevich'),(2,'Massive Crossbow',4,'2019-11-04',5,460.7,'No additional information','Lobanova Valeria Demidovna'),(3,'Elastic Omega',6,'2019-11-19',5,285.9,'No additional information','Potapova Anna Germanovna'),(4,'Rebel Unique Flea',9,'2019-11-20',4,140.3,'No additional information','Rybakova Vera Ivanovna'),(5,'Strong Tea',14,'2019-12-18',4,168.2,'Project about species of tea','Sokolova Alexandra Daniilovna'),(6,'Empty Permanent Burst',21,'2020-03-08',5,192.1,'No additional information','Vlasov Timofey Leonidovich '),(7,'White Rubber',24,'2020-04-28',3,253.65,'No additional information','Chebotareva Amelia Ruslanovna'),(8,'Subtle Pineapple',29,'2020-09-11',5,190.15,'No additional information','Nesterova Maria Vladimirovna'),(9,'Hot Beacon Flannel',NULL,'2020-09-14',6,392.4,'Project about beacons','Rumyantsev Alexey Danilovich'),(10,'Bitter Remote Leather',34,'2020-09-15',7,650.8,'No additional information','Korovin Vasily Anatolievich'),(11,'Tungsten Rich',38,'2020-09-20',4,570.65,'No additional information','Ermilov Egor Vitalievich');
/*!40000 ALTER TABLE `projects` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-05-22 23:52:45
