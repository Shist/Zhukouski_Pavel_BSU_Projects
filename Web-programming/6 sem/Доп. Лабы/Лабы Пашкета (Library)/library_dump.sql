-- MySQL dump 10.13  Distrib 8.0.23, for Win64 (x86_64)
--
-- Host: localhost    Database: library
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
-- Table structure for table `books`
--

DROP TABLE IF EXISTS `books`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `books` (
  `bookid` bigint NOT NULL AUTO_INCREMENT,
  `popularity` decimal(19,2) DEFAULT NULL,
  `cost` decimal(19,2) DEFAULT NULL,
  `onDistrib` int DEFAULT NULL,
  `bAuthor` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`bookid`),
  UNIQUE KEY `books_bookid_uindex` (`bookid`),
  UNIQUE KEY `books_bAuthor_uindex` (`bAuthor`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `books`
--

LOCK TABLES `books` WRITE;
/*!40000 ALTER TABLE `books` DISABLE KEYS */;
INSERT INTO `books` VALUES (1,9.23,125.00,1,'J.K. Rowling'),(2,7.82,253.99,0,'Lev Tolstoy'),(3,8.26,214.50,1,'William Shakespeare'),(4,6.92,387.79,1,'Fyodor Dostoevsky'),(5,9.78,132.99,1,'Alexander Pushkin'),(6,8.26,119.99,1,'Anthon Checkov'),(7,6.63,87.49,0,'William Faulkner'),(8,7.12,107.99,1,'Maxim Gorky'),(9,8.56,157.29,1,'George Orwell'),(10,8.70,550.99,0,'Janarek Kort');
/*!40000 ALTER TABLE `books` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `formular`
--

DROP TABLE IF EXISTS `formular`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `formular` (
  `formularid` bigint NOT NULL AUTO_INCREMENT,
  `bookId` bigint DEFAULT NULL,
  `requestId` bigint DEFAULT NULL,
  `isReturned` int DEFAULT NULL,
  `bookState` decimal(19,2) DEFAULT NULL,
  PRIMARY KEY (`formularid`),
  UNIQUE KEY `formular_formularid_uindex` (`formularid`),
  UNIQUE KEY `formular_requestId_uindex` (`requestId`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `formular`
--

LOCK TABLES `formular` WRITE;
/*!40000 ALTER TABLE `formular` DISABLE KEYS */;
INSERT INTO `formular` VALUES (1,4,1,1,0.80),(2,6,2,0,0.90),(3,8,3,0,0.95),(4,9,4,1,0.75);
/*!40000 ALTER TABLE `formular` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `readers`
--

DROP TABLE IF EXISTS `readers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `readers` (
  `readerid` bigint NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `bookId` bigint DEFAULT NULL,
  `bAuthor` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`readerid`),
  UNIQUE KEY `readers_readerid_uindex` (`readerid`),
  UNIQUE KEY `readers_bAuthor_uindex` (`bAuthor`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `readers`
--

LOCK TABLES `readers` WRITE;
/*!40000 ALTER TABLE `readers` DISABLE KEYS */;
INSERT INTO `readers` VALUES (1,'Anthony',4,'Fyodor Dostoevsky'),(2,'Peter',6,'Anthon Checkov'),(3,'Janamel',8,'Maxim Gorky'),(4,'Margaret',9,'George Orwell');
/*!40000 ALTER TABLE `readers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `requests`
--

DROP TABLE IF EXISTS `requests`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `requests` (
  `requestid` bigint NOT NULL AUTO_INCREMENT,
  `requiredPopularity` decimal(19,2) DEFAULT NULL,
  `maxCost` decimal(19,2) DEFAULT NULL,
  PRIMARY KEY (`requestid`),
  UNIQUE KEY `requests_requestid_uindex` (`requestid`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `requests`
--

LOCK TABLES `requests` WRITE;
/*!40000 ALTER TABLE `requests` DISABLE KEYS */;
INSERT INTO `requests` VALUES (1,7.00,300.00),(2,7.50,250.00),(3,6.00,175.00),(4,5.50,160.00),(5,8.00,150.00),(6,7.50,180.00),(7,9.05,440.45);
/*!40000 ALTER TABLE `requests` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `roles`
--

DROP TABLE IF EXISTS `roles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `roles` (
  `roleId` bigint NOT NULL AUTO_INCREMENT,
  `roleName` varchar(255) NOT NULL,
  PRIMARY KEY (`roleId`),
  UNIQUE KEY `roles_roleName_uindex` (`roleName`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roles`
--

LOCK TABLES `roles` WRITE;
/*!40000 ALTER TABLE `roles` DISABLE KEYS */;
INSERT INTO `roles` VALUES (1,'L'),(2,'R');
/*!40000 ALTER TABLE `roles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `users` (
  `userId` bigint NOT NULL AUTO_INCREMENT,
  `login` varchar(255) NOT NULL,
  `pass` varchar(255) NOT NULL,
  `roleId` bigint NOT NULL,
  PRIMARY KEY (`userId`),
  UNIQUE KEY `users_login_uindex` (`login`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'Pavel','7777777',1),(2,'Anthony','1111111',2),(3,'Margaret','2222222',2),(4,'Peter','3333333',2),(5,'Tom','4444444',2),(6,'Janamel','5555555',2),(7,'Riareli','6666666',2),(8,'Hellew','8888888',2),(9,'Fachevi','9999999',2),(10,'Rojer','2233445',2),(11,'Kerny','4447777',2);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-06-02  3:41:16
