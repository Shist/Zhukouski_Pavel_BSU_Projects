-- MySQL dump 10.13  Distrib 8.0.23, for Win64 (x86_64)
--
-- Host: localhost    Database: library_db
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
-- Table structure for table `authorization`
--

DROP TABLE IF EXISTS `authorization`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `authorization` (
  `login` varchar(64) NOT NULL,
  `password` varchar(64) NOT NULL,
  `type` varchar(64) NOT NULL,
  PRIMARY KEY (`login`),
  UNIQUE KEY `login_UNIQUE` (`login`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `authorization`
--

LOCK TABLES `authorization` WRITE;
/*!40000 ALTER TABLE `authorization` DISABLE KEYS */;
INSERT INTO `authorization` VALUES ('Anthony Perez','1111111','R'),('Arturo Parks','2222222','G'),('Byron Gibbs','3333333','R'),('Heather Brady','4444444','G'),('Marlon Robertson','5555555','G'),('Mary Collier','6666666','R'),('Pavel','7777777','L'),('Steve Alvarez','8888888','R'),('Willie Hanson','9999999','R');
/*!40000 ALTER TABLE `authorization` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `books`
--

DROP TABLE IF EXISTS `books`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `books` (
  `id_books` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL DEFAULT 'MysteryBook',
  `author` varchar(64) DEFAULT NULL,
  `number_of_instances` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id_books`),
  UNIQUE KEY `idBooks_UNIQUE` (`id_books`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `books`
--

LOCK TABLES `books` WRITE;
/*!40000 ALTER TABLE `books` DISABLE KEYS */;
INSERT INTO `books` VALUES (1,'The Hunger Games','Suzanne Collins',5),(2,'Harry Potter and the Order of the Phoenix','J.K. Rowling',4),(3,'To Kill a Mockingbird','Harper Lee',1),(4,'Pride and Prejudice','Jane Austen',0),(5,'Twilight','Stephenie Meyer',1),(6,'The Book Thief','Markus Zusak',1),(7,'Animal Farm','George Orwell',5);
/*!40000 ALTER TABLE `books` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `formular`
--

DROP TABLE IF EXISTS `formular`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `formular` (
  `id_formular` int unsigned NOT NULL AUTO_INCREMENT,
  `books_id_books` int unsigned NOT NULL,
  `reader_id_reader` int unsigned NOT NULL,
  `start_date` date NOT NULL,
  `end_date` date NOT NULL,
  `return_date` date DEFAULT NULL,
  PRIMARY KEY (`id_formular`),
  UNIQUE KEY `id_formular_UNIQUE` (`id_formular`),
  KEY `FKqhxgs7fqituvnwg3k7hf6oh2m` (`books_id_books`),
  KEY `FK1wljmrqdnhkpxd0vic5feg3nh` (`reader_id_reader`),
  CONSTRAINT `FK1wljmrqdnhkpxd0vic5feg3nh` FOREIGN KEY (`reader_id_reader`) REFERENCES `reader` (`id_reader`),
  CONSTRAINT `FKqhxgs7fqituvnwg3k7hf6oh2m` FOREIGN KEY (`books_id_books`) REFERENCES `books` (`id_books`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `formular`
--

LOCK TABLES `formular` WRITE;
/*!40000 ALTER TABLE `formular` DISABLE KEYS */;
INSERT INTO `formular` VALUES (1,2,7,'2020-02-11','2020-08-11','2020-08-17'),(2,5,2,'2020-04-25','2020-10-25','2020-11-14'),(3,1,4,'2020-05-21','2020-11-21','2020-11-21'),(4,1,3,'2020-07-27','2021-01-27','2021-01-28'),(5,1,2,'2020-09-24','2021-03-24','2021-03-26'),(6,2,5,'2020-10-12','2021-04-12','2021-04-25'),(7,6,4,'2020-11-09','2021-05-09','2021-05-10'),(8,1,1,'2020-11-22','2021-05-22','2021-05-24'),(9,2,6,'2020-11-28','2021-05-28','2021-05-29');
/*!40000 ALTER TABLE `formular` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reader`
--

DROP TABLE IF EXISTS `reader`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `reader` (
  `id_reader` int unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL DEFAULT 'MysteryReader',
  `birth_date` date NOT NULL DEFAULT '2021-02-16',
  PRIMARY KEY (`id_reader`),
  UNIQUE KEY `idReaders_UNIQUE` (`id_reader`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reader`
--

LOCK TABLES `reader` WRITE;
/*!40000 ALTER TABLE `reader` DISABLE KEYS */;
INSERT INTO `reader` VALUES (1,'Anthony Perez','2020-10-12'),(2,'Verna Roy','2020-11-07'),(3,'Mary Collier','2020-12-12'),(4,'Byron Gibbs','2020-06-03'),(5,'Willie Hanson','2020-03-02'),(6,'Steve Alvarez','2020-08-04'),(7,'Heather Brady','2020-08-24'),(8,'Arturo Parks','2020-09-12'),(9,'Marlon Robertson','2021-01-27');
/*!40000 ALTER TABLE `reader` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-05-24 22:02:36
