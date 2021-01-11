PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "international_companies" (id integer primary key, name verchar(50), internet_site verchar(50), mail_index integer, country verchar(50), region verchar(50), district verchar(50), town verchar(50), street verchar(50), house integer, flat integer, foundation_year integer, length_of_stay_in_the_global_market integer, employees_number integer, europe_branches_number integer);
INSERT INTO international_companies VALUES(1,'Almaz','almaz.com',573859,'USA','New_Jercy','White_Field','Hedok','Kolen',24,3,1978,37,172,14);
INSERT INTO international_companies VALUES(2,'Pear','pear.com',275834,'Germany','New_Mok','Clear_Place','Lok','Lenku',67,8,1987,21,214,19);
INSERT INTO international_companies VALUES(3,'Gigabyte','idea.com',987482,'Poland','Kaishi','Long_Lace','Pell','Mill',93,2,1997,17,53,4);
COMMIT;
